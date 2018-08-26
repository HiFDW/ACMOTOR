
#include "bsp_GeneralTimPWM.h" 



//TIM1.4->PA11
// TIM1 ����Ƚ�ͨ��4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH4_PORT          GPIOA
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_11



static void TIM1_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH4_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH4_PORT, &GPIO_InitStructure);
}


// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

 void TIM1_PWM_Mode_Config(u16 arr,u16 psc)
{  
	
		/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	// ռ�ձ�����
//	uint16_t CCR1_Val = 5;
//	uint16_t CCR2_Val = 4;
//	uint16_t CCR3_Val = 3;
//	uint16_t CCR4_Val = 2;
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=arr;	
	TIM_TimeBaseStructure.TIM_Prescaler= psc;	   //500HZ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);


	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 4
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM1, ENABLE);
}

void TIM1_PWM_Init(u16 arr,u16 psc)
{
	TIM1_GPIO_Config();
	TIM1_PWM_Mode_Config( arr,psc);		 //Ĭ��ֵ
}

void PWM_out_AC_MOTO(u16 param)
{
	TIM_SetCompare4(TIM1,param);
}

/*********************************************END OF FILE**********************/
