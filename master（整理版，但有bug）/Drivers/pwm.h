#ifndef _PWM_H
#define _PWM_H

#include "common.h"
#include "SKEAZ1284.h"
//-----------------------------------  FTM  -----------------------------------

//      ģ��ͨ��        �˿�      ��ѡ��Χ                ����
//#define FTM0_CH0_PIN    PTA0        //B2 A0
//#define FTM0_CH1_PIN    PTA1        //B3 A1

//      ģ��ͨ��        �˿�      ��ѡ��Χ                ����
#define FTM1_CH0_PIN    PTH2        //H2 C4
#define FTM1_CH1_PIN    PTC5        //E7 C5

//      ģ��ͨ��        �˿�      ��ѡ��Χ                ����
#define FTM2_CH0_PIN   PTC0// H0        //C0  H0 F0              
#define FTM2_CH1_PIN   PTC1        //C1  H1 F1  
#define FTM2_CH2_PIN   PTC2// D0        //C2  G4 D0  
#define FTM2_CH3_PIN   PTC3// D1        //C3  G5 D1
#define FTM2_CH4_PIN   PTG6        //B4  G6  
#define FTM2_CH5_PIN   PTB5//  G7        //B5  G7              

//�ⲿ����ģ��ͨ��      �˿�      ��ѡ��Χ                ����
#define FTM0_COUNT_PIN  PTE0        //E7 A5  E0             A5��Ҫ�ã��븴λ������ͻ��                
                                           
#define FTM1_COUNT_PIN  PTE7        //E0 A5  E7             A5��Ҫ�ã��븴λ������ͻ��
                                           
#define FTM2_COUNT_PIN  PTA5        //E0 E7  A5             A5��Ҫ�ã��븴λ������ͻ��



typedef enum
{
    ftm0,
    ftm1,
    ftm2,
} FTMn;


typedef enum
{
    ftm_ch0,
    ftm_ch1,
    ftm_ch2,
    ftm_ch3,
    ftm_ch4,
    ftm_ch5,
    ftm_ch6,
    ftm_ch7,
} FTM_CHn;



//------------------------ PWM ------------------------

#define FTM0_PRECISON 1000u     //����ռ�ձȾ��ȣ���˼��ʹ��һ�����ڷֳɶ��ٷ֣��ֶ�Խ����������Խ�ߣ�����ռ�ձȵ�ʱ��duty�ķ�Χ����0-FTM0_PRECISON
#define FTM1_PRECISON 1000u     //����ռ�ձȾ��ȣ���˼��ʹ��һ�����ڷֳɶ��ٷ֣��ֶ�Խ����������Խ�ߣ�����ռ�ձȵ�ʱ��duty�ķ�Χ����0-FTM0_PRECISON
#define FTM2_PRECISON 1000u     //����ռ�ձȾ��ȣ���˼��ʹ��һ�����ڷֳɶ��ٷ֣��ֶ�Խ����������Խ�ߣ�����ռ�ձȵ�ʱ��duty�ķ�Χ����0-FTM0_PRECISON


void ftm_pwm_init(FTMn ftmn, FTM_CHn ch, uint32_t freq, uint32_t duty);
void ftm_pwm_duty(FTMn ftmn, FTM_CHn ch, uint32_t duty);
void ftm_pwm_freq(FTMn ftmn, uint32_t freq) ;
void ftm_count_init(FTMn ftmn);
uint16_t ftm_count_get(FTMn ftmn);
void ftm_count_clean(FTMn ftmn);

void FTM_PWM_set_CnV(FTMn ftmNo, FTM_CHn channel, uint16_t cnv);



#endif

//#ifndef FTM_H_
//#define FTM_H_


//#include "common.h"

//////FTMģ���
////#define FTM_0 0
////#define FTM_1 1
////#define FTM_2 2

//////ͨ���ţ�FTM0��FTM1��ͨ��0~ͨ��1��FTM2��ͨ��0~ͨ��5
////#define CHANNEL0 0
////#define CHANNEL1 1
////#define CHANNEL2 2
////#define CHANNEL3 3
////#define CHANNEL4 4
////#define CHANNEL5 5

//typedef enum   //FTMģ���
//{
//    FTM_0, FTM_1, FTM_2,
//} FTMn;

//typedef enum   //ͨ����
//{
//    CH_0, CH_1, CH_2, CH_3, CH_4, CH_5,
//} FTM_CHn;

///*------------------------PWMģʽ  FTM0ͨ��������ѡ��----------------------*/

////#define FTM0_CHANNEL0_GROUP 0     //FTM0ͨ��0������: 1 PTA0��, 2 PTB2��
////#define FTM0_CHANNEL1_GROUP 0     //FTM0ͨ��1������: 1 PTA1��, 2 PTB3��

///*------------------------PWMģʽ  FTM1ͨ��������ѡ��----------------------*/

////#define FTM1_CHANNEL0_GROUP 0     //FTM1ͨ��0������: 1 PTC4��, 2=PTH2��
////#define FTM1_CHANNEL1_GROUP 0     //FTM1ͨ��1������: 1 PTC5��, 2=PTE7��

///*------------------------PWMģʽ  FTM2ͨ��������ѡ��-----------------------*/

//#define FTM2_CHANNEL0_GROUP  1    //FTM2ͨ��0������: 1 PTC0��, 2 PTH0��, 3 PTF0��
//#define FTM2_CHANNEL1_GROUP  1    //FTM2ͨ��1������: 1 PTC1��, 2 PTH1��, 3 PTF1��
//#define FTM2_CHANNEL2_GROUP  1    //FTM2ͨ��2������: 1 PTC2��, 2 PTD0��, 3 PTG4��
//#define FTM2_CHANNEL3_GROUP  1    //FTM2ͨ��3������: 1 PTC3��, 2 PTD1��, 3 PTG5��
//#define FTM2_CHANNEL4_GROUP  1    //FTM2ͨ��4������: 1 PTB4��, 2 PTG6��
//#define FTM2_CHANNEL5_GROUP  1    //FTM2ͨ��5������: 1 PTB5��, 2 PTG7��

///*------------------------����ģʽ  ͨ��������ѡ��-----------------------*/

//#define FTM0_COUNT_PIN  PTE0        //PTE7  PTA5  PTE0             A5��Ҫ�ã��븴λ������ͻ��                                                  
//#define FTM1_COUNT_PIN  PTE7        //PTE0  PTA5  PTE7             A5��Ҫ�ã��븴λ������ͻ��                         
//#define FTM2_COUNT_PIN  PTA5        //PTE0  PTE7  PTA5             A5��Ҫ�ã��븴λ������ͻ��


//void FTM_PWM_init(FTMn ftmNo, FTM_CHn channel, float freq, float duty);
//void FTM_PWM_set_duty(FTMn ftmNo, FTM_CHn channel, float duty);
//void FTM_PWM_set_CnV(FTMn ftmNo, FTM_CHn channel, uint16_t cnv);
//void FTM_Count_Mux(FTMn ftmn);

//#endif

////#ifndef _PWM_H
////#define _PWM_H

////#include "common.h"
////#include "SKEAZ1284.h"


/////***************************ģ��ͨ��ѡ��*******************************************/

//////      ģ��ͨ��        �˿�      ��ѡ��Χ
////#define FTM0_CH0_PIN    PTA0        //PTB2 PTA0
////#define FTM0_CH1_PIN    PTA1        //PTB3 PTA1

////#define FTM1_CH0_PIN    PTH2        //PTH2 PTC4
////#define FTM1_CH1_PIN    PTC5        //PTE7 PTC5

////#define FTM2_CH0_PIN    PTC0        //PTC0  PTH0  PTF0              
////#define FTM2_CH1_PIN    PTC1        //PTC1  PTH1  PTF1 

////#define FTM2_CH2_PIN    PTC2        //PTC2  PTG4  PTD0  
////#define FTM2_CH3_PIN    PTC3        //PTC3  PTG5  PTD1
////#define FTM2_CH4_PIN    PTB4        //PTB4  PTG6  
////#define FTM2_CH5_PIN    PTB5        //PTB5  PTG7             

/////********************************************************************************/
//////�ⲿ����ģ��ͨ��        �˿�        ��ѡ��Χ                           ����

////#define FTM0_COUNT_PIN  PTE0        //PTE7  PTA5  PTE0             A5��Ҫ�ã��븴λ������ͻ��                                                  
////#define FTM1_COUNT_PIN  PTE7        //PTE0  PTA5  PTE7             A5��Ҫ�ã��븴λ������ͻ��                         
////#define FTM2_COUNT_PIN  PTA5        //PTE0  PTE7  PTA5             A5��Ҫ�ã��븴λ������ͻ��





//////------------------------ PWM ------------------------

////#define FTM0_PRECISON 10000u     //����ռ�ձȾ��ȣ���˼��ʹ��һ�����ڷֳɶ��ٷ֣��ֶ�Խ����������Խ�ߣ�����ռ�ձȵ�ʱ��duty�ķ�Χ����0-FTM0_PRECISON
////#define FTM1_PRECISON 10000u     //����ռ�ձȾ��ȣ���˼��ʹ��һ�����ڷֳɶ��ٷ֣��ֶ�Խ����������Խ�ߣ�����ռ�ձȵ�ʱ��duty�ķ�Χ����0-FTM0_PRECISON
////#define FTM2_PRECISON 10000u     //����ռ�ձȾ��ȣ���˼��ʹ��һ�����ڷֳɶ��ٷ֣��ֶ�Խ����������Խ�ߣ�����ռ�ձȵ�ʱ��duty�ķ�Χ����0-FTM0_PRECISON


////void ftm_pwm_init(FTMn ftmn, FTM_CHn ch, uint32_t freq, uint32_t duty);
////void ftm_pwm_duty(FTMn ftmn, FTM_CHn ch, uint32_t duty);
////void ftm_pwm_freq(FTMn ftmn, uint32_t freq) ;
////void ftm_count_init(FTMn ftmn);
////uint16_t ftm_count_get(FTMn ftmn);
////void ftm_count_clean(FTMn ftmn);



////#endif
