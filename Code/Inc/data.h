#ifndef __DATA_H
#define __DATA_H

#include "common.h"






struct PID//PID�ṹ��
{
    uint16_t P;
    uint16_t I;
    uint16_t D;
    uint16_t tp;
	  uint16_t td;
};
struct TARGET//Ŀ��ֵ�ṹ��
{
    uint16_t Angle;
    uint16_t Speed;   //Ŀ���ٶ�
};



struct PLAN
{
    struct PID Angle; //�ǶȻ�ֵ
    struct PID Speed; //�ٶȻ�ֵ
    struct PID Turn;  //ת�价ֵ
    
    struct TARGET Target;//��Ŀ��ֵ
    
    uint16_t Safe_Angle;
};
struct CON
{
	uint8_t Run;
	uint8_t LED;
	uint8_t Buzzer;
	uint8_t BT;

};



extern struct PLAN Plan1;//Ҫ���෽���������
extern struct PLAN Blue;//��������
extern struct CON  Con;



extern int16_t Add_L;
extern int16_t Target_Angle;
extern int16_t Target_Speed;

extern int16_t Balance_P;
extern float Balance_D;

extern int16_t Speed_P;
extern float Speed_I;

extern int16_t Turn_P;

/*���ò˵�����*/
extern uint8_t Set_LED;
extern uint8_t Set_Beep;
extern uint8_t Bluetooth;

extern volatile int16_t Value_End;

uint32_t ABS(int32_t Num);//ȡ����ֵ

#endif


