#ifndef __HAL_LED_H
#define   __HAL_LED_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

#define LED0_GPIOx						GPIOB
#define LED0_PIN						GPIO_PIN_1
#define LED0_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define LED0_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define LED1_GPIOx						GPIOB
#define LED1_PIN						GPIO_PIN_0
#define LED1_RCC_GPIO_CLK_ENABLE()			__HAL_RCC_GPIOB_CLK_ENABLE()
#define LED1_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()

#define LED0(n)		(n ? HAL_GPIO_WritePin(LED0_GPIOx, LED0_PIN, GPIO_PIN_RESET) : HAL_GPIO_WritePin(LED0_GPIOx, LED0_PIN, GPIO_PIN_SET))
#define LED1(n)		(n ? HAL_GPIO_WritePin(LED1_GPIOx, LED1_PIN, GPIO_PIN_RESET) : HAL_GPIO_WritePin(LED1_GPIOx, LED1_PIN, GPIO_PIN_SET))

#define LED0_Toggle()	(HAL_GPIO_TogglePin(LED0_GPIOx, LED0_PIN))
#define LED1_Toggle()	(HAL_GPIO_TogglePin(LED1_GPIOx, LED1_PIN))

void LED_Init(void);													//LED初始化

#endif /* __HAL_LED_H */
