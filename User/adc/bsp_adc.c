#include "bsp_adc.h"
#include "mycommon.h"

/**
  * @brief  ADC GPIO 初始化
  * @param  无
  * @retval 无
  */
//PA4，（PA5作为备用）	
static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);				
}

/**
  * @brief  配置ADC工作模式
  * @param  无
  * @retval 无
  */
static void ADC_Mode_Config(ADC_TypeDef* ADCx)
{

	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE );		


	DMA_DeInit(ADC_DMA_CHANNEL);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADCx->DR ) );
	
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvertedValue;
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	DMA_InitStructure.DMA_BufferSize = 1;
	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	


	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 	// 只使用一个ADC，属于单模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;    	// 禁止扫描模式，多通道才要，单通道不需要

	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	// 连续转换模式


	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 	// 不用外部触发转换，软件开启即可


	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	// 转换结果右对齐
	

	ADC_InitStructure.ADC_NbrOfChannel = 1;	   	// 转换通道1个
		

	ADC_Init(ADCx, &ADC_InitStructure);   	// 初始化ADC
	

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);     	// 配置ADC时钟为PCLK2的8分频，即9MHz

	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
	
	ADC_DMACmd(ADCx, ENABLE);

	ADC_Cmd(ADCx, ENABLE);
	
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx));

	ADC_SoftwareStartConvCmd(ADCx, ENABLE);  	// 由于没有采用外部触发，所以使用软件触发ADC转换 
 
}

/**
  * @brief  ADC初始化
  * @param  无
  * @retval 无
  */
void ADC1_Init(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config(ADC1);
}
/*********************************************END OF FILE**********************/
