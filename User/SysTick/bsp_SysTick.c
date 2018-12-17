  
#include "bsp_SysTick.h"
#include "core_cm3.h"
#include "misc.h"
#include "mycommon.h"

   
/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 1000000))	// ST3.5.0库版本
	{ 
		while (1);
	}
}

/**
  * @brief   us延时程序,1us为一个单位
  * @param  
  *		@arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 1us = 1us
  * @retval  无
  */
void Delay_us(__IO u32 nTime)
{ 
	u32 nus=0;
	while(nTime--)
	{
		nus = g_systime.usec;
		while( nus ==g_systime.usec ); //1us延时
	}
	
}



/*********************************************END OF FILE**********************/
