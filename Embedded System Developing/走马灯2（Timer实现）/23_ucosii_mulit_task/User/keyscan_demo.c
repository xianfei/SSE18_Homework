/**
  ******************************************************************************
  * File Name          : keyscan_demo.c
  * Description        : demo code for key scan for STM32F407 of farsight 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 jkuang@BUPT
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include	"farsight_f407.h"
#include	"uCOSII_Demo.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
INT8U 	KeySwitch[KEY_NUMBER];	//Board key switch identification, value toggled while specified key pressed.

#define TASK_KETSCAN_PRIO    	60
static OS_STK task_keyscan_stk[STK_SIZE_DEF];
static void task_keyscan(void *p_arg);
/* Private variables ---------------------------------------------------------*/

//--------------Key Scan Task--------------------
#define PRINT_EN_KEYSCAN
// Key Value
#define KEY_UP				1
#define KEY_DOWN			0

//============================================================
//task KeyScan Create
INT8U Task_KeyScan_Creat(void)
{
	INT8U err, i;

	//Key Switch Record initial
	for(i=0; i<KEY_NUMBER; i++)
	{
		KEYSWITCH(i+1) = 1;
	}
	
	//Creat Key scan task
	err = OSTaskCreate(	task_keyscan, (void*)0,
											&task_keyscan_stk[STK_SIZE_DEF-1], TASK_KETSCAN_PRIO);
	return(err);
}
	

//============================================================
static void task_keyscan(void *p_arg)
{
	INT8U 				keyscan[KEY_NUMBER]; //'0': key down already, scan halt; '1': key scan enable

#define KEYSCAN(x)	keyscan[x-1]
//Scan Enable & Disable
#define SCAN_DISABLE	0
#define SCAN_ENABLE		1

	App_Record[APP_TID_keyscan].tPrio = TASK_KETSCAN_PRIO;

	USER_USART1_print("\n====Task KeyScan Created====\n");

	while(1)
	{	       
		// enable scan only when key up
		if(KEY1_READ == KEY_UP)
			KEYSCAN(1) = SCAN_ENABLE;
		if(KEY2_READ == KEY_UP)
			KEYSCAN(2) = SCAN_ENABLE;
		if(KEY3_READ == KEY_UP)
			KEYSCAN(3) = SCAN_ENABLE;
		if(KEY4_READ == KEY_UP)
			KEYSCAN(4) = SCAN_ENABLE;

		// any key down process while scan enable
		if(	(KEYSCAN(1) && (KEY1_READ == KEY_DOWN)) ||
			 	(KEYSCAN(2) && (KEY2_READ == KEY_DOWN)) ||
				(KEYSCAN(3) && (KEY3_READ == KEY_DOWN)) ||
				(KEYSCAN(4) && (KEY4_READ == KEY_DOWN)))
		{
			OSTimeDly(OS_TICKS_PER_SEC/10); // È¥¶¶¶¯

			// key 1 down process
			if(KEY1_READ == KEY_DOWN) 
			{
				KEYSCAN(1) = SCAN_DISABLE;			// key down confirm, stop scan the key
				KEYSWITCH(1) ^= 1;							// key switch (global Variable)
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 1\n");
#endif
			}

			// key 2 down process
			if(KEY2_READ==KEY_DOWN) 
			{
				KEYSCAN(2) = SCAN_DISABLE;
				KEYSWITCH(2) ^= 1;
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 2\n");
#endif
			}

			// key 3 down process
			if(KEY3_READ==KEY_DOWN) 
			{
				KEYSCAN(3) = SCAN_DISABLE;
				KEYSWITCH(3) ^= 1;
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 3\n");
#endif
			}

			// key 4 down process
			if(KEY4_READ==KEY_DOWN) 
			{
				KEYSCAN(4) = SCAN_DISABLE;
				KEYSWITCH(4) ^= 1;
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 4\n");
#endif
			}
		}
		else
		{
			OSTimeDly(OS_TICKS_PER_SEC/10);	// task delay
		}
  }
}

/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
