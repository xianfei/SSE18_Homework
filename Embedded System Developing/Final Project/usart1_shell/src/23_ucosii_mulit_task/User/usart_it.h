/**
  ******************************************************************************
  * File Name          : usart_it.h
  * Description        : USATR driver & shell code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 xianfei wang & jkuang@BUPT
  *
  ******************************************************************************
  */


#ifndef   UASRT_IT
#define   UASRT_IT
#ifdef __cplusplus
		 extern "C" {
#endif

void Uart_Sendbuf_Init(void);
char* Uart_Sendbuf_Get(void);

void USER_USART1_print(char *);
INT8U Task_USART1_Creat(void);
			 
INT8U Task_SHELL_Creat(void);

void task_USART1 (void* p_arg);

void OS_CPU_USART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif 
#endif  //UASRT_IT
