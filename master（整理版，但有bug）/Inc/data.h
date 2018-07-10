#ifndef __DATA_H
#define __DATA_H

#include "common.h"


//各部分参数在数组中的下标偏移量
#define PLAN1_ARRAY_OFFSET		0
#define PLAN2_ARRAY_OFFSET		40
#define PLAN3_ARRAY_OFFSET		80
#define PLAN4_ARRAY_OFFSET		120
#define PLAN5_ARRAY_OFFSET		160
#define COM_ARRAY_OFFSET		200

extern uint16_t uint16_TMEP;

//struct PID//PID结构体
//{
//    uint16_t P;
//    uint16_t I;
//    uint16_t D;
//    uint16_t tp;
//	  uint16_t td;
//};
//struct TARGET//目标值结构体
//{
//    uint16_t Angle;
//    uint16_t Speed;   //目标速度
//};



//struct PLAN
//{
//    struct PID Angle; //角度环值
//    struct PID Speed; //速度环值
//    struct PID Turn;  //转弯环值

//    struct TARGET Target;//各目标值

//    uint16_t Safe_Angle;
//};
//struct CON
//{

//	uint16_t LED;
//	uint16_t Buzzer;
//	uint16_t BT;
//	uint16_t Run;

//	uint16_t XX1;
//	uint16_t XX2;
//	uint16_t XX3;
//	uint16_t XX4;
//	uint16_t XX5;

//};

/******************* 方案菜单 ************************/
#define _INDEX_Target_Angle_	0
#define _INDEX_Target_Speed_	1
#define _INDEX_AnglePID_P_		2
#define _INDEX_AnglePID_D_		3
#define _INDEX_SpeedPID_P_ 		4
#define _INDEX_SpeedPID_I_ 		5
#define _INDEX_TurnPID_P_ 		6
#define _INDEX_TurnPID_D_ 		7
#define _INDEX_HuanTurn_Add_    8   //环拐弯补偿，值为10时补偿为0。25时补偿为15


#define _INDEX_Huan1_Para_		9  // 储存环1方向和大小
#define _INDEX_Huan2_Para_		10  // 储存环2方向和大小
#define _INDEX_Huan3_Para_		11  // 储存环3方向和大小
#define _INDEX_Huan4_Para_		12  // 储存环4方向和大小
#define _INDEX_Huan5_Para_		13  // 储存环5方向和大小
#define _INDEX_Huan6_Para_		14  // 储存环6方向和大小
#define _INDEX_Huan7_Para_		15  // 储存环7方向和大小
#define _INDEX_Huan8_Para_		16  // 储存环8方向和大小
#define _INDEX_Huan9_Para_		17  // 储存环9方向和大小

#define _INDEX_Huan50_Add_		20
#define _INDEX_InHuan50_Min_	21
#define _INDEX_InHuan50_Max_	22

#define _INDEX_Huan60_Add_		23
#define _INDEX_InHuan60_Min_	24
#define _INDEX_InHuan60_Max_	25

#define _INDEX_Huan70_Add_		26
#define _INDEX_InHuan70_Min_	27
#define _INDEX_InHuan70_Max_	28

#define _INDEX_Huan80_Add_		29
#define _INDEX_InHuan80_Min_	30
#define _INDEX_InHuan80_Max_	31

#define _INDEX_Huan90_Add_		32
#define _INDEX_InHuan90_Min_	33
#define _INDEX_InHuan90_Max_	34

#define _INDEX_Huan100_Add_		35
#define _INDEX_InHuan100_Min_	36
#define _INDEX_InHuan100_Max_	37

/******************* 方案菜单 修改一 ↑******************/

#define _P1_Target_Angle_		ALL_DATA[0]
#define _P1_Target_Speed_		ALL_DATA[1]
#define _P1_AnglePID_P_			ALL_DATA[2]
#define _P1_AnglePID_D_			ALL_DATA[3]
#define _P1_SpeedPID_P_			ALL_DATA[4]
#define _P1_SpeedPID_I_			ALL_DATA[5]
#define _P1_TurnPID_P_			ALL_DATA[6]
#define _P1_TurnPID_D_			ALL_DATA[7]

/******************* 设置菜单 ************************/
#define _Com_LED_				ALL_DATA[200]	
#define _Com_Buzzer_			ALL_DATA[201]
#define _Com_BT_				ALL_DATA[202]	
#define _Com_Debug_				ALL_DATA[203]	// 调试开关。开后电机一直禁能
#define _Com_Huan_Value_		ALL_DATA[204]   // 环处电磁阈值
#define _Com_InHuan_Min_		ALL_DATA[205]
#define _Com_InHuan_Max_		ALL_DATA[206]
#define _Com_XX4_				ALL_DATA[207]
#define _Com_XX5_				ALL_DATA[208]

#define _Com_Plan_				ALL_DATA[209]	// 使用范围为1~5，代表方案一到方案五
#define _Com_CountDown_         ALL_DATA[210]   // 发车倒计时时间
#define _Com_RunProtect_        ALL_DATA[211]	// 发车时的保护
#define _Com_RunTimeStop_       ALL_DATA[212]	// 定时停车
#define _Com_RunDisStop_       	ALL_DATA[213]	// 定距停车
#define _Com_Huan_LR_       	ALL_DATA[214]	// 设置左入环还是右入环
#define _Com_HuanOut_L_Add_     ALL_DATA[215]	// 左出环补偿
#define _Com_HuanOut_R_Add_     ALL_DATA[216]	// 右出环补偿
#define _Com_HuanOut_AddDis_    ALL_DATA[217]	// 出环补偿路程
#define _Com_Go_Mode_    		ALL_DATA[218]	// 发车模式（普通、预赛、决赛）
/******************* 设置菜单 修改一 ↑******************/

//将flash中得数据缓存到数组里
#define Cache_ALL_DATA()	{for(uint16_t i=0; i<256; i++)    ALL_DATA[i] = FLASH_Read(DATA_FLASH, i*2, uint16_t);}

//extern struct PLAN Plan1;//要更多方案在这里加
//extern struct PLAN Blue;//蓝牙方案
//extern struct CON  Con;



//extern int16_t Add_L;
//extern int16_t Target_Angle;
//extern int16_t Target_Speed;

//extern int16_t Balance_P;
//extern float Balance_D;

//extern int16_t Speed_P;
//extern float Speed_I;

//extern int16_t Turn_P;

///*设置菜单数据*/
//extern uint8_t Set_LED;
//extern uint8_t Set_Beep;
//extern uint8_t Bluetooth;

//extern volatile int16_t Value_End;

/*********车体姿态相关全局变量*********/

extern volatile int16_t 	Accel_X;
extern volatile int16_t 	Accel_Y;
extern volatile int16_t 	Accel_Z;
extern volatile int16_t 	Gyro_X;
extern volatile int16_t 	Gyro_Y;
extern volatile int16_t 	Gyro_Z;
extern volatile float 		Pitch;
extern volatile float 		Roll;
extern volatile float 		Yaw;



uint32_t ABS(int32_t Num);//取绝对值

void Data_Init(void);

#endif


