#ifndef	__MOTOR_H
#define __MOTOR_H

#include "common.h"

/*电机使能脚*/
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
 * 函数声明
 * 
 **********************************************************/
void Motor_Init(void);

void Motor_Set_Go_Speed(uint16_t L, uint16_t R);
void Motor_Set_Back_Speed(uint16_t L, uint16_t R);
void Motor_L_Back_V(uint16_t L);
void Motor_L_Go_V(uint16_t L);
void Motor_R_Back_V(uint16_t R);
void Motor_R_Go_V(uint16_t R);





#endif
