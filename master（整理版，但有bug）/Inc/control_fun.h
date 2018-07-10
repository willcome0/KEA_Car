#ifndef __CONTROL_FUN_H
#define __CONTROL_FUN_H

#include "common.h"

extern volatile uint8_t Huan_No;	// 记录现在要过的是第几个环

extern volatile uint16_t CONTROL_Huan50_Add   ;
extern volatile uint16_t CONTROL_InHuan50_Min ;
extern volatile uint16_t CONTROL_InHuan50_Max ;

extern volatile uint16_t CONTROL_Huan60_Add   ;
extern volatile uint16_t CONTROL_InHuan60_Min ;
extern volatile uint16_t CONTROL_InHuan60_Max ;

extern volatile uint16_t CONTROL_Huan70_Add   ;
extern volatile uint16_t CONTROL_InHuan70_Min ;
extern volatile uint16_t CONTROL_InHuan70_Max ;

extern volatile uint16_t CONTROL_Huan80_Add   ;
extern volatile uint16_t CONTROL_InHuan80_Min ;
extern volatile uint16_t CONTROL_InHuan80_Max ;

extern volatile uint16_t CONTROL_Huan90_Add   ;
extern volatile uint16_t CONTROL_InHuan90_Min ;
extern volatile uint16_t CONTROL_InHuan90_Max ;

extern volatile uint16_t CONTROL_Huan100_Add  ;
extern volatile uint16_t CONTROL_InHuan100_Min;
extern volatile uint16_t CONTROL_InHuan100_Max;

extern volatile uint16_t CONTROL_Huan1_Data	;
extern volatile uint16_t CONTROL_Huan2_Data	;
extern volatile uint16_t CONTROL_Huan3_Data	;
extern volatile uint16_t CONTROL_Huan4_Data	;
extern volatile uint16_t CONTROL_Huan5_Data	;
extern volatile uint16_t CONTROL_Huan6_Data	;
extern volatile uint16_t CONTROL_Huan7_Data	;
extern volatile uint16_t CONTROL_Huan8_Data	;
extern volatile uint16_t CONTROL_Huan9_Data	;

extern volatile uint16_t Now_Huan_Add;
extern volatile uint16_t Now_InHuan_Min;
extern volatile uint16_t Now_InHuan_Max;

extern uint16_t BB_Times;

extern uint8_t Bt_Send;

extern volatile int32_t Angle_PWM;
extern volatile int32_t Speed_PWM;
extern volatile int32_t Turn_PWM;
extern volatile int32_t L_Final_PWM;
extern volatile int32_t R_Final_PWM;
extern volatile uint8_t Stop_Flag;

void Judge_Huan_Form(void);			// 判断环的形态
void Send_Upper(void);				// 上位机发送

extern volatile int16_t Value_End_L;
extern volatile int16_t Value_End_R;
extern volatile int16_t Ave_End;	// 平均转速
void Get_End(void);					// 获取转速（编码器值）
void Get_Pose(void);				// 获取姿态（6050数据）

extern volatile uint16_t Value_Inductor_L;
extern volatile uint16_t Value_Inductor_R;
extern volatile uint16_t Value_Inductor_BL;
extern volatile uint16_t Value_Inductor_BR;
extern volatile int16_t Error_Ind;
extern volatile int16_t Eroor_Ind_Old;
void Get_Ind(void);					// 获取电感值

void Beep_Task(void);				// 蜂鸣器任务（并行）
void Go_or_Stop(void);				// PID值给电机和停车
void Reed_Stop(void);				// 干簧管停车

extern volatile uint8_t Huan_Flag;	// 记录环标志位
void In_Huan(void);					// 入环

extern volatile uint16_t Run_Time_Flag;
extern volatile uint32_t Run_Time;
extern volatile uint32_t Run_Distance;

#endif
