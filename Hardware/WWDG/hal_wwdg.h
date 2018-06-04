#ifndef __HAL_WWDG_H
#define   __HAL_WWDG_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

extern WWDG_HandleTypeDef				WWDG_Handler;						//窗口看门狗句柄

void WWDG_Init(u8 trcount, u8 wrval, u32 fprer);								//WWDG初始化

void WWDG_EWI_Event_IRQn(void);

#endif /* __HAL_WWDG_H */
