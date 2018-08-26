#ifndef __MY_COMMON_H
#define __MY_COMMON_H

#include <stdint.h>

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

typedef struct
{
	u16 key1_cnt;
	u16 key2_cnt;
	u16 key3_cnt;

}time_cnt;

extern time_cnt g_tim_cnt;
extern u8 g_zero_flag; 
extern u16 g_zero_cnt;
extern u16 g_zero_op_cnt;
extern u8 g_key_no;



extern u8 g_key_press;        //哪个按键被按下
extern  __IO u16 ADC_ConvertedValue;
  





#endif
