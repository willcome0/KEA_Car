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

#define AD_1     1
#define AD_2     2
#define AD_3     3
#define AD_4     4
#define AD_BAT   5
/***********************************************************
 * 
 * 函数声明
 * 
 **********************************************************/
void AD_Init(void);
uint16_t Get_Ind_V(uint8_t ADX);


#endif
