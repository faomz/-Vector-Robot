#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
# include "robot.h"
# include "key.h"

//uint32_t count = 0;
int main(void)
{ 
	delay_init(168);		  // 延时初始化
	LED_Init();		        // LED初始化
//	KEY_Config();
	uart_init(115200);    //串口初始化
//	robot_Config();
	LED1 = 1;
	delay_ms(500);
	LED1 = 0;
		robot_RangingConfig();
		robot_PhotoelectricConfig();
		robot_MotorConfig();
// 	robot_UpPlatform();
	
	while(1)
	{
		LED0 = ~LED0;
//		robot_DebugRanging();
////		robot_DebugGray();
//		robot_DebugPho();
//		delay_ms(500);
//		
		
	robot_EgdeDetect();
//	if(!Robot.IsEdge)
	//	robot_PeriDetect();
		
	}
}





