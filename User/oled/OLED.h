#ifndef __OLED_H
#define __OLED_H


//-----------------OLED¶Ë¿Ú¶¨Òå----------------  					   
//PB15-IO2->SCL
//PA8 -IO1->SDA
#define LCD_SCL_CLR()	GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define LCD_SCL_SET()	GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define LCD_SDA_CLR()	GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define LCD_SDA_SET()	GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define LCD_SDA_IN()   {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=8<<0;}   //PA8
#define LCD_SDA_OUT()  {GPIOA->CRH&=0XFFFFFFF0;GPIOA->CRH|=3<<0;}   


void OLED_GPIO_Configuration(void);

void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_WrDat(unsigned char IIC_Data);
void OLED_WrCmd(unsigned char IIC_Command);	
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_Fill(unsigned char bmp_dat) ;
void OLED_CLS(void);
void OLED_Init(void);
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char* ch);
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char* ch);
void OLED_P16x16Ch(unsigned char x, unsigned char y,unsigned char N);
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


#endif

