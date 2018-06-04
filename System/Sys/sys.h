#ifndef __SYS_H
#define   __SYS_H

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "core_cm7.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#define SYSTEM_SUPPORT_OS		1											//定义系统文件夹是否支持OS 0:不支持os 1:支持os

#define ON					1
#define OFF					0

#define Write_Through()			(*(__IO uint32_t*)0XE000EF9C=1UL<<2)				//Cache透写模式. 和SCB->CACR|=1<<2,作用一致

typedef int32_t		s32;
typedef int16_t		s16;
typedef int8_t			s8;

typedef const int32_t	sc32;
typedef const int16_t	sc16;
typedef const int8_t	sc8;

typedef __IO int32_t	vs32;
typedef __IO int16_t	vs16;
typedef __IO int8_t		vs8;

typedef __I int32_t		vsc32;
typedef __I int16_t		vsc16;
typedef __I int8_t		vsc8;

typedef uint32_t		u32;
typedef uint16_t		u16;
typedef uint8_t		u8;

typedef const uint32_t	uc32;
typedef const uint16_t	uc16;
typedef const uint8_t	uc8;

typedef __IO uint32_t	vu32;
typedef __IO uint16_t	vu16;
typedef __IO uint8_t	vu8;

typedef __I uint32_t	vuc32;
typedef __I uint16_t	vuc16;
typedef __I uint8_t		vuc8;

typedef struct
{
	unsigned int	xTicksToWait;
	unsigned int	xTimeOut;
}Stm32_CalculagraphTypeDef;													//计时器

extern __IO u32 SystemRunningTimesSecond;										//系统运行时间(S)

void Stm32_Cache_Enable(void);												//使能CPU的L1-Cache
void Stm32_Clock_Init(u32 plln, u32 pllm, u32 pllp, u32 pllq);						//配置系统时钟
void Stm32_Software_Reboot(void);												//软重启

void Stm32_IncSecondTick(void);												//运行时间加1秒
u32  Stm32_GetSecondTick(void);												//获取运行秒数

void Stm32_Calculagraph_Init(Stm32_CalculagraphTypeDef* timer);						//初始化计时器
void Stm32_Calculagraph_CountdownMS(Stm32_CalculagraphTypeDef* timer, u32 timeout_ms);	//配置计时器倒数时间(MS)
bool Stm32_Calculagraph_IsExpiredMS(Stm32_CalculagraphTypeDef* timer);				//查询是否到达计时器计时时间(MS)
void Stm32_Calculagraph_CountdownSec(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec);	//配置计时器倒数时间(S)
bool Stm32_Calculagraph_IsExpiredSec(Stm32_CalculagraphTypeDef* timer);				//查询是否到达计时器计时时间(S)

u8 Stm32_Get_ICahceSta(void);													//判断I_Cache是否打开
u8 Stm32_Get_DCahceSta(void);													//判断D_Cache是否打开

void WFI_SET(void);															//执行WFI指令
void INTX_DISABLE(void);														//关闭所有中断
void INTX_ENABLE(void);														//开启所有中断
void MSR_MSP(u32 addr);														//设置堆栈地址

#endif /* __SYS_H */
