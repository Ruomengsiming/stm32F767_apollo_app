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

/****************************************** Select DEBUG *************************************************/
#define DEVICE_DEBUG		0											//定义开启设备调试
/********************************************* DEBUG *****************************************************/
#if DEVICE_DEBUG

void DeBugMain(void);
#endif
/****************************************** Debug Ending *************************************************/

/****************************************** FreeRTOS TASK ************************************************/
#define START_TASK_PRIO		1											//任务优先级
#define START_STK_SIZE 		128											//任务堆栈大小
TaskHandle_t				StartTask_Handler;								//任务句柄
void start_task(void *pvParameters);										//任务函数

#define LED0_TASK_PRIO		2											//任务优先级
#define LED0_STK_SIZE 		50											//任务堆栈大小
TaskHandle_t				LED0Task_Handler;								//任务句柄
void led0_task(void *pvParameters);										//任务函数

#define LED1_TASK_PRIO		3											//任务优先级
#define LED1_STK_SIZE 		50											//任务堆栈大小
TaskHandle_t				LED1Task_Handler;								//任务句柄
void led1_task(void *pvParameters);										//任务函数

#define PRINT1_TASK_PRIO		4											//任务优先级
#define PRINT1_STK_SIZE 		128											//任务堆栈大小
TaskHandle_t				PRINT1Task_Handler;								//任务句柄
void print1_task(void *pvParameters);										//任务函数

#define PRINT2_TASK_PRIO		5											//任务优先级
#define PRINT2_STK_SIZE		128											//任务堆栈大小
TaskHandle_t				PRINT2Task_Handler;								//任务句柄
void print2_task(void *pvParameters);										//任务函数
/****************************************** FreeRTOS Ending **********************************************/

/****************************************** Static Code **************************************************/
static const char *pcTextForTask1 = "Print Task 1 is running\r\n";
static const char *pcTextForTask2 = "Print Task 2 is running\r\n";
static const u8 PwmindexWave[] = {1,1,2,2,3,4,6,8,10,14,19,25,33,44,59,80,107,143,191,255,255,191,143,107,80,59,44,33,25,19,14,10,8,6,4,3,2,2,1,1};
/****************************************** Static Ending ************************************************/

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
#if 0
	IWDG_Init(IWDG_PRESCALER_64, 1000);									//初始化独立看门狗溢出时间2S
	WWDG_Init(0x7F, 0x5F, WWDG_PRESCALER_8);								//初始化窗口看门狗
#endif
	Uart1_Init(9600);													//初始化串口1波特率9600
	Uart2_Init(9600);													//初始化串口2波特率9600
	Uart3_Init(9600);													//初始化串口3波特率9600
#if 0
	LED_Init();														//初始化LED
	KEY_Init();														//初始化KEY
	EXTI_Init();														//初始化EXTI
	TIM3_PWM_Init(500-1, 108-1);											//初始化TIM3周期500US
	TIM4_BASE_Init(5000-1, 10800-1);										//初始化TIM4周期500MS
#else
	LED_Init();														//初始化LED
	TIM3_PWM_Init(500-1, 108-1);											//初始化TIM3周期500US
#endif
	
	/* 创建开始任务 */
	xTaskCreate( (TaskFunction_t )start_task,								//任务函数
			   (const char*    )"start_task",								//任务名称
			   (uint16_t       )START_STK_SIZE,							//任务堆栈大小
			   (void*          )NULL,									//传递给任务函数的参数
			   (UBaseType_t    )START_TASK_PRIO,							//任务优先级
			   (TaskHandle_t*  )&StartTask_Handler );						//任务句柄
	
	vTaskStartScheduler();												//开启任务调度
	
	while (true);
	
#if 0
	while (true) {
		
#if DEVICE_DEBUG
		DeBugMain();
#endif
		
		
		IWDG_Feed();
		
		Delay_MS(1000);
	}
#endif
}

/**********************************************************************************************************
 @Function			void start_task(void *pvParameters)
 @Description			start_task			: 开始任务任务函数
 @Input				pvParameters
 @Return				void
**********************************************************************************************************/
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();												//进入临界区
	
	/* 创建LED0任务 */
	xTaskCreate( (TaskFunction_t )led0_task,								//任务函数
			   (const char*    )"led0_task",								//任务名称
			   (uint16_t       )LED0_STK_SIZE,								//任务堆栈大小
			   (void*          )NULL,									//传递给任务函数的参数
			   (UBaseType_t    )LED0_TASK_PRIO,							//任务优先级
			   (TaskHandle_t*  )&LED0Task_Handler );						//任务句柄
	
	/* 创建LED1任务 */
	xTaskCreate( (TaskFunction_t )led1_task,								//任务函数
			   (const char*    )"led1_task",								//任务名称
			   (uint16_t       )LED1_STK_SIZE,								//任务堆栈大小
			   (void*          )NULL,									//传递给任务函数的参数
			   (UBaseType_t    )LED1_TASK_PRIO,							//任务优先级
			   (TaskHandle_t*  )&LED1Task_Handler );						//任务句柄
	
	/* 创建Print1任务 */
	xTaskCreate( (TaskFunction_t )print1_task,								//任务函数
			   (const char*    )"print1_task",								//任务名称
			   (uint16_t       )PRINT1_STK_SIZE,							//任务堆栈大小
			   (void*          )pcTextForTask1,							//传递给任务函数的参数
			   (UBaseType_t    )PRINT1_TASK_PRIO,							//任务优先级
			   (TaskHandle_t*  )&PRINT1Task_Handler );						//任务句柄
	
	/* 创建Print2任务 */
	xTaskCreate( (TaskFunction_t )print2_task,								//任务函数
			   (const char*    )"print2_task",								//任务名称
			   (uint16_t       )PRINT2_STK_SIZE,							//任务堆栈大小
			   (void*          )pcTextForTask2,							//传递给任务函数的参数
			   (UBaseType_t    )PRINT2_TASK_PRIO,							//任务优先级
			   (TaskHandle_t*  )&PRINT2Task_Handler );						//任务句柄
	
	vTaskDelete(StartTask_Handler);										//删除开始任务
	
	taskEXIT_CRITICAL();												//退出临界区
}

/**********************************************************************************************************
 @Function			void led0_task(void *pvParameters)
 @Description			led0_task				: LED0任务函数
 @Input				pvParameters
 @Return				void
**********************************************************************************************************/
void led0_task(void *pvParameters)
{
	u8 led0dir = 1;
	u16 led0pwmval = 0;
	
	while (true) {
		vTaskDelay(80 / portTICK_RATE_MS);
		
		if (led0dir) led0pwmval++;
		else led0pwmval--;
		
		if (led0pwmval >= 40) led0dir = 0;
		else if (led0pwmval == 0) led0dir = 1;
		
		TIM3_SetCH4Compare(PwmindexWave[led0pwmval]);
	}
	
#if 0
	while (true) {
		LED0_Toggle();
		vTaskDelay(500 / portTICK_RATE_MS);
	}
#endif
}

/**********************************************************************************************************
 @Function			void led1_task(void *pvParameters)
 @Description			led1_task				: LED1任务函数
 @Input				pvParameters
 @Return				void
**********************************************************************************************************/
void led1_task(void *pvParameters)
{
	u8 led1dir = 1;
	u16 led1pwmval = 0;
	
	while (true) {
		vTaskDelay(50 / portTICK_RATE_MS);
		
		if (led1dir) led1pwmval++;
		else led1pwmval--;
		
		if (led1pwmval >= 40) led1dir = 0;
		else if (led1pwmval == 0) led1dir = 1;
		
		TIM3_SetCH3Compare(PwmindexWave[led1pwmval]);
	}
	
#if 0
	while (true) {
		LED1(ON);
		vTaskDelay(200 / portTICK_RATE_MS);
		LED1(OFF);
		vTaskDelay(800 / portTICK_RATE_MS);
	}
#endif
}

/**********************************************************************************************************
 @Function			void print1_task(void *pvParameters)
 @Description			print1_task			: Print1任务函数
 @Input				pvParameters
 @Return				void
**********************************************************************************************************/
void print1_task(void *pvParameters)
{
	char *pcTaskName = (char *)pvParameters;
	
	while (true) {
		printf("%s", pcTaskName);
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

/**********************************************************************************************************
 @Function			void print2_task(void *pvParameters)
 @Description			print2_task			: Print2任务函数
 @Input				pvParameters
 @Return				void
**********************************************************************************************************/
void print2_task(void *pvParameters)
{
	char *pcTaskName = (char *)pvParameters;
	
	while (true) {
		printf("%s", pcTaskName);
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}


#if DEVICE_DEBUG
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
#if 0
	Stm32_CalculagraphTypeDef CalTimer;
	u8 key;
	u8 led0sta = OFF, led1sta = OFF;
#endif
	
	while (true) {
		
#if 0
		key = KEY_Scan(false);
		if (key) {
			switch (key)
			{
				case KEY0_PRES :
					led0sta = !led0sta;
					led1sta = !led1sta;
					break;
				case KEY1_PRES :
					led0sta = !led0sta;
					break;
				case KEY2_PRES :
					led1sta = !led1sta;
					break;
				case WKUP_PRES :
					led0sta = !led1sta;
					led1sta = !led1sta;
					break;
			}
			LED0(led0sta);
			LED1(led1sta);
		}
		else Delay_MS(10);
#endif
		
#if 0
		Stm32_Calculagraph_CountdownSec(&CalTimer, 1);
		while (Stm32_Calculagraph_IsExpiredSec(&CalTimer) != true);
		
		for (int i = 0; i < 6; i++) {
			LED0_Toggle();
			LED1_Toggle();
		
			Delay_MS(200);
		}
		
		printf("Hello World!\n");
#endif
		
#if 0
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
#endif
		
		IWDG_Feed();
		
		Delay_MS(1000);
	}
}
#endif

/********************************************** END OF FLEE **********************************************/
