#include "key.h"

void KEY_Init(void)
{
    Pin_Input_Config(KEY_Up_Port,    KEY_Up_Pin,    1);
    Pin_Input_Config(KEY_Down_Port,  KEY_Down_Pin,  1);
    Pin_Input_Config(KEY_Mid_Port,   KEY_Mid_Pin,   1);
    Pin_Input_Config(KEY_Left_Port,  KEY_Left_Pin,  1);
    Pin_Input_Config(KEY_Right_Port, KEY_Right_Pin, 1);
}


uint8_t Get_Key(void)
{
//    #define Key_Delay_Time 50;
    static uint16_t Key_Keep = 0;
    static uint8_t Key_Delay = 60;
    
    volatile uint8_t temp_return = 0;
    
	if(0 == Read_Input_State(KEY_Up_Port, KEY_Up_Pin))
	{
		Delay_ms(Key_Delay);
		if(0 == Read_Input_State(KEY_Up_Port, KEY_Up_Pin))
		{
            Key_Keep++;
            if(Key_Keep >50)
                Key_Delay = 1;
            else if(Key_Keep > 12)
                Key_Delay = 10;
            else if(Key_Keep > 6)
                Key_Delay = 30;
            else if(Key_Keep > 3)
                Key_Delay = 50;
            
            temp_return = Press_Up; 
            Beep_Time(2);

		}
        return temp_return;
	}
	
	else if(0 == Read_Input_State(KEY_Down_Port, KEY_Down_Pin))
	{
		Delay_ms(Key_Delay);
		if(0 == Read_Input_State(KEY_Down_Port, KEY_Down_Pin))
		{
            Key_Keep++;
            if(Key_Keep >50)
                Key_Delay = 1;
            else if(Key_Keep > 12)
                Key_Delay = 10;
            else if(Key_Keep > 6)
                Key_Delay = 30;
            else if(Key_Keep > 3)
                Key_Delay = 50;
            temp_return = Press_Down;  
            Beep_Time(2);

		}
        return temp_return;
	}
	
	else if(0 == Read_Input_State(KEY_Mid_Port, KEY_Mid_Pin))
	{
		Delay_ms(Key_Delay*1.1);
		if(0 == Read_Input_State(KEY_Mid_Port, KEY_Mid_Pin))
		{
			Beep_Time(2);
            temp_return = Press_Mid;
		}
        return temp_return;
	}
	
	else if(0 == Read_Input_State(KEY_Left_Port, KEY_Left_Pin))
	{
		Delay_ms(Key_Delay);
		if(0 == Read_Input_State(KEY_Left_Port, KEY_Left_Pin))
		{
			Beep_Time(2);
            temp_return = Press_Left;
		}
        return temp_return;
	}
	
	else if(0 == Read_Input_State(KEY_Right_Port, KEY_Right_Pin))
	{
		Delay_ms(100);  /*****/
		if(0 == Read_Input_State(KEY_Right_Port, KEY_Right_Pin))
		{
			Beep_Time(2);
            temp_return = Press_Right;  //右键也改为中键
		}
		return temp_return;
	}
	else
    {
        Key_Delay = 70;
        Key_Keep = 0;
		return 0;
    }
}


