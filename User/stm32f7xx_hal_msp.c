/**
  *********************************************************************************************************
  * @file    stm32f7xx_hal_msp.c
  * @author  Yunjie-K
  * @version V1.0
  * @date    2018-05-30
  * @brief   回调函数
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "hal_iwdg.h"
#include "hal_wwdg.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_exti.h"
#include "hal_timer.h"

#if SYSTEM_SUPPORT_OS													//如果使用OS, 则包括下面的头文件(以FreeRTOS为例)即可
#include "FreeRTOS.h"													//支持OS时使用
#include "task.h"
#endif

/**********************************************************************************************************
 @Function			void HAL_MspInit(void)
 @Description			HAL_MspInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void HAL_MspInit(void)
{
	
}

/**********************************************************************************************************
 @Function			void HAL_MspDeInit(void)
 @Description			HAL_MspDeInit
 @Input				void
 @Return				void
**********************************************************************************************************/
void HAL_MspDeInit(void)
{
	
}


/**********************************************************************************************************
 @Function			void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
 @Description			TIM_BASE底层驱动, 时钟配置, 中断配置
					此函数会被HAL_TIM_Base_Init()调用
 @Input				htim:TIM句柄
 @Output				void
 @Return				void
**********************************************************************************************************/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();										//使能通用定时器4时钟
		
		HAL_NVIC_SetPriority(TIM4_IRQn, 3, 0);								//强占优先级3, 次优先级0
		HAL_NVIC_EnableIRQ(TIM4_IRQn);									//使能TIM4中断
	}
}

/**********************************************************************************************************
 @Function			void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
 @Description			TIM_BASE底层驱动, 时钟失能, 中断关闭
					此函数会被HAL_TIM_Base_DeInit()调用
 @Input				htim:TIM句柄
 @Output				void
 @Return				void
**********************************************************************************************************/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM4)
	{
		__HAL_RCC_TIM4_CLK_DISABLE();										//失能通用定时器4时钟
		
		HAL_NVIC_DisableIRQ(TIM4_IRQn);									//失能TIM4中断
	}
}


/**********************************************************************************************************
 @Function			void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
 @Description			TIM_PWM底层驱动, 时钟配置, 中断配置
					此函数会被HAL_TIM_PWM_Init()调用
 @Input				htim:TIM句柄
 @Output				void
 @Return				void
**********************************************************************************************************/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if (htim->Instance == TIM3)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_TIM3_CLK_ENABLE();										//使能通用定时器3时钟
		
		GPIO_Initure.Pin		= GPIO_PIN_0;								//PB0
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;							//复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLUP;								//上拉
		GPIO_Initure.Speed		= GPIO_SPEED_HIGH;							//高速
		GPIO_Initure.Alternate	= GPIO_AF2_TIM3;							//PB0复用为TIM3_CH3
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);								//初始化PB0
		
		GPIO_Initure.Pin		= GPIO_PIN_1;								//PB1
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;							//复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLUP;								//上拉
		GPIO_Initure.Speed		= GPIO_SPEED_HIGH;							//高速
		GPIO_Initure.Alternate	= GPIO_AF2_TIM3;							//PB1复用为TIM3_CH4
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);								//初始化PB1
	}
}

/**********************************************************************************************************
 @Function			void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
 @Description			TIM_PWM底层驱动, 时钟失能, 中断关闭
					此函数会被HAL_TIM_PWM_DeInit()调用
 @Input				htim:TIM句柄
 @Output				void
 @Return				void
**********************************************************************************************************/
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		__HAL_RCC_TIM3_CLK_DISABLE();										//失能通用定时器4时钟
		
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_1);
	}
}


/**********************************************************************************************************
 @Function			void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
 @Description			WWDG底层驱动, 时钟配置, 中断配置
					此函数会被HAL_WWDG_Init()调用
 @Input				hwwdg:窗口看门狗句柄
 @Output				void
 @Return				void
**********************************************************************************************************/
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
	if (hwwdg->Instance == WWDG)
	{
		__HAL_RCC_WWDG_CLK_ENABLE();										//使能窗口看门狗时钟
		
		HAL_NVIC_SetPriority(WWDG_IRQn, 4, 4);								//强占优先级为4, 次优先级4
		HAL_NVIC_EnableIRQ(WWDG_IRQn);									//使能窗口看门狗中断
	}
}

/**********************************************************************************************************
 @Function			void HAL_WWDG_MspDeInit(WWDG_HandleTypeDef *hwwdg)
 @Description			WWDG底层驱动, 时钟失能, 中断关闭
					此函数会被HAL_WWDG_DeInit()调用
 @Input				hwwdg:窗口看门狗句柄
 @Output				void
 @Return				void
**********************************************************************************************************/
void HAL_WWDG_MspDeInit(WWDG_HandleTypeDef *hwwdg)
{
	if (hwwdg->Instance == WWDG)
	{
		__HAL_RCC_WWDG_CLK_DISABLE();										//失能窗口看门狗时钟
		
		HAL_NVIC_DisableIRQ(WWDG_IRQn);									//失能窗口看门狗中断
	}
}


/**********************************************************************************************************
 @Function			void HAL_UART_MspInit(UART_HandleTypeDef *huart)
 @Description			UART底层初始化, 时钟使能, 引脚配置, 中断配置
					此函数会被HAL_UART_Init()调用
					USART1_TX : PA9
					USART1_RX : PA10
					USART2_TX : PA2
					USART2_RX : PA3
					USART3_TX : PB10
					USART3_RX : PB11
 @Input				huart:串口句柄
 @Return				void
**********************************************************************************************************/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if (huart->Instance == USART1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();										//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();									//使能USART1时钟
		
		GPIO_Initure.Pin		= GPIO_PIN_9 | GPIO_PIN_10;					//PA9|PA10
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;							//复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLUP;								//上拉
		GPIO_Initure.Speed		= GPIO_SPEED_FAST;							//高速
		GPIO_Initure.Alternate	= GPIO_AF7_USART1;							//复用为串口1
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);								//初始化PA9|PA10
		
		HAL_NVIC_SetPriority(USART1_IRQn, 2, 0);							//抢占优先级2, 子优先级0
		HAL_NVIC_EnableIRQ(USART1_IRQn);									//使能USART1中断通道
	}
	
	if (huart->Instance == USART2)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();										//使能GPIOA时钟
		__HAL_RCC_USART2_CLK_ENABLE();									//使能USART2时钟
		
		GPIO_Initure.Pin		= GPIO_PIN_2 | GPIO_PIN_3;					//PA2|PA3
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;							//复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLUP;								//上拉
		GPIO_Initure.Speed		= GPIO_SPEED_FAST;							//高速
		GPIO_Initure.Alternate	= GPIO_AF7_USART2;							//复用为串口2
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);								//初始化PA2|PA3
		
		HAL_NVIC_SetPriority(USART2_IRQn, 2, 1);							//抢占优先级2, 子优先级1
		HAL_NVIC_EnableIRQ(USART2_IRQn);									//使能USART2中断通道
	}
	
	if (huart->Instance == USART3)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();										//使能GPIOB时钟
		__HAL_RCC_USART3_CLK_ENABLE();									//使能USART3时钟
		
		GPIO_Initure.Pin		= GPIO_PIN_10 | GPIO_PIN_11;					//PB10|PB11
		GPIO_Initure.Mode		= GPIO_MODE_AF_PP;							//复用推挽输出
		GPIO_Initure.Pull		= GPIO_PULLUP;								//上拉
		GPIO_Initure.Speed		= GPIO_SPEED_FAST;							//高速
		GPIO_Initure.Alternate	= GPIO_AF7_USART3;							//复用为串口3
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);								//初始化PB10|PB11
		
		HAL_NVIC_SetPriority(USART3_IRQn, 2, 2);							//抢占优先级2, 子优先级2
		HAL_NVIC_EnableIRQ(USART3_IRQn);									//使能USART3中断通道
	}
}

/**********************************************************************************************************
 @Function			void HAL_UART_MspInit(UART_HandleTypeDef *huart)
 @Description			UART底层恢复初始化, 时钟失能, 引脚复位, 中断关闭
					此函数会被HAL_UART_DeInit()调用
					USART1_TX : PA9
					USART1_RX : PA10
					USART2_TX : PA2
					USART2_RX : PA3
					USART3_TX : PB10
					USART3_RX : PB11
 @Input				huart:串口句柄
 @Return				void
**********************************************************************************************************/
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		__HAL_RCC_USART1_CLK_DISABLE();									//失能USART1时钟
		
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);
		
		HAL_NVIC_DisableIRQ(USART1_IRQn);									//失能USART1中断通道
	}
	
	if (huart->Instance == USART2)
	{
		__HAL_RCC_USART2_CLK_DISABLE();									//失能USART2时钟
		
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);
		
		HAL_NVIC_DisableIRQ(USART2_IRQn);									//失能USART2中断通道
	}
	
	if (huart->Instance == USART3)
	{
		__HAL_RCC_USART3_CLK_DISABLE();									//失能USART3时钟
		
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11);
		
		HAL_NVIC_DisableIRQ(USART3_IRQn);									//失能USART3中断通道
	}
}

/********************************************** END OF FLEE **********************************************/
