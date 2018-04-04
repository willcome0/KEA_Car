#ifndef __ENCODER_H
#define __ENCODER_H

#include "common.h"

#define Dir_End_L_Port PTB
#define Dir_End_L_Pin  PTB2

#define Dir_End_R_Port PTE
#define Dir_End_R_Pin  PTE5

#define End_L  0
#define End_R  1

#define Debug_Pin1_H()		Pin_Output_Set(PTE, PTE0, 1)
#define Debug_Pin1_L()		Pin_Output_Set(PTE, PTE0, 0)
#define Debug_Pin1_Toggle()	Pin_Output_Toggle(PTE, PTE0)

#define Debug_Pin2_H()		Pin_Output_Set(Dir_End_L_Port, Dir_End_L_Pin, 1)
#define Debug_Pin2_L()		Pin_Output_Set(Dir_End_L_Port, Dir_End_L_Pin, 0)
#define Debug_Pin2_Toggle()	Pin_Output_Toggle(Dir_End_L_Port, Dir_End_L_Pin)

void Encoder_Init(void);
uint8_t End_Read_Dir(uint8_t Dir);
uint8_t Debug_Pin_Init(void);

#endif
