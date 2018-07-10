#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"

#define CON_PERIOD	5	// 控制周期(ms)
#define PERIOD	CON_PERIOD/1000	// 控制周期(s)
#define DIS_RATIO	5620


extern float LR_Error;




uint8_t Just_Do_It(void);

#endif
