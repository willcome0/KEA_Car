#include "motor.h"

//���Ƶ��Ϊ12.5KHz�� �Զ�װ��ֵ1600
void Motor_Init(void)
{
    //ע�⣺�ӿ�����Ͱ�Ƶ�ʺ�ռ�ո����ˣ�12.5K Hz  0ռ�գ�
    ftm_pwm_init(ftm2,ftm_ch3,12500,0);//���� //��ת
    ftm_pwm_init(ftm2,ftm_ch2,12500,0);
    Pin_Output_Config(Motor_L_EN_Port, Motor_L_EN_Pin, 0);
    
    ftm_pwm_init(ftm2,ftm_ch0,12500,0);//���� //��ת
    ftm_pwm_init(ftm2,ftm_ch5,12500,0);//��߷��ˣ����ߵ�PB5  1
    Pin_Output_Config(Motor_R_EN_Port, Motor_R_EN_Pin, 0);
    
//    ftm_pwm_init(FTM_2,CH_5,13000,3000);  //APWM_1  PB5   FTM2_CH5   ��
//    ftm_pwm_init(FTM_2,CH_0,13000,3000);  //APWM_2  PC0   FTM2_CH0
//    ftm_pwm_init(FTM_2,CH_3,13000,3000);  //BPWM_1  PC3   FTM2_CH3   ��
//    ftm_pwm_init(FTM_2,CH_2,13000,3000);  //BPWM_2  PC2   FTM2_CH2 

//    FTM_PWM_init(FTM_2, CH_0, 12.5, 1);   //APWM_2  PC0   FTM2_CH0   ��   �� 
//    FTM_PWM_init(FTM_2, CH_5, 12.5, 1);    //APWM_1  PB5   FTM2_CH5

//    FTM_PWM_init(FTM_2, CH_2, 12.5, 1);    //BPWM_2  PC2   FTM2_CH2   ��   ��
//    FTM_PWM_init(FTM_2, CH_3, 12.5, 1);    //BPWM_1  PC3   FTM2_CH3
    
    
//    FTM_PWM_set_CnV(ftm2, ftm_ch0, 100);  //��
////    Pin_Output_Config(PTC, PTC0, 0);
//    FTM_PWM_set_CnV(ftm2, ftm_ch5, 800);
//    
//       
//    FTM_PWM_set_CnV(ftm2, ftm_ch2, 100);
////    Pin_Output_Config(PTC, PTC2, 0);
//    FTM_PWM_set_CnV(ftm2, ftm_ch3, 800);
    
    
//    Pin_Output_Config(PTC, PTC0, 0);
//    Pin_Output_Config(PTB, PTB5, 1);
//    
//    Pin_Output_Config(PTC, PTC2, 0);
//    Pin_Output_Config(PTC, PTC3, 1);
}

void Motor_Set_Go_Speed(uint16_t L, uint16_t R)
{
    FTM_PWM_set_CnV(ftm2, ftm_ch3, L);
    FTM_PWM_set_CnV(ftm2, ftm_ch2, 1);
    
    FTM_PWM_set_CnV(ftm2, ftm_ch0, R);
    FTM_PWM_set_CnV(ftm2, ftm_ch5, 1);
}
void Motor_Set_Back_Speed(uint16_t L, uint16_t R)
{
    FTM_PWM_set_CnV(ftm2, ftm_ch3, 1);
    FTM_PWM_set_CnV(ftm2, ftm_ch2, L);
    
    FTM_PWM_set_CnV(ftm2, ftm_ch0, 1);
    FTM_PWM_set_CnV(ftm2, ftm_ch5, R);
}

void Motor_L_Back_V(uint16_t L)
{
    FTM_PWM_set_CnV(ftm2, ftm_ch3, L);
    FTM_PWM_set_CnV(ftm2, ftm_ch2, 1);
}
void Motor_L_Go_V(uint16_t L)
{
    FTM_PWM_set_CnV(ftm2, ftm_ch3, 1);
    FTM_PWM_set_CnV(ftm2, ftm_ch2, L);
}

void Motor_R_Back_V(uint16_t R)
{
    FTM_PWM_set_CnV(ftm2, ftm_ch0, R);
    FTM_PWM_set_CnV(ftm2, ftm_ch5, 1);
}
void Motor_R_Go_V(uint16_t R)
{
    FTM_PWM_set_CnV(ftm2, ftm_ch0, 1);
    FTM_PWM_set_CnV(ftm2, ftm_ch5, R);
}