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
 @Function			void SVC_Handler(void)
 @Description			This function handles SVCall exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void SVC_Handler(void)
{
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

/**********************************************************************************************************
 @Function			void PendSV_Handler(void)
 @Description			This function handles PendSVC exception.
 @Input				void
 @Return				void
**********************************************************************************************************/
void PendSV_Handler(void)
{
}


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

/********************************************** END OF FLEE **********************************************/
