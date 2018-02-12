#ifndef __DATA_H
#define __DATA_H

#include "common.h"






struct PID//PID结构体
{
    uint16_t P;
    uint16_t I;
    uint16_t D;
    uint16_t tp;
	  uint16_t td;
};
struct TARGET//目标值结构体
{
    uint16_t Angle;
    uint16_t Speed;   //目标速度
};



struct PLAN
{
    struct PID Angle; //角度环值
    struct PID Speed; //速度环值
    struct PID Turn;  //转弯环值
    
    struct TARGET Target;//各目标值
    
    uint16_t Safe_Angle;
};
struct CON
{
	uint8_t Run;
	uint8_t LED;
	uint8_t Buzzer;
	uint8_t BT;

};



extern struct PLAN Plan1;//要更多方案在这里加
extern struct PLAN Blue;//蓝牙方案
extern struct CON  Con;



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

uint32_t ABS(int32_t Num);//取绝对值

#endif


