#ifndef __LED_BUZZER_H
#define __LED_BUZZER_H

#include "common.h"

/*********************�����ӵļ��ݴ���**************************/

#if (PCB_VERSION == 20)    //����PCB V2.0 �궨��
    #define LED_Red_Port    PTG
    #define LED_Red_Pin     PTG2

    #define LED_Green_Port  PTG
    #define LED_Green_Pin   PTG1

    #define LED_Blue_Port   PTE
    #define LED_Blue_Pin    PTG0

    #define Buzzer_Port     PTE
    #define Buzzer_Pin      PTE5

#elif (PCB_VERSION == 30)  //����PCB V3.0 �궨��
    #define LED_Red_Port    PTE
    #define LED_Red_Pin     PTE1

    #define LED_Green_Port  PTG
    #define LED_Green_Pin   PTG1                 

    #define LED_Blue_Port   PTE
    #define LED_Blue_Pin    PTG0

    #define Buzzer_Port     PTB
    #define Buzzer_Pin      PTB1
    
#elif (PCB_VERSION == 0)  //���ݿ����� �궨��
    #define LED_Red_Port    PTE
    #define LED_Red_Pin     PTE1

    #define LED_Green_Port  PTG
    #define LED_Green_Pin   PTG1                 

    #define LED_Blue_Port   PTE
    #define LED_Blue_Pin    PTG0

    #define Buzzer_Port     PTE
    #define Buzzer_Pin      PTE5
#endif
/**************************************************************************************/

#define LED_Red_ON()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   RESET) //��
#define LED_Red_OFF()    Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   SET)

#define LED_Green_ON()   Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0) //��
#define LED_Green_OFF()  Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1)

#define LED_Blue_ON()    Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //��
#define LED_Blue_OFF()   Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)

#define LED_Orange_ON()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0) //��ɫ
#define LED_Orange_OFF()    Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1)

#define LED_Purple_ON()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //��ɫ
#define LED_Purple_OFF()    Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)

#define LED_Indigo_ON()     Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //��ɫ
#define LED_Indigo_OFF()    Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)

#define LED_White_ON()      Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //��ɫ
#define LED_White_OFF()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)


#define Beep_ON()        Pin_Output_Set(Buzzer_Port, Buzzer_Pin, SET);
#define Beep_OFF()       Pin_Output_Set(Buzzer_Port, Buzzer_Pin, RESET);



/***********************************************************
 * 
 * ��������ʾ��
 * 
 **********************************************************/
#define Beep_Time(time)  {Beep_ON();  Delay_ms(time);  Beep_OFF();}

/***********************************************************
 * 
 * ��������
 * 
 **********************************************************/
void LED_Init(void);
void Buzzer_Init(void);

#endif
