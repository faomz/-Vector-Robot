# include "robot.h"

Robot_Dev Robot;	

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
void robot_Config(void)
{
	robot_DetectConfig();
	robot_MotorConfig();
	TIM_Cmd(TIM1,ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE); 
# if ROBOT_DEBUG > 0u
	robot_DebugConfig();
# endif
}

