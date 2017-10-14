# include "robot.h"


uint16_t ADC1ConvValue[ROBOT_RANG_COUNT];
uint8_t flag = 0x00;
uint16_t EdgeTime = 0x0000;
extern uint16_t ADC1ConvValue[ROBOT_RANG_COUNT];

void robot_Detect(void)
{
	robot_EgdeDetect();
//	if(!Robot.IsEdge)
//		robot_PeriDetect();
}





uint8_t IsPhoDetected(uint8_t PhoId)
{
	uint8_t result = 0x00;
	switch(PhoId)
	{
		case ROBOT_PHO_A:result = PCin(4);break;
		case ROBOT_PHO_B:result = PFin(13);break;
		case ROBOT_PHO_C:result = PEin(3);break;
		case ROBOT_PHO_D:result = PCin(2);break;
	
//	  case ROBOT_PHO_H:result = PCin(3);break;
//		case ROBOT_PHO_I:result = PCin(1);break;
//		case ROBOT_PHO_J:result = PCin(0);break;
//		case ROBOT_PHO_K:result = PEin(6);break;
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
*                                          
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

//	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_H_GPIO_PIN;
//	GPIO_Init(ROBOT_PHO_H_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_SetBits(ROBOT_PHO_H_GPIO_PORT, ROBOT_PHO_H_GPIO_PIN);

//	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_I_GPIO_PIN;
//	GPIO_Init(ROBOT_PHO_I_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_SetBits(ROBOT_PHO_I_GPIO_PORT, ROBOT_PHO_I_GPIO_PIN);

//	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_J_GPIO_PIN;
//	GPIO_Init(ROBOT_PHO_J_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_SetBits(ROBOT_PHO_J_GPIO_PORT, ROBOT_PHO_J_GPIO_PIN);

//	GPIO_InitStructure.GPIO_Pin = ROBOT_PHO_K_GPIO_PIN;
//	GPIO_Init(ROBOT_PHO_K_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_SetBits(ROBOT_PHO_K_GPIO_PORT, ROBOT_PHO_K_GPIO_PIN);
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
	if(IsRangDetected(ROBOT_RANG_B)  && !Robot.IsChess ) //??????????,?????????????
	{
//		if(Robot.dirction == NEGETIVE)  //??????
//		{
			Robot.dirction = POSITIVE;  //??????
			Robot.M1_Dirction = POSITIVE; //??????
			Robot.M2_Dirction = POSITIVE; //??????
//		}

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
		//???????????????
		Robot.IsChess = 1;  //???????
		Robot.M1_pwm = Robot.ModeSpeed;
		Robot.M2_pwm = Robot.ModeSpeed;
		robot_MotorMove(200);
	}else if(IsRangDetected(ROBOT_RANG_J) && !Robot.IsChess) //??????????
	{
		if(Robot.dirction == POSITIVE) //??????
		{
			Robot.M1_Dirction = NEGETIVE; //??????
			Robot.M2_Dirction = NEGETIVE; //
			Robot.dirction = NEGETIVE;  //
		}else
		{
			Robot.M1_Dirction = NEGETIVE; //??????
			Robot.M2_Dirction = NEGETIVE; //
			Robot.dirction = NEGETIVE;  //
		}

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
		Robot.M1_pwm = Robot.ModeSpeed;
		Robot.M2_pwm = Robot.ModeSpeed;
		robot_MotorMove(200);
		Robot.IsChess = 1;
	//	return;
	}else	if(IsRangDetected(ROBOT_RANG_A) && !Robot.IsChess)  //??????????,?????????????
	{
		Robot.IsChess = 1;  //???????
		if(Robot.dirction == NEGETIVE)  //??????
		{
			Robot.dirction = POSITIVE;
			Robot.M1_Dirction = NEGETIVE;
			Robot.M2_Dirction = POSITIVE; //??????
		}else  //??????
		{
			Robot.dirction = POSITIVE;
			Robot.M1_Dirction = NEGETIVE;
			Robot.M2_Dirction = POSITIVE;
		}
//		Robot.dirction = POSITIVE;
		Robot.M1_pwm = 400;  //
		Robot.M2_pwm = 400;  //??????,??????
		
		robot_MotorMove(200);
	}else if(IsRangDetected(ROBOT_RANG_H) && !Robot.IsChess) //?????????
	{
		if(Robot.dirction == POSITIVE) //??????
		{ 
//			Robot.dirction = NEGETIVE;  //?????,????????????
			Robot.M2_Dirction = POSITIVE;
			Robot.M1_Dirction = NEGETIVE;//??????,????
		}else  //??????
		{
			Robot.dirction = POSITIVE;//????????????
			Robot.M1_Dirction = NEGETIVE;
			Robot.M2_Dirction = POSITIVE;//
		}
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(400);
		Robot.IsChess = 1;
	}else if(IsRangDetected(ROBOT_RANG_I) && !Robot.IsChess) //??????????
	{
		if(Robot.dirction == POSITIVE)//??????,
		{
			Robot.dirction = NEGETIVE; //??????
			Robot.M1_Dirction = POSITIVE;
			Robot.M2_Dirction = NEGETIVE;//????
		}else //??????
		{
//			Robot.dirction = NEGETIVE;
			Robot.M1_Dirction = POSITIVE;
			Robot.M2_Dirction = NEGETIVE;
		}
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		
		robot_MotorMove(150);
		Robot.IsChess = 1;
	}else if(IsRangDetected(ROBOT_RANG_K) && !Robot.IsChess)	//????????????
	{
		if(Robot.dirction == POSITIVE) //??????,??????
		{
			Robot.dirction = NEGETIVE; //????????
			Robot.M1_Dirction = NEGETIVE;//??????,??
			Robot.M2_Dirction = POSITIVE;
		}else //??????
		{
			Robot.M1_Dirction = NEGETIVE;
			Robot.M2_Dirction = POSITIVE;
		}
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		robot_MotorMove(150);
		Robot.IsChess = 1;
	}else if(IsRangDetected(ROBOT_RANG_D) && !Robot.IsChess) //?????????
	{
		Robot.IsChess = 1;
		if(Robot.dirction == NEGETIVE) //????
		{
			Robot.dirction = POSITIVE; //?????????
			Robot.M1_Dirction = POSITIVE; //??????
			Robot.M2_Dirction = NEGETIVE;//??????
		}else  //????
		{
			Robot.dirction = POSITIVE; //???????????
			Robot.M2_Dirction = NEGETIVE;//??????
			Robot.M1_Dirction = POSITIVE; //??????
		}
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(400);
		Robot.IsChess = 1;
	}else if(IsRangDetected(ROBOT_RANG_C) && !Robot.IsChess)  //??????????
	{
		Robot.IsChess = 1;
		if(Robot.dirction == POSITIVE) //??????
		{
			Robot.M1_Dirction = POSITIVE;
			Robot.M2_Dirction = NEGETIVE; //??????,??
		}else  //??????
		{
			Robot.dirction = POSITIVE; //????????
			Robot.M1_Dirction = POSITIVE;  //??????
			Robot.M2_Dirction = NEGETIVE; //??????,??
		}
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(150);
	}else  //??????????
	{
		//?????????
		Robot.M1_Dirction = Robot.M2_Dirction = Robot.dirction;
//		if(Robot.HandDirction == 0x01)
//			runActionGroup(3,1);
//		else if(Robot.HandDirction == 0x02)
//			runActionGroup(5,1);
		Robot.HandDirction = 0x00;
		Robot.IsChess = 0;//????????
		return;
	}
}


static uint32_t SpeedCount = 0;
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
void robot_EgdeDetect(void)
{
	if(IsPhoDetected(ROBOT_PHO_A))  //如果左前方出界
	{
			robot_OutOfBounds(FRONT_LEFT);  //执行回程函数
			if(flag != 0x01)  //
			{
				EdgeTime++;
				flag |= 0x01;
			}
	}else if(IsPhoDetected(ROBOT_PHO_B))  //如果右前方出界
	{
			robot_OutOfBounds(FRONT_RIGHT);  //右前方出界
			if(flag != 0x02)  //
			{
				EdgeTime++;
				flag |= 0x02;
			}
	}else if(IsPhoDetected(ROBOT_PHO_C))  //如果左后方出界
	{
			robot_OutOfBounds(BACK_LEFT);  //
			if(flag != 0x03)  //
			{
				EdgeTime++;
				flag |= 0x03;
			}
	}	else if(IsPhoDetected(ROBOT_PHO_D))		//如果右后方出界
	{		
			robot_OutOfBounds(BACK_RIGHT);  //
			if(flag != 0x01)  //
			{
				EdgeTime++;
				flag |= 0x01;
			}
	}else  //没有出界
	{
		Robot.M1_pwm = 200;
		Robot.M2_pwm = 200;
		robot_MotorMove(0);  //
		Robot.IsEdge = 0;  //
		flag = 0x00;  //
	}
}

