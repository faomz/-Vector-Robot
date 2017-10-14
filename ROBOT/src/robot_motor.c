# include "robot.h"

/*
*********************************************************************************************************
*                                          robot_MotorConfig
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_MotorConfig(void)
{
	robot_MotorControlConfig();
	robot_MotorPWMConfig();
	robot_MotorStrConfig();
}

/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_MotorStrConfig(void)
{
//	uint8_t key = 0x00;
	
	Robot.dirction = POSITIVE;		//
	Robot.M1_Dirction = POSITIVE;
	Robot.M2_Dirction = POSITIVE;
	Robot.M1_pwm = 1000;
	Robot.M2_pwm = 500;
	Robot.IsChess = 0;
	Robot.IsEdge = 0;
	Robot.HandDirction = 0x00; //
	

		Robot.RobotMode = CHESS_MODE;
	if(Robot.RobotMode == CHESS_MODE)
		Robot.ModeSpeed = 260;
	else if(Robot.RobotMode == ATTACK_MODE)
		Robot.ModeSpeed = 400;
	
	robot_MotorMove(0);
}

/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_MotorPWMConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 6 - 1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 50;
	
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);	
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);	
	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_Cmd(TIM4,ENABLE);
}

/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_MotorControlConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB, ENABLE); //
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
//	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1); //
//	GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9);
}

/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_SetDirction(void)
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


/*
 *********************************************************************************************************
 *                                          
 *
 * Description: 
 *             
 * Arguments : 
 *
 * Note(s)   : 
 *********************************************************************************************************
 */						 
void robot_OutOfBounds(uint8_t RobotPos)
{
	switch(RobotPos)
	{
		case FRONT_LEFT:  /* 左前方出界 */
		{
			Robot.dirction = NEGETIVE;  /* 车子换向 */
			Robot.M1_Dirction = NEGETIVE; 
			Robot.M2_Dirction = NEGETIVE;
			if(Robot.RobotMode == ATTACK_MODE)  /*  攻击模式和推棋子模式的回退速度不一样 */
			{
				Robot.M1_pwm = 400;
				Robot.M2_pwm = 380;
				robot_MotorMove(100);
			}else if(Robot.RobotMode == CHESS_MODE)
			{
				Robot.M1_pwm = 300;
				Robot.M2_pwm = 300;
				robot_MotorMove(200);
				
				Robot.M2_Dirction = POSITIVE;
				robot_MotorMove(50);
			}
		}break;
		case FRONT_RIGHT:  /* 右前方出界 */
		{
			Robot.dirction = NEGETIVE;
			Robot.M1_Dirction = NEGETIVE;
			Robot.M2_Dirction = NEGETIVE;
			
			if(Robot.RobotMode == ATTACK_MODE)
			{
				Robot.M1_pwm = 380;
				Robot.M2_pwm = 400;
				robot_MotorMove(100);
			}else if(Robot.RobotMode == CHESS_MODE)
			{
				Robot.M1_pwm = 260;
				Robot.M2_pwm = 400;
				robot_MotorMove(200);
			}
		}break;
		case BACK_LEFT:
		{
			Robot.dirction = POSITIVE;
			Robot.M1_Dirction = POSITIVE;
			Robot.M2_Dirction = POSITIVE;
			if(Robot.RobotMode == ATTACK_MODE)
			{
				Robot.M1_pwm = 400;
				Robot.M2_pwm = 380;
				robot_MotorMove(100);
			}else if(Robot.RobotMode == CHESS_MODE)
			{
				Robot.M1_pwm = 400;
				Robot.M2_pwm = 260;
				robot_MotorMove(200);
			}
		}break;
		case BACK_RIGHT:
		{
			Robot.dirction = POSITIVE;
			Robot.M1_Dirction = POSITIVE;
			Robot.M2_Dirction = POSITIVE;
			if(Robot.RobotMode == ATTACK_MODE)
			{
				Robot.M1_pwm = 380;
				Robot.M2_pwm = 400;
				robot_MotorMove(100);
			}else if(Robot.RobotMode == CHESS_MODE)
			{
				Robot.M1_pwm = 260;
				Robot.M2_pwm = 400;
				robot_MotorMove(200);
			}
		}break;
		default:break;
	}
}


/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_UpPlatform(void)
{
	//	runActionGroup(0,1);
	while((ADC1ConvValue[2]>>4) < 130 || (ADC1ConvValue[7]>>4) <130)
	{
		LED0 = ~LED0;
		LED1 = ~LED1;
		LED2 = ~LED2;
		delay_ms(50);
	}
	Robot.M1_pwm = 340;
	Robot.M2_pwm = 300;
	robot_MotorMove(100);
//	runActionGroup(1,1);
	Robot.M2_pwm = 240;
	Robot.M1_pwm = 200;
}
/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_MotorMove(uint16_t time)
{	
	robot_SetDirction();
	
	TIM_SetCompare2(TIM4, Robot.M1_pwm);

	TIM_SetCompare1(TIM4, Robot.M2_pwm);
	
	if(time >0)
		delay_ms(time);
}


uint32_t count = 0x00;

/*
*********************************************************************************************************
*                                          
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_WaitChessFail(uint8_t ChessPos)
{
	switch(ChessPos)
	{
		case FRONT_LEFT:
		{
				if(IsRangDetected(ROBOT_RANG_A) || IsRangDetected(ROBOT_RANG_B) || IsRangDetected(ROBOT_RANG_C))//????????,????????????????
				{
					while(IsPhoDetected(ROBOT_PHO_C))//???????????
					{
						Robot.M1_Dirction = NEGETIVE;
						Robot.M2_Dirction = POSITIVE;
						Robot.dirction = POSITIVE;
						Robot.M1_pwm = 40;
						Robot.M2_pwm = 80;
						robot_MotorMove(10);
						
						count ++;
						if(count >40) //???????????????????,?????,?????
						{
							count = 0; break;
						}
					}
				}
		}break;
		case FRONT_RIGHT:
		{
				if(IsRangDetected(ROBOT_RANG_A) || IsRangDetected(ROBOT_RANG_B) || IsRangDetected(ROBOT_RANG_C))
				{
					while(!IsPhoDetected(ROBOT_PHO_A))
					{
						Robot.M1_Dirction = POSITIVE;
						Robot.M2_Dirction = NEGETIVE;
						Robot.dirction = POSITIVE;
						Robot.M1_pwm = 80;
						Robot.M2_pwm = 40;
						robot_MotorMove(10);
						
						count ++;
						if(count >40)
						{
							count = 0; break;
						}
					}
				}
		}break;
		case BACK_LEFT:
		{
				if(IsRangDetected(ROBOT_RANG_I) || IsRangDetected(ROBOT_RANG_J) || IsRangDetected(ROBOT_RANG_K))
				{
					while(!IsPhoDetected(ROBOT_PHO_J))
					{
						Robot.M2_Dirction = NEGETIVE;
						Robot.M1_Dirction = POSITIVE;
						Robot.dirction = NEGETIVE;
						Robot.M1_pwm = 40;
						Robot.M2_pwm = 80;
						robot_MotorMove(10);
						
						count ++;
						if(count >40)
						{
							count = 0; break;
						}
					}
				}
		}break;
		case BACK_RIGHT:
		{
				if(IsRangDetected(ROBOT_RANG_I) || IsRangDetected(ROBOT_RANG_J) || IsRangDetected(ROBOT_RANG_K))
				{
					while(!IsPhoDetected(ROBOT_PHO_H))
					{
						Robot.M2_Dirction = POSITIVE;
						Robot.M1_Dirction = NEGETIVE;
						Robot.dirction = NEGETIVE;
						Robot.M2_pwm = 40;
						Robot.M1_pwm = 80;
						robot_MotorMove(10);
						
						count ++;
						if(count >40)
						{
							count = 0; break;
						}
					}
				}
		}break;
		default:break;
	}
}

