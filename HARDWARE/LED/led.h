#ifndef _LED_H
#define _LED_H
#include "sys.h"

//LED端口定义
#define LED0 PEout(8)
#define LED1 PGout(1)
#define LED2 PEout(7)

void LED_Init(void);  //初始化
#endif
