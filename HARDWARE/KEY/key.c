# include "key.h"
# include "delay.h"
void KEY_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE); //
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_8 | GPIO_Pin_9); //
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

uint8_t KEY_Scan(void)
{
	if(KEY_UP == 0)
	{
		delay_ms(10);
		if(KEY_UP == 0)
			return 0x01;
	}
	else if(KEY_OK == 0)
	{
		delay_ms(10);
		if(KEY_OK == 0)
			return 0x02;
	}
	else if(KEY_DOWN == 0)
	{
		delay_ms(10);
		if(KEY_DOWN == 0)
			return 0x03;
	}
	return 0x00;
}