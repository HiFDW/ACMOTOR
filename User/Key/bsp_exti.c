/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I/O���ж�Ӧ��bsp
  ******************************************************************************
  */
 
#include "mycommon.h"
#include "bsp_exti.h"
#include "bsp_Tim.h" 


//3���������Լ������������ж�
//pb15
//pb14
//pb13
//PB0   ���ǵ͵�ƽ������

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_KEY_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  

  NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	


  NVIC_InitStructure.NVIC_IRQChannel = KEY3_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
  NVIC_InitStructure.NVIC_IRQChannel = ZERO_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  ���� IOΪEXTI�жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(KEY3_INT_GPIO_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(ZERO_INT_GPIO_CLK,ENABLE);
												

	NVIC_KEY_Configuration();
	
	/*--------------------------KEY1����-----------------------------*/
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------KEY2����-----------------------------*/
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------KEY3����-----------------------------*/
  GPIO_InitStructure.GPIO_Pin = KEY3_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY3_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(KEY3_INT_EXTI_PORTSOURCE, KEY3_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY3_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
	 /*--------------------------ZERO����--���͵�ƽ�ж�---------------------------*/
  GPIO_InitStructure.GPIO_Pin = ZERO_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(ZERO_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(ZERO_INT_EXTI_PORTSOURCE, ZERO_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = ZERO_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
}

u8 Key_Check_Pressed(void)
{
	u8 key_press=0;
	uint16_t key_value=0;
	key_value = GPIO_ReadInputData(GPIOB);
	
	if(((key_value&0x8000)==0)&&(g_tim_cnt.key1_cnt >=20))  //PB15
	{
			TIM2_STOP();
		  g_tim_cnt.key1_cnt =0;
			key_press = 1;   //Key1����
		
	}
		if(((key_value&0x4000)==0)&&(	g_tim_cnt.key2_cnt >=20))  //PB14
	{	
		    TIM2_STOP();
				g_tim_cnt.key2_cnt =0;
				key_press = 2;    //key2����
	}
	if(((key_value&0x2000)==0)&&(	g_tim_cnt.key3_cnt >=20))	//PB13

	{
      TIM2_STOP();
			g_tim_cnt.key3_cnt =0;
			key_press = 3;     //key3 ����
	}
	return key_press;
}

/*********************************************END OF FILE**********************/
