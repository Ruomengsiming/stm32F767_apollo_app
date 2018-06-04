#ifndef __HAL_KEY_H
#define   __HAL_KEY_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

#define KEY0_GPIOx						GPIOH
#define KEY0_PIN						GPIO_PIN_3
#define KEY0_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOH_CLK_ENABLE()
#define KEY0_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOH_CLK_DISABLE()

#define KEY1_GPIOx						GPIOH
#define KEY1_PIN						GPIO_PIN_2
#define KEY1_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOH_CLK_ENABLE()
#define KEY1_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOH_CLK_DISABLE()

#define KEY2_GPIOx						GPIOC
#define KEY2_PIN						GPIO_PIN_13
#define KEY2_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOC_CLK_ENABLE()
#define KEY2_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOC_CLK_DISABLE()

#define WKUP_GPIOx						GPIOA
#define WKUP_PIN						GPIO_PIN_0
#define WKUP_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOA_CLK_ENABLE()
#define WKUP_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOA_CLK_DISABLE()

#define KEY0							HAL_GPIO_ReadPin(KEY0_GPIOx, KEY0_PIN)
#define KEY1							HAL_GPIO_ReadPin(KEY1_GPIOx, KEY1_PIN)
#define KEY2							HAL_GPIO_ReadPin(KEY2_GPIOx, KEY2_PIN)
#define WKUP							HAL_GPIO_ReadPin(WKUP_GPIOx, WKUP_PIN)

#define KEY0_PRES						1
#define KEY1_PRES						2
#define KEY2_PRES						3
#define WKUP_PRES						4

void KEY_Init(void);													//KEY初始化
u8 KEY_Scan(u8 mode);													//KEY按键处理函数

#endif /* __HAL_KEY_H */
