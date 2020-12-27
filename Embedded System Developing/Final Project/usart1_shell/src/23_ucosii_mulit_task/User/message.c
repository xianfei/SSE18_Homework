/**
  ******************************************************************************
  * File Name          : message.c
  * Description        : demo code of message driven 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 jkuang@BUPT
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include	"uCOSII_Demo.h"


/* Private variables ---------------------------------------------------------*/

//Message mem partition
char 		memMsgBuf[MEMPART_MSG_NBLK][MEMPART_MSG_BLKSIZE];
OS_MEM *memMsgP;


//============================================================
//Message mem partition initial
INT8U Msg_MemInit(void)
{
	INT8U err;

	//mem partition Create
	memMsgP = OSMemCreate((void*)memMsgBuf, MEMPART_MSG_NBLK, MEMPART_MSG_BLKSIZE, &err);
	return(err);
}

//============================================================
//Release a Message mem block
INT8U Msg_MemPut(MESSAGE_HEAD* msgP)
{
	return(OSMemPut(memMsgP, (void *)msgP));
}


//============================================================
//Short Message send
//
//	get msg buf & send msg to a task Q 
//
// 	Arguments:
//		mCode: 			Message code
//		mSendTsk:		Sender TaskID
//		mRecvTsk:		Recv TaskID
//		mSendInst:	Send instance
//		mRecvInst:	Recv Instance
//
//	Returns:
//		Error code
//
INT8U Msg_SendShort(INT16U mCode, INT16S mSendTsk, INT16S mRecvTsk, 
												INT16U	mSendInst, INT16U	mRecvInst)
{
	INT8U err;
	MESSAGE_HEAD *msgP;
	
	//get msg buf & send msg to task Q
	msgP = (MESSAGE_HEAD*)OSMemGet(memMsgP, &err);
	if(msgP)
	{
		msgP->mCode 		= mCode;
		msgP->mSendTsk 	= mSendTsk;
		msgP->mRecvTsk 	= mRecvTsk;
		msgP->mSendInst = mSendInst;
		msgP->mRecvInst = mRecvInst;
		msgP->mLen			= 0;					//Short msg

		err = OSQPost((OS_EVENT*)APP_TQID(mRecvTsk), (void *)msgP);
		if(err)
		{
			err = OSMemPut(memMsgP, (void *)msgP); //Release memory
			return(err);
		}
		return(OS_ERR_NONE);
	}
	return(err);
}



//MESSAGE_C

