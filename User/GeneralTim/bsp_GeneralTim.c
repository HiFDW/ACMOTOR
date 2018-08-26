
#include "bsp_Tim.h" 


//#define            GENERAL_TIM                   TIM2
//#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
//#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
//#define            GENERAL_TIM_Period            (1000-1)
//#define            GENERAL_TIM_Prescaler         71
//#define            GENERAL_TIM_IRQ               TIM2_IRQn
//#define            GENERAL_TIM_IRQHandler        TIM2_IRQHandler


static void NVIC_TIM2_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn ;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void NVIC_TIM3_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn ;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//STM32F103 TIM1,TIM2,3,4
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */
static void TIM2_Mode_Config(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE);	
	TIM_TimeBaseStructure.TIM_Period= arr;    //(1000-1);
	TIM_TimeBaseStructure.TIM_Prescaler= 71;	   //1ms定时一次
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	//TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	//TIM_Cmd(TIM2, ENABLE);
	
	
//    /* PCLK2 = HCLK */  72Mhz
//    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
//    
//    /* PCLK1 = HCLK/2 */ =36Mhz
//    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
	
}




static void TIM3_Mode_Config(void)
{
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;		//10us一次中断
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE);	
    TIM_TimeBaseStructure.TIM_Period=(10-1);
    TIM_TimeBaseStructure.TIM_Prescaler= 71;	
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		//时钟分频不为1，TIM时钟为72M
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 		
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);

//    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//    TIM_Cmd(TIM3, ENABLE);
}



void TIM2_Init(u16 arr,u16 psc)
{

	NVIC_TIM2_Config();		
	TIM2_Mode_Config(arr,psc);
}

void TIM3_Init(u16 arr,u16 psc)
{

	NVIC_TIM3_Config();		
	TIM3_Mode_Config();
}



void  TIM2_RUN(void)
{
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	  TIM_Cmd(TIM2, ENABLE);
}

void  TIM2_STOP(void)
{
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
//	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
	TIM_Cmd(TIM2, DISABLE);
}

void TIM3_RUN(void)
{
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_STOP(void)
{
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
	TIM_Cmd(TIM3, DISABLE);
}


/*********************************************END OF FILE**********************/
