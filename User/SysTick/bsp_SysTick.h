#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

typedef struct{
	u32 usec;	
	u32 sec;		
}st_systime;

extern st_systime g_systime; //系统时间

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);


#endif /* __SYSTICK_H */
