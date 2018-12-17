  
#include "bsp_SysTick.h"
#include "core_cm3.h"
#include "misc.h"
#include "mycommon.h"

   
/**
  * @brief  ����ϵͳ�δ�ʱ�� SysTick
  * @param  ��
  * @retval ��
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 1000000))	// ST3.5.0��汾
	{ 
		while (1);
	}
}

/**
  * @brief   us��ʱ����,1usΪһ����λ
  * @param  
  *		@arg nTime: Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 1us = 1us
  * @retval  ��
  */
void Delay_us(__IO u32 nTime)
{ 
	u32 nus=0;
	while(nTime--)
	{
		nus = g_systime.usec;
		while( nus ==g_systime.usec ); //1us��ʱ
	}
	
}



/*********************************************END OF FILE**********************/
