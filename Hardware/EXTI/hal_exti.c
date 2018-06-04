/**
  *********************************************************************************************************
  * @file    hal_exti.c
  * @author  Apollo -- KK
  * @version V1.0
  * @date    2018-06-03
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hal_exti.h"
#include "hal_key.h"
#include "hal_led.h"

/**********************************************************************************************************
 @Function			void EXTI_Init(void)
 @Description			EXTI_Init					: 外部中断初始化 按键中断
					KEY0			--- PH3
					KEY1			--- PH2
					KEY2			--- PC13
					WKUP			--- PA0
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	KEY0_RCC_GPIO_CLK_ENABLE();
	KEY1_RCC_GPIO_CLK_ENABLE();
	KEY2_RCC_GPIO_CLK_ENABLE();
	WKUP_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin		= KEY0_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_IT_FALLING;
	GPIO_Initure.Pull		= GPIO_PULLUP;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(KEY0_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin		= KEY1_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_IT_FALLING;
	GPIO_Initure.Pull		= GPIO_PULLUP;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(KEY1_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin		= KEY2_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_IT_FALLING;
	GPIO_Initure.Pull		= GPIO_PULLUP;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(KEY2_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin		= WKUP_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_IT_RISING;
	GPIO_Initure.Pull		= GPIO_PULLDOWN;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(WKUP_GPIOx, &GPIO_Initure);
	
	HAL_NVIC_SetPriority(KEY0_IRQn, 3, 0);
	HAL_NVIC_EnableIRQ(KEY0_IRQn);
	
	HAL_NVIC_SetPriority(KEY1_IRQn, 3, 1);
	HAL_NVIC_EnableIRQ(KEY1_IRQn);
	
	HAL_NVIC_SetPriority(KEY2_IRQn, 3, 2);
	HAL_NVIC_EnableIRQ(KEY2_IRQn);
	
	HAL_NVIC_SetPriority(WKUP_IRQn, 3, 3);
	HAL_NVIC_EnableIRQ(WKUP_IRQn);
}

/**********************************************************************************************************
 @Function			void EXTI_KEY0_Event_IRQn(void)
 @Description			EXTI_KEY0_Event_IRQn
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI_KEY0_Event_IRQn(void)
{
#if 0
	Delay_MS(300);
	if (KEY0 == 0) {
		LED0_Toggle();
	}
#endif
}

/**********************************************************************************************************
 @Function			void EXTI_KEY1_Event_IRQn(void)
 @Description			EXTI_KEY1_Event_IRQn
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI_KEY1_Event_IRQn(void)
{
#if 0
	Delay_MS(300);
	if (KEY1 == 0) {
		LED1_Toggle();
	}
#endif
}

/**********************************************************************************************************
 @Function			void EXTI_KEY2_Event_IRQn(void)
 @Description			EXTI_KEY2_Event_IRQn
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI_KEY2_Event_IRQn(void)
{
#if 0
	Delay_MS(300);
	if (KEY2 == 0) {
		LED0(OFF);
		LED1(OFF);
	}
#endif
}

/**********************************************************************************************************
 @Function			void EXTI_WKUP_Event_IRQn(void)
 @Description			EXTI_WKUP_Event_IRQn
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI_WKUP_Event_IRQn(void)
{
#if 0
	Delay_MS(300);
	if (WKUP == 1) {
		LED0(ON);
		LED1(ON);
	}
#endif
}

/********************************************** END OF FLEE **********************************************/
