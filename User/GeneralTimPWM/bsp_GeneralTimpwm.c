
#include "bsp_GeneralTimPWM.h" 



//TIM1.4->PA11
// TIM1 输出比较通道4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH4_PORT          GPIOA
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_11




 void TIM1_PWM_Config(u16 arr,u16 psc)
{  
	
		/*--------------------输出比较结构体初始化-------------------*/	
	// 占空比配置
//	uint16_t CCR1_Val = 5;
//	uint16_t CCR2_Val = 4;
//	uint16_t CCR3_Val = 3;
//	uint16_t CCR4_Val = 2;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_DeInit(TIM1);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH4_GPIO_CLK, ENABLE);
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH4_PORT, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period=arr;	
	TIM_TimeBaseStructure.TIM_Prescaler= psc;	   //71, 1Mhz
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 4
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);  //高级定时器必须开启
	// 使能计数器
	TIM_Cmd(TIM1, ENABLE);
	
	
}

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	TIM1_PWM_Config( arr,psc);		 //默认值
}

void PWM_out_AC_MOTO(u16 param)
{
	TIM_SetCompare4(TIM1,param);
}

/*********************************************END OF FILE**********************/
