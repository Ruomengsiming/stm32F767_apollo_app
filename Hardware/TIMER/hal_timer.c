/**
  *********************************************************************************************************
  * @file    hal_timer.c
  * @author  Apollo -- KK
  * @version V1.0
  * @date    2018-06-05
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hal_timer.h"
#include "hal_led.h"

TIM_HandleTypeDef						TIM4_Handler;						//定时器4句柄

/**********************************************************************************************************
 @Function			void TIM4_Init(u16 arr, u16 psc)
 @Description			TIM4_Init			: 通用定时器4初始化
 @Input				arr				: 自动重装值
					psc				: 时钟预分频数
 @other				定时器溢出时间计算	: Tout=((arr+1)*(psc+1))/Ft us
									  Ft = 定时器工作频率,单位:Mhz
					这里使用的是定时器4!(定时器4挂在APB1上,时钟为HCLK/2)
 @Return				void
**********************************************************************************************************/
void TIM4_Init(u16 arr, u16 psc)
{
	TIM4_Handler.Instance				= TIM4;							//通用定时器4
	TIM4_Handler.Init.Prescaler			= psc;							//分频数
	TIM4_Handler.Init.CounterMode			= TIM_COUNTERMODE_UP;				//向上计数器
	TIM4_Handler.Init.Period				= arr;							//自动装载值
	TIM4_Handler.Init.ClockDivision		= TIM_CLOCKDIVISION_DIV1;			//时钟分频因子
	HAL_TIM_Base_Init(&TIM4_Handler);
	
	HAL_TIM_Base_Start_IT(&TIM4_Handler);									//使能定时器4和定时器4更新中断 : TIM_IT_UPDATE
}

/**********************************************************************************************************
 @Function			void TIM4_DeInit(void)
 @Description			TIM4_DeInit		: 通用定时器4反初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void TIM4_DeInit(void)
{
	HAL_TIM_Base_DeInit(&TIM4_Handler);
}

/**********************************************************************************************************
 @Function			void TIM4_Event_IRQn(void)
 @Description			TIM4_Event_IRQn
 @Input				void
 @Return				void
**********************************************************************************************************/
void TIM4_Event_IRQn(void)
{
#if 0
	LED0_Toggle();
#endif
}


































/********************************************** END OF FLEE **********************************************/
