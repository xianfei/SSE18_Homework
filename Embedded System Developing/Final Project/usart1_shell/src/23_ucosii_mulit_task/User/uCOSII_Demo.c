/**
  ******************************************************************************
  * File Name          : uCOSII_Demo.c
  * Description        : demo code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 xianfei wang & jkuang@BUPT
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/


/* USER CODE BEGIN Includes */
#include	"uCOSII_Demo.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

APP_RECORD App_Record[APP_RECORD_NUM];

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
		APP_TQID(i) 	= 0;
		APP_TPRIO(i) = 0xFF;
	}

#if OS_TMR_EN > 0u
	APP_TPRIO(OS_TID_Timer) = OS_TASK_TMR_PRIO;  //Timer task record init
#endif

	//Message mem partition Init
	err = Msg_MemInit();
	if(err)
		return(err);
	
	//UART Send buffer init
	Uart_Sendbuf_Init();

	//task USART1 Create
	err = Task_USART1_Creat();
	if(err)
		return(err);
	
	
	// creat shell timeout timer
	err = Task_SHELL_Creat();
	if(err)
		return(err);
	
	//task KeyScan Create
	// err = Task_KeyScan_Creat();
	if(err)
		return(err);


	return(0);
}

/************************ (C) COPYRIGHT xianfei wang & jkuang@BUPT *****END OF FILE****/
