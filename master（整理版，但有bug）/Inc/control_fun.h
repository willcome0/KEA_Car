#ifndef __CONTROL_FUN_H
#define __CONTROL_FUN_H

#include "common.h"

extern volatile uint8_t Huan_No;	// ��¼����Ҫ�����ǵڼ�����

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

void Judge_Huan_Form(void);			// �жϻ�����̬
void Send_Upper(void);				// ��λ������

extern volatile int16_t Value_End_L;
extern volatile int16_t Value_End_R;
extern volatile int16_t Ave_End;	// ƽ��ת��
void Get_End(void);					// ��ȡת�٣�������ֵ��
void Get_Pose(void);				// ��ȡ��̬��6050���ݣ�

extern volatile uint16_t Value_Inductor_L;
extern volatile uint16_t Value_Inductor_R;
extern volatile uint16_t Value_Inductor_BL;
extern volatile uint16_t Value_Inductor_BR;
extern volatile int16_t Error_Ind;
extern volatile int16_t Eroor_Ind_Old;
void Get_Ind(void);					// ��ȡ���ֵ

void Beep_Task(void);				// ���������񣨲��У�
void Go_or_Stop(void);				// PIDֵ�������ͣ��
void Reed_Stop(void);				// �ɻɹ�ͣ��

extern volatile uint8_t Huan_Flag;	// ��¼����־λ
void In_Huan(void);					// �뻷

extern volatile uint16_t Run_Time_Flag;
extern volatile uint32_t Run_Time;
extern volatile uint32_t Run_Distance;

#endif
