#ifndef __HAL_TIMER_H
#define   __HAL_TIMER_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

extern TIM_HandleTypeDef					TIM3_Handler;						//定时器3句柄
extern TIM_HandleTypeDef					TIM4_Handler;						//定时器4句柄

extern TIM_OC_InitTypeDef				TIM3_CH3Handler;					//定时器3通道3句柄
extern TIM_OC_InitTypeDef				TIM3_CH4Handler;					//定时器3通道4句柄

void TIM3_PWM_Init(u16 arr, u16 psc);										//通用定时器3初始化
void TIM3_PWM_DeInit(void);												//通用定时器3反初始化
void TIM3_SetCH3Compare(u32 compare);										//设置TIM3通道3的占空比
void TIM3_SetCH4Compare(u32 compare);										//设置TIM3通道4的占空比

void TIM4_BASE_Init(u16 arr, u16 psc);										//通用定时器4初始化
void TIM4_BASE_DeInit(void);												//通用定时器4反初始化
void TIM4_BASE_Event_IRQn(void);












#endif /* __HAL_TIMER_H */
