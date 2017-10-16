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
	if(IsRangDetected(ROBOT_RANG_B)) /* �����������ǰ����⵽Ŀ�� */
	{
		/* �����ϸ�ʱ�̻����˷�����Σ��ı�Ϊ������ */
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
		/*  ���õ��ת���ٶ�Ϊ������ģʽ�ٶ� */
		Robot.M1_pwm = Robot.ModeSpeed;
		Robot.M2_pwm = Robot.ModeSpeed;
		robot_MotorMove(400);
	}else 
# endif
# if DEBUG_RANG_BACK > 0u
	if(IsRangDetected(ROBOT_RANG_J))   /* ������������󷽼�⵽Ŀ�� */
	{
		/* ���ۻ������ϸ�ʱ�̷�����Σ��ı�Ϊ������ */
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
		/*  ���õ��ת���ٶ�Ϊ������ģʽ�ٶ� */
		Robot.M1_pwm = Robot.ModeSpeed;
		Robot.M2_pwm = Robot.ModeSpeed;
		robot_MotorMove(400);
	}else	
# endif
# if DEBUG_RANG_FRONT_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_A))  /* �����������ǰ����⵽Ŀ��  */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䳵�ӷ���Ϊ������  */
		Robot.dirction = POSITIVE;
		/* ͬʱ������ת��Ŀ�귽�򣬻�������Ҫ��ʱ��ת�� */
		Robot.M1_Dirction = NEGETIVE;   /* ��ߵ����ת */
		Robot.M2_Dirction = POSITIVE;		/* �ұߵ����ת */

		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 300;  
		Robot.M2_pwm = 300;  
		robot_MotorMove(150);
	}else 
# endif
# if DEBUG_RANG_FRONT_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_C))  /* �����������ǰ����⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䷽��Ϊ������ */
		Robot.dirction = POSITIVE;
		
		/* ͬʱ������ת��Ŀ�귽����Ҫ˳ʱ��ת�� */
		Robot.M1_Dirction = POSITIVE; /* ��ߵ����ת */
		Robot.M2_Dirction = NEGETIVE; /* �ұߵ����ת */
		
		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		robot_MotorMove(150);
	}else 
# endif
# if DEBUG_RANG_BACK_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_I)) /* �����������󷽼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ������,�ı䳵�ӷ���Ϊ������ */
		Robot.dirction = NEGETIVE;
		
		/* ��������Ҫ˳ʱ��ת������ߵ����ת���ұߵ����ת	*/
		Robot.M1_Dirction = POSITIVE;
		Robot.M2_Dirction = NEGETIVE;
		
		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 400;
		Robot.M2_pwm = 400;
		robot_MotorMove(200);
	}else 
# endif
# if DEBUG_RANG_BACK_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_K)) /* ����������Һ󷽼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̷�����Σ����÷���Ϊ������	*/
		Robot.dirction = NEGETIVE;
		
		/* ͬʱ��������Ҫ��ʱ��ת����ת��Ŀ�귽�� */
		Robot.M1_Dirction = NEGETIVE;  /* ��ߵ����ת */
		Robot.M2_Dirction = POSITIVE;  /* �ұߵ����ת*/
		
		/* ���û����˵��ת���ٶ� */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		
		robot_MotorMove(200);
	}else 
# endif
# if DEBUG_RANG_LEFT > 0u
	if(IsRangDetected(ROBOT_RANG_H))	/* �����������߼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䷽��Ϊ������	*/
		Robot.dirction = POSITIVE;
		
		/* ͬʱ��������ʱ��ת����ʹ��������Ŀ�� */
		Robot.M1_Dirction = NEGETIVE; /* ��ߵ����ת */
		Robot.M2_Dirction = POSITIVE; /* �ұߵ����ת */	

		/* ���õ��ת���ٶ� */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		robot_MotorMove(300);
	}else 
# endif
# if DEBUG_RANG_RIGHT > 0u
	if(IsRangDetected(ROBOT_RANG_D)) /* ����������ұ߼�⵽Ŀ�� */
	{
		/* ���ܻ�������һ��ʱ�̵ķ�����Σ��ı䷽��Ϊ������	*/
		Robot.dirction = NEGETIVE;
		
		/* ͬʱ������˳ʱ��ת����ʹ��������Ŀ�� */
		Robot.M1_Dirction = POSITIVE; /* ��ߵ����ת */
		Robot.M2_Dirction = NEGETIVE; /* �ұߵ����ת */	

		/* ���õ��ת���ٶ� */
		Robot.M1_pwm = 300;
		Robot.M2_pwm = 300;
		robot_MotorMove(300);
	}else  /* ����������ܱ߶�û��Ŀ�� */
# endif
	{
		/* �����˱��ֵ�ǰ�н����� */
		Robot.M1_Dirction = Robot.M2_Dirction = Robot.dirction;

		/* ͷ������ָ���ʼֵ */
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
	if(IsPhoDetected(ROBOT_PHO_A))  /* �����ǰ������ */
	{
		Robot.IsEdge = FRONT_LEFT;
		robot_OutOfBounds(FRONT_LEFT);  /* ִ�лس̺��� */
//			if(flag != 0x01)  //
//			{
//				EdgeTime++;
//				flag |= 0x01;
//			}
	}else if(IsPhoDetected(ROBOT_PHO_B))  /* �����ǰ������ */
	{
		Robot.IsEdge = FRONT_RIGHT;
		robot_OutOfBounds(FRONT_RIGHT);  /* ��ǰ������ */
//			if(flag != 0x02)  //
//			{
//				EdgeTime++;
//				flag |= 0x02;
//			}
	}else if(IsPhoDetected(ROBOT_PHO_C))  /* �����󷽳��� */
	{
		Robot.IsEdge = BACK_LEFT;
		robot_OutOfBounds(BACK_LEFT);  /* ��󷽳��� */
//			if(flag != 0x03)  //
//			{
//				EdgeTime++;
//				flag |= 0x03;
//			}
	}	else if(IsPhoDetected(ROBOT_PHO_D))		/* ����Һ󷽳��� */
	{		
		Robot.IsEdge = BACK_RIGHT;
		robot_OutOfBounds(BACK_RIGHT);  /* �Һ󷽳��� */
//			if(flag != 0x01)  //
//			{
//				EdgeTime++;
//				flag |= 0x01;
//			}
	}else  /* û�г��� */
	{
		Robot.M1_pwm = 180;
		Robot.M2_pwm = 180;
		robot_MotorMove(0);  
		Robot.IsEdge = 0;  
	}
}

