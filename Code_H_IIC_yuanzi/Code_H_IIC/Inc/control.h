#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"

#define CON_PERIOD	5	// ��������

extern uint16_t Value_Inductor_L;
extern uint16_t Value_Inductor_R;
extern float LR_Error;

extern int16_t Value_End_L;
extern int16_t Value_End_R;
extern int16_t Error_Ind;

extern uint32_t Run_Time;
extern uint32_t Run_Distance;

extern float pitch,roll,yaw;
extern short Gyro_X, Gyro_Y, Gyro_Z;
uint8_t Just_Do_It(void);

#endif
