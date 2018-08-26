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


u8 g_key_no;           //按键编号
u8 g_key_press;        //哪个按键被按下
time_cnt g_tim_cnt;    //按键时间检测 
 __IO u16 ADC_ConvertedValue;  // ADC1转换的电压值通过MDA方式传到SRAM
   

u8 g_zero_flag;      //交流过零检测       
u16 g_zero_cnt;        //交流过零时间
u16 g_zero_op_cnt;     //

u16 g_pwmout[4]={0,255,500,1000};

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
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
	
	USART_Config();     //PB10 （TX）,PB11（RX）
	
 	ADC1_Init();        // PA4 ->ADC1.channel4


  TIM2_Init(999,71);
	TIM3_Init(999,71);
	EXTI_Key_Config();

	TIM1_PWM_Init(999,71);
	TIM_SetCompare4(TIM1,250);	

	OLED_GPIO_Configuration();
	OLED_Init(); //OLED初始化

	
	while(1)
	{
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3;
		
		LED1_TOGGLE;
		OLED_P16x16Ch(24,0,1);
		OLED_P16x16Ch(40,0,2);
		OLED_P16x16Ch(57,0,3);
		OLED_P16x16Ch(74,0,4);
		OLED_P16x16Ch(91,0,5);
		for(i=0; i<8; i++)//通过点整显示汉字 -- i表示字表数组的位置
		{
			OLED_P16x16Ch(i*16,0,i);
		 	OLED_P16x16Ch(i*16,2,i+8);
		 	OLED_P16x16Ch(i*16,4,i+16);
		 	OLED_P16x16Ch(i*16,6,i+24);
		}
		Delay_us(400000);
		OLED_CLS();//清屏

		OLED_P8x16Str(0,0,"HelTec");//第一行 -- 8x16的显示单元显示ASCII码
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
		//交流周期为10ms.10ms=1000*10us
		if(g_Zero_Flag)  
		{
					printf("\r\n time is %d",g_Zero_cnt);
					PWM_out_AC_MOTO(2);
//			if(g_Zero_cnt>=300)
//				;
		}
		
		//pwm输出控制交流电机。限于在中断下降沿至上升沿之间。
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
			
			case 3:  // 确认
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
