/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  */
  
#include "bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);   //点亮LED
		
}

/*********************************************END OF FILE**********************/
