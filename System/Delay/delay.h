#ifndef __DELAY_H
#define   __DELAY_H

#include "sys.h"

void Delay_Init(u32 SYSCLK);
void Delay_US(u32 nus);
void Delay_MS(u16 nms);

#endif /* __DELAY_H */
