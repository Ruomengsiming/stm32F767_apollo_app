#ifndef __HAL_EXTI_H
#define   __HAL_EXTI_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

#define KEY0_IRQn						EXTI0_IRQn
#define KEY1_IRQn						EXTI2_IRQn
#define KEY2_IRQn						EXTI3_IRQn
#define WKUP_IRQn						EXTI15_10_IRQn

void EXTI_Init(void);													//外部中断初始化 按键中断

void EXTI_KEY0_Event_IRQn(void);
void EXTI_KEY1_Event_IRQn(void);
void EXTI_KEY2_Event_IRQn(void);
void EXTI_WKUP_Event_IRQn(void);

#endif /* __HAL_EXTI_H */
