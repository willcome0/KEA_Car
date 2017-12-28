#ifndef __DATA_H
#define __DATA_H

#include "common.h"






struct PID//PID结构体
{
    int16_t P;
    int16_t I;
    int16_t D;
    int16_t tp;
	  int16_t td;
};
struct TARGET//目标值结构体
{
    int16_t Angle;
    int16_t Speed;   //目标速度
};



struct PLAN
{
    struct PID Angle; //角度环值
    struct PID Speed; //速度环值
    struct PID Turn;  //转弯环值
    
    struct TARGET Target;//各目标值
    
    int16_t Safe_Angle;
};
extern struct PLAN Plan1;//要更多方案在这里加
extern struct PLAN Blue;//蓝牙方案




extern int16_t Add_L;
extern int16_t Target_Angle;
extern int16_t Target_Speed;

extern int16_t Balance_P;
extern float Balance_D;

extern int16_t Speed_P;
extern float Speed_I;

extern int16_t Turn_P;

/*设置菜单数据*/
extern uint8_t Set_LED;
extern uint8_t Set_Beep;
extern uint8_t Bluetooth;

extern volatile int16_t Value_End;



#endif


