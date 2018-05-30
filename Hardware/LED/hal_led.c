/**
  *********************************************************************************************************
  * @file    hal_led.c
  * @author  Apollo -- KK
  * @version V1.0
  * @date    2018-05-30
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hal_led.h"

/**********************************************************************************************************
 @Function			void LED_Init(void)
 @Description			LED_Init					: LED初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	LED0_RCC_GPIO_CLK_ENABLE();
	LED1_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin	= LED0_PIN;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull	= GPIO_PULLUP;
	GPIO_Initure.Speed	= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(LED0_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin	= LED1_PIN;
	GPIO_Initure.Mode	= GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull	= GPIO_PULLUP;
	GPIO_Initure.Speed	= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(LED1_GPIOx, &GPIO_Initure);
	
	HAL_GPIO_WritePin(LED0_GPIOx, LED0_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1_GPIOx, LED1_PIN, GPIO_PIN_SET);
}

/********************************************** END OF FLEE **********************************************/
