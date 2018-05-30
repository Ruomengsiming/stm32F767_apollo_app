/**
  *********************************************************************************************************
  * @file    sys.c
  * @author  Apollo -- KK
  * @version V1.0
  * @date    2018-05-30
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "sys.h"

__IO u32 SystemRunningTimesSecond = 0;										//系统运行时间(S)

/**********************************************************************************************************
 @Function			void Stm32_Cache_Enable(void)
 @Description			Stm32_Cache_Enable						: 使能CPU的L1-Cache
 @Input				void
 @Return				void
**********************************************************************************************************/
void Stm32_Cache_Enable(void)
{
	SCB_EnableICache();													//使能I-Cache
	SCB_EnableDCache();													//使能D-Cache
	SCB->CACR|=1<<2;													//强制D-Cache透写,如不开启,实际使用中可能遇到各种问题
}

/**********************************************************************************************************
 @Function			void Stm32_Clock_Init(u32 plln, u32 pllm, u32 pllp, u32 pllq)
 @Description			时钟设置函数(MAX216MHz)
 @Input				plln		: 主PLL倍频系数(PLL倍频),取值范围:64~432
					pllm		: 主PLL和音频PLL分频系数(PLL之前的分频),取值范围:2~63
					pllp		: 系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,4,6,8.(仅限这4个值!)
					pllq		: USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频),取值范围:2~15
 @Return				void
 @attention			外部晶振为25M的时候,推荐值:plln=432,pllm=25,pllp=2,pllq=9
					得到		: Fvco = 25*(432/25)=432Mhz
							  Fsys = 432/2=216Mhz
							  Fusb = 432/9=48Mhz
					Fvco		: VCO频率
					Fsys		: 系统时钟频率
					Fusb		: USB,SDIO,RNG等的时钟频率
					Fs		: PLL输入时钟频率,可以是HSI,HSE等
**********************************************************************************************************/
void Stm32_Clock_Init(u32 plln, u32 pllm, u32 pllp, u32 pllq)
{
	HAL_StatusTypeDef ret = HAL_OK;
	RCC_OscInitTypeDef RCC_OscInitStructure;
	RCC_ClkInitTypeDef RCC_ClkInitStructure;
	
	HAL_RCC_DeInit();
	
	__HAL_RCC_PWR_CLK_ENABLE();											//使能PWR时钟
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);				//设置调压器输出电压级别,以便在器件未以最大频率工作
	while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY) != RESET) {};
	
	RCC_OscInitStructure.OscillatorType			= RCC_OSCILLATORTYPE_HSE;	//时钟源为HSE
	RCC_OscInitStructure.HSEState					= RCC_HSE_ON;				//打开HSE
	RCC_OscInitStructure.PLL.PLLState				= RCC_PLL_ON;				//打开PLL
	RCC_OscInitStructure.PLL.PLLSource				= RCC_PLLSOURCE_HSE;		//PLL时钟源选择HSE
	RCC_OscInitStructure.PLL.PLLN					= plln;					//主PLL倍频系数(PLL倍频)
	RCC_OscInitStructure.PLL.PLLM					= pllm;					//主PLL和音频PLL分频系数(PLL之前的分频)
	RCC_OscInitStructure.PLL.PLLP					= pllp;					//系统时钟的主PLL分频系数(PLL之后的分频)
	RCC_OscInitStructure.PLL.PLLQ					= pllq;					//USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频)
	ret = HAL_RCC_OscConfig(&RCC_OscInitStructure);							//初始化
	if (ret != HAL_OK) while(1);
	
	ret = HAL_PWREx_EnableOverDrive();										//开启Over-Driver功能
	if (ret != HAL_OK) while(1);
	
	/* 选中PLL作为系统时钟源并且配置HCLK, PCLK1 和 PCLK2 */
	RCC_ClkInitStructure.ClockType				= (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStructure.SYSCLKSource				= RCC_SYSCLKSOURCE_PLLCLK;	//设置系统时钟时钟源为PLL
	RCC_ClkInitStructure.AHBCLKDivider				= RCC_SYSCLK_DIV1;			//AHB分频系数为1
	RCC_ClkInitStructure.APB1CLKDivider			= RCC_HCLK_DIV4;			//APB1分频系数为4
	RCC_ClkInitStructure.APB2CLKDivider			= RCC_HCLK_DIV2;			//APB2分频系数为2
	
	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_7);			//同时设置FLASH延时周期为7WS,也就是8个CPU周期
	if (ret != HAL_OK) while(1);
}

/**********************************************************************************************************
 @Function			void Stm32_Software_Reboot(void)
 @Description			Stm32_Software_Reboot		: 软重启
 @Input				void
 @Return				void
**********************************************************************************************************/
void Stm32_Software_Reboot(void)
{
	__set_FAULTMASK(1);													//关闭所有中断
	HAL_NVIC_SystemReset();												//软件复位
	__NOP();
}

/**********************************************************************************************************
 @Function			void Stm32_IncSecondTick(void)
 @Description			Stm32_IncSecondTick : 运行时间加1秒
 @Input				void
 @Return				void
**********************************************************************************************************/
void Stm32_IncSecondTick(void)
{
	static u32 SecondTickPre;
	u32 SecondTickNow;
	
	SecondTickNow = HAL_GetTick();
	if ((SecondTickNow > SecondTickPre) && ((SecondTickNow - SecondTickPre) >= 1000)) {
		SystemRunningTimesSecond++;
		SecondTickPre += 1000;
	}
	else if ((0xFFFFFFFF - SecondTickPre + SecondTickNow + 1) >= 1000) {
		SystemRunningTimesSecond++;
		SecondTickPre += 1000;
	}
}

/**********************************************************************************************************
 @Function			u32 Stm32_GetSecondTick(void)
 @Description			Stm32_GetSecondTick 	: 获取运行秒数
 @Input				void
 @Return				SystemRunningTimesSecond : 运行秒数
**********************************************************************************************************/
u32 Stm32_GetSecondTick(void)
{
	return SystemRunningTimesSecond;
}

/**********************************************************************************************************
 @Function			void Stm32_Calculagraph_Init(Stm32_CalculagraphTypeDef* timer)
 @Description			Stm32_Calculagraph_Init 			: 初始化计时器
 @Input				Stm32_CalculagraphTypeDef*		: 计时器结构体指针
 @Return				void
**********************************************************************************************************/
void Stm32_Calculagraph_Init(Stm32_CalculagraphTypeDef* timer)
{
	timer->xTicksToWait = 0;
	timer->xTimeOut = 0;
}

/**********************************************************************************************************
 @Function			void Stm32_Calculagraph_CountdownMS(Stm32_CalculagraphTypeDef* timer, u32 timeout_ms)
 @Description			Stm32_Calculagraph_CountdownMS	: 配置计时器倒数时间(MS)
 @Input				Stm32_CalculagraphTypeDef*		: 计时器结构体指针
					timeout_ms					: 倒计时时间(MS)
 @Return				void
**********************************************************************************************************/
void Stm32_Calculagraph_CountdownMS(Stm32_CalculagraphTypeDef* timer, u32 timeout_ms)
{
	timer->xTicksToWait = timeout_ms;
	timer->xTimeOut = HAL_GetTick() + timeout_ms;
}

/**********************************************************************************************************
 @Function			bool Stm32_Calculagraph_IsExpiredMS(Stm32_CalculagraphTypeDef* timer)
 @Description			Stm32_Calculagraph_IsExpiredMS	: 查询是否到达计时器计时时间(MS)
 @Input				Stm32_CalculagraphTypeDef*		: 计时器结构体指针
 @Return				true							: 到达
					false						: 未到达
**********************************************************************************************************/
bool Stm32_Calculagraph_IsExpiredMS(Stm32_CalculagraphTypeDef* timer)
{
	u32 MilliSecondTickNow;
	
	MilliSecondTickNow = HAL_GetTick();
	
	if ((MilliSecondTickNow > (timer->xTimeOut - timer->xTicksToWait)) && ((MilliSecondTickNow - (timer->xTimeOut - timer->xTicksToWait)) >= timer->xTicksToWait)) {
		return true;
	}
	else if ((0xFFFFFFFF - (timer->xTimeOut - timer->xTicksToWait) + MilliSecondTickNow + 1) >= timer->xTicksToWait) {
		return true;
	}
	else {
		return false;
	}
}

/**********************************************************************************************************
 @Function			void Stm32_Calculagraph_CountdownSec(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec)
 @Description			Stm32_Calculagraph_CountdownSec	: 配置计时器倒数时间(S)
 @Input				Stm32_CalculagraphTypeDef*		: 计时器结构体指针
					timeout_sec					: 倒计时时间(S)
 @Return				void
**********************************************************************************************************/
void Stm32_Calculagraph_CountdownSec(Stm32_CalculagraphTypeDef* timer, u32 timeout_sec)
{
	timer->xTicksToWait = timeout_sec;
	timer->xTimeOut = Stm32_GetSecondTick() + timeout_sec;
}

/**********************************************************************************************************
 @Function			bool Stm32_Calculagraph_IsExpiredSec(Stm32_CalculagraphTypeDef* timer)
 @Description			Stm32_Calculagraph_IsExpiredSec	: 查询是否到达计时器计时时间(S)
 @Input				Stm32_CalculagraphTypeDef*		: 计时器结构体指针
 @Return				true							: 到达
					false						: 未到达
**********************************************************************************************************/
bool Stm32_Calculagraph_IsExpiredSec(Stm32_CalculagraphTypeDef* timer)
{
	u32 SecondTickNow;
	
	SecondTickNow = Stm32_GetSecondTick();
	
	if ((SecondTickNow > (timer->xTimeOut - timer->xTicksToWait)) && ((SecondTickNow - (timer->xTimeOut - timer->xTicksToWait)) >= timer->xTicksToWait)) {
		return true;
	}
	else if ((0xFFFFFFFF - (timer->xTimeOut - timer->xTicksToWait) + SecondTickNow + 1) >= timer->xTicksToWait) {
		return true;
	}
	else {
		return false;
	}
}


#ifdef  USE_FULL_ASSERT
/**********************************************************************************************************
 @Function			void assert_failed(uint8_t* file, uint32_t line)
 @Description			当编译提示出错的时候此函数用来报告错误的文件和所在行
 @Input				file		: 指向源文件
					line		: 指向在文件中的行数
 @Return				void
**********************************************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
	while (1)
	{
	}
}
#endif

/**********************************************************************************************************
 @Function			u8 Stm32_Get_ICahceSta(void)
 @Description			判断I_Cache是否打开
 @Input				void
 @Return				0		: 关闭
					1		: 打开
**********************************************************************************************************/
u8 Stm32_Get_ICahceSta(void)
{
	u8 sta;
	
	sta = ((SCB->CCR)>>17)&0X01;
	
	return sta;
}

/**********************************************************************************************************
 @Function			u8 Stm32_Get_DCahceSta(void)
 @Description			判断D_Cache是否打开
 @Input				void
 @Return				0		: 关闭
					1		: 打开
**********************************************************************************************************/
u8 Stm32_Get_DCahceSta(void)
{
	u8 sta;
	
	sta = ((SCB->CCR)>>16)&0X01;
	
	return sta;
}

/**********************************************************************************************************
	THUMB指令不支持汇编内联
	采用如下方法实现
**********************************************************************************************************/
/**********************************************************************************************************
 @Function			__asm void WFI_SET(void)
 @Description			执行汇编指令WFI
 @Input				void
 @Return				void
**********************************************************************************************************/
__asm void WFI_SET(void)
{
	WFI;
}

/**********************************************************************************************************
 @Function			__asm void INTX_DISABLE(void)
 @Description			关闭所有中断(但是不包括fault和NMI中断)
 @Input				void
 @Return				void
**********************************************************************************************************/
__asm void INTX_DISABLE(void)
{
	CPSID	I
	BX		LR
}

/**********************************************************************************************************
 @Function			__asm void INTX_ENABLE(void)
 @Description			开启所有中断
 @Input				void
 @Return				void
**********************************************************************************************************/
__asm void INTX_ENABLE(void)
{
	CPSIE	I
	BX		LR
}

/**********************************************************************************************************
 @Function			__asm void MSR_MSP(u32 addr)
 @Description			设置栈顶地址
 @Input				addr			: 栈顶地址
 @Return				void
**********************************************************************************************************/
__asm void MSR_MSP(u32 addr)
{
	MSR	MSP,	r0
	BX	r14
}

/********************************************** END OF FLEE **********************************************/
