/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "mycommon.h"
#include "bsp_adc.h"
#include "bsp_led.h" 
#include "bsp_Tim.h" 
#include "bsp_SysTick.h"
#include "bsp_exti.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/


/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
	if (CoreDebug->DHCSR & 1) {  //check C_DEBUGEN == 1 -> Debugger Connected  

      __breakpoint(0);  // halt program execution here         

  }  
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	static u32 usec  = 0;
	g_systime.usec++;

	if(usec++ >= 1000000)
	{
		usec = 0;	
		g_systime.sec++;
		g_s_update=1;
	} 
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void ADC1_2_IRQHandler(void)
{
	if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET) {
		ADC_ConvertedValue = ADC_GetConversionValue(ADC1);

	}
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET)
	{
		  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
	if(g_key_no==0)
	{
		g_tim_cnt.key1_cnt =0;
		g_tim_cnt.key2_cnt=0;
		g_tim_cnt.key3_cnt=0;
	}
	else if(g_key_no==1)
		g_tim_cnt.key1_cnt ++;
	else if (g_key_no==2)
	{
		g_tim_cnt.key2_cnt ++;
	}		
	else if (g_key_no==3)
		g_tim_cnt.key3_cnt ++;

}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET)
	{
		  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		  if(g_ZeroTime.Zero_low_flag==1)
			{
				g_ZeroTime.Zero_low_cnt++;
				
			}
	}

}

void TIM4_IRQHandler(void)
{
	
}

void USART1_IRQHandler (void)
{
	
}
void USART2_IRQHandler(void)
{
	
}
void EXTI0_IRQHandler(void)
{	

}


void EXTI1_IRQHandler(void)
{
	
}

void EXTI2_IRQHandler(void)
{
	
}

void EXTI3_IRQHandler(void)
{
	
}

void EXTI4_IRQHandler(void)
{
	
}

//交流过零检测
//   _____
//  |    |
/*__|    |__    */
//
void EXTI9_5_IRQHandler(void)
{
	uint16_t key_value=0xff7f;

	if (EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
			EXTI_ClearITPendingBit(EXTI_Line7); //清除标志
		
			key_value = GPIO_ReadInputData(GPIOA);  //PA7
		
		  //下降沿交流过零开始，上升沿交流过零结束
		  if((key_value&0x0080)==0)  //交流过零
			{
				MOTO_Stop ();
				TIM3_Run();
				g_ZeroTime.Zero_low_cnt=0;
			  g_ZeroTime.Zero_low_flag=1;

			}
			else if((key_value&0x0080)==1)
			{	
				TIM3_Stop();
				g_ZeroTime.Zero_low_flag =2;


				if(g_Zero_Hz>100)
				{
					g_Zero_Hz=0;
				}

//extern u8 nmOrMxx;     //nm=1,Mxx=0

				if(g_moto_enable)
				{
					 if(g_nmOrMxx==0)
					 {
						  Zero_Cross( g_moto_power);
					 }
					 else if(g_nmOrMxx==1)
					 {
						  Zero_Cross( g_moto_power*2);
					 }
					
				}
				
				
				g_Zero_Hz++;
				
			}

		
			//常态为低电平。上升沿为过零开始，下降沿为过零结束。
//		  if(key_value&0x0080)  //交流过零开始
//			{
//				TIM3_STOP();	
//				g_zero_cnt=0;
//				g_zero_flag=0;
//				//过零开始停止PWM输出
//			}
//			else
//			{
//				g_zero_cnt=0;
//				TIM3_RUN();
//				g_zero_flag=1;
//			//过零结束启动PWM输出
//			}
//		
			
	}
}


void EXTI15_10_IRQHandler(void)
{
	  g_key_no=0;

	  if (EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line14); //清除标志 //PB14.right

		   	g_key_no = 1;
			
				TIM2_Run();
			
				g_tim_cnt.key1_cnt =0;
			
    }
		
		if (EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line13); //清除标志   //pb13.M

			 	g_key_no = 2;
				g_tim_cnt.key2_cnt=0;
				TIM2_Run();
		
    }
		
		if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line12); //清除标志

			  g_key_no = 3;                        //   left .pb12
			
				TIM2_Run();
			
				g_tim_cnt.key3_cnt=0;
    }
		
}

void DMA1_Channel1_IRQHandler(void)
{
	
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
