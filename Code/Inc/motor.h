#ifndef	__MOTOR_H
#define __MOTOR_H

#include "common.h"


#define Motor_L_EN_Port PTD
#define Motor_L_EN_Pin  PTD7

#define Motor_R_EN_Port PTC
#define Motor_R_EN_Pin  PTC1

#define Enable  1
#define Disable 0

#define Motor_L_EN(STATE)    Pin_Output_Set(Motor_L_EN_Port, Motor_L_EN_Pin, STATE)
#define Motor_R_EN(STATE)    Pin_Output_Set(Motor_R_EN_Port, Motor_R_EN_Pin, STATE)


/***********************************************************
 * 
 * º¯ÊýÉùÃ÷
 * 
 **********************************************************/
void Motor_Init(void);







#endif