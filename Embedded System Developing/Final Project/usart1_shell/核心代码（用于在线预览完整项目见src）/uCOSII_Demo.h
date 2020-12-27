/**
  ******************************************************************************
  * File Name          : uCOSII_Demo.h
  * Description        : demo code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */
#ifndef UCOSII_DEMO_H
#define UCOSII_DEMO_H
#ifdef __cplusplus
		 extern "C" {
#endif

#include  "ucos_ii.h"
#include	"farsight_f407.h"
#include 	"usart_it.h"
#include  "message.h"

//Common Stick Size of Task
#define STK_SIZE_DEF	128

//===================================================================
//app task record 
typedef struct _APP_RECORD
{
	OS_EVENT*	tQid;			// task Q ID
	INT16U    tPrio;		// task priority
	INT16U		tRes;			// reserved
} APP_RECORD;

#define APP_RECORD_NUM	OS_MAX_TASKS	//Max. number of tasks supported

extern APP_RECORD App_Record[APP_RECORD_NUM];

#define APP_TQID(x)		App_Record[x].tQid	
#define APP_TPRIO(x)	App_Record[x].tPrio	

//Task or Driver ID
//Driver ID
#define DRV_ID_usart1			-1
//System Task ID
#define OS_TID_Timer			0		// OS Timer task id use '0'
//User Task ID
#define APP_TID_usart1		1
#define APP_TID_keyscan		2
#define APP_TID_sender		3
#define APP_TID_receiver	4
#define APP_TID_tmrtest		5



//===================================================================
//Key Scan
#define KEY_NUMBER		4
extern 	INT8U 	KeySwitch[KEY_NUMBER];	//Board key switch identification, value toggled while specified key pressed.

#define	KEYSWITCH(x)	KeySwitch[x-1]

INT8U Task_KeyScan_Creat(void);


//===================================================================
// prototypes
int User_App_Initial(void);
void USER_Print_Decimal(INT32U);
void USER_Print_OSIdleCtr(void);


#ifdef __cplusplus
}
#endif
#endif /* UCOSII_DEMO_H */

/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
