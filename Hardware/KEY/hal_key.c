/**
  *********************************************************************************************************
  * @file    hal_key.c
  * @author  Apollo -- KK
  * @version V1.0
  * @date    2018-06-02
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hal_key.h"
#include "delay.h"

/**********************************************************************************************************
 @Function			void KEY_Init(void)
 @Description			KEY_Init					: KEY初始化
					KEY0			--- PH3
					KEY1			--- PH2
					KEY2			--- PC13
					WKUP			--- PA0
 @Input				void
 @Return				void
**********************************************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	KEY0_RCC_GPIO_CLK_ENABLE();
	KEY1_RCC_GPIO_CLK_ENABLE();
	KEY2_RCC_GPIO_CLK_ENABLE();
	WKUP_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin		= KEY0_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_INPUT;
	GPIO_Initure.Pull		= GPIO_PULLUP;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(KEY0_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin		= KEY1_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_INPUT;
	GPIO_Initure.Pull		= GPIO_PULLUP;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(KEY1_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin		= KEY2_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_INPUT;
	GPIO_Initure.Pull		= GPIO_PULLUP;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(KEY2_GPIOx, &GPIO_Initure);
	
	GPIO_Initure.Pin		= WKUP_PIN;
	GPIO_Initure.Mode		= GPIO_MODE_INPUT;
	GPIO_Initure.Pull		= GPIO_PULLDOWN;
	GPIO_Initure.Speed		= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(WKUP_GPIOx, &GPIO_Initure);
}

/**********************************************************************************************************
 @Function			u8 KEY_Scan(u8 mode)
 @Description			KEY_Scan					: KEY按键处理函数
 @Input				false					: 不支持连续按
					true						: 支持连续按
 @Return				按键值
 @other				注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
**********************************************************************************************************/
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1;												//按键松开标志	松开为1 按下清0
	
	if (mode == true) {													//支持连按
		key_up = 1;
	}
	
	if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WKUP == 1)) {
		Delay_MS(10);
		key_up = 0;													//按键按下清0
		if (KEY0 == 0)			return KEY0_PRES;							//判断并返回键值
		else if (KEY1 == 0)		return KEY1_PRES;
		else if (KEY2 == 0) 	return KEY2_PRES;
		else if (WKUP == 1)		return WKUP_PRES;
	}
	else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WKUP == 0) key_up = 1;		//按键松开置1
	
	return 0;															//无按键按下
}

/********************************************** END OF FLEE **********************************************/
