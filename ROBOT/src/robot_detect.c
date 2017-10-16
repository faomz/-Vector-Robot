# include "robot.h"


uint16_t ADC1ConvValue[ROBOT_RANG_COUNT];
uint8_t flag = 0x00;
uint16_t EdgeTime = 0x0000;
extern uint16_t ADC1ConvValue[ROBOT_RANG_COUNT];

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
void robot_Detect(void)
{
	robot_EgdeDetect();
# if DEBUG_PERI_DETECT > 0u
	if(!Robot.IsEdge)
		robot_PeriDetect();
# endif
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
uint8_t IsPhoDetected(uint8_t PhoId)
{
	uint8_t result = 0x00;
	switch(PhoId)
	{
		case ROBOT_PHO_A:result = PCin(5);break;
		case ROBOT_PHO_B:result = PCin(4);break;
		case ROBOT_PHO_C:result = PBin(1);break;
		case ROBOT_PHO_D:result = PBin(0);break;
		case ROBOT_PHO_E:result = PFin(12);break;
	
	  case ROBOT_PHO_H:result = PCin(3);break;
		case ROBOT_PHO_I:result = PCin(1);break;
		case ROBOT_PHO_J:result = PCin(0);break;
		case ROBOT_PHO_K:result = PEin(6);break;
		case ROBOT_PHO_L:result = PEin(5);break;
		default:break;
	}
	return result;
}

//uint8_t IsRangDetected(uint8_t RangId)
//{
//	return (((ADC1ConvValue[RangId]>>4) > DISTANCE)?1:0);
//}

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
void robot_DetectConfig(void)
{
	robot_RangingConfig();
	robot_PhotoelectricConfig();
}

/*
*********************************************************************************************************
*                                      robot_PhotoelectricConfig    
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_PhotoelectricConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(ROBOT_PHO_RCC_ALL, ENABLE); //
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_A_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_A_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_A_GPIO_PORT, ROBOT_PHO_A_GPIO_PIN);
	
	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_B_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_B_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_B_GPIO_PORT, ROBOT_PHO_B_GPIO_PIN);

	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_C_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_C_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_C_GPIO_PORT, ROBOT_PHO_C_GPIO_PIN);

	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_D_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_D_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_D_GPIO_PORT, ROBOT_PHO_D_GPIO_PIN);
	
	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_E_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_E_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_E_GPIO_PORT, ROBOT_PHO_E_GPIO_PIN);

	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_H_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_H_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_H_GPIO_PORT, ROBOT_PHO_H_GPIO_PIN);

	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_I_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_I_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_I_GPIO_PORT, ROBOT_PHO_I_GPIO_PIN);

	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_J_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_J_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_J_GPIO_PORT, ROBOT_PHO_J_GPIO_PIN);

	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_K_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_K_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_K_GPIO_PORT, ROBOT_PHO_K_GPIO_PIN);
	
	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_L_GPIO_PIN;
	GPIO_Init(ROBOT_PHO_L_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(ROBOT_PHO_L_GPIO_PORT, ROBOT_PHO_L_GPIO_PIN);
}

/*
*********************************************************************************************************
*                                         robot_RangingConfig 
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_RangingConfig(void)
{	
	robot_PhoADC_GPIOConfig();
	robot_PhoADC_CHConfig();
	robot_PhoADC_DMAConfig();
	robot_PhoADC_TIMConfig();
}



/*
*********************************************************************************************************
*                                          robot_PeriDetect
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_PeriDetect(void)
{
# if DEBUG_RANG_FRONT > 0u
	if(IsRangDetected(ROBOT_RANG_B)) /* 如果机器人正前方检测到目标 */
	{
		/* 不管上个时刻机器人方向如何，改变为正方向 */
		Robot.dirction = POSITIVE;  
		Robot.M1_Dirction = POSITIVE; 
		Robot.M2_Dirction = POSITIVE; 

//		if(Robot.RobotMode == ATTACK_MODE)
//		{
//			if(Robot.dirction == POSITIVE)
//			{
//				runActionGroup(2,1);
//				Robot.HandDirction = 0x01;
//			}
//			else 
//			{
//				runActionGroup(4,1);
//				Robot.HandDirction = 0x02;
//			}
//		}
		/*  设置电机转动速度为机器人模式速度 */
		Robot.M1_pwm = Robot.ModeSpeed;
		Robot.M2_pwm = Robot.ModeSpeed;
		robot_MotorMove(400);
	}else 
# endif
# if DEBUG_RANG_BACK > 0u
	if(IsRangDetected(ROBOT_RANG_J))   /* 如果机器人正后方检测到目标 */
	{
		/* 无论机器人上个时刻方向如何，改变为负方向 */
		Robot.dirction = NEGETIVE; 
		Robot.M1_Dirction = NEGETIVE; 
		Robot.M2_Dirction = NEGETIVE;  
		
//			if(Robot.dirction == POSITIVE)
//			{
//				runActionGroup(2,1);
//				Robot.HandDirction = 0x01;
//			}
//			else 
//			{
//				runActionGroup(4,1);
//				Robot.HandDirction = 0x02;
//			}
		/*  设置电机转动速度为机器人模式速度 */
		Robot.M1_pwm = Robot.ModeSpeed;
		Robot.M2_pwm = Robot.ModeSpeed;
		robot_MotorMove(400);
	}else	
# endif
# if DEBUG_RANG_FRONT_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_A))  /* 如果机器人左前方检测到目标  */
	{
		/* 不管机器人上一个时刻的方向如何，改变车子方向为正方向  */
		Robot.dirction = POSITIVE;
		/* 同时机器人转向目标方向，机器人需要逆时针转动 */
		Robot.M1_Dirction = NEGETIVE;   /* 左边电机反转 */
		Robot.M2_Dirction = POSITIVE;		/* 右边电机正转 */

		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 300;  
		Robot.M2_pwm = 300;  
		robot_MotorMove(150);
	}else 
# endif
# if DEBUG_RANG_FRONT_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_C))  /* 如果机器人右前方检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何，改变方向为正方向 */
		Robot.dirction = POSITIVE;
		
		/* 同时机器人转向目标方向，需要顺时针转动 */
		Robot.M1_Dirction = POSITIVE; /* 左边电机正转 */
		Robot.M2_Dirction = NEGETIVE; /* 右边电机反转 */
		
		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		robot_MotorMove(150);
	}else 
# endif
# if DEBUG_RANG_BACK_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_I)) /* 如果机器人左后方检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何,改变车子方向为负方向 */
		Robot.dirction = NEGETIVE;
		
		/* 机器人需要顺时针转动，左边电机正转，右边电机反转	*/
		Robot.M1_Dirction = POSITIVE;
		Robot.M2_Dirction = NEGETIVE;
		
		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(200);
	}else 
# endif
# if DEBUG_RANG_BACK_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_K)) /* 如果机器人右后方检测到目标 */
	{
		/* 不管机器人上一个时刻方向如何，设置方向为负方向	*/
		Robot.dirction = NEGETIVE;
		
		/* 同时机器人需要逆时针转动，转向目标方向 */
		Robot.M1_Dirction = NEGETIVE;  /* 左边电机反转 */
		Robot.M2_Dirction = POSITIVE;  /* 右边电机正转*/
		
		/* 设置机器人电机转动速度 */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		
		robot_MotorMove(200);
	}else 
# endif
# if DEBUG_RANG_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_H))	/* 如果机器人左边检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何，改变方向为正方向	*/
		Robot.dirction = POSITIVE;
		
		/* 同时机器人逆时针转动，使正方向朝向目标 */
		Robot.M1_Dirction = NEGETIVE; /* 左边电机反转 */
		Robot.M2_Dirction = POSITIVE; /* 右边电机正转 */	

		/* 设置电机转动速度 */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		robot_MotorMove(300);
	}else 
# endif
# if DEBUG_RANG_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_D)) /* 如果机器人右边检测到目标 */
	{
		/* 不管机器人上一个时刻的方向如何，改变方向为负方向	*/
		Robot.dirction = NEGETIVE;
		
		/* 同时机器人顺时针转动，使负方向朝向目标 */
		Robot.M1_Dirction = POSITIVE; /* 左边电机正转 */
		Robot.M2_Dirction = NEGETIVE; /* 右边电机反转 */	

		/* 设置电机转动速度 */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		robot_MotorMove(300);
	}else  /* 如果机器人周边都没有目标 */
# endif
	{
		/* 机器人保持当前行进方向 */
		Robot.M1_Dirction = Robot.M2_Dirction = Robot.dirction;

		/* 头部方向恢复初始值 */
		Robot.HandDirction = 0x00;
	}
}

//static uint32_t SpeedCount = 0;
/*
*********************************************************************************************************
*                                     robot_EgdeDetect     
*
* Description: 
*             
* Arguments : 
*
* Note(s)   : 
*********************************************************************************************************
*/
void robot_EgdeDetect(void)
{
	if(IsPhoDetected(ROBOT_PHO_A))  /* 如果左前方出界 */
	{
		Robot.IsEdge = FRONT_LEFT;
		robot_OutOfBounds(FRONT_LEFT);  /* 执行回程函数 */
//			if(flag != 0x01)  //
//			{
//				EdgeTime++;
//				flag |= 0x01;
//			}
	}else if(IsPhoDetected(ROBOT_PHO_B))  /* 如果右前方出界 */
	{
		Robot.IsEdge = FRONT_RIGHT;
		robot_OutOfBounds(FRONT_RIGHT);  /* 右前方出界 */
//			if(flag != 0x02)  //
//			{
//				EdgeTime++;
//				flag |= 0x02;
//			}
	}else if(IsPhoDetected(ROBOT_PHO_C))  /* 如果左后方出界 */
	{
		Robot.IsEdge = BACK_LEFT;
		robot_OutOfBounds(BACK_LEFT);  /* 左后方出界 */
//			if(flag != 0x03)  //
//			{
//				EdgeTime++;
//				flag |= 0x03;
//			}
	}	else if(IsPhoDetected(ROBOT_PHO_D))		/* 如果右后方出界 */
	{		
		Robot.IsEdge = BACK_RIGHT;
		robot_OutOfBounds(BACK_RIGHT);  /* 右后方出界 */
//			if(flag != 0x01)  //
//			{
//				EdgeTime++;
//				flag |= 0x01;
//			}
	}else  /* 没有出界 */
	{
		Robot.M1_pwm = 180;
		Robot.M2_pwm = 180;
		robot_MotorMove(0);  
		Robot.IsEdge = 0;  
	}
}

