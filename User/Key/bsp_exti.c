/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  */
 
#include "mycommon.h"
#include "bsp_exti.h"
#include "bsp_Tim.h" 
#include "stdio.h"

//3个按键，以及交流过零检测中断

//pb14
//pb13
//pb12


//PB0   都是低电平触发。



 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
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
  * @brief  配置 IO为EXTI中断口，并设置中断优先级
  * @param  无
  * @retval 无
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
	
	/*--------------------------KEY1配置-----------------------------*/
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------KEY2配置-----------------------------*/
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------KEY3配置-----------------------------*/
  GPIO_InitStructure.GPIO_Pin = KEY3_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY3_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(KEY3_INT_EXTI_PORTSOURCE, KEY3_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY3_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
	 /*--------------------------ZERO配置--，低电平中断---------------------------*/
  GPIO_InitStructure.GPIO_Pin = ZERO_INT_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(ZERO_INT_GPIO_PORT, &GPIO_InitStructure);
  GPIO_EXTILineConfig(ZERO_INT_EXTI_PORTSOURCE, ZERO_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = ZERO_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
}

u8 Key_Check_Pressed(void)
{
	u16 time=0;
	u8 key_press=0;
	uint16_t key_value=0;
	key_value = GPIO_ReadInputData(GPIOB);
	
	if(((key_value&0x4000)==0)&&(g_tim_cnt.key1_cnt >10))  //PB14 +
	{
			TIM2_Stop();
		  g_tim_cnt.key1_cnt =0;
			key_press = 1;   //Key1按下
		
	}
	
	if(((key_value&0x2000)==0)&&(	g_tim_cnt.key2_cnt >10))  //PB13 确认键
	{	    
		    time = g_systime.sec;
				TIM2_Stop();
		    g_tim_cnt.key2_cnt =0;
			  key_press = 2;   
				while(g_systime.sec == time) ;  //等待1s
		    while(g_systime.sec == time+1);  //等待1s
		   	key_value = GPIO_ReadInputData(GPIOB);      //
		    if((key_value&0x2000)==0)
				{
						key_press =4 ;
				}

	}

	if(((key_value&0x1000)==0)&&(	g_tim_cnt.key3_cnt >10))	//PB12 -

	{
      TIM2_Stop();
			g_tim_cnt.key3_cnt =0;
			key_press = 3;     //key3 按下
	}
	
	return key_press;
}


void MOTO_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(  RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);   
}

void MOTO_Run(void)
{
		GPIO_SetBits(GPIOA,GPIO_Pin_11);   
}

void MOTO_Stop(void)
{
  	GPIO_ResetBits(GPIOA,GPIO_Pin_11);   
}


//	 if(g_ZeroTime.Zero_low_flag ==2)
void Zero_Cross(u8 n)
{

	 switch(n){
		 
		 case 1:    //10%
			 if((g_Zero_Hz%10)==0)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			 break;
		 case 2:
			 if(g_Zero_Hz%5==0)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			 break;
		 case 3:
			  if(g_Zero_Hz%10 <3)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			 break;
		 case 4:
			  if(g_Zero_Hz%10<4)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			 break;
		 case 5:
			  if(g_Zero_Hz%2==0)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			 break;
		 case 6:
			  if(g_Zero_Hz%10 <6)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			break;
		 case 7:
			  if(g_Zero_Hz%10 <7)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			break;
		 case 8:
			  if(g_Zero_Hz%10 <8)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			break;
		 case 9:
			  if(g_Zero_Hz%10 !=9)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			break;
		 
		 case 10:
			  if(1)
			 {
				 MOTO_Run();
			 }
			 else
			 {	 MOTO_Stop();}
			 break;		 
				 
		 default:
			 break;		 
		 
		 
		 
		 
		 
	 }
	 
	 
	 
	
}




/*********************************************END OF FILE**********************/
