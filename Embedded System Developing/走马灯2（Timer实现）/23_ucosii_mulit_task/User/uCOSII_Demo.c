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

#ifdef DEMO_01
OS_TMR *Timer1;
OS_TMR *Timer2;
static void task1(OS_TMR *ptmr, void *callback_arg);
static void task2(OS_TMR *ptmr, void *callback_arg);
#endif //DEMO_01


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
	//OSTaskCreate(task1, (void*)0, &task1_stk[STK_SIZE_DEF-1], TASK1_PRIO);
	//OSTaskCreate(task2, (void*)0, &task2_stk[STK_SIZE_DEF-1], TASK2_PRIO);

	INT8U errorCode1,errorCode2;
	Timer1 = OSTmrCreate(0,8,OS_TMR_OPT_PERIODIC,task1,NULL,NULL,&errorCode1);
	if(errorCode1==OS_ERR_NONE) OSTmrStart(Timer1,&errorCode1);
	else USER_USART1_print("error for timer1 create");
		if(errorCode1!=OS_ERR_NONE)USER_USART1_print("error for timer1 start");
	Timer2 = OSTmrCreate(0,1,OS_TMR_OPT_PERIODIC,task2,NULL,NULL,&errorCode2);
	if(errorCode2==OS_ERR_NONE) OSTmrStart(Timer2,&errorCode2);
	else USER_USART1_print("error for timer2 create");
	if(errorCode2!=OS_ERR_NONE)USER_USART1_print("error for timer2 start");
		
#endif //DEMO_01
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
static void task1(OS_TMR *ptmr, void *callback_arg)
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
}

//============================================================
int key1LastStatu = 0;
int key2LastStatu = 0;
int key3LastStatu = 0;
int key4LastStatu = 0;
static void task2(OS_TMR *ptmr, void *callback_arg)
{

		if(KEY4_READ==0)	//key1 switch
		{
			if(!key4LastStatu){ // if key4 reverse
				isReverse=!isReverse;
				USER_USART1_print("\nKey4 is pressed, will reverse\n");
			}
			key4LastStatu = 1;
		}else key4LastStatu = 0;
		if(KEY3_READ==0)	//key1 switch
		{
			if(!key3LastStatu){ // if key4 reverse
				Timer1->OSTmrPeriod=8;
				USER_USART1_print("\nKey3 is pressed\n");
			}
			key3LastStatu = 1;
		}else key3LastStatu = 0;
		if(KEY2_READ==0)	//key1 switch
		{
			if(!key2LastStatu){ // if key4 reverse
				Timer1->OSTmrPeriod=5;
				USER_USART1_print("\nKey2 is pressed\n");
			}
			key2LastStatu = 1;
		}else key2LastStatu = 0;
		if(KEY1_READ==0)	//key1 switch
		{
			if(!key1LastStatu){ // if key4 reverse
				Timer1->OSTmrPeriod=2;
				USER_USART1_print("\nKey1 is pressed\n");
			}
			key1LastStatu = 1;
		}else key1LastStatu = 0;
}
#endif //DEMO_01


/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
