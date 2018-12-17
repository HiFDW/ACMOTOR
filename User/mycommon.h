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

typedef struct{
	u32 usec;	
	u32 sec;		
}st_systime;


typedef struct{
	u8  Zero_low_flag;
  u8  Zero_high_flag;	
	u16 Zero_low_cnt;	
	u16 Zero_high_cnt;		
}ZeroTime;



extern ZeroTime  g_ZeroTime;
extern u8 g_Zero_Hz;  //取100个周期。
extern st_systime g_systime; //系统时间

extern u8 g_s_update;

extern time_cnt g_tim_cnt;

extern u8 g_moto_power;
extern u8 g_nmOrMxx;     //nm=1,Mxx=0
extern u8 g_moto_enable;



extern u8 g_key_no;



extern  __IO u16 ADC_ConvertedValue;
  

void Soft_delay(__IO uint32_t nCount);

#endif
