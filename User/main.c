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
#include "stdio.h"



/* 全局变量声明*/
st_systime g_systime={0,0}; //系统时间 2^32 /3600/24/365 =  136.19年。 

u8 g_s_update=0;         //用于每秒刷新画面

ZeroTime  g_ZeroTime;
u8 g_Zero_Hz=0;         //取100个周期。

u8  g_key_no=0;          //按键编号
time_cnt g_tim_cnt;    //按键时间检测 


 __IO u16 ADC_ConvertedValue;  // ADC1转换的电压值通过MDA方式传到SRAM
   

u8 g_moto_enable=0;   //控制电机输出使能
u8 g_moto_power=0;    //选择电机马力

u8 g_nmOrMxx=0;      //切换扭矩or螺栓大小 nm=1,Mxx=0,默认螺栓

    
//u16 g_pwmout[10]={99,199,299,399,499,599,699,799,899,999};
u16 g_pwmout[10]={1,2,3,4,5,6,7,8,9,10};


u16 g_NM[10]={1700,1750,1800,1850,1900,2000,2050,2100,2150,2200};
float g_Mxx[5]={4.8,6.8,8.8,10.9,12.9};






/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
  u8 display=0;    //有三个画面
  u8 key=0;
	u8 i;
	float ADC_ConvertedValueLocal=0;   

	char adc_str[16]={0};
  char run_time[16]={0};
	char p[16]={0};
	
	g_tim_cnt.key1_cnt =0;
	g_tim_cnt.key2_cnt =0;
	g_tim_cnt.key3_cnt =0;
	
	g_Zero_Hz=0;
	g_ZeroTime.Zero_low_flag =0;
	g_ZeroTime.Zero_high_flag=0;
	g_ZeroTime.Zero_low_cnt=0;
	g_ZeroTime.Zero_high_cnt=0;
	
	
	g_moto_enable = 0;
	g_moto_power = 0;
	g_nmOrMxx =0;
	
	
	
	
	LED_GPIO_Config();	//PC13   ->LED

  Soft_delay(7200000);//大约100ms 
	
	LED1_TOGGLE;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	USART_Config();     //Pa3 （TX）,Pa2（RX）
	LED_GPIO_Config();	//PC13   ->LED
  SysTick_Init();     //1us  串口初始化需要在systick之前
 	ADC1_Init();        // PA4 ->ADC1.channel4


  TIM2_Init(999,71);
	TIM3_Init(999,71);  //保留暂未使用
	EXTI_Key_Config();

  MOTO_GPIO_Config();

//	TIM1_PWM_Init(999,71);   //这里没有使能 TIM_Cmd(TIM1, ENABLE);
	
	OLED_GPIO_Configuration();
	OLED_Init(); //OLED初始化

  OLED_P8x16Str(0,0,"time:      ");  
  OLED_P8x16Str(0,2,"  NM <--- M22  "); 
  OLED_P8x16Str(0,6,"    EMEG140     ");
    
	while(1)
	{
		if(	g_s_update!=0)
		{
			g_s_update=0;
//			if(g_ZeroTime.Zero_low_flag ==2)
			{
				g_ZeroTime.Zero_low_flag = 0;
				sprintf(run_time, "%d ---%d ",g_systime.sec,g_ZeroTime.Zero_low_cnt );
				OLED_P8x16Str(40,0,run_time);
			}
			if(	g_moto_enable==1)
			{
				OLED_P8x16Str(0,4,"    Run    ");
			}
			else if(g_moto_enable==0)
			{
				OLED_P8x16Str(0,4,"    Stop    ");
			}
			
		ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/2048*3.3;   //
	  sprintf(adc_str, "%2.2f",  ADC_ConvertedValueLocal);            //
		Delay_us(1000);

		}
		
		LED1_TOGGLE;
		
		key=Key_Check_Pressed(); 
		switch(key)
		{
			
			case 0:
				
				break;
			
			case 1:  //+ , >
				key=0;
				g_moto_enable=0;
				  if(display==0)
					{
						 OLED_P8x16Str(0,2,"  NM ---> M22  "); 
						 g_nmOrMxx=1;
						 i=0;
					}
					if(display==1)  
					{
						g_moto_power=i;
						if( g_nmOrMxx==0) //显示nm 画面
						{
							sprintf(p, "  NM: %4d      ", g_NM[i++]);
							Delay_us(1000);
							OLED_P8x16Str(0,2,p); 
							if(i>=10)
							{
								i=9;
							}
						}
						else if( g_nmOrMxx==1)  //显示Mxx 画面
						{
							sprintf(p, "  M58: %2.2f   ", g_Mxx[i++]); 
							Delay_us(1000);							
							OLED_P8x16Str(0,2,p); 
							if(i>4)
							{
								i=4;
							}
						}
			
					}
					break;
					
					case 3:  //- ,<
					g_moto_enable=0;
				  key=0;
					if(display==0)
					{
						 OLED_P8x16Str(0,2,"  NM <--- M22  "); 
						 g_nmOrMxx=0;
						 i=0;
					}
					if(display==1)  
					{
						g_moto_power = i;
						if( g_nmOrMxx==0) //显示nm 画面
						{
							sprintf(p, "  NM: %4d      ", g_NM[i--]);
							OLED_P8x16Str(0,2,p); 
							if(i>=10)
							{
								i=0;
							}
						}
						else if( g_nmOrMxx==1)  //显示Mxx 画面
						{
							sprintf(p, "  M58: %2.2f   ", g_Mxx[i--]);  
							OLED_P8x16Str(0,2,p); 
							if(i>=10)
							{
								i=0;
							}
						}
			
					}
			    break;
					
			case 2:  // 确认 
				  key=0;
			
          if(display==0)
					{
					}
					if(display==1)
					{
						g_moto_enable =1;
						if(g_nmOrMxx==0)
						{

						}
						else	if(g_nmOrMxx==1)
						{
//							   TIM_SetCompare4(TIM1,g_pwmout[i*2]);
						}

						
					}
			     break;
			
			case  4:  //切换画面
				g_moto_enable=0;
				key=0;
					if(display==0)
					{  
							display=1;
					   if(g_nmOrMxx==0)
						{ 
							
							sprintf(p, "  NM: %4d      ", g_NM[0]);
							Delay_us(1000);
							OLED_P8x16Str(0,2,p); 

							
						}else
						if(g_nmOrMxx==1)
						{ 
							sprintf(p, "  M58: %2.2f   ", g_Mxx[i++]); 
							Delay_us(1000);							
							OLED_P8x16Str(0,2,p); 
						}
						
					}else if (display==1)
					{
						display=0;
						OLED_P8x16Str(0,2,"  NM <--- M22  "); 
						g_nmOrMxx =0;
					}
					
					break;

			default:
				
				break;
		}
		
		
	}
		
}		


#if 0


	while(1)
	{
		LED1_TOGGLE;
		Delay_us(1000000);
	}


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
		}

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
	
	
void Screen_Disp(u8 display)
{

	switch (display){

		case 0:

			break;
		
		case 1:
			
			break;
		
		case 2:
			
			break;
				
		default:
			
			break;
		
	}
}	
	
	
#endif			
		
		



void Soft_delay(__IO uint32_t nCount)
{
	for(;nCount!=0;nCount--);
}




/*********************************************END OF FILE**********************/
