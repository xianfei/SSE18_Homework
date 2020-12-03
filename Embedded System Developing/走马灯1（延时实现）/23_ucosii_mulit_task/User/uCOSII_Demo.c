/**
  ******************************************************************************
  * File Name          : uCOSII_Demo.c
  * Description        : demo code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/


/* USER CODE BEGIN Includes */
#include	"farsight_f407.h"
#include	"uCOSII_Demo.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

APP_RECORD App_Record[APP_RECORD_NUM];

//DEMO_01: 2 Tasks timedelay Led demo
#define DEMO_01
//DEMO_02: 2 Tasks sem demo
//#define DEMO_02

#ifdef DEMO_01
#define TASK1_PRIO    								11
#define TASK2_PRIO    								12

static OS_STK task1_stk[STK_SIZE_DEF];
static OS_STK task2_stk[STK_SIZE_DEF];

static void task1(void *p_arg);
static void task2(void *p_arg);
#endif //DEMO_01

#ifdef DEMO_02
#define TASK_SENDER_PRIO    					17
#define TASK_RECIVER_PRIO    					16

static OS_STK task_sender_stk[STK_SIZE_DEF];
static OS_STK task_reciver_stk[STK_SIZE_DEF];

static void task_sender(void *p_arg);
static void task_reciver(void *p_arg);

OS_EVENT *demo_semp;
#endif //DEMO_02

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


//============================================================
int User_App_Initial(void)
{
	int 	i;
	INT8U err;

	//BEEP off
	BEEP_OFF;
	
	//4 leds off
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;


	//Task record array initial
	for(i=0; i<APP_RECORD_NUM; i++)
	{
		App_Record[i].tQid = 0;
		App_Record[i].tPrio = 0xFF;
	}

#if OS_TMR_EN > 0u
	App_Record[OS_TID_Timer].tPrio = OS_TASK_TMR_PRIO;  //Timer task record init
#endif

	//UART Send buffer init
	Uart_Sendbuf_Init();

	//task USART1 Create
	err = Task_USART1_Creat();
	if(err)
		return(err);
	
	//task KeyScan Create
	err = Task_KeyScan_Creat();
	if(err)
		return(err);


#ifdef DEMO_01
	OSTaskCreate(task1, (void*)0, &task1_stk[STK_SIZE_DEF-1], TASK1_PRIO);
	OSTaskCreate(task2, (void*)0, &task2_stk[STK_SIZE_DEF-1], TASK2_PRIO);
#endif //DEMO_01

#ifdef DEMO_02
	demo_semp = OSSemCreate(0);
	if(demo_semp == 0)
		return(255);
	
	err = OSTaskCreate(task_sender, (void*)0, &task_sender_stk[STK_SIZE_DEF-1], TASK_SENDER_PRIO);
	if(err)
		return(err);

  err = OSTaskCreate(task_reciver, (void*)0, &task_reciver_stk[STK_SIZE_DEF-1], TASK_RECIVER_PRIO);
	if(err)
		return(err);
#endif //DEMO_02

	return(0);
}

//============================================================
void USER_Print_Decimal(INT32U value)
{
	char* aStr;

	aStr = Uart_Sendbuf_Get();

	sprintf((char*)aStr, "%d", value);
	USER_USART1_print(aStr);
}

//============================================================
//static char aStr[16];
void USER_Print_OSIdleCtr(void)
{
//	static char aStr[16];	//???????????
	char* aStr;

	aStr = Uart_Sendbuf_Get();

	sprintf((char*)aStr, "[%08X]", OSIdleCtr);
	USER_USART1_print(aStr);
}


#ifdef DEMO_01
//------------ DEMO 01 ----------------
//============================================================

int isReverse = 0;
int currentLed = 1;
static void task1(void *p_arg)
{
	USER_USART1_print("\n====Task1 Created====\n");

	while(1)  
	{	       
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task1 LED flow\n");
		LED4_OFF;
		LED3_OFF;
		LED2_OFF;
		LED1_OFF;
		switch(currentLed){
			case 1:LED1_ON;break;
			case 2:LED2_ON;break;
			case 3:LED3_ON;break;
			case 4:LED4_ON;break;
		}
		if(isReverse){
			currentLed--;
			if(currentLed==0)currentLed=4;
		}else{
			currentLed++;
			if(currentLed==5)currentLed=1;
		}
		OSTimeDlyHMSM(0,0,0,500);
  }
}

//============================================================
static void task2(void *p_arg)
{
	
	USER_USART1_print("\n====Task2 Created====\n");

	while(1)
	{
		if(KEYSWITCH(4))	//key1 switch
		{
			isReverse=!isReverse;
			USER_USART1_print("\nKey4 is pressed, will reverse\n");
		}
		OSTimeDlyHMSM(0,0,0,50);
    }
}
#endif //DEMO_01

#ifdef DEMO_02
//------------ DEMO 02 ----------------
#define PRINT_EN_DEMO02

//============================================================
static void task_sender(void *p_arg)
{
	INT32U task_active_cnt = 0;

	App_Record[APP_TID_sender].tPrio = TASK_SENDER_PRIO;

	USER_USART1_print("\n====Task Sender Created====\n");

	while(1)  
	{	       
		if(KEYSWITCH(1))	//key1 switch
		{
			LED1_TOGGLE;
		}
		if(OSSemPost(demo_semp))
			USER_USART1_print("Task Sender SEM-POST ERR!\n");

#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		task_active_cnt++;
		USER_USART1_print(" Task Sender active:");
		USER_Print_Decimal(task_active_cnt);
		USER_USART1_print("\n");
#endif
		OSTimeDlyHMSM(0,0,0,400);

  }
}

//============================================================
static void task_reciver(void *p_arg)
{
	INT8U  				err;
  GPIO_PinState bitstatus;
	INT32U 				task_active_cnt = 0;

	
	App_Record[APP_TID_receiver].tPrio = TASK_RECIVER_PRIO;

	USER_USART1_print("\n====Task Reciver Created====\n");

	while(1)
	{
		OSSemPend (demo_semp, 0, &err);
		if(err)
			USER_USART1_print("Task Reciver SEM-PEND ERR!\n");

		if(KEYSWITCH(2))	//key2 switch
		{
			bitstatus = LED1_READ;
			if(bitstatus == GPIO_PIN_RESET) //led2 set reverse state of led1 
			{
				LED2_OFF;
			}else{
				LED2_ON;
			}
			if(KEYSWITCH(4))	//key4 switch
			{
				BEEP_TOGGLE;
			}
		}
#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		task_active_cnt++;
		USER_USART1_print(" Task Reciver active:");
		USER_Print_Decimal(task_active_cnt);
		USER_USART1_print("\n");
#endif
	}
}
#endif //DEMO_02




/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
