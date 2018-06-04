#ifndef __DELAY_H
#define   __DELAY_H

#include "sys.h"

void Delay_Init(u32 SYSCLK);

#if SYSTEM_SUPPORT_OS
void Delay_US(u32 nus);
void Delay_MS(u32 nms);
void Delay_xMS(u32 nms);
#else
void Delay_US(u32 nus);
void Delay_MS(u32 nms);
#endif

#endif /* __DELAY_H */
