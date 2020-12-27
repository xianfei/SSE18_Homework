/**
  ******************************************************************************
  * File Name          : farsight_f407.h
  * Description        : demo code of board specified for »ªÇåÔ¶¼û STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 jkuang@BUPT
  *
  ******************************************************************************
  */
#ifndef FARSIGHT_F407_H
#define FARSIGHT_F407_H
#ifdef __cplusplus
		 extern "C" {
#endif

#include 	"gpio.h"

//===================================================================
//Beep
#define BEEP_OFF			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET)
#define BEEP_TOGGLE		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6)

//===================================================================
//Leds
#define LED1_OFF			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET)
#define LED2_OFF			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET)
#define LED3_OFF			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET)
#define LED4_OFF			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET)

#define LED1_ON				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET)
#define LED2_ON				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET)
#define LED3_ON				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET)
#define LED4_ON				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET)

#define LED1_TOGGLE		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10)
#define LED2_TOGGLE		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9)
#define LED3_TOGGLE		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8)
#define LED4_TOGGLE		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2)

#define LED1_READ			HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10)
#define LED2_READ			HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9)
#define LED3_READ			HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8)
#define LED4_READ			HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2)

//===================================================================
//Keys
#define KEY1_READ 		HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_9)
#define KEY2_READ 		HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_11)
#define KEY3_READ 		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)
#define KEY4_READ			HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)

#ifdef __cplusplus
}
#endif
#endif /* FARSIGHT_F407_H */

/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
