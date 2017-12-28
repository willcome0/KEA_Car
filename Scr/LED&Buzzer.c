#include "LED&Buzzer.h"


void LED_Init(void)
{
    Pin_Output_Config(LED_Red_Port,   LED_Red_Pin,   1);
    Pin_Output_Config(LED_Green_Port, LED_Green_Pin, 1);
    Pin_Output_Config(LED_Blue_Port,  LED_Blue_Pin,  1);
}
void Buzzer_Init(void)
{
    Pin_Output_Config(Buzzer_Port, Buzzer_Pin, 0);

}