/**
  *********************************************************************************************************
  * @file    main.c
  * @author  Yunjie-K
  * @version V1.0
  * @date    2018-04-23
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "main.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "hal_led.h"

/****************************************** Select DEBUG *************************************************/
//#define	DEVICE_DEBUG													//定义开启设备调试
/********************************************* DEBUG *****************************************************/
#ifdef	DEVICE_DEBUG

void DeBugMain(void);
#endif
/****************************************** Debug Ending *************************************************/

/**********************************************************************************************************
 @Function			int main(void)
 @Description			Main
 @Input				void
 @Return				int
**********************************************************************************************************/
int main(void)
{
	Stm32_Cache_Enable();												//打开L1-Cache
	HAL_Init();														//初始化HAL库
	Stm32_Clock_Init(432, 25, 2, 9);										//初始化时钟216Mhz 
	Delay_Init(216);													//初始化延时
	
	Uart1_Init(9600);													//初始化串口1波特率9600
	Uart2_Init(9600);													//初始化串口2波特率9600
	Uart3_Init(9600);													//初始化串口3波特率9600
	
	LED_Init();														//初始化LED
	
	while (1) {
		
#ifdef	DEVICE_DEBUG
		DeBugMain();
#endif
		
		
		
		Delay_MS(1000);
		
	}
}

#ifdef	DEVICE_DEBUG
/********************************************* DEBUG *****************************************************/

/****************************************** Debug Ending *************************************************/
/**********************************************************************************************************
 @Function			void DeBugMain(void)
 @Description			DeBugMain
 @Input				void
 @Return				void
**********************************************************************************************************/
void DeBugMain(void)
{
	Stm32_CalculagraphTypeDef CalTimer;
	
	while (1) {
		
		Stm32_Calculagraph_CountdownSec(&CalTimer, 1);
		while (Stm32_Calculagraph_IsExpiredSec(&CalTimer) != true);
		
		for (int i = 0; i < 6; i++) {
			LED0_Toggle();
			LED1_Toggle();
		
			Delay_MS(200);
		}
		
		Uart1_PortSerialEnable(DISABLE, DISABLE);
		if (USART1_RX_STA & 0x8000) {
			printf("RecvData : %s\n", USART1_RX_BUF);
			memset((void*)USART1_RX_BUF, 0x00, sizeof(USART1_RX_BUF));
			USART1_RX_STA = 0;
		}
		Uart1_PortSerialEnable(ENABLE, DISABLE);
		
		Uart2_PortSerialEnable(DISABLE, DISABLE);
		if (USART2_RX_STA & 0x8000) {
			printf("RecvData : %s\n", USART2_RX_BUF);
			memset((void*)USART2_RX_BUF, 0x00, sizeof(USART2_RX_BUF));
			USART2_RX_STA = 0;
		}
		Uart2_PortSerialEnable(ENABLE, DISABLE);
		
		Uart3_PortSerialEnable(DISABLE, DISABLE);
		if (USART3_RX_STA & 0x8000) {
			printf("RecvData : %s\n", USART3_RX_BUF);
			memset((void*)USART3_RX_BUF, 0x00, sizeof(USART3_RX_BUF));
			USART3_RX_STA = 0;
		}
		Uart3_PortSerialEnable(ENABLE, DISABLE);
		
	}
}
#endif

/********************************************** END OF FLEE **********************************************/
