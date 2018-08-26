#ifndef __EXTI_H
#define	__EXTI_H


#include "stm32f10x.h"

//3个按键，以及交流过零检测中断
//pb15  key1
//pb14  key2
//pb13  key3
//PA7   都是低电平触发。

//引脚定义
#define KEY1_INT_GPIO_PORT         GPIOB
#define KEY1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN          GPIO_Pin_14
#define KEY1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource14
#define KEY1_INT_EXTI_LINE         EXTI_Line14
#define KEY1_INT_EXTI_IRQ          EXTI15_10_IRQn

#define KEY1_IRQHandler            EXTI15_10_IRQHandler



#define KEY2_INT_GPIO_PORT         GPIOB
#define KEY2_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEY2_INT_GPIO_PIN          GPIO_Pin_13
#define KEY2_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEY2_INT_EXTI_PINSOURCE    GPIO_PinSource14
#define KEY2_INT_EXTI_LINE         EXTI_Line13
#define KEY2_INT_EXTI_IRQ          EXTI15_10_IRQn
#define KEY2_IRQHandler            EXTI15_10_IRQHandler


#define KEY3_INT_GPIO_PORT         GPIOB
#define KEY3_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define KEY3_INT_GPIO_PIN          GPIO_Pin_12
#define KEY3_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEY3_INT_EXTI_PINSOURCE    GPIO_PinSource13
#define KEY3_INT_EXTI_LINE         EXTI_Line12
#define KEY3_INT_EXTI_IRQ          EXTI15_10_IRQn
#define KEY3_IRQHandler            EXTI15_10_IRQHandler


#define ZERO_INT_GPIO_PORT         GPIOA
#define ZERO_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define ZERO_INT_GPIO_PIN          GPIO_Pin_7
#define ZERO_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define ZERO_INT_EXTI_PINSOURCE    GPIO_PinSource7
#define ZERO_INT_EXTI_LINE         EXTI_Line7
#define ZERO_INT_EXTI_IRQ          EXTI9_5_IRQn
#define ZERO_IRQHandler            EXTI9_5_IRQHandler 


void EXTI_Key_Config(void);
u8 Key_Check_Pressed(void);

#endif /* __EXTI_H */
