#ifndef __HAL_TIMER_H
#define   __HAL_TIMER_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

extern TIM_HandleTypeDef					TIM4_Handler;						//定时器4句柄

void TIM4_Init(u16 arr, u16 psc);											//通用定时器4初始化
void TIM4_DeInit(void);													//通用定时器4反初始化
void TIM4_Event_IRQn(void);



















#endif /* __HAL_TIMER_H */
