#include "AD.h"


void AD_Init(void)
{
    ADC_Config(AD_1);
    ADC_Config(AD_2);
    ADC_Config(AD_3);
    ADC_Config(AD_4);
    ADC_Config(AD_BAT);
}

uint16_t Get_Ind_V(uint8_t ADX)
{
    switch(ADX)
    {
        case AD_1:   return ADC_Ave(AD_1, 5);
        case AD_2:   return ADC_Ave(AD_2, 5);
        case AD_3:   return ADC_Ave(AD_3, 1);
        case AD_4:   return ADC_Ave(AD_4, 1);
        case AD_BAT: return ADC_Ave(AD_BAT, 200);
		default: return 0;
    }
}



