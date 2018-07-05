#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"

#define CON_PERIOD	5	// 控制周期(ms)
#define PERIOD	CON_PERIOD/1000	// 控制周期(s)
#define DIS_RATIO	5620

extern uint16_t Value_Inductor_L;
extern uint16_t Value_Inductor_R;
extern uint16_t Value_Inductor_BL;
extern uint16_t Value_Inductor_BR;

extern float LR_Error;

extern int16_t Value_End_L;
extern int16_t Value_End_R;
extern int16_t Error_Ind;

extern uint32_t Run_Time;
extern uint32_t Run_Distance;

uint8_t Just_Do_It(void);

#endif
