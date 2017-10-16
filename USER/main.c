#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
# include "robot.h"
# include "key.h"

uint32_t SysCount = 0;
int main(void)
{ 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);		  // 延时初始化
	LED_Init();		        // LED初始化
//	KEY_Config();
//	uart_init(115200);    //串口初始化
	uart_init(115200);
//	robot_Config();
//	LED0 = 1;
//	LED1 = 1;
//	LED2 = 1;
		robot_RangingConfig();
		robot_PhotoelectricConfig();
//		robot_MotorConfig();
// 	robot_UpPlatform();
	
	while(1)
	{
//		SysCount ++;
//		if(SysCount % 5 == 0)
//			robot_DataReport();
			LED1 = ~LED1;
	delay_ms(200);
//		LED0 = ~LED0;
robot_DebugRanging();
		robot_DebugGray();
		robot_DebugPho();
//		printf("sndifsd\r\n");
	//robot_Detect();

	}
}





