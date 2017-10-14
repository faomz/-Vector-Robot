# include "motor.h"

void MOTOR_PWM_Config(void)
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

