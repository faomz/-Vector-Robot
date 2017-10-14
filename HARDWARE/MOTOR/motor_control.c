# include "motor.h"
# include "delay.h"
# include "bsp_adc.h"
# include "led.h"
# include "LobotServoController.h"
# include "key.h"
Robot_Dev Robot;
extern int EdgeTime;
void MOTOR_Control_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB, ENABLE); //
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1); //
	GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9);
}

void MOTOR_Config(void)
{
	uint8_t key = 0x00;
	MOTOR_Control_Config();
	MOTOR_PWM_Config();
	
	Robot.dirction = POSITIVE;		//
	Robot.M1_Dirction = POSITIVE;
	Robot.M2_Dirction = POSITIVE;
	Robot.M1_pwm = 200;
	Robot.M2_pwm = 200;
	Robot.IsChess = 0;
	Robot.IsEdge = 0;
	Robot.HandDirction = 0x00; //双手垂直下放
	
//	while(key == 0x00 || key == 0x02)
//	{
//		key == KEY_Scan();
//		delay_ms(20);
//		LED2 = ~LED2;
//	}
//	if(key == 0x01)
		Robot.RobotMode = CHESS_MODE;
//	else if(key == 0x03)
//		Robot.RobotMode = ATTACK_MODE;
	//Robot.
	if(Robot.RobotMode == CHESS_MODE)
		Robot.ModeSpeed = 200;
	else if(Robot.RobotMode == ATTACK_MODE)
		Robot.ModeSpeed = 400;
}

void Motor_SetDirction(void)
{
	switch(Robot.M1_Dirction)
	{
		case POSITIVE:M1_Ahead();break;
		case NEGETIVE:M1_Backward();break;
	}
	
	switch(Robot.M2_Dirction)
	{
		case POSITIVE:M2_Ahead();break;
		case NEGETIVE:M2_Backward();break;
	}
}

void Motor_SwitchDirction()
{
	//if()
}
//左前方出界
void Front_Left_Out(void)
{
	Robot.dirction = NEGETIVE;
	Robot.M1_Dirction = NEGETIVE;
	Robot.M2_Dirction = NEGETIVE;
	if(Robot.RobotMode == ATTACK_MODE)
	{
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 380;
		Motor_Move();
		delay_ms(100);
	}else if(Robot.RobotMode == CHESS_MODE)
	{
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 100;
		Motor_Move();
		delay_ms(400);
	}
}


//右前方出界
void Front_Right_Out(void)
{
	Robot.dirction = NEGETIVE;
	Robot.M1_Dirction = NEGETIVE;
	Robot.M2_Dirction = NEGETIVE;
	
	if(Robot.RobotMode == ATTACK_MODE)
	{
		Robot.M1_pwm = 380;
		Robot.M2_pwm = 400;
		Motor_Move();
		delay_ms(100);
	}else if(Robot.RobotMode == CHESS_MODE)
	{
		Robot.M1_pwm = 100;
		Robot.M2_pwm = 400;
		Motor_Move();
		delay_ms(400);
	}
}
//左后方出界
void Back_Left_Out(void)
{
	Robot.dirction = POSITIVE;
	Robot.M1_Dirction = POSITIVE;
	Robot.M2_Dirction = POSITIVE;
	if(Robot.RobotMode == ATTACK_MODE)
	{
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 380;
		Motor_Move();
		delay_ms(100);
	}else if(Robot.RobotMode == CHESS_MODE)
	{
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 100;
		Motor_Move();
		delay_ms(400);
	}
}

//右后方出界
void Back_Right_Out(void)
{
	Robot.dirction = POSITIVE;
	Robot.M1_Dirction = POSITIVE;
	Robot.M2_Dirction = POSITIVE;
	if(Robot.RobotMode == ATTACK_MODE)
	{
		Robot.M1_pwm = 380;
		Robot.M2_pwm = 400;
		Motor_Move();
		delay_ms(100);
	}else if(Robot.RobotMode == CHESS_MODE)
	{
		Robot.M1_pwm = 100;
		Robot.M2_pwm = 400;
		Motor_Move();
		delay_ms(400);
	}
}


void Up_Platform(void)
{
	runActionGroup(0,1);
	while((ADC1ConvValue[2]>>4) < 130 || (ADC1ConvValue[7]>>4) <130)
	{
		LED0 = ~LED0;
		LED1 = ~LED1;
		LED2 = ~LED2;
		delay_ms(100);
	}
	Robot.M1_pwm = 340;
	Robot.M2_pwm = 300;
	Motor_Move();
	delay_ms(1000);
	runActionGroup(1,1);
	Robot.M2_pwm = 240;
	Robot.M1_pwm = 200;
}
void Motor_Move(void)
{
	Motor_SetDirction();
	
	TIM_SetCompare2(TIM4, Robot.M1_pwm);

	
	TIM_SetCompare1(TIM4, Robot.M2_pwm);
}

