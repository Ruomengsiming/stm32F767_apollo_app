/**
  *********************************************************************************************************
  * @file    hal_wwdg.c
  * @author  Apollo -- KK
  * @version V1.0
  * @date    2018-06-03
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "hal_wwdg.h"
#include "hal_led.h"

WWDG_HandleTypeDef						WWDG_Handler;						//窗口看门狗句柄

/**********************************************************************************************************
 @Function			void WWDG_Init(u8 trcount, u8 wrval, u32 fprer)
 @Description			初始化窗口看门狗
 @Input				trcount			: T[6:0],计数器值 
					wrval			: W[6:0],窗口值 
					fprer			: 分频系数（WDGTB）,仅最低2位有效 
					Fwwdg = PCLK1/(4096*2^fprer).		一般PCLK1 = 54Mhz
 @Return				void
**********************************************************************************************************/
void WWDG_Init(u8 trcount, u8 wrval, u32 fprer)
{
	WWDG_Handler.Instance		= WWDG;
	WWDG_Handler.Init.Prescaler	= fprer;									//设置分频系数
	WWDG_Handler.Init.Counter	= trcount;								//设置计数器值
	WWDG_Handler.Init.Window		= wrval;									//设置窗口值
	WWDG_Handler.Init.EWIMode	= WWDG_EWI_ENABLE;							//使能窗口看门狗提前唤醒中断
	HAL_WWDG_Init(&WWDG_Handler);											//初始化WWDG
}

/**********************************************************************************************************
 @Function			void WWDG_EWI_Event_IRQn(void)
 @Description			WWDG_EWI_Event_IRQn
 @Input				void
 @Return				void
**********************************************************************************************************/
void WWDG_EWI_Event_IRQn(void)
{
#if 0
	LED0_Toggle();
#endif
}

/********************************************** END OF FLEE **********************************************/
