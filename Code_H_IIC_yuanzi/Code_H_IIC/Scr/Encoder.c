#include "Encoder.h"

void Encoder_Init(void)
{
    ftm_count_init(ftm0);
    ftm_count_init(ftm1);

    Pin_Input_Config(Dir_End_L_Port, Dir_End_L_Pin, 1);
    Pin_Input_Config(Dir_End_R_Port, Dir_End_R_Pin, 1);
}
uint8_t End_Read_Dir(uint8_t Dir)
{
    switch(Dir)
    {
        case 0:		return Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin);
        case 1:		return Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin);
		default:	return 0;
    }
}
uint8_t Debug_Pin_Init(void)
{
	Pin_Output_Config(PTE, PTE0, 1);
	Pin_Output_Config(Dir_End_L_Port, Dir_End_L_Pin, 1);
}
