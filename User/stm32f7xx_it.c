/**
  *********************************************************************************************************
  * @file    stm32f7xx_it.c
  * @author  Yunjie-K
  * @version V1.0
  * @date    2018-05-30
  * @brief   中断函数
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "stm32f7xx_it.h"
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
 @Function			void TIM4_IRQHandler(void)
 @Description			定时器4中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM4_Handler);										//调用中断处理公共函数
}

/**********************************************************************************************************
 @Function			void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 @Description			定时器中断处理回调函数
					在HAL库中所有定时器中断服务函数都会调用此函数
 @Input				htim : TIM
 @Return				void
**********************************************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM4)
	{
		TIM4_Event_IRQn();
	}
}


/**********************************************************************************************************
 @Function			void EXTI0_IRQHandler(void)
 @Description			外部中断0中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(WKUP_PIN);									//调用中断处理公共函数
}

/**********************************************************************************************************
 @Function			void EXTI2_IRQHandler(void)
 @Description			外部中断2中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(KEY1_PIN);									//调用中断处理公共函数
}

/**********************************************************************************************************
 @Function			void EXTI3_IRQHandler(void)
 @Description			外部中断3中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI3_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(KEY0_PIN);									//调用中断处理公共函数
}

/**********************************************************************************************************
 @Function			void EXTI15_10_IRQHandler(void)
 @Description			外部中断15_10中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(KEY2_PIN);									//调用中断处理公共函数
}

/**********************************************************************************************************
 @Function			void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 @Description			外部中断处理回调函数
					在HAL库中所有外部中断服务函数都会调用此函数
 @Input				GPIO_Pin : GPIO_Pin
 @Return				void
**********************************************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
		case KEY0_PIN:
			EXTI_KEY0_Event_IRQn();
			break;
		
		case KEY1_PIN:
			EXTI_KEY1_Event_IRQn();
			break;
		
		case KEY2_PIN:
			EXTI_KEY2_Event_IRQn();
			break;
		
		case WKUP_PIN:
			EXTI_WKUP_Event_IRQn();
			break;
	}
}


/**********************************************************************************************************
 @Function			void USART1_IRQHandler(void)
 @Description			串口1中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void USART1_IRQHandler(void)
{
	u32 timeout = 0;
	
	HAL_UART_IRQHandler(&UART1_Handler);									//调用HAL库中断处理公用函数
	
	timeout = 0;
	while (HAL_UART_GetState(&UART1_Handler) != HAL_UART_STATE_READY) {			//等待就绪
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
	
	timeout = 0;
	/* 一次处理完成之后, 重新开启中断并设置RxXferCount为1 */
	while (HAL_UART_Receive_IT(&UART1_Handler, (u8 *)USART1_aRxBuffer, USART1_RXBUFFERSIZE) != HAL_OK) {
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
}

/**********************************************************************************************************
 @Function			void USART2_IRQHandler(void)
 @Description			串口2中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void USART2_IRQHandler(void)
{
	u32 timeout = 0;
	
	HAL_UART_IRQHandler(&UART2_Handler);									//调用HAL库中断处理公用函数
	
	timeout = 0;
	while (HAL_UART_GetState(&UART2_Handler) != HAL_UART_STATE_READY) {			//等待就绪
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
	
	timeout = 0;
	/* 一次处理完成之后, 重新开启中断并设置RxXferCount为1 */
	while (HAL_UART_Receive_IT(&UART2_Handler, (u8 *)USART2_aRxBuffer, USART2_RXBUFFERSIZE) != HAL_OK) {
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
}

/**********************************************************************************************************
 @Function			void USART3_IRQHandler(void)
 @Description			串口3中断服务程序
 @Input				void
 @Return				void
**********************************************************************************************************/
void USART3_IRQHandler(void)
{
	u32 timeout = 0;
	
	HAL_UART_IRQHandler(&UART3_Handler);									//调用HAL库中断处理公用函数
	
	timeout = 0;
	while (HAL_UART_GetState(&UART3_Handler) != HAL_UART_STATE_READY) {			//等待就绪
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
	
	timeout = 0;
	/* 一次处理完成之后, 重新开启中断并设置RxXferCount为1 */
	while (HAL_UART_Receive_IT(&UART3_Handler, (u8 *)USART3_aRxBuffer, USART3_RXBUFFERSIZE) != HAL_OK) {
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
}

/**********************************************************************************************************
 @Function			void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 @Description			串口接收中断处理回调函数
					在HAL库中所有串口接收中断服务函数都会调用此函数
 @Input				huart : UART句柄
 @Return				void
**********************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)										//如果是串口1
	{
		if ((USART1_RX_STA & 0x8000) == 0) {								//接收未完成
			if (USART1_RX_STA & 0x4000) {									//接收到了0x0D
				if (USART1_aRxBuffer[0] != 0x0a) {							//还未接收到\r\n
					USART1_RX_STA &= 0xBFFF;
					USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X3FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
				else {												//接收完成了
					USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X3FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART1_RX_STA |= 0x8000;
				}
			}
			else {													//还没收到0x0D
				if (USART1_aRxBuffer[0] == 0x0d) {
					USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X3FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART1_RX_STA |= 0x4000;
				}
				else {
					USART1_RX_BUF[USART1_RX_STA & 0X3FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X3FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
			}
		}
	}
	
	if (huart->Instance == USART2)										//如果是串口2
	{
		if ((USART2_RX_STA & 0x8000) == 0) {								//接收未完成
			if (USART2_RX_STA & 0x4000) {									//接收到了0x0D
				if (USART2_aRxBuffer[0] != 0x0a) {							//还未接收到\r\n
					USART2_RX_STA &= 0xBFFF;
					USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = USART2_aRxBuffer[0];
					USART2_RX_STA++;
					if ((USART2_RX_STA & 0X3FFF) > (USART2_REC_LEN-1)) USART2_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
				else {												//接收完成了
					USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = USART2_aRxBuffer[0];
					USART2_RX_STA++;
					if ((USART2_RX_STA & 0X3FFF) > (USART2_REC_LEN-1)) USART2_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART2_RX_STA |= 0x8000;
				}
			}
			else {													//还没收到0x0D
				if (USART2_aRxBuffer[0] == 0x0d) {
					USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = USART2_aRxBuffer[0];
					USART2_RX_STA++;
					if ((USART2_RX_STA & 0X3FFF) > (USART2_REC_LEN-1)) USART2_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART2_RX_STA |= 0x4000;
				}
				else {
					USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = USART2_aRxBuffer[0];
					USART2_RX_STA++;
					if ((USART2_RX_STA & 0X3FFF) > (USART2_REC_LEN-1)) USART2_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
			}
		}
	}
	
	if (huart->Instance == USART3)										//如果是串口3
	{
		if ((USART3_RX_STA & 0x8000) == 0) {								//接收未完成
			if (USART3_RX_STA & 0x4000) {									//接收到了0x0D
				if (USART3_aRxBuffer[0] != 0x0a) {							//还未接收到\r\n
					USART3_RX_STA &= 0xBFFF;
					USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = USART3_aRxBuffer[0];
					USART3_RX_STA++;
					if ((USART3_RX_STA & 0X3FFF) > (USART3_REC_LEN-1)) USART3_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
				else {												//接收完成了
					USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = USART3_aRxBuffer[0];
					USART3_RX_STA++;
					if ((USART3_RX_STA & 0X3FFF) > (USART3_REC_LEN-1)) USART3_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART3_RX_STA |= 0x8000;
				}
			}
			else {													//还没收到0x0D
				if (USART3_aRxBuffer[0] == 0x0d) {
					USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = USART3_aRxBuffer[0];
					USART3_RX_STA++;
					if ((USART3_RX_STA & 0X3FFF) > (USART3_REC_LEN-1)) USART3_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART3_RX_STA |= 0x4000;
				}
				else {
					USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = USART3_aRxBuffer[0];
					USART3_RX_STA++;
					if ((USART3_RX_STA & 0X3FFF) > (USART3_REC_LEN-1)) USART3_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
			}
		}
	}
}


/**********************************************************************************************************
 @Function			void WWDG_IRQHandler(void)
 @Description			窗口看门狗中断服务函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void WWDG_IRQHandler(void)
{
	HAL_WWDG_IRQHandler(&WWDG_Handler);									//调用HAL库中断处理公用函数
}

/**********************************************************************************************************
 @Function			void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* hwwdg)
 @Description			窗口看门狗中断处理回调函数
					在HAL库中所有窗口看门狗中断服务函数都会调用此函数
 @Input				hwwdg : WWDG句柄
 @Return				void
**********************************************************************************************************/
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
	HAL_WWDG_Refresh(&WWDG_Handler);										//更新窗口看门狗值
	
	WWDG_EWI_Event_IRQn();
}


/**********************************************************************************************************
 @Function			void NMI_Handler(void)
 @Description			This function handles NMI exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void NMI_Handler(void)
{
}

/**********************************************************************************************************
 @Function			void HardFault_Handler(void)
 @Description			This function handles Hard Fault exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void MemManage_Handler(void)
 @Description			This function handles Memory Manage exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void BusFault_Handler(void)
 @Description			This function handles Bus Fault exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void UsageFault_Handler(void)
 @Description			This function handles Usage Fault exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while(1) {
	}
}

/**********************************************************************************************************
 @Function			void DebugMon_Handler(void)
 @Description			This function handles Debug Monitor exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void DebugMon_Handler(void)
{
}

#if (SYSTEM_SUPPORT_OS == 0)
/**********************************************************************************************************
 @Function			void SVC_Handler(void)
 @Description			This function handles SVCall exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void SVC_Handler(void)
{
}
#endif

#if (SYSTEM_SUPPORT_OS == 0)
/**********************************************************************************************************
 @Function			void PendSV_Handler(void)
 @Description			This function handles PendSVC exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void PendSV_Handler(void)
{
}
#endif

#if SYSTEM_SUPPORT_OS
extern void xPortSysTickHandler(void);

/**********************************************************************************************************
 @Function			void SysTick_Handler(void)
 @Description			This function handles SysTick Handler.
 @Input				void
 @Return				void
**********************************************************************************************************/
void SysTick_Handler(void)
{
	HAL_SYSTICK_IRQHandler();
}

/**********************************************************************************************************
 @Function			void HAL_SYSTICK_Callback(void)
 @Description			系统嘀嗒定时器中断处理回调函数
					在HAL库中所有系统嘀嗒定时器中断服务函数都会调用此函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void HAL_SYSTICK_Callback(void)
{
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
		xPortSysTickHandler();
	}
	
	HAL_IncTick();
	Stm32_IncSecondTick();
}
#else
/**********************************************************************************************************
 @Function			void SysTick_Handler(void)
 @Description			This function handles SysTick Handler.
 @Input				void
 @Return				void
**********************************************************************************************************/
void SysTick_Handler(void)
{
	HAL_SYSTICK_IRQHandler();
}

/**********************************************************************************************************
 @Function			void HAL_SYSTICK_Callback(void)
 @Description			系统嘀嗒定时器中断处理回调函数
					在HAL库中所有系统嘀嗒定时器中断服务函数都会调用此函数
 @Input				void
 @Return				void
**********************************************************************************************************/
void HAL_SYSTICK_Callback(void)
{
	HAL_IncTick();
	Stm32_IncSecondTick();
}
#endif

/********************************************** END OF FLEE **********************************************/
