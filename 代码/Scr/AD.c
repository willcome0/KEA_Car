#include "AD.h"


void AD_Init(void)
{
    ADC_Config(0);
    ADC_Config(1);
    ADC_Config(15);
    ADC_Config(14);
    ADC_Config(9);
}

uint16_t Get_Ind_V(uint8_t ADX)
{
    switch(ADX)
    {
        case AD_1:   return ADC_Ave(0 , 3);
        case AD_2:   return ADC_Ave(1 , 3);
        case AD_3:   return ADC_Ave(15, 3);
        case AD_4:   return ADC_Ave(14, 3);
        case AD_BAT: return ADC_Ave(9, 200);
    }
}



