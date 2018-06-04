#ifndef __HAL_IWDG_H
#define   __HAL_IWDG_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

extern IWDG_HandleTypeDef				IWDG_Handler;						//独立看门狗句柄

void IWDG_Init(u8 prer, u16 rlr);											//IWDG初始化
void IWDG_Feed(void);													//IWDG喂独立看门狗

#endif /* __HAL_IWDG_H */
