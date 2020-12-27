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
#include	"uCOSII_Demo.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
INT8U 	KeySwitch[KEY_NUMBER];	//Board key switch identification, value toggled while specified key pressed.

INT8U 	keyscan; //key scan state, bit0-3, '0': key down already, scan halt; '1': key scan enable
#define KEYSCANGET(x)		(keyscan & (0x1<<(x-1)))		//get key(x) scan state, x = 1-4 
#define KEYSCANEN(x) 		(keyscan |= 0x1<<(x-1))		//set key(x) scan enable, x = 1-4 
#define KEYSCANDISEN(x) (keyscan &= ~(0x1<<(x-1)))		//set key(x) scan disable, x = 1-4 

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
static INT8U KEYx_Down_Process(INT8U key)
{
	KEYSCANDISEN(key);
	KEYSWITCH(key) ^= 1;
	//send msg to tmetst task Q Instance 3
	return(Msg_SendShort(MC_KEYx_SWITCH, APP_TID_keyscan, APP_TID_tmrtest, key, key));
}



//============================================================
static void task_keyscan(void *p_arg)
{
	INT8U 				err = err;

	keyscan = 0;
	
	APP_TPRIO(APP_TID_keyscan) = TASK_KETSCAN_PRIO;

	USER_USART1_print("\n====Task KeyScan Created====\n");

	while(1)
	{	       
		// enable scan only when key up
		if(KEY1_READ == KEY_UP)
			KEYSCANEN(1);
		if(KEY2_READ == KEY_UP)
			KEYSCANEN(2);
		if(KEY3_READ == KEY_UP)
			KEYSCANEN(3);
		if(KEY4_READ == KEY_UP)
			KEYSCANEN(4);

		// any key down process while scan enable
		if(	(KEYSCANGET(1) && (KEY1_READ == KEY_DOWN)) ||
			 	(KEYSCANGET(2) && (KEY2_READ == KEY_DOWN)) ||
				(KEYSCANGET(3) && (KEY3_READ == KEY_DOWN)) ||
				(KEYSCANGET(4) && (KEY4_READ == KEY_DOWN)))
		{
			OSTimeDly(OS_TICKS_PER_SEC/10); // È¥¶¶¶¯

			// key 1 down process
			if(KEYSCANGET(1) && (KEY1_READ == KEY_DOWN)) 
			{
				KEYx_Down_Process(1);
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 1\n");
#endif
			}

			// key 2 down process
			if(KEYSCANGET(2) && (KEY2_READ == KEY_DOWN)) 
			{
				KEYx_Down_Process(2);
				//send a invalid mCode msg for test
				Msg_SendShort(65535, APP_TID_keyscan, APP_TID_tmrtest, 0, 0);
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 2\n");
#endif
			}

			// key 3 down process
			if(KEYSCANGET(3) && (KEY3_READ == KEY_DOWN))
			{
				KEYx_Down_Process(3);
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 3\n");
#endif
			}

			// key 4 down process
			if(KEYSCANGET(4) && (KEY4_READ == KEY_DOWN))
			{
				KEYx_Down_Process(4);
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
