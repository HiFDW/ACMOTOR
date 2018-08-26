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
		g_tim_cnt.key2_cnt ++;
	else if (g_key_no==3)
		g_tim_cnt.key3_cnt ++;

}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET)
	{
		  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			g_zero_cnt++;
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
void EXTI9_5_IRQHandler(void)
{
	static u8 s_Cnt=0;
	uint16_t key_value=0;

	if (EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
			EXTI_ClearITPendingBit(EXTI_Line7); //清除标志
		
			key_value = GPIO_ReadInputData(GPIOA);  //PA7
			//常态为低电平。上升沿为过零开始，下降沿为过零结束。
		  if(key_value&0x0080)  //交流过零开始
			{
				TIM3_RUN();
				g_zero_cnt=0;
				g_zero_flag=0;
			}
			else
			{
				TIM3_STOP();
				g_zero_flag=1;
				
			}
		
			
	}
}


void EXTI15_10_IRQHandler(void)
{
	  g_key_no=0;

	  if (EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line14); //清除标志

		   	g_key_no = 1;
			
				TIM2_RUN();
    }
		
		if (EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line13); //清除标志

			 	g_key_no = 2;
				TIM2_RUN();
    }
		if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line12); //清除标志

			  g_key_no = 3;
			
				TIM2_RUN();
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
