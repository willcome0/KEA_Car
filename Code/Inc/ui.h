#ifndef __UI_H
#define __UI_H

#include "common.h"

uint8_t UI_Main(void);
uint8_t UI_Go(void);
uint8_t UI_Plan(void);
uint8_t UI_Driver(void);
uint8_t UI_Set(void);
uint8_t UI_Check(void);

uint8_t UI_MPU6050(void);
uint8_t UI_Read_Ind(void);
uint8_t UI_Read_End(void);

uint8_t UI_Adjust_Ind(void);
uint8_t UI_Huan_About(void);

extern volatile uint8_t Adjust_Flag;
extern uint16_t Adjust_L_Ind;
extern uint16_t Adjust_R_Ind;










#endif
