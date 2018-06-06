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

TIM_HandleTypeDef						TIM3_Handler;						//定时器3句柄
TIM_HandleTypeDef						TIM4_Handler;						//定时器4句柄

TIM_OC_InitTypeDef						TIM3_CH3Handler;					//定时器3通道3句柄
TIM_OC_InitTypeDef						TIM3_CH4Handler;					//定时器3通道4句柄

/**********************************************************************************************************
 @Function			void TIM3_PWM_Init(u16 arr, u16 psc)
 @Description			TIM3_PWM_Init		: 通用定时器3初始化
 @Input				arr				: 自动重装值
					psc				: 时钟预分频数
 @Return				void
**********************************************************************************************************/
void TIM3_PWM_Init(u16 arr, u16 psc)
{
	TIM3_Handler.Instance				= TIM3;							//通用定时器3
	TIM3_Handler.Init.Prescaler			= psc;							//分频数
	TIM3_Handler.Init.CounterMode			= TIM_COUNTERMODE_UP;				//向上计数器
	TIM3_Handler.Init.Period				= arr;							//自动装载值
	TIM3_Handler.Init.ClockDivision		= TIM_CLOCKDIVISION_DIV1;			//时钟分频因子
	HAL_TIM_PWM_Init(&TIM3_Handler);
	
	TIM3_CH3Handler.OCMode				= TIM_OCMODE_PWM1;					//模式选择PWM1
	TIM3_CH3Handler.Pulse				= arr / 2;						//设置比较值,此值用来确定占空比50%
	TIM3_CH3Handler.OCPolarity			= TIM_OCPOLARITY_LOW;				//输出比较性为低
	HAL_TIM_PWM_ConfigChannel(&TIM3_Handler, &TIM3_CH3Handler, TIM_CHANNEL_3);		//配置TIM3通道3
	
	TIM3_CH4Handler.OCMode				= TIM_OCMODE_PWM1;					//模式选择PWM1
	TIM3_CH4Handler.Pulse				= arr / 2;						//设置比较值,此值用来确定占空比50%
	TIM3_CH4Handler.OCPolarity			= TIM_OCPOLARITY_LOW;				//输出比较性为低
	HAL_TIM_PWM_ConfigChannel(&TIM3_Handler, &TIM3_CH4Handler, TIM_CHANNEL_4);		//配置TIM3通道4
	
	HAL_TIM_PWM_Start(&TIM3_Handler, TIM_CHANNEL_3);							//配置TIM3通道3
	HAL_TIM_PWM_Start(&TIM3_Handler, TIM_CHANNEL_4);							//配置TIM3通道4
}

/**********************************************************************************************************
 @Function			void TIM3_PWM_DeInit(void)
 @Description			TIM3_PWM_DeInit	: 通用定时器3反初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void TIM3_PWM_DeInit(void)
{
	HAL_TIM_PWM_DeInit(&TIM3_Handler);
}

/**********************************************************************************************************
 @Function			void TIM3_SetCH3Compare(u32 compare)
 @Description			TIM3_SetCH3Compare	: 设置TIM3通道3的占空比
 @Input				compare			: 比较值
 @Return				void
**********************************************************************************************************/
void TIM3_SetCH3Compare(u32 compare)
{
	TIM3->CCR3 = compare;
}

/**********************************************************************************************************
 @Function			void TIM3_SetCH4Compare(u32 compare)
 @Description			TIM3_SetCH4Compare	: 设置TIM3通道4的占空比
 @Input				compare			: 比较值
 @Return				void
**********************************************************************************************************/
void TIM3_SetCH4Compare(u32 compare)
{
	TIM3->CCR4 = compare;
}

/**********************************************************************************************************
 @Function			void TIM4_BASE_Init(u16 arr, u16 psc)
 @Description			TIM4_BASE_Init		: 通用定时器4初始化
 @Input				arr				: 自动重装值
					psc				: 时钟预分频数
 @other				定时器溢出时间计算	: Tout=((arr+1)*(psc+1))/Ft us
									  Ft = 定时器工作频率,单位:Mhz
					这里使用的是定时器4!(定时器4挂在APB1上,时钟为HCLK/2)
 @Return				void
**********************************************************************************************************/
void TIM4_BASE_Init(u16 arr, u16 psc)
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
void TIM4_BASE_DeInit(void)
{
	HAL_TIM_Base_DeInit(&TIM4_Handler);
}

/**********************************************************************************************************
 @Function			void TIM4_Event_IRQn(void)
 @Description			TIM4_Event_IRQn
 @Input				void
 @Return				void
**********************************************************************************************************/
void TIM4_BASE_Event_IRQn(void)
{
#if 0
	LED0_Toggle();
#endif
}

































/********************************************** END OF FLEE **********************************************/
