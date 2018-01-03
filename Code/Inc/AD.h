#ifndef __AD_H
#define __AD_H

#include "common.h"

/***********************************************************
 * 
 * 引脚重命名
 * 
 **********************************************************/
#define AD1_Port     PTA
#define AD1_Pin      PTA0 

#define AD2_Port     PTA
#define AD2_Pin      PTA1

#define AD3_Port     PTF
#define AD3_Pin      PTF7

#define AD4_Port     PTF
#define AD4_Pin      PTF6

#define AD_BAT_Port  PTC
#define AD_BAT_Pin   PTC1

#define AD_1     0  //ADC0_SE0
#define AD_2     1  //ADC0_SE1
#define AD_3     14 //ADC0_SE14
#define AD_4     13 //ADC0_SE13
#define AD_BAT   12 //ADC0_SE12
/***********************************************************
 * 
 * 函数声明
 * 
 **********************************************************/
void AD_Init(void);
uint16_t Get_Ind_V(uint8_t ADX);


#endif
