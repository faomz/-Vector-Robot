#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOG, ENABLE); //
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8); //
	GPIO_ResetBits(GPIOG, GPIO_Pin_1);
}
