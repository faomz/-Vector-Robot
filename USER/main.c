#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "os_app_hooks.h"
# include "bsp_adc.h"

#define START_TASK_PRIO		3

#define START_STK_SIZE 		512

OS_TCB StartTaskTCB;
	
CPU_STK START_TASK_STK[START_STK_SIZE];

void start_task(void *p_arg);

#define LED0_TASK_PRIO		4

#define LED0_STK_SIZE 		128

OS_TCB Led0TaskTCB;
	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *p_arg);


#define LED1_TASK_PRIO		5
	
#define LED1_STK_SIZE 		128

OS_TCB Led1TaskTCB;
	
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];

void led1_task(void *p_arg);


#define FLOAT_TASK_PRIO		6

#define FLOAT_STK_SIZE		128

OS_TCB	FloatTaskTCB;

__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];

void float_task(void *p_arg);

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init(168);  	//
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//
	uart_init(115200);  //
	LED_Init();         //

	BSP_ADC_Config();
	OSInit(&err);		
	OS_CRITICAL_ENTER();
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//
				 (CPU_CHAR	* )"start task", 		//
                 (OS_TASK_PTR )start_task, 			//
                 (void		* )0,					//
                 (OS_PRIO	  )START_TASK_PRIO,     //
                 (CPU_STK   * )&START_TASK_STK[0],	//
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//
                 (CPU_STK_SIZE)START_STK_SIZE,		
                 (OS_MSG_QTY  )0,					//
                 (OS_TICK	  )0,					//
                 (void   	* )0,					//
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //
                 (OS_ERR 	* )&err);				//
	OS_CRITICAL_EXIT();	//
	OSStart(&err);  //
	while(1);
}


void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	
	OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,		
				 (CPU_CHAR	* )"led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK   * )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);				
				 
	
	OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,		
				 (CPU_CHAR	* )"led1 task", 		
                 (OS_TASK_PTR )led1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED1_TASK_PRIO,     	
                 (CPU_STK   * )&LED1_TASK_STK[0],	
                 (CPU_STK_SIZE)LED1_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	
	OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,		
				 (CPU_CHAR	* )"float test task", 		
                 (OS_TASK_PTR )float_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
                 (CPU_STK   * )&FLOAT_TASK_STK[0],	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//			 
	OS_CRITICAL_EXIT();	//
}

void led0_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		LED0=0;
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //
		LED0=1;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //
	}
}

void led1_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		LED1=~LED1;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //
	}
}

void float_task(void *p_arg)
{
	CPU_SR_ALLOC();
	static uint8_t i = 0;
	while(1)
	{
		i++;
		if(i > 15)i = 0;
		OS_CRITICAL_ENTER();	//
		printf("ADC[%d]: %d\r\n",i,ADC1ConvValue[i]);
		OS_CRITICAL_EXIT();		//
		delay_ms(500);			//
	}
}
