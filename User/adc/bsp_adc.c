#include "bsp_adc.h"
#include "mycommon.h"

/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */
//PA4����PA5��Ϊ���ã�	
static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);				
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
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
	


	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;    	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ

	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	// ����ת��ģʽ


	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 	// �����ⲿ����ת���������������


	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	// ת������Ҷ���
	

	ADC_InitStructure.ADC_NbrOfChannel = 1;	   	// ת��ͨ��1��
		

	ADC_Init(ADCx, &ADC_InitStructure);   	// ��ʼ��ADC
	

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);     	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz

	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
	
	ADC_DMACmd(ADCx, ENABLE);

	ADC_Cmd(ADCx, ENABLE);
	
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	ADC_StartCalibration(ADCx);
	while(ADC_GetCalibrationStatus(ADCx));

	ADC_SoftwareStartConvCmd(ADCx, ENABLE);  	// ����û�в����ⲿ����������ʹ���������ADCת�� 
 
}

/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADC1_Init(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config(ADC1);
}
/*********************************************END OF FILE**********************/
