#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"



// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/

// PC1-ͨ��11 ����IO
#define    ADC_PIN                       GPIO_Pin_1
#define    ADC_CHANNEL                   ADC_Channel_4
#define    ADC_DMA_CHANNEL               DMA1_Channel1

void ADC1_Init(void);


#endif /* __ADC_H */

