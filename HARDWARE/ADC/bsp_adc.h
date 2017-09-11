# ifndef __BSP_ADC_H
# define __BSP_ADC_H
# include "stm32f4xx.h"

#	define ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)

extern uint16_t ADC1ConvValue[16];

void BSP_ADC_Config(void);
void BSP_ADC_TIM_Config(void);
void BSP_ADC_GPIO_Config(void);
void BSP_ADC_CH_Config(void);
void BSP_ADC_DMA_Config(void);

# endif

