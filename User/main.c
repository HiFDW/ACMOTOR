#include "mycommon.h"
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_SysTick.h"
#include "bsp_adc.h"
#include "bsp_exti.h"
#include "bsp_usart.h"
#include "bsp_Tim.h" 
#include "bsp_GeneralTimPWM.h" 
#include "oled.h"


u8 g_key_no;           //�������
u8 g_key_press;        //�ĸ�����������
time_cnt g_tim_cnt;    //����ʱ���� 
 __IO u16 ADC_ConvertedValue;  // ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
   

u8 g_zero_flag;      //����������       
u16 g_zero_cnt;        //��������ʱ��
u16 g_zero_op_cnt;     //

u16 g_pwmout[4]={0,255,500,1000};

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
  u8 key=0;
	static u8 i;
	float ADC_ConvertedValueLocal=0;   
	
	g_tim_cnt.key1_cnt=0;
	g_tim_cnt.key2_cnt=0;
	g_tim_cnt.key3_cnt=0;
	
  
	
	SysTick_Init();     //1us

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	LED_GPIO_Config();	//PC13   ->LED
	
	USART_Config();     //PB10 ��TX��,PB11��RX��
	
 	ADC1_Init();        // PA4 ->ADC1.channel4


  TIM2_Init(999,71);
	TIM3_Init(999,71);
	EXTI_Key_Config();

	TIM1_PWM_Init(999,71);
	TIM_SetCompare4(TIM1,250);	

	OLED_GPIO_Configuration();
	OLED_Init(); //OLED��ʼ��

	
	while(1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3;
		
		LED1_TOGGLE;
		OLED_P16x16Ch(24,0,1);
		OLED_P16x16Ch(40,0,2);
		OLED_P16x16Ch(57,0,3);
		OLED_P16x16Ch(74,0,4);
		OLED_P16x16Ch(91,0,5);
		for(i=0; i<8; i++)//ͨ��������ʾ���� -- i��ʾ�ֱ������λ��
		{
			OLED_P16x16Ch(i*16,0,i);
		 	OLED_P16x16Ch(i*16,2,i+8);
		 	OLED_P16x16Ch(i*16,4,i+16);
		 	OLED_P16x16Ch(i*16,6,i+24);
		}
		Delay_us(400000);
		OLED_CLS();//����

		OLED_P8x16Str(0,0,"HelTec");//��һ�� -- 8x16����ʾ��Ԫ��ʾASCII��
		OLED_P8x16Str(0,2,"OLED Display");
		OLED_P8x16Str(0,4,"www.heltec.cn");
		OLED_P6x8Str(0,6,"cn.heltec@gmail.com");
		OLED_P6x8Str(0,7,"heltec.taobao.com");
		Delay_us(400000);
		OLED_CLS();
	}
		
}
#if 0
	while(1)
	{	
			TIM_SetCompare4(TIM1,250);																																																																																																																																																																										
		  Delay_us(10000);
		while(1)
		{
			;
		}
		//��������Ϊ10ms.10ms=1000*10us
		if(g_Zero_Flag)  
		{
					printf("\r\n time is %d",g_Zero_cnt);
					PWM_out_AC_MOTO(2);
//			if(g_Zero_cnt>=300)
//				;
		}
		
		//pwm������ƽ���������������ж��½�����������֮�䡣
//		PWM_out_AC_MOTO(2);

		key=Key_Check_Pressed(); 
		switch(key)
		{
			case 0:
				break;
			
			case 1:  // +
					LED1_TOGGLE;
					i++;
					if(i>4)
					{
						i=3;
					}
					printf("\r\n key1 pressed.\r\n");
					break;
			
			case 2:  // -
					LED1_TOGGLE;
					i--;
					if(i<=0)
					{
						i=0;
					}
					printf("\r\n key2 pressed. \r\n");
			    break;
			
			case 3:  // ȷ��
					LED1_TOGGLE;
					TIM_SetCompare4(TIM1,g_pwmout[i++]);
					printf("\r\n Key3 pressed \r\n");
			    break;
			
			default:
				break;
		}
	}
#endif			
		
		





/*********************************************END OF FILE**********************/
