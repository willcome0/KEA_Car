#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"

#define CON_PERIOD	5	// ¿ØÖÆÖÜÆÚ

extern uint16_t Value_Inductor_L;
extern uint16_t Value_Inductor_R;
extern float LR_Error;

extern int16_t Value_End_L;
extern int16_t Value_End_R;
extern int16_t Error_Ind;

extern uint32_t Run_Time;
extern uint32_t Run_Distance;

extern volatile float Pitch, Roll, Yaw;
extern volatile float Pitch1, Roll1, Yaw1;
extern volatile short Gyro[3];
extern volatile short Accel[3];
extern float angle, angle_dot; 

uint8_t Just_Do_It(void);

#endif
