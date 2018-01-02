#ifndef __LED_H
#define __LED_H

#include "common.h"

/***********************************************************
 * 
 * 引脚重命名
 * 
 **********************************************************/
#define LED_Red_Port    PTE
#define LED_Red_Pin     PTE0

#define LED_Green_Port  PTG
#define LED_Green_Pin   PTG0

#define LED_Blue_Port   PTE
#define LED_Blue_Pin    PTE1

#define Buzzer_Port     PTB
#define Buzzer_Pin      PTB1

#define LED_Red_ON()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0)
#define LED_Red_OFF()    Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1)

#define LED_Green_ON()   Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0)
#define LED_Green_OFF()  Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1)

#define LED_Blue_ON()    Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0)
#define LED_Blue_OFF()   Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)

#define Beep_ON()        Pin_Output_Set(Buzzer_Port, Buzzer_Pin, 1);
#define Beep_OFF()       Pin_Output_Set(Buzzer_Port, Buzzer_Pin, 0);



/***********************************************************
 * 
 * 蜂鸣器提示音
 * 
 **********************************************************/
#define Beep_Time(time)  {Beep_ON();  Delay_ms(time);  Beep_OFF();}

/***********************************************************
 * 
 * 函数声明
 * 
 **********************************************************/
void LED_Init(void);
void Buzzer_Init(void);

#endif
