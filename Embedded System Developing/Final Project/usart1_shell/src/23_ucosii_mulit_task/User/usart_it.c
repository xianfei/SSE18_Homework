/**
  ******************************************************************************
  * File Name          : usart_it.c
  * Description        : USATR driver & shell code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 xianfei wang & jkuang@BUPT
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart.h"
//#include "gpio.h"

//#include  "os_cpu.h"
#include 	"string.h"
#include  "stdarg.h"
#include  "stdlib.h"
#include 	"uCOSII_Demo.h"

/* variables ---------------------------------------------------------*/

//USART1 Task
#define  TASK_USART1_PRIO               5
#define  TASK_USART1_STK_SIZE           128
static OS_STK Task_USART1_Stk[TASK_USART1_STK_SIZE];


//SHELL Task
#define  TASK_SHELL_PRIO               61
#define  TASK_SHELL_STK_SIZE           128
static OS_STK Task_SHELL_Stk[TASK_USART1_STK_SIZE];

//msgQ of USART1
#define TASK_USART1_QSIZE		10
static void *TaskUsart1_Qarray[TASK_USART1_QSIZE];

//Rx message buffer of USART1
//目前仅定义两个消息数组，乒乓使用，每条消息承载1个接收字符
#define UART1_RXMSGBUF_NUM			2
static UART_RX_MSG uart1_rxmsgbuf[UART1_RXMSGBUF_NUM];
static INT8U Rxmsg_idx;

//sendbuf Q of USART1
static OS_EVENT* SendBufQid = NULL;			// sendbuf Q ID
#define SENDBUF_USART1_QSIZE		16
void *SendBuf_QArray[SENDBUF_USART1_QSIZE];
static char *SendChrP;									// current send char ptr

//send buffer array for UART
#define UART_SENDBUF_NUM		8
#define UART_SENDBUF_LEN		16
static char uart_sendbuf[UART_SENDBUF_NUM][UART_SENDBUF_LEN];
static INT8U uart_sendbuf_idx;					//current send buffer idx
static char *uart_sending_bufP;					//UART ISR sending buffer ptr

// shell error code
#define SHELL_ERR_NONE 0
#define SHELL_ERR_FUN_NOT_EXIST -1
#define SHELL_ERR_PARA -2

// shell size
#define SHELL_BUFF_SIZE 128
#define SHELL_DEFAULT_PARA_SIZE 8
#define SHELL_FUNC_SIZE 10
#define INT8 int
	
char input_line[SHELL_BUFF_SIZE];
int input_index=0;

static OS_TMR *shellTmr; //one shot timer

/* variables ---------------------------------------------------------*/


//============================================================
//	查询方式发送。直接送入到发送缓冲区。
static void USER_USART1_send(char *pData)
{
	while(*pData)
	{
		while(READ_BIT(huart1.Instance->SR, UART_FLAG_TXE) == RESET);

		huart1.Instance->DR = (uint8_t)*pData;
		pData++;
	}
}

//============================================================
void USER_USART1_print(char *pData)
{

	if((pData == NULL)||(*pData == 0))
		return;

	if(SendBufQid)
	{
		//中断方式发送
		if(OSQPost(SendBufQid, (void *)pData) == OS_ERR_NONE)
		{
			SET_BIT(huart1.Instance->CR1, USART_CR1_TXEIE); //TXEIE int enable
		}
	}
	else
	{
		//查询方式发送
		USER_USART1_send(pData); // print to HW directly
#ifdef HAL
    uint16_t len = 0;
		char *p = pData;
		while((*p)&&(len<=256)) 
		{
				len++; 
				p++;
		}
		HAL_UART_Transmit(&huart1, (uint8_t*)pData, len, 100);
#endif
	} 

}

//============================================================
//uart send buffer init
void Uart_Sendbuf_Init(void)
{
	for(uart_sendbuf_idx=0; uart_sendbuf_idx<UART_SENDBUF_NUM; uart_sendbuf_idx++)
		uart_sendbuf[uart_sendbuf_idx][0] = 0;
	uart_sendbuf_idx = UART_SENDBUF_NUM - 1;
}

//============================================================
//get a uart send buffer
char* Uart_Sendbuf_Get(void)
{
	char *strP;
#if OS_CRITICAL_METHOD == 3u                     /* Allocate storage for CPU status register           */
		OS_CPU_SR  cpu_sr = 0u;
#endif

	//若下一个buffer未发送完毕，返回空指针
	strP = (char*)&(uart_sendbuf[(uart_sendbuf_idx + 1) % UART_SENDBUF_NUM][0]);
	if(strP == uart_sending_bufP)
		return(NULL);
	
	OS_ENTER_CRITICAL();
	uart_sendbuf_idx = (uart_sendbuf_idx + 1) % UART_SENDBUF_NUM;		//注意，临界资源。
	OS_EXIT_CRITICAL();
	return(strP);
  
}



//============================================================
//task USART1 Create
INT8U Task_USART1_Creat(void)
{
	INT8U err;

	err = OSTaskCreate( task_USART1, (void*)0,
											&Task_USART1_Stk[TASK_USART1_STK_SIZE-1], TASK_USART1_PRIO);
	return(err);
}


//============================================================
//shell utlities

#define shell_print USER_USART1_print

// output like 'printf()' in C
void shell_printf(const char *fmt, ...){
	// var list
    va_list myargs;
    va_start(myargs, fmt);
	// output to str
		char str[SHELL_BUFF_SIZE];
    vsnprintf(str,SHELL_BUFF_SIZE,fmt, myargs);
		USER_USART1_print(str);
    va_end(myargs);
}

// shell functions

INT8 testinput(INT8U argc,const char ** argv){
    shell_printf("argc:%d\n",argc);
    for (int i = 0; i < argc; ++i) {
        shell_printf("argv[%d]:%s\n",i,argv[i]);
    }
    return 0;
}

INT8 help(INT8U argc,const char ** argv){
  shell_print("A simple Shell for STM32. \nBy xianfei wang@BUPT.\n");
	shell_print("Functions:\n");
	shell_print("\t'led' control leds on borad, see more with 'led help'.\n");
	shell_print("\t'testinput' show arguments of input, for test in development.\n");
    return 0;
}

INT8 led(INT8U argc,const char ** argv){
	// show the help if the frist arguments is help
    if(strcmp(argv[0], "help")==0){
        shell_print("Control on broad LEDs.\nUsage: led [port] [on/off]\n");
        return SHELL_ERR_NONE;
    }
		// if arguments is too much or less
    if(argc!=2){shell_print("Arguments error. Use 'led help' for help.\n");return SHELL_ERR_PARA;}
    switch (atoi(argv[0])) {
        case 1:
            if(strcmp(argv[1], "on")==0)
            {
                // LED ON
							LED1_ON;
            }else if(strcmp(argv[1], "off")==0)
            {
                // LED OFF
							LED1_OFF;
            }else {shell_print("Arguments error. Use 'led help' for help.\n");return SHELL_ERR_PARA;}
            break;
        case 2:
            if(strcmp(argv[1], "on")==0)
            {
                // LED ON
							LED2_ON;
            }else if(strcmp(argv[1], "off")==0)
            {
                // LED OFF
							LED2_OFF;
            }else {shell_print("Arguments error. Use 'led help' for help.\n");return SHELL_ERR_PARA;}
            break;
        case 3:
            if(strcmp(argv[1], "on")==0)
            {
                // LED ON
							LED3_ON;
            }else if(strcmp(argv[1], "off")==0)
            {
                // LED OFF
							LED3_OFF;
            }else {shell_print("Arguments error. Use 'led help' for help.\n");return SHELL_ERR_PARA;}
            break;
        case 4:
            if(strcmp(argv[1], "on")==0)
            {
                // LED ON
							LED4_ON;
            }else if(strcmp(argv[1], "off")==0)
            {
                // LED OFF
							LED4_OFF;
            }else {shell_print("Arguments error. Use 'led help' for help.\n");return SHELL_ERR_PARA;}
            break;
        default:
            {shell_print("Arguments error. Use 'led help' for help.\n");return SHELL_ERR_PARA;};
    }
    return SHELL_ERR_NONE;
}

//============================================================
// the list for functions
INT8 (*shell_func_callbacks[SHELL_FUNC_SIZE])(INT8U,const char ** )
			={testinput,led,help};
// the name of functions
const char *shell_func_names[SHELL_FUNC_SIZE] 
			={"testinput","led","help"};

// shell interpreter
INT8 shell_parse(char* input){
	// shell_printf("Input: %s\n",input);
    INT8U paraSize = SHELL_DEFAULT_PARA_SIZE;
    const char * funcName = strtok(input," "); // function name in input
    const char * argv[paraSize];
    INT8U argc = -1;  // the number of arguments
	// parse the arguments
    do {
        argc++;
        *(argv+argc)=strtok(NULL," ");
        if(argc>paraSize){
            shell_printf("Too much arguments. Should less than %d",paraSize);
            return SHELL_ERR_PARA;
        }
    }while(*(argv+argc));
    INT8U func_index=0;
    while (1){
			// find the function in the array
        if(func_index>SHELL_FUNC_SIZE-1||!shell_func_names[func_index])
				{ 
					shell_printf("Can not found function: %s\n",funcName);
					return SHELL_ERR_FUN_NOT_EXIST;
				}
				// found
        if(strcmp(funcName,shell_func_names[func_index])==0)break;
        func_index++;
    }
    // call the function pointer
    INT8 ret_val =shell_func_callbacks[func_index](argc,argv);
    shell_printf("Function return with exit code:%d\n",ret_val);
    return ret_val;
}

// timer for timeout send
static void timer_SHELL_timeout (void* p_arg){	
	input_line[input_index]=0; // add end character 
	if(input_index!=0)shell_parse(input_line);
	// clear the buffer (fake, just set index to zero)
	input_line[0]=0;
	input_index=0;
	shell_print("\n>");
}

INT8U Task_SHELL_Creat(void)
{
	INT8U err;
	shellTmr = OSTmrCreate((INT32U )5,
												(INT32U )0,
												(INT8U  )OS_TMR_OPT_ONE_SHOT,
												(OS_TMR_CALLBACK)timer_SHELL_timeout,
												(void * )0,
												(INT8U *)"Tmr1",
												(INT8U *)&err);
	
	//err = OSTaskCreate( task_SHELL, (void*)0, &Task_SHELL_Stk[TASK_SHELL_STK_SIZE-1], TASK_SHELL_PRIO);
	return(err);
}


//============================================================
#define USART1_ECHO_TEST
static void task_USART1 (void* p_arg)
{
	INT8U err;
	char c;
	UART_RX_MSG *pmsg;


	//Rx message buffer initial
	{
		for(Rxmsg_idx=0; Rxmsg_idx<UART1_RXMSGBUF_NUM; Rxmsg_idx++)
		{
			uart1_rxmsgbuf[Rxmsg_idx].mCode	= MC_USART1_IRQ_RXNE;
			uart1_rxmsgbuf[Rxmsg_idx].mSendTsk = DRV_ID_usart1;
			uart1_rxmsgbuf[Rxmsg_idx].mRecvTsk = APP_TID_usart1;
		}
		Rxmsg_idx = 0;
	}

	//Create Q of USART1
	APP_TQID(APP_TID_usart1) = 
							OSQCreate(&TaskUsart1_Qarray[0], TASK_USART1_QSIZE);
	if(APP_TQID(APP_TID_usart1) == NULL)
	{
		APP_TPRIO(APP_TID_usart1) = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	//sendbuf Q of USART1 initial
	SendChrP = NULL;
	SendBufQid = OSQCreate(&SendBuf_QArray[0], SENDBUF_USART1_QSIZE);
	if(SendBufQid == NULL)
	{
		OSQDel(APP_TQID(APP_TID_usart1), OS_DEL_ALWAYS,&err);
		APP_TQID(APP_TID_usart1) = NULL;
		APP_TPRIO(APP_TID_usart1) = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	// NVIC IRQ enable of USART1
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	SET_BIT(huart1.Instance->CR3, USART_CR3_EIE);
	/* Enable the UART Parity Error/Data Register not empty Interrupts */
	SET_BIT(huart1.Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	

	APP_TPRIO(APP_TID_usart1) = TASK_USART1_PRIO;

	// USER_USART1_print("\n====Task USART1 Initialized====\n");
	

	while(1)
	{
		
		pmsg = OSQPend(APP_TQID(APP_TID_usart1), 0, &err); // wait forever
	
				
		if(	(pmsg->mCode != MC_USART1_IRQ_RXNE) ||
				(pmsg->mRecvTsk != APP_TID_usart1) ||
				(pmsg->mSendTsk != DRV_ID_usart1))
			continue;
		
		c = pmsg->aChr;
#ifdef USART1_ECHO_TEST
		{
			while(READ_BIT(huart1.Instance->SR, UART_FLAG_TXE) == RESET);
			// huart1.Instance->DR = (uint8_t)c;
			// echo back the char
			shell_printf("%c",c);
		}
#endif
		
		// write to shell buffer
		input_line[input_index]=c;
		input_index++;
		// reset timer delay
		shellTmr->OSTmrDly=5;
		// start the timeout timer
		OSTmrStart(shellTmr, &err);
	  if(err) return;
		
	} // while(1)

}


//============================================================
//USART1 IRQHandler

void OS_CPU_USART1_IRQHandler(void)
{
	OS_CPU_SR  	cpu_sr;
	uint32_t 		isrflags;
	uint32_t 		cr1its;
	uint32_t 		cr3its;
	uint32_t 		errorflags;
	uint8_t 		data;
	INT8U 			err;

	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

  isrflags 	= READ_REG(huart1.Instance->SR);
	cr1its 		= READ_REG(huart1.Instance->CR1);
	cr3its 		= READ_REG(huart1.Instance->CR3);

	/* UART in mode Receiver -------------------------------------------------*/
	if(((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
	{
		data = (uint8_t)(huart1.Instance->DR);
		if(APP_TQID(APP_TID_usart1) != NULL) 
		{
			uart1_rxmsgbuf[Rxmsg_idx].aChr = data;
			OSQPost(APP_TQID(APP_TID_usart1), (void *)&uart1_rxmsgbuf[Rxmsg_idx]); //send to task_uasrt1
			Rxmsg_idx ^= 1;
		}

	}

  /* If some errors occur */
  errorflags = (isrflags & (uint32_t)(USART_SR_PE | USART_SR_FE | USART_SR_ORE | USART_SR_NE));
  if((errorflags != RESET) && (((cr3its & USART_CR3_EIE) != RESET) || ((cr1its & (USART_CR1_RXNEIE | USART_CR1_PEIE)) != RESET)))
  {
    /* UART parity error interrupt occurred ----------------------------------*/
    if(((isrflags & USART_SR_PE) != RESET) && ((cr1its & USART_CR1_PEIE) != RESET))
    {
      huart1.ErrorCode |= HAL_UART_ERROR_PE;
    }
    
    /* UART noise error interrupt occurred -----------------------------------*/
    if(((isrflags & USART_SR_NE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      huart1.ErrorCode |= HAL_UART_ERROR_NE;
    }
    
    /* UART frame error interrupt occurred -----------------------------------*/
    if(((isrflags & USART_SR_FE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      huart1.ErrorCode |= HAL_UART_ERROR_FE;
    }
    
    /* UART Over-Run interrupt occurred --------------------------------------*/
    if(((isrflags & USART_SR_ORE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    { 
      huart1.ErrorCode |= HAL_UART_ERROR_ORE;
    }
  }

	//Transmit ...
  if(((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
  {
		if((SendChrP)&&(*SendChrP != 0))
		{
			huart1.Instance->DR = (uint8_t)(*SendChrP);
			SendChrP++;
		}
		else //SendChrP == NULL or str end
		{
			SendChrP = OSQAccept(SendBufQid, &err);
			uart_sending_bufP = SendChrP;
			if(SendChrP == NULL)
				CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TXEIE); //TXEIE int disable
		}


  }

	OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}


