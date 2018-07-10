#include "LED&Buzzer.h"





/***********************************************************
 *
 * ��ʼ��
 *
 **********************************************************/
void LED_Init(void)
{
    Pin_Output_Config(LED_Red_Port,   LED_Red_Pin,   1);
    Pin_Output_Config(LED_Green_Port, LED_Green_Pin, 1);
    Pin_Output_Config(LED_Blue_Port,  LED_Blue_Pin,  1);
	
	
	Pin_Output_Set(LED_Red_Port, LED_Red_Pin, RESET);
}
void Buzzer_Init(void)
{
    Pin_Output_Config(Buzzer_Port, Buzzer_Pin, 1);
	
	Pin_Output_Set(Buzzer_Port, Buzzer_Pin, SET);
//	while(1);
	Delay_ms(5);
	Beep_OFF();
}




/***********************************************************
 *
 * ����־λ�ĵ�&������ON����
 *
 **********************************************************/
void LED_Red_ON(void)       //��
{
    if(1 == _Com_LED_)
    {
       Pin_Output_Set(LED_Red_Port, LED_Red_Pin, RESET);
    }
}
void LED_Green_ON(void)     //��
{
    if(1 == _Com_LED_)
    {
       Pin_Output_Set(LED_Green_Port, LED_Green_Pin, RESET);
    }
}
void LED_Blue_ON(void)      //��
{
    if(1 == _Com_LED_)
    {
       Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  RESET);
    }
}
void LED_Orange_ON(void)    //��
{
    if(1 == _Com_LED_)
    {
       Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   RESET);
       Pin_Output_Set(LED_Green_Port, LED_Green_Pin, RESET);
    }
}
void LED_Purple_ON(void)     //��
{
    if(1 == _Com_LED_)
    {
       Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   RESET);
       Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  RESET);
    }
}
void LED_Indigo_ON(void)     //��
{
    if(1 == _Com_LED_)
    {
       Pin_Output_Set(LED_Green_Port, LED_Green_Pin, RESET);
       Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  RESET);

    }
}
void LED_White_ON(void)     //��
{
    if(1 == _Com_LED_)
    {
        Pin_Output_Set(LED_Red_Port,   LED_Red_Pin,   RESET);
        Pin_Output_Set(LED_Green_Port, LED_Green_Pin, RESET);
        Pin_Output_Set(LED_Blue_Port,  LED_Blue_Pin,  RESET);
    }
}


void Beep_ON(void)
{
    if(1 == _Com_Buzzer_)
    {
        Pin_Output_Set(Buzzer_Port, Buzzer_Pin, SET);
    }
}


