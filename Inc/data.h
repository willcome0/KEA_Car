#ifndef __DATA_H
#define __DATA_H

#include "common.h"






struct PID//PID�ṹ��
{
    int16_t P;
    int16_t I;
    int16_t D;
    int16_t tp;
	  int16_t td;
};
struct TARGET//Ŀ��ֵ�ṹ��
{
    int16_t Angle;
    int16_t Speed;   //Ŀ���ٶ�
};



struct PLAN
{
    struct PID Angle; //�ǶȻ�ֵ
    struct PID Speed; //�ٶȻ�ֵ
    struct PID Turn;  //ת�价ֵ
    
    struct TARGET Target;//��Ŀ��ֵ
    
    int16_t Safe_Angle;
};
extern struct PLAN Plan1;//Ҫ���෽���������
extern struct PLAN Blue;//��������




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



#endif


