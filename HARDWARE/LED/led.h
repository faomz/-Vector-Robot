#ifndef _LED_H
#define _LED_H
#include "sys.h"

//LED�˿ڶ���
#define LED0 PEout(8)
#define LED1 PGout(1)
#define LED2 PEout(7)

void LED_Init(void);  //��ʼ��
#endif
