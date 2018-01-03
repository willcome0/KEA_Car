#ifndef __LED_H
#define __LED_H

#include "common.h"

/***********************************************************
 * 
 * 引脚重命名
 * 
 **********************************************************/
#define LED_Red_Port    PTE
#define LED_Red_Pin     PTE1

#define LED_Green_Port  PTG
#define LED_Green_Pin   PTG1

#define LED_Blue_Port   PTE
#define LED_Blue_Pin    PTG0

#define Buzzer_Port     PTB
#define Buzzer_Pin      PTB1

#define LED_Red_ON()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0) //红
#define LED_Red_OFF()    Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1)

#define LED_Green_ON()   Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0) //绿
#define LED_Green_OFF()  Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1)

#define LED_Blue_ON()    Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //蓝
#define LED_Blue_OFF()   Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)

#define LED_Orange_ON()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0) //橙色
#define LED_Orange_OFF()    Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1)

#define LED_Purple_ON()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //紫色
#define LED_Purple_OFF()    Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)

#define LED_Indigo_ON()     Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //靛色
#define LED_Indigo_OFF()    Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)

#define LED_White_ON()      Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   0), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 0), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  0) //白色
#define LED_White_OFF()     Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   1), Pin_Output_Set(LED_Green_Port, LED_Green_Pin, 1), Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  1)


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
