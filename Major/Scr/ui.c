#include "ui.h"

/*更新显示方案几，本文件内部使用*/
void Show_Plan(void)
{
	switch(_Com_Plan_)
	{
		case 1:	OLED_Show_StrAll(0, 19, "        案 一         ", Normal);	break;
		case 2:	OLED_Show_StrAll(0, 19, "        案 二         ", Normal);	break;
		case 3:	OLED_Show_StrAll(0, 19, "        案 三         ", Normal);	break;
		case 4:	OLED_Show_StrAll(0, 19, "        案 四         ", Normal);	break;
		case 5:	OLED_Show_StrAll(0, 19, "        案 五         ", Normal);	break;
		default: 														    break;
	}
}

uint8_t UI_Main(void)
{
    uint8_t UI_Case = 1;
    uint8_t Case_Temp = 0;
	OLED_Clear();
//    OLED_Show_StrAll(0,  0, "      主  菜  单      ", Normal);
	OLED_Show_StrAll(0, 3, "        发 车         ", Normal);

	_Com_Plan_ = _Com_Plan_<1?5:_Com_Plan_;
	_Com_Plan_ = _Com_Plan_>5?1:_Com_Plan_;
	Show_Plan();

	OLED_Show_StrAll(0, 35, "        外 设         ", Normal);
	OLED_Show_StrAll(0, 51, "        设 置         ", Normal);

	for(;;)
	{
		Case_Temp = UI_Case;
		switch (Get_Key())
		{
			case Press_Up:   	UI_Case--;
                                UI_Case = UI_Case<1 ? 4:UI_Case;
                                break;

			case Press_Down: 	UI_Case++;
                                UI_Case=UI_Case>4?1:UI_Case;
                                break;

			case Press_Mid:
								switch(UI_Case)
								{
									case 1:		return 1;
									case 2:		return 2;
									case 3:		return 3;
									case 4:		return 4;
									default:	return 0;// 防止出现其他情况
								}

			case Press_Left:	if(UI_Case==2)
								{
									_Com_Plan_--;
									_Com_Plan_ = _Com_Plan_<1 ? 5:_Com_Plan_;
									/******************更新并保存数据***********************/

									uint16_TMEP = _Com_Plan_;
									Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
									_Com_Plan_ = uint16_TMEP; 	// 更新该数组成员的值
									FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
									FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

									/******************************************************/
									Show_Plan();
								}
								break;

			case Press_Right:	if(UI_Case==2)
								{
									_Com_Plan_++;
									_Com_Plan_ = _Com_Plan_>5?1:_Com_Plan_;
									/******************更新并保存数据***********************/

									uint16_TMEP = _Com_Plan_;
									Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
									_Com_Plan_ = uint16_TMEP; 	// 更新该数组成员的值
									FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
									FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

									/******************************************************/
									Show_Plan();
								}
								break;

			default:            break;
		}

		if(Case_Temp != UI_Case)  // 菜单号有改动时，清楚指示
		{
			OLED_Show_Char(32,  3, ' ', 12, Normal);
            OLED_Show_Char(32, 19, ' ', 12, Normal);
            OLED_Show_Char(32, 35, ' ', 12, Normal);
            OLED_Show_Char(32, 51, ' ', 12, Normal);
		}
		switch (UI_Case)  // 判断所处菜单号，显示对应指示
		{
            case 1: OLED_Show_Char(32,  3, '@', 12, Normal);  break;
            case 2: OLED_Show_Char(32, 19, '@', 12, Normal);  break;
            case 3: OLED_Show_Char(32, 35, '@', 12, Normal);  break;
            case 4: OLED_Show_Char(32, 51, '@', 12, Normal);  break;
		}
		OLED_Refresh_Gram();
	}
}

/*倒计时函数，本文件内部使用*/
uint8_t CountDown(uint16_t time)
{
    OLED_Clear();

    for(uint8_t i=time; i!=0; i--)
    {
        Beep_Time(100);
        OLED_Show_Char48_64(40, 0, i+'0', Normal);
        OLED_Refresh_Gram();
        //考虑到最后一秒蜂鸣器时常
        if(1 == i)
        {
            Delay_ms(600);
            continue;
        }
        Delay_ms(700);
		switch (Get_Key())
		{
			case Press_Left: return 1;
		}
    }
    Beep_Time(300);
	return 0;
//    OLED_Refresh_Gram();
}

uint8_t UI_Go(void)
{
	OLED_Clear();
	
    for(;;)
    {
		
		uint8_t str[30];

		sprintf((char *)str, "s%-.2f", (float)Run_Distance/DIS_RATIO);
//		sprintf((char *)str, "s%-.2f", (float)Run_Distance);
		OLED_Show_Str(0, 27, str, 12, 1);
		sprintf((char *)str, "t%-.2f", (float)Run_Time*PERIOD);
//		sprintf((char *)str, "t%-.2f", (float)Run_Time);
		OLED_Show_Str(0, 40, str, 12, 1);
		sprintf((char *)str, "v%-.2f", (float)Run_Distance/DIS_RATIO/((float)Run_Time*PERIOD));
		OLED_Show_Str(0, 53, str, 12, 1);
		sprintf((char *)str, "V%-.2f", (float)Run_Distance/Run_Time);
		OLED_Show_Str(98, 35, str, 12, 1);
		
        OLED_Show_Str(6,  0, "<", 12, Normal);
        OLED_Show_Char48_64(55, 0, _Com_CountDown_+'0', Normal);
		
		switch( _Com_Go_Mode_ )
		{
			case 0:
					sprintf((char *)str, "普通>");
					break;
			
			case 1:
					sprintf((char *)str, "预赛>");
					break;
			
			case 2:
					sprintf((char *)str, "决赛>");
					break;
		}
		OLED_Show_StrAll(98, 48, str, Normal);
		
		_Com_CountDown_ = _Com_CountDown_>=5?5:_Com_CountDown_;
        switch (Get_Key())
        {
            case Press_Up:      _Com_CountDown_++;
                                _Com_CountDown_ = _Com_CountDown_>=5 ? 5:_Com_CountDown_;
                                /******************更新并保存数据***********************/

                                uint16_TMEP = _Com_CountDown_;
                                Cache_ALL_DATA();           // 缓存所有flash中的数据到数组
                                _Com_CountDown_ = uint16_TMEP;   // 更新该数组成员的值
                                FLASH_Erase_All_Data();     // 完全擦除存数据的扇叶
                                FLASH_Write_All_Data();     // 写入所有数据到存数据的扇叶

                                /******************************************************/
                                break;

            case Press_Down:    _Com_CountDown_ = _Com_CountDown_==0 ? 1:_Com_CountDown_;
								_Com_CountDown_--;
                                
                                /******************更新并保存数据***********************/

                                uint16_TMEP = _Com_CountDown_;
                                Cache_ALL_DATA();           // 缓存所有flash中的数据到数组
                                _Com_CountDown_ = uint16_TMEP;   // 更新该数组成员的值
                                FLASH_Erase_All_Data();     // 完全擦除存数据的扇叶
                                FLASH_Write_All_Data();     // 写入所有数据到存数据的扇叶

                                /******************************************************/
                                break;

            case Press_Mid:     if(CountDown(_Com_CountDown_))
									return 1;
                                Just_Do_It();
                                break;

            case Press_Left:    
								Run_Time = 0;
								Run_Distance = 0;
								return 0;

            case Press_Right:   
								_Com_Go_Mode_++;
								_Com_Go_Mode_ = _Com_Go_Mode_>2 ? 0:_Com_Go_Mode_;
								
								
								/******************更新并保存数据***********************/

                                uint16_TMEP = _Com_Go_Mode_;
                                Cache_ALL_DATA();           // 缓存所有flash中的数据到数组
                                _Com_Go_Mode_ = uint16_TMEP;   // 更新该数组成员的值
                                FLASH_Erase_All_Data();     // 完全擦除存数据的扇叶
                                FLASH_Write_All_Data();     // 写入所有数据到存数据的扇叶

                                /******************************************************/
								
				break;
        }

        OLED_Refresh_Gram();
    }
}

void Chang_Value_End(uint8_t UI_Case, uint8_t Frame_Min, uint16_t *Value, uint8_t Div_Num)
{
    int16_t temp_value = *Value;
    temp_value = temp_value>9999 ? 9999:temp_value;
	temp_value = temp_value<1 ? 1:temp_value;
    uint8_t ch[25];

    for(;;)
    {

        if(1 == Div_Num)
        {
            sprintf((char *)ch, "%4d", temp_value);
            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
        }
        else
        {
            if(10  == Div_Num)
                sprintf((char *)ch, "%2.1f", (float)temp_value/Div_Num);
            else if(100 == Div_Num)
                sprintf((char *)ch, "%1.2f", (float)temp_value/Div_Num);  

            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Toggle);
        }
        uint8_t value_ok_flag = 0;
		
		
		temp_value += Value_End_L;	//增加编码器数值
		temp_value = temp_value>9999 ? 9999:temp_value;
		temp_value = temp_value<1 ? 1:temp_value;
        switch (Get_Key())
        {
//            case Press_Up:      temp_value++;
//                                temp_value = temp_value>9999 ? 9999:temp_value;
//                                break;

//            case Press_Down:    
//								temp_value = temp_value<1? 1:temp_value;
//								temp_value--;
//                                break;

            case Press_Mid:     value_ok_flag = 1;
                				/******************更新并保存数据***********************/

                				Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
                				*Value = temp_value; 		// 单独更新传参进的数组成员的值
                				FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
                				FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

                				/******************************************************/
                                break;

            case Press_Left:    value_ok_flag = 1;
				                temp_value = *Value;
                                break;

            case Press_Right:   break;
        }



        if(1 == value_ok_flag)
        {
            if(1 == Div_Num)
            {
                sprintf((char *)ch, "%4d", temp_value);
                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
            }
            else
            {
                if(10  == Div_Num)
                    sprintf((char *)ch, "%2.1f", (float)temp_value/Div_Num);
                else if(100 == Div_Num)
                    sprintf((char *)ch, "%1.2f", (float)temp_value/Div_Num);

                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
            }
            OLED_Refresh_Gram();
            break;
        }
        OLED_Refresh_Gram();
    }
}

void Chang_Value(uint8_t UI_Case, uint8_t Frame_Min, uint16_t *Value, uint8_t Div_Num)
{
    int16_t temp_value = *Value;
    temp_value = temp_value>9999 ? 9999:temp_value;
	temp_value = temp_value<1 ? 1:temp_value;
    uint8_t ch[25];

    for(;;)
    {

//        if(1 == Div_Num)
//        {
            sprintf((char *)ch, "%4d ", temp_value);
            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
//        }
//        else
//        {
//            if(10  == Div_Num)
//                sprintf((char *)ch, "%2.1f", (float)temp_value/Div_Num);
//            else if(100 == Div_Num)
//                sprintf((char *)ch, "%1.2f", (float)temp_value/Div_Num);

//            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Toggle);
//        }
        uint8_t value_ok_flag = 0;
        switch (Get_Key())
        {
            case Press_Up:      temp_value++;
                                temp_value = temp_value>9999 ? 9999:temp_value;
                                break;

            case Press_Down:    
								temp_value = temp_value<1? 1:temp_value;
								temp_value--;
                                break;

            case Press_Mid:     value_ok_flag = 1;
                				/******************更新并保存数据***********************/

                				Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
                				*Value = temp_value; 		// 单独更新传参进的数组成员的值
                				FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
                				FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

                				/******************************************************/
                                break;

            case Press_Left:    
								if( 10 <= UI_Case && UI_Case <= 18 )	//  环设置的调节
								{
									temp_value = temp_value%2==0 ? temp_value : temp_value--;	// 奇数为左
									break;
								}
								value_ok_flag = 1;
				                temp_value = *Value;
                                break;

            case Press_Right:	
								if( 10 <= UI_Case && UI_Case <= 18 )	//  环设置的调节
								{
									temp_value = temp_value%2==1 ? temp_value : temp_value++;	// 偶数为右
									break;
								}
								/******************编码器调值***********************/
								;	// case后不能定义变量
								uint8_t BreakFor_Flag = 0;
								for(;;)
								{
									temp_value += Value_End_L;	//增加编码器数值
									temp_value = temp_value>9999 ? 9999:temp_value;
									temp_value = temp_value<0 ? 0:temp_value;
									
									switch(Get_Key())//编码器调节
									{
										case Press_Left:
														temp_value = *Value;
														BreakFor_Flag = 1;
														break;
										case Press_Mid:	
														/******************更新并保存数据***********************/

														Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
														*Value = temp_value; 		// 单独更新传参进的数组成员的值
														FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
														FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

														/******************************************************/
														BreakFor_Flag = 1;
														break;
									}
									sprintf((char *)ch, "%4d#", temp_value);
									OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
									OLED_Refresh_Gram();
									if(BreakFor_Flag)	break;
								}
								break;
        }



        if(1 == value_ok_flag)
        {
//            if(1 == Div_Num)
//            {
			sprintf((char *)ch, "%4d ", temp_value);
			OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
//            }
//            else
//            {
//                if(10  == Div_Num)
//                    sprintf((char *)ch, "%2.1f", (float)temp_value/Div_Num);
//                else if(100 == Div_Num)
//                    sprintf((char *)ch, "%1.2f", (float)temp_value/Div_Num);

//                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
//            }
            OLED_Refresh_Gram();
            break;
        }
        OLED_Refresh_Gram();
    }
}

void Plan_Chang_Value(uint8_t UI_Case, uint8_t Frame_Min, uint16_t *Value, uint8_t Div_Num)
{
    int16_t temp_value = *Value;
    temp_value = temp_value>9999 ? 9999:temp_value;
	temp_value = temp_value<0 ? 0:temp_value;
    uint8_t ch[25];

    for(;;)
    {

//        if(1 == Div_Num)
//        {
            sprintf((char *)ch, "%4d ", temp_value);
            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
//        }
//        else
//        {
//            if(10  == Div_Num)
//                sprintf((char *)ch, "%2.1f", (float)temp_value/Div_Num);
//            else if(100 == Div_Num)
//                sprintf((char *)ch, "%1.2f", (float)temp_value/Div_Num);

//            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Toggle);
//        }
        uint8_t value_ok_flag = 0;
        switch (Get_Key())
        {
            case Press_Up:      
								
								temp_value++;
                                temp_value = temp_value>9999 ? 9999:temp_value;
                                break;

            case Press_Down:    
								
								temp_value = temp_value<1? 1:temp_value;
								temp_value--;
                                break;

            case Press_Mid:     value_ok_flag = 1;
                				/******************更新并保存数据***********************/

                				Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
                				*Value = temp_value; 		// 单独更新传参进的数组成员的值
                				FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
                				FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

                				/******************************************************/
                                break;

            case Press_Left:    
								if( 10 <= UI_Case && UI_Case <= 18 )	//  环设置的调节
								{
									temp_value = temp_value%2==0 ? temp_value-1 : temp_value;	// 奇数为左
									break;
								}
								value_ok_flag = 1;
				                temp_value = *Value;
                                break;

            case Press_Right:	
								
								/******************编码器调值***********************/
								;	// case后不能定义变量
								uint8_t BreakFor_Flag = 0;
								for(;;)
								{
									temp_value += Value_End_L;	//增加编码器数值
									temp_value = temp_value>9999 ? 9999:temp_value;
									temp_value = temp_value<0 ? 0:temp_value;
									
									switch(Get_Key())//编码器调节
									{
										case Press_Left:
														temp_value = *Value;
														BreakFor_Flag = 1;
														break;
										case Press_Mid:	
														/******************更新并保存数据***********************/

														Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
														*Value = temp_value; 		// 单独更新传参进的数组成员的值
														FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
														FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

														/******************************************************/
														BreakFor_Flag = 1;
														break;
									}
									sprintf((char *)ch, "%4d#", temp_value);
									OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
									OLED_Refresh_Gram();
									if(BreakFor_Flag)	break;
								}
								break;
        }



        if(1 == value_ok_flag)
        {
//            if(1 == Div_Num)
//            {
			sprintf((char *)ch, "%4d ", temp_value);
			OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
//            }
//            else
//            {
//                if(10  == Div_Num)
//                    sprintf((char *)ch, "%2.1f", (float)temp_value/Div_Num);
//                else if(100 == Div_Num)
//                    sprintf((char *)ch, "%1.2f", (float)temp_value/Div_Num);

//                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
//            }
            OLED_Refresh_Gram();
            break;
        }
        OLED_Refresh_Gram();
    }
}

void Plan_Judge_State(uint8_t Judge_ch1[], uint8_t Judge_ch2[], uint16_t state)
{
	if( 0 == state )
	{
		sprintf((char *)Judge_ch1, "---");
		sprintf((char *)Judge_ch2, "---");
		return;
	}
    switch( state%2 )
    {
        case 0:   sprintf((char *)Judge_ch1, "右 ");  break;
        case 1:   sprintf((char *)Judge_ch1, "左 ");  break;
        default:  sprintf((char *)Judge_ch1, "??");
    }
	state = state%2==0 ? state-1 : state;	// 偶数时除2 大1
	switch( state/2 )
    {
        case 0:	sprintf((char *)Judge_ch2, " 50");	break;
		case 1:	sprintf((char *)Judge_ch2, " 60");	break;
		case 2:	sprintf((char *)Judge_ch2, " 70");	break;
		case 3:	sprintf((char *)Judge_ch2, " 80");	break;
		case 4:	sprintf((char *)Judge_ch2, " 90");	break;
		case 5:	sprintf((char *)Judge_ch2, "100");	break;
		
        default:  sprintf((char *)Judge_ch2, "???");
    }
}
void Plan_Chang_State(uint8_t UI_Case, uint8_t Frame_Min, uint16_t *Value)
{
    int8_t temp_value = *Value;
    uint8_t ch1[25];
	uint8_t ch2[25];
//	uint8_t Which_4B = (UI_Case-1)/2; 	// 判断属于哪4字节空间里，flash写数据一次至少4字节;
										// 这里的哪是指从公共参数开始，即偏移量400开始。
    for(;;)
    {
        Plan_Judge_State(ch1, ch2, temp_value);	// 判断并写入左右、大小
        OLED_Show_StrAll(84,  (UI_Case-Frame_Min+1)*13, ch1, Toggle);	// 显示ON/OFF
		OLED_Show_StrAll(108, (UI_Case-Frame_Min+1)*13, ch2, Toggle);	// 显示ON/OFF
		
        uint8_t value_ok_flag = 0;	//值更改完成标志位
        switch (Get_Key())
        {
            case Press_Up:
							temp_value += 2;	// 奇数为左
							temp_value = temp_value==13 ? 11:temp_value;
							temp_value = temp_value==14 ? 12:temp_value;
							break;
            case Press_Down:
							temp_value -= 2;	// 奇数为左
							temp_value = temp_value<=0 ? 0:temp_value;
							break;
			
            case Press_Mid:
							value_ok_flag = 1;


							ALL_DATA_Change = COM_ARRAY_OFFSET + UI_Case -1;
							ALL_DATA[ALL_DATA_Change] = *Value;

							/******************更新并保存数据***********************/

							Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
							*Value = temp_value; 		// 单独更新传参进的数组成员的值
							FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
							FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

							/******************************************************/
			
							break;
			
            case Press_Left:
							temp_value = temp_value%2==0 ? temp_value-1 : temp_value;	// 奇数为左
							break;
			
            case Press_Right:	
							temp_value = temp_value%2==1 ? temp_value+1 : temp_value;	// 偶数为右
							break;

        }


        if(1 == value_ok_flag)
        {
            Plan_Judge_State(ch1, ch2, temp_value);
            OLED_Show_StrAll(84,  (UI_Case-Frame_Min+1)*13, ch1, Normal);	// 显示ON/OFF
			OLED_Show_StrAll(108, (UI_Case-Frame_Min+1)*13, ch2, Normal);	// 显示ON/OFF
            OLED_Refresh_Gram();
            break;
        }
        OLED_Refresh_Gram();
    }
}
void Write_Value(uint8_t in_ch[][30])
{
//                       "123456789012345678901"
//	uint16_t Index_Plan_Offset = (_Com_Plan_-1)*40;
	uint8_t i = 0;
	uint8_t Judge_ch1[3] = "";
	uint8_t Judge_ch2[3] = "";
	
	switch( _Com_Plan_ )
	{
		case 1:	sprintf((char *)in_ch [0], "  <    方  案  一     ");	break;
		case 2:	sprintf((char *)in_ch [0], "  <    方  案  二     ");	break;
		case 3:	sprintf((char *)in_ch [0], "  <    方  案  三     ");	break;
		case 4:	sprintf((char *)in_ch [0], "  <    方  案  四     ");	break;
		case 5:	sprintf((char *)in_ch [0], "  <    方  案  五     ");	break;
		default:                
				/******************更新并保存数据***********************/

				uint16_TMEP = 1;
				Cache_ALL_DATA();           // 缓存所有flash中的数据到数组
				_Com_Plan_ = uint16_TMEP;   // 更新该数组成员的值
				FLASH_Erase_All_Data();     // 完全擦除存数据的扇叶
				FLASH_Write_All_Data();     // 写入所有数据到存数据的扇叶

                /******************************************************/
				break;
	}
    sprintf((char *)in_ch[++i], "   1.  目标角度  %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_	]);
    sprintf((char *)in_ch[++i], "   2.  目标速度  %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Speed_	]);
    sprintf((char *)in_ch[++i], "   3.  角 度 P   %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_AnglePID_P_		]);
    sprintf((char *)in_ch[++i], "   4.  角 度 D   %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_AnglePID_D_		]);
    sprintf((char *)in_ch[++i], "   5.  速 度 P   %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_SpeedPID_P_		]);
    sprintf((char *)in_ch[++i], "   6.  速 度 I   %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_SpeedPID_I_		]);
    sprintf((char *)in_ch[++i], "   7.  转 向 P   %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_TurnPID_P_		]);
    sprintf((char *)in_ch[++i], "   8.  转 向 D   %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_TurnPID_D_   	]);
    sprintf((char *)in_ch[++i], "   9.  环弯补偿  %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_HuanTurn_Add_	]);
	
	uint16_t Huan1_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan1_Para_];
	uint16_t Huan2_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan2_Para_];
	uint16_t Huan3_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan3_Para_];
	uint16_t Huan4_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan4_Para_];
	uint16_t Huan5_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan5_Para_];
	uint16_t Huan6_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan6_Para_];
	uint16_t Huan7_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan7_Para_];
	uint16_t Huan8_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan8_Para_];
	uint16_t Huan9_Data = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan9_Para_];

	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan1_Data);
    sprintf((char *)in_ch[++i], "   10. 环  1  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan2_Data);
    sprintf((char *)in_ch[++i], "   11. 环  2  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan3_Data);
    sprintf((char *)in_ch[++i], "   12. 环  3  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan4_Data);
    sprintf((char *)in_ch[++i], "   13. 环  4  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan5_Data);
    sprintf((char *)in_ch[++i], "   14. 环  5  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan6_Data);
    sprintf((char *)in_ch[++i], "   15. 环  6  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan7_Data);
    sprintf((char *)in_ch[++i], "   16. 环  7  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan8_Data);
    sprintf((char *)in_ch[++i], "   17. 环  8  %3s %3s ",	Judge_ch1, Judge_ch2);
	Plan_Judge_State(Judge_ch1, Judge_ch2, Huan9_Data);
    sprintf((char *)in_ch[++i], "   18. 环  9  %3s %3s ",	Judge_ch1, Judge_ch2);

	sprintf((char *)in_ch[++i], "   19.  50环补偿 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan50_Add_		]);
	sprintf((char *)in_ch[++i], "   20.  50入环小 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan50_Min_	]);
	sprintf((char *)in_ch[++i], "   21.  50入环大 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan50_Max_	]);

	sprintf((char *)in_ch[++i], "   22.  60环补偿 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan60_Add_		]);
	sprintf((char *)in_ch[++i], "   23.  60入环小 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan60_Min_	]);
	sprintf((char *)in_ch[++i], "   24.  60入环大 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan60_Max_	]);
	
	sprintf((char *)in_ch[++i], "   25.  70环补偿 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan70_Add_		]);
	sprintf((char *)in_ch[++i], "   26.  70入环小 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan70_Min_	]);
	sprintf((char *)in_ch[++i], "   27.  70入环大 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan70_Max_	]);
	
	sprintf((char *)in_ch[++i], "   28.  80环补偿 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan80_Add_		]);
	sprintf((char *)in_ch[++i], "   29.  80入环小 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan80_Min_	]);
	sprintf((char *)in_ch[++i], "   30.  80入环大 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan80_Max_	]);
	
	sprintf((char *)in_ch[++i], "   31.  90环补偿 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan90_Add_		]);
	sprintf((char *)in_ch[++i], "   32.  90入环小 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan90_Min_	]);
	sprintf((char *)in_ch[++i], "   33.  90入环大 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan90_Max_	]);
	
	sprintf((char *)in_ch[++i], "   34. 100环补偿 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan100_Add_		]);
	sprintf((char *)in_ch[++i], "   35. 100入环小 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan100_Min_	]);
	sprintf((char *)in_ch[++i], "   36. 100入环大 %4d  ",	ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_InHuan100_Max_	]);
													/******************* 方案菜单 修改二 ↑******************/
}

uint8_t UI_Plan(void)
{
    uint8_t UI_Case = 1;
    uint8_t Case_Temp = 0;
    uint8_t Frame_Min = 1;
    uint8_t Frame_Temp = 0;
    uint8_t Should_Refresh = 0;		//用于更改值后刷新
	const uint8_t SHOW_NUM = 37;	// 显示数目，菜单数目为SHOW_NUM-1
	
	uint16_t Index_Plan_Offset = (_Com_Plan_-1)*40;

    uint8_t UI_Menu[SHOW_NUM][30];


	OLED_Clear();
    Write_Value(UI_Menu);
    OLED_Show_StrAll(0,  0, UI_Menu[0],           Normal);
    OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   Normal);
    OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], Normal);
    OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], Normal);
    OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], Normal);
    for(;;)	// 第一层循环
    {
        Case_Temp = UI_Case;
        Frame_Temp = Frame_Min;

		switch (Get_Key())
		{
			case Press_Up:   	UI_Case--;
								UI_Case=UI_Case<1?SHOW_NUM-1:UI_Case;
								break;
			
			case Press_Down: 	UI_Case++;
								UI_Case=UI_Case>SHOW_NUM-1?1:UI_Case;
								break;
			
			case Press_Left:	return 0;
			
			case Press_Right:	;	// case后不能定义变量
								uint8_t TEMP_GRAM_1[OLED_X_MAX][8];
								for(uint8_t i=0; i<OLED_X_MAX; i++)
									for(uint8_t j=0; j<8; j++)
										TEMP_GRAM_1[i][j] = OLED_GRAM[i][j];
			
								uint8_t UI_Case_1;	UI_Case_1 = 1;	// 为了解决警告
								uint8_t Break_Flag;	Break_Flag = 0;
								
								for(; Break_Flag != 1 ;)	// 第二层循环
								{
									OLED_Fill(30, 23, 71, 56, 1);	// 白色背景
									switch(UI_Case_1)				// 菜单显示
									{
										case 1:	OLED_Show_StrAll(33, 26, " 清空 ",   Normal);
												OLED_Fill(33, 25, 68, 25, 0);
												OLED_Fill(33, 38, 68, 38, 0);
												OLED_Show_StrAll(33, 41, " 复制 ",   Toggle);
												break;
												
										
										case 2:	OLED_Show_StrAll(33, 26, " 清空 ",   Toggle);
												OLED_Show_StrAll(33, 41, " 复制 ",   Normal);
												OLED_Fill(33, 40, 68, 40, 0);
												OLED_Fill(33, 53, 68, 53, 0);
									}
									
									switch (Get_Key())				//功能选择
									{
										case Press_Up:		UI_Case_1 = 1;	break;
										case Press_Down:	UI_Case_1 = 2;	break;
										
										case Press_Mid:		
										case Press_Right:	;	// case后不能定义变量
															uint8_t TEMP_GRAM_2[OLED_X_MAX][8];
															for(uint8_t i=0; i<OLED_X_MAX; i++)
																for(uint8_t j=0; j<8; j++)
																	TEMP_GRAM_2[i][j] = OLED_GRAM[i][j];
										
															uint8_t UI_Case_2;		UI_Case_2 = 1;
															uint8_t Break_Flag_1;	Break_Flag_1 = 0;
															for(; Break_Flag_1 != 1 ;)	// 第三层循环
															{
																if(UI_Case_1 == 1)				
																{
																	OLED_Fill(69, 14, 110, 47, 1);	// 白色背景
																	switch(UI_Case_2)				// 菜单显示				
																	{
																		case 1:	OLED_Show_StrAll(72, 17, " 当前 ", Normal);
																				OLED_Fill(72, 16, 107, 16, 0);
																				OLED_Fill(72, 29, 107, 29, 0);
																				OLED_Show_StrAll(72, 32, " 所有 ", Toggle);
																				break;

																		case 2:	OLED_Show_StrAll(72, 17, " 当前 ", Toggle);
																				OLED_Show_StrAll(72, 32, " 所有 ", Normal);
																				OLED_Fill(72, 31, 107, 31, 0);
																				OLED_Fill(72, 44, 107, 44, 0);
																	}
																}
																else if(UI_Case_1 == 2)	
																{
																	OLED_Fill(69, 1, 122, 63, 1);	// 白色背景
																	uint8_t Temp_Str[4][9];
																	switch( _Com_Plan_ )
																	{
																		case 1:	sprintf((char *)Temp_Str[0], " 方案二 ");
																				sprintf((char *)Temp_Str[1], " 方案三 ");
																				sprintf((char *)Temp_Str[2], " 方案四 ");
																				sprintf((char *)Temp_Str[3], " 方案五 ");
																				break;
																		case 2:	sprintf((char *)Temp_Str[0], " 方案一 ");
																				sprintf((char *)Temp_Str[1], " 方案三 ");
																				sprintf((char *)Temp_Str[2], " 方案四 ");
																				sprintf((char *)Temp_Str[3], " 方案五 ");
																				break;
																		case 3:	sprintf((char *)Temp_Str[0], " 方案一 ");
																				sprintf((char *)Temp_Str[1], " 方案二 ");
																				sprintf((char *)Temp_Str[2], " 方案四 ");
																				sprintf((char *)Temp_Str[3], " 方案五 ");
																				break;
																		case 4:	sprintf((char *)Temp_Str[0], " 方案一 ");
																				sprintf((char *)Temp_Str[1], " 方案二 ");
																				sprintf((char *)Temp_Str[2], " 方案三 ");
																				sprintf((char *)Temp_Str[3], " 方案五 ");
																				break;
																		case 5:	sprintf((char *)Temp_Str[0], " 方案一 ");
																				sprintf((char *)Temp_Str[1], " 方案二 ");
																				sprintf((char *)Temp_Str[2], " 方案三 ");
																				sprintf((char *)Temp_Str[3], " 方案四 ");
																				break;
																	}
																	OLED_Show_StrAll(72,  4, Temp_Str[0], Toggle);
																	OLED_Show_StrAll(72, 19, Temp_Str[1], Toggle);
																	OLED_Show_StrAll(72, 34, Temp_Str[2], Toggle);
																	OLED_Show_StrAll(72, 49, Temp_Str[3], Toggle);
																	switch(UI_Case_2)				// 菜单显示
																	{
																		case 1:	OLED_Show_StrAll(72,  4, Temp_Str[0], Normal);
																				OLED_Fill(72,  3, 119,  3, 0);
																				OLED_Fill(72, 16, 119, 16, 0);
																				break;
																		case 2:	OLED_Show_StrAll(72, 19, Temp_Str[1], Normal);
																				OLED_Fill(72, 18, 119, 18, 0);
																				OLED_Fill(72, 31, 119, 31, 0);
																				break;
																		case 3:	OLED_Show_StrAll(72, 34, Temp_Str[2], Normal);
																				OLED_Fill(72, 33, 119, 33, 0);
																				OLED_Fill(72, 46, 119, 46, 0);
																				break;
																		case 4:	OLED_Show_StrAll(72, 49, Temp_Str[3], Normal);
																				OLED_Fill(72, 48, 119, 48, 0);
																				OLED_Fill(72, 61, 119, 61, 0);
																				break;	
																	}
																}	// 菜单显示结束
																
																switch (Get_Key())
																{
																	case Press_Up:		if(UI_Case_1 == 1)
																						{
																							UI_Case_2 = 1;
																						}
																						else
																						{
																							UI_Case_2--;
																							UI_Case_2 = UI_Case_2<1 ? 1:UI_Case_2;
																						}
																						break;
																	
																	case Press_Down:	if(UI_Case_1 == 1)
																						{
																							UI_Case_2 = 2;
																						}
																						else
																						{
																							UI_Case_2++;
																							UI_Case_2 = UI_Case_2>4 ? 4:UI_Case_2;
																						}
																						break;
																						
																	case Press_Left:	Break_Flag_1 = 1;
																						break;
																						
																	case Press_Mid:		/*********计算实际指向的是方案几*********/
																						;	// case后不能定义变量
																						uint8_t Real_Plan;
																						if(UI_Case_2 < _Com_Plan_)
																							Real_Plan = UI_Case_2;
																						else
																							Real_Plan = UI_Case_2 + 1;
																						/****************************************/
																						switch(UI_Case_1*10 + UI_Case_2)
																						{
																							case 11:	Cache_ALL_DATA();
																										ALL_DATA[Index_Plan_Offset + (UI_Case-1)] = 0;
																										FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
																										FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶
																										break;
																							
																							case 12:	Cache_ALL_DATA();
																										for(uint8_t i=0; i<40; i++)
																											ALL_DATA[Index_Plan_Offset + i] = 0;
																										FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
																										FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶
																										break;
																							
																							case 21:	//这儿贼巧妙
																							case 22:
																							case 23:
																							case 24:	Cache_ALL_DATA();
																										for(uint8_t i=0; i<40; i++)
																											ALL_DATA[Index_Plan_Offset + i] = ALL_DATA[(Real_Plan-1)*40 + i];
																										FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
																										FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶
																										break;
																						}
																						return 2;

																						
																	case Press_Right:	
																						break;
																}
																OLED_Refresh_Gram();
															}	// 第三层循环结束
															for(uint8_t i=0; i<OLED_X_MAX; i++)
																for(uint8_t j=0; j<8; j++)
																	OLED_GRAM[i][j] = TEMP_GRAM_2[i][j];
															break;
											
										case Press_Left:	Break_Flag = 1;	break;
									}
									OLED_Refresh_Gram();
								}	// 第二层循环结束
								for(uint8_t i=0; i<OLED_X_MAX; i++)
									for(uint8_t j=0; j<8; j++)
										OLED_GRAM[i][j] = TEMP_GRAM_1[i][j];
								break;
								
			case Press_Mid:		//按中


				
				switch(UI_Case)
				{
						case  1:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Target_Angle_	],  Normal);	break;
						case  2:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Target_Speed_	],  Normal);	break;
						case  3:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_AnglePID_P_	],  Normal);	break;
						case  4:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_AnglePID_D_	],  Normal);	break;
						case  5:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_SpeedPID_P_	],  Normal);	break;
						case  6:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_SpeedPID_I_	],  Normal);	break;
						case  7:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_TurnPID_P_	],  Normal);	break;
						case  8:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_TurnPID_D_	],  Normal);	break;
						case  9:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_HuanTurn_Add_	],	Normal);	break;
					
						case  10:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan1_Para_	]);	break;
						case  11:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan2_Para_	]);	break;
						case  12:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan3_Para_	]);	break;
						case  13:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan4_Para_	]);	break;
						case  14:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan5_Para_	]);	break;
						case  15:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan6_Para_	]);	break;
						case  16:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan7_Para_	]);	break;
						case  17:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan8_Para_	]);	break;
						case  18:	Plan_Chang_State(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan9_Para_	]);	break;
					
						case  19:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan50_Add_	],	Normal);	break;
						case  20:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan50_Min_	],	Normal);	break;
						case  21:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan50_Max_	],	Normal);	break;
						
						case  22:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan60_Add_	],	Normal);	break;
						case  23:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan60_Min_	],	Normal);	break;
						case  24:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan60_Max_	],	Normal);	break;
						
						case  25:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan70_Add_	],	Normal);	break;
						case  26:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan70_Min_	],	Normal);	break;
						case  27:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan70_Max_	],	Normal);	break;
						
						case  28:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan80_Add_	],	Normal);	break;
						case  29:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan80_Min_	],	Normal);	break;
						case  30:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan80_Max_	],	Normal);	break;
						
						case  31:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan90_Add_	],	Normal);	break;
						case  32:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan90_Min_	],	Normal);	break;
						case  33:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan90_Max_	],	Normal);	break;
						
						case  34:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan100_Add_	],	Normal);	break;
						case  35:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan100_Min_],	Normal);	break;
						case  36:	Plan_Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_InHuan100_Max_],	Normal);	break;
						
//						case  11:   Chang_Value(UI_Case, Frame_Min, &DATA_11, DATA_P_11);  break;
//						case  12:   Chang_Value(UI_Case, Frame_Min, &DATA_12, DATA_P_12);  break;
//						case  13:   Chang_Value(UI_Case, Frame_Min, &DATA_13, DATA_P_13);  break;
//						case  14:   Chang_Value(UI_Case, Frame_Min, &DATA_14, DATA_P_14);  break;
//						case  15:   Chang_Value(UI_Case, Frame_Min, &DATA_15, DATA_P_15);  break;
//						case  16:   Chang_Value(UI_Case, Frame_Min, &DATA_16, DATA_P_16);  break;

							/******************* 方案菜单 修改三 ↑******************/
				}
				break;
			}
        
        /*判断框的范围*/
        Frame_Min = UI_Case<Frame_Min?UI_Case:Frame_Min;
        Frame_Min = UI_Case-3>Frame_Min?UI_Case-3:Frame_Min;
        if(Case_Temp != UI_Case || Should_Refresh == 1)
        {
            OLED_Show_Char(6, 12, ' ', 12, Normal);
            OLED_Show_Char(6, 25, ' ', 12, Normal);
            OLED_Show_Char(6, 38, ' ', 12, Normal);
            OLED_Show_Char(6, 50, ' ', 12, Normal);
            /*状态写入UI_Menu里*/
            Write_Value(UI_Menu);
            Should_Refresh = 0;
        }

        if(Frame_Temp != Frame_Min)
        {
            /*显示菜单*/
            OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   Normal);
            OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], Normal);
            OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], Normal);
            OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], Normal);
        }
        /*显示指示器*/
        if(UI_Case == Frame_Min)          OLED_Show_Char(6, 12, '@', 12, Normal);
        else if(UI_Case == Frame_Min+1)   OLED_Show_Char(6, 25, '@', 12, Normal);
        else if(UI_Case == Frame_Min+2)   OLED_Show_Char(6, 38, '@', 12, Normal);
        else if(UI_Case == Frame_Min+3)   OLED_Show_Char(6, 50, '@', 12, Normal);
        OLED_Refresh_Gram();
    }// 第一层循环结束
}


uint8_t UI_Driver(void)
{
    uint8_t UI_Case = 1;
    uint8_t Case_Temp = 0;
    uint8_t Frame_Min = 1;
    uint8_t Frame_Temp = 0;
	const uint8_t SHOW_NUM = 10;	// 显示数目，菜单数目为SHOW_NUM-1
	
    OLED_Clear();
    uint8_t UI_Menu[SHOW_NUM][30] =
                  {
                    "  <     外  设       ",
                    "    1.  陀 螺 仪     ",
                    "    2.  电 感 值     ",
                    "    3.  编码器值     ",
                    "    4.   自 检       ",
                    "    5.  XXXXXXX      ",
                    "    6.  XXXXXXX      ",
                    "    7.  XXXXXXX      ",
                    "    8.  XXXXXXX      ",
                    "    9.  XXXXXXX      "
                  };
    OLED_Show_StrAll(0,  0, UI_Menu[0]          , Normal);
    OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min]  , Normal);
    OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], Normal);
    OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], Normal);
    OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], Normal);
    for(;;)
    {
        Case_Temp = UI_Case;
        Frame_Temp = Frame_Min;

		switch (Get_Key())
		{
			case Press_Up:   
						UI_Case--;
						UI_Case=UI_Case<1?SHOW_NUM-1:UI_Case;
						break;
			
            case Press_Down: 
						UI_Case++;
						UI_Case=UI_Case>SHOW_NUM-1?1:UI_Case;
						break;

			case Press_Left: return 0;
			
			case Press_Mid:		//按中
				switch(UI_Case)
				{
					case 1:		return 31;
					case 2:		return 32;
					case 3:		return 33;
					case 4:		return 5;	//自检界面
					default:	return 0;	//防止真出现其他情况
				}
		}
        
        
        /*判断框的范围*/
        Frame_Min = UI_Case<Frame_Min?UI_Case:Frame_Min;
        Frame_Min = UI_Case-3>Frame_Min?UI_Case-3:Frame_Min;
        if(Case_Temp != UI_Case)
        {
            OLED_Show_Char(12, 12, ' ', 12, Normal);
            OLED_Show_Char(12, 25, ' ', 12, Normal);
            OLED_Show_Char(12, 38, ' ', 12, Normal);
            OLED_Show_Char(12, 50, ' ', 12, Normal);
        }
        if(Frame_Temp != Frame_Min)
        {
            /*显示菜单*/
            OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min]  , Normal);
            OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], Normal);
            OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], Normal);
            OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], Normal);
        }
        /*显示指示器*/
        if(UI_Case == Frame_Min)          OLED_Show_Char(12, 12, '@', 12, Normal);
        else if(UI_Case == Frame_Min+1)   OLED_Show_Char(12, 25, '@', 12, Normal);
        else if(UI_Case == Frame_Min+2)   OLED_Show_Char(12, 38, '@', 12, Normal);
        else if(UI_Case == Frame_Min+3)   OLED_Show_Char(12, 50, '@', 12, Normal);
        OLED_Refresh_Gram();
    }
}
void Judge_State(uint8_t Judge_ch[], uint16_t state)
{
    switch(state)
    {
        case 0:   sprintf((char *)Judge_ch, "关");  break;
        case 1:   sprintf((char *)Judge_ch, "开");  break;
        default:  sprintf((char *)Judge_ch, "??");
    }

}
/*只用于UI_Set()函数*/
void Write_State(uint8_t in_ch[][30])
{
    uint8_t Judge_ch[4] = "";

    sprintf((char *)in_ch[0],  "  <     设  置       ");
	
	sprintf((char *)in_ch[1],  "   1.  环磁阈值  %4d  ", _Com_Huan_Value_);		//环磁补偿

    sprintf((char *)in_ch[2],  "   2.  环 数 量  %4d  ", _Com_Huan_Num_);		//环的数量

	sprintf((char *)in_ch[3],  "   3.  入环最小  %4d  ", _Com_InHuan_Min_);
	
	sprintf((char *)in_ch[4],  "   4.  入环最大  %4d  ", _Com_InHuan_Max_ );

	sprintf((char *)in_ch[5],  "   5.  时间停车  %4d  ", _Com_RunTimeStop_);
	
	sprintf((char *)in_ch[6],  "   6.  距离停车  %4d  ", _Com_RunDisStop_ );
	
	Judge_State(Judge_ch, _Com_RunProtect_);
    sprintf((char *)in_ch[7],  "   7.  保  护      %s", Judge_ch);	// 保护开关

	Judge_State(Judge_ch, _Com_Debug_);
    sprintf((char *)in_ch[8],  "   8.  调  试      %s", Judge_ch);	// 调试开关：开后，电机禁能且关保护
	
    Judge_State(Judge_ch, _Com_LED_);
    sprintf((char *)in_ch[9],  "   9.  L E D       %s", Judge_ch);
	
    Judge_State(Judge_ch, _Com_Buzzer_);
    sprintf((char *)in_ch[10], "  10.  蜂 鸣 器    %s", Judge_ch);
	
    Judge_State(Judge_ch, _Com_BT_);
    sprintf((char *)in_ch[11], "  11.  蓝  牙      %s", Judge_ch);

	sprintf((char *)in_ch[12], "  12.  左出补偿  %4d  ", _Com_HuanOut_L_Add_ );
	
	sprintf((char *)in_ch[13], "  13.  右出补偿  %4d  ", _Com_HuanOut_R_Add_ );
	
	sprintf((char *)in_ch[14], "  14.  出补路程  %4d  ", _Com_HuanOut_AddDis_);
	/****************************设置菜单 修改二 ↑****************************/
}


void Chang_State(uint8_t UI_Case, uint8_t Frame_Min, uint16_t *Value)
{
    int8_t temp_value = *Value;
    uint8_t ch[25];
//	uint8_t Which_4B = (UI_Case-1)/2; 	// 判断属于哪4字节空间里，flash写数据一次至少4字节;
										// 这里的哪是指从公共参数开始，即偏移量400开始。
    for(;;)
    {
        Judge_State(ch, temp_value);	// 判断并写入ON/OFF
        OLED_Show_StrAll(114, (UI_Case-Frame_Min+1)*13, ch, Toggle);	// 显示ON/OFF

        uint8_t value_ok_flag = 0;	//值更改完成标志位
        switch (Get_Key())
        {
            case Press_Up:
                temp_value++;
                break;
            case Press_Down:
                temp_value--;
			
                break;
            case Press_Mid:
                value_ok_flag = 1;


				ALL_DATA_Change = COM_ARRAY_OFFSET + UI_Case -1;
				ALL_DATA[ALL_DATA_Change] = *Value;

				/******************更新并保存数据***********************/

				Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
				*Value = temp_value; 		// 单独更新传参进的数组成员的值
				FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
				FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

				/******************************************************/

//				U8_DATA[0] = flash_read(DATA_FLASH, COM_OFFSET+Which_4B*4+0, uint8_t);
//				U8_DATA[1] = flash_read(DATA_FLASH, COM_OFFSET+Which_4B*4+1, uint8_t);
//				U8_DATA[2] = flash_read(DATA_FLASH, COM_OFFSET+Which_4B*4+2, uint8_t);
//				U8_DATA[3] = flash_read(DATA_FLASH, COM_OFFSET+Which_4B*4+3, uint8_t);
//
//				U8_DATA[(UI_Case-1)%4] = *Value;//flash缓存数组中更新被修改的那个

//				FLASH_EraseSector(DATA_FLASH);
//				FLASH_WriteSector(DATA_FLASH, (const uint8_t *)U8_DATA, 4, COM_OFFSET+Which_4B*4);// 写入前擦除

				/////////
                break;
            case Press_Left:
				temp_value = *Value;	// 恢复之前未修改时的值
                value_ok_flag = 1;
                break;
        }
        temp_value = temp_value>1?0:temp_value;
        temp_value = temp_value<0?1:temp_value;


        if(1 == value_ok_flag)
        {
            Judge_State(ch, temp_value);
            OLED_Show_StrAll(114, (UI_Case-Frame_Min+1)*13, ch, Normal);	// 更新状态（ON/OFF）
            OLED_Refresh_Gram();
            break;
        }
        OLED_Refresh_Gram();
    }
}

uint8_t UI_Set(void)
{
    uint8_t UI_Case = 1;
    uint8_t Case_Temp = 0;
    uint8_t Frame_Min = 1;
    uint8_t Frame_Temp = 0;
    uint8_t Should_Refresh = 0;//用于更改值后刷新
	const uint8_t SHOW_NUM = 15;	// 显示数目，菜单数目为SHOW_NUM-1

    OLED_Clear();
    uint8_t UI_Menu[SHOW_NUM][30];
    Write_State(UI_Menu);
    OLED_Show_StrAll(0,  0, UI_Menu[0],           Normal);
    OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   Normal);
    OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], Normal);
    OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], Normal);
    OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], Normal);
    for(;;)
    {
        Case_Temp = UI_Case;
        Frame_Temp = Frame_Min;

		switch (Get_Key())
		{
			case Press_Up:		UI_Case--;
								UI_Case=UI_Case<1?SHOW_NUM-1:UI_Case;	// 菜单选项数目
								break;
			
            case Press_Down:	UI_Case++;
								UI_Case=UI_Case>SHOW_NUM-1?1:UI_Case;
								break;
			
			case Press_Left:	return 0;	// 退出
			
			case Press_Mid:
								switch(UI_Case)
								{
									case  1:	Chang_Value(UI_Case, Frame_Min, &_Com_Huan_Value_,    1);	break;	// 环磁补偿
									case  2:	Chang_Value(UI_Case, Frame_Min, &_Com_Huan_Num_ , 	  1);	break;	// 入环方向
									case  3:	Chang_Value(UI_Case, Frame_Min, &_Com_InHuan_Min_,    1);	break;	// 入环最小
									case  4:	Chang_Value(UI_Case, Frame_Min, &_Com_InHuan_Max_ ,   1);	break;	// 入环最大
									case  5:	Chang_Value(UI_Case, Frame_Min, &_Com_RunTimeStop_,   1);	break;	// 时间停车
									case  6:	Chang_Value(UI_Case, Frame_Min, &_Com_RunDisStop_ ,   1);	break;	// 距离停车
									
									case  7:	Chang_State(UI_Case, Frame_Min, &_Com_RunProtect_		);	break;	// 保护开关
									case  8:	Chang_State(UI_Case, Frame_Min, &_Com_Debug_			);	break;	// 调试开关
									case  9:  	Chang_State(UI_Case, Frame_Min, &_Com_LED_				);	break;	// LED开关
									case 10:  	Chang_State(UI_Case, Frame_Min, &_Com_Buzzer_			);	break;	// 蜂鸣器开关
									case 11:  	Chang_State(UI_Case, Frame_Min, &_Com_BT_				);	break;	// 蓝牙开关

									case 12:	Chang_Value(UI_Case, Frame_Min, &_Com_HuanOut_L_Add_ , 1);	break;	// 左出环补偿
									case 13:	Chang_Value(UI_Case, Frame_Min, &_Com_HuanOut_R_Add_ , 1);	break;	// 左出环补偿
									case 14:	Chang_Value(UI_Case, Frame_Min, &_Com_HuanOut_AddDis_, 1);	break;	// 出环补偿路程
									/****************************设置菜单 修改三 ↑****************************/

									default:	return 0;//防止真出现其他情况
								}
								break;
		}
        
        
        /*判断框的范围*/
        Frame_Min = UI_Case<Frame_Min?UI_Case:Frame_Min;
        Frame_Min = UI_Case-3>Frame_Min?UI_Case-3:Frame_Min;
		/*判断更新界面与值*/
        if(Case_Temp != UI_Case || Should_Refresh == 1)
        {
			/*刷新指示*/
            OLED_Show_Char(6, 12, ' ', 12, Normal);
            OLED_Show_Char(6, 25, ' ', 12, Normal);
            OLED_Show_Char(6, 38, ' ', 12, Normal);
            OLED_Show_Char(6, 50, ' ', 12, Normal);
            /*状态写入UI_Menu里*/
            Write_State(UI_Menu);
            Should_Refresh = 0;
        }
		/*框最小值变更，更新内容*/
        if(Frame_Temp != Frame_Min)
        {
            /*显示菜单*/
            OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   Normal);
            OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], Normal);
            OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], Normal);
            OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], Normal);
        }
        /*显示指示器*/
        if		(UI_Case == Frame_Min)		OLED_Show_Char(6, 12, '@', 12, Normal);
        else if	(UI_Case == Frame_Min+1)	OLED_Show_Char(6, 25, '@', 12, Normal);
        else if	(UI_Case == Frame_Min+2)	OLED_Show_Char(6, 38, '@', 12, Normal);
        else if	(UI_Case == Frame_Min+3)	OLED_Show_Char(6, 50, '@', 12, Normal);
        OLED_Refresh_Gram();
    }
}

uint8_t UI_Check(void)
{
    OLED_Clear();
    OLED_Show_StrAll(0,  0, "  <     自  检        ", 1);
	
	for(;;)
	{
		switch(Get_Key())
		{
			case Press_Left:
			case Press_Mid:	return 0;
		}
		uint8_t str[32];
		sprintf((char *)str, "俯仰角:%-3.2f", Pitch);		//俯仰角
		OLED_Show_StrAll(0, 12, str, 1);
		sprintf((char *)str, "AD左  :%-4d 右:%-4d", Value_Inductor_L, Value_Inductor_R);	//电感值
		OLED_Show_StrAll(0, 26, str, 1);
		sprintf((char *)str, "转速左:%-4d 右:%-4d", Value_End_L, Value_End_R);		//编码器值
        OLED_Show_StrAll(0, 39, str, 1);

		OLED_Refresh_Gram();
	}
}



uint8_t UI_Read_Ind(void)
{
//    uint32_t Ind_L = 0;
//    uint32_t Ind_R = 0;

//    uint32_t Ind_L_Integral = 0;
//    uint32_t Ind_R_Integral = 0;

//    uint16_t Pre_L_Integral[10] = {0,0,0,0,0,0,0,0,0,0,};
//    uint16_t Pre_R_Integral[10] = {0,0,0,0,0,0,0,0,0,0,};

//    int16_t L_R = 0;
//    uint8_t ch[20] = "";
//    float error_dis = 0;
    OLED_Clear();
    OLED_Show_StrAll(0,  0, " <    电  感  值      ", 1);
    for(;;)
    {
		switch(Get_Key())
		{
			case Press_Left:	return 3;
		}
//            MPU6050_GetData(&GYRO, &ACC);   //获取原始数据
//            //    Data_Filter();     //原始数据滤波
//            Get_Attitude_NoF();


            uint8_t str[32];
            sprintf((char *)str, "AD_L:%4d  AD_R:%4d", Value_Inductor_L, Value_Inductor_R);
            OLED_Show_Str(0, 12, str, 12, 1);
//            sprintf((char *)str, "AD1-2  :%4d ", Value_Inductor_L-Value_Inductor_R);
//            OLED_Show_Str(0, 25, str, 12, 1);
		
			sprintf((char *)str, " B_L:%4d   B_R:%4d", Value_Inductor_BL, Value_Inductor_BR);
            OLED_Show_Str(0, 25, str, 12, 1);
		
		
			sprintf((char *)str, "A :%4d  B :%4d    ", Value_Inductor_L-Value_Inductor_R, Value_Inductor_BL-Value_Inductor_BR);
            OLED_Show_Str(0, 38, str, 12, 1);


		       sprintf((char *)str, "P: %3.2f   x:%2.1f ", Pitch, LR_Error);
           OLED_Show_Str(0,51, str, 12, 1);

//            sprintf((char *)str, "Pitch:%2.1f", Pitch );
//            OLED_Show_Str(0, 38, str, 12, 1);

//           sprintf((char *)str, "BAT:%2.2f", (float)Get_Ind_V(5)/410*1.78);
//           OLED_Show_Str(0, 60, str, 12, 1);

            OLED_Refresh_Gram();

    }
}



//float K1 =0.05; // 对加速度计取值的权重
//float dt=20*0.001;//注意：dt的取值为滤波器采样时间
//long angle1 = 0;

//int16_t Yijielvbo(short angle_m, short gyro_m)//采集后计算的角度和角加速度
//{
//     angle1 =  K1 * angle_m+ (1-K1) * (angle1 + gyro_m * dt);
//    return angle1;
////    angle1 =  0.05 * angle_m;
////    angle1 = 0.05 * angle_m + 0.95 * (angle1 + gyro_m * 0.02);
//}

//    short Gyro_X = 0;
//    short Gyro_Y = 0;
//    short Gyro_Z = 0;
//    short Accel_X = 0;
//    short Accel_Y = 0;
//    short Accel_Z = 0;
//    short Pitch = 0;
//    short Roll = 0;
//    short Yaw = 0;
    short Pitch_Kalman;



//float K1 =0.1; // 对加速度计取值的权重
//float dt=0.0001;//注意：dt的取值为滤波器采样时间
//float angle;

//float yijiehubu(float angle_m, float gyro_m)//采集后计算的角度和角加速度
//{
//     angle = 0.1 * angle_m + 0.9 * (angle + gyro_m * 0.0001);
//     return angle;
//}

uint8_t UI_MPU6050(void)
{
//    uint32_t temp_tem = 0;

    OLED_Clear();
    OLED_Show_StrAll(0,  0, " <    陀  螺  仪      ", 1);
    uint8_t str[32];

    for(;;)
    {
		switch(Get_Key())
		{
			case Press_Left:	return 3;
		}

//    MPU6050_GetData(&GYRO, &ACC);   //获取原始数据
////    Data_Filter();     //原始数据滤波
//    Get_Attitude_NoF();


//        sprintf((char *)str, "TEMP: %4d", Read_Temperature());
//        OLED_Show_Str(0, 34, str, 12, 1);
//
//        Get_Angle();
//        printf("Pitch: %f\r\n",Pitch);
        sprintf((char *)str, "P:%3.2f    Y:%3.2f", Pitch, Yaw);
        OLED_Show_Str(0, 20, str, 12, 1);
        sprintf((char *)str, "G X: %5d  Y: %5d ", Accel_X, Accel_Y);
        OLED_Show_Str(0, 33, str, 12, 1);

        OLED_Refresh_Gram();
    }
}

uint8_t UI_Read_End(void)
{
    uint8_t ch[20] = "";
    OLED_Clear();

    OLED_Show_StrAll(0,  0, " <    编 码 器 值      ", 1);

//    int16_t Value_End_L = 0;
//    int16_t Value_End_R = 0;
    for(;;)
    {
		switch(Get_Key())
		{
			case Press_Left:	return 3;
		}

//        Value_End_L = End_Read_Dir(End_L)==0? -ftm_count_get(ftm0) : ftm_count_get(ftm0);
//        Value_End_R = End_Read_Dir(End_R)==0? ftm_count_get(ftm1) : -ftm_count_get(ftm1);

        sprintf((char *)ch,"L_编码器:%5d ", Value_End_L);
        OLED_Show_StrAll(0,  26, ch, 1);
        sprintf((char *)ch,"R_编码器:%5d ", Value_End_R);

        OLED_Show_StrAll(0,  39, ch, 1);

//        ftm_count_clean(ftm0);
//        ftm_count_clean(ftm1);

        OLED_Refresh_Gram();
//        Delay_ms(7);
    }
}



/**********************************************
*****************多选项的模板*********************
//    uint8_t UI_Case = 1;
//    uint8_t Case_Temp = 0;
//    uint8_t Frame_Min = 1;
//    uint8_t Frame_Temp = 0;
//    uint8_t Should_Refresh = 0;//用于更改值后刷新
//
//
//    OLED_Clear();
//    uint8_t UI_Menu[20][30];
//
//    Write_Value(UI_Menu);
//    OLED_Show_Str(0,  0, UI_Menu[0],           12, 0);
//    OLED_Show_Str(0, 13, UI_Menu[Frame_Min],   12, 1);
//    OLED_Show_Str(0, 26, UI_Menu[Frame_Min+1], 12, 1);
//    OLED_Show_Str(0, 39, UI_Menu[Frame_Min+2], 12, 1);
//    OLED_Show_Str(0, 52, UI_Menu[Frame_Min+3], 12, 1);
//    for(;;)
//    {
//        Case_Temp = UI_Case;
//        Frame_Temp = Frame_Min;
//
//		switch (Get_Key())
//		{
//			case Press_Up:
//				if(--UI_Case < 1)
//					UI_Case = 16;
//				break;
//
//			case Press_Down:
//				if(++UI_Case > 16)
//					UI_Case = 1;
//				break;
//			case Press_Left:
//				return 0;
//			case Press_Mid:		//按中
//				switch(UI_Case)
//				{
//					case 1:		return 0;
//					case 2:		return 0;
//					case 3:		return 0;
//					case 4:		return 0;
//					default:	return 0;//防止真出现其他情况
//				}
//		}
//        判断框的范围*/
//        Frame_Min = UI_Case<Frame_Min?UI_Case:Frame_Min;
//        Frame_Min = UI_Case-3>Frame_Min?UI_Case-3:Frame_Min;
//        if(Case_Temp != UI_Case || Should_Refresh == 1)
//        {
//            OLED_Show_Char(6, 12, ' ', 12, 1);
//            OLED_Show_Char(6, 25, ' ', 12, 1);
//            OLED_Show_Char(6, 38, ' ', 12, 1);
//            OLED_Show_Char(6, 50, ' ', 12, 1);
//            /*状态写入UI_Menu里*/
//            Write_Value(UI_Menu);
//            Should_Refresh == 0;
//        }

//        if(Frame_Temp != Frame_Min)
//        {
//            /*显示菜单*/
//            OLED_Show_Str(0, 13, UI_Menu[Frame_Min],   12, 1);
//            OLED_Show_Str(0, 26, UI_Menu[Frame_Min+1], 12, 1);
//            OLED_Show_Str(0, 39, UI_Menu[Frame_Min+2], 12, 1);
//            OLED_Show_Str(0, 52, UI_Menu[Frame_Min+3], 12, 1);
//        }
//        /*显示指示器*/
//        if(UI_Case == Frame_Min)          OLED_Show_Char(6, 12, '@', 12, 1);
//        else if(UI_Case == Frame_Min+1)   OLED_Show_Char(6, 25, '@', 12, 1);
//        else if(UI_Case == Frame_Min+2)   OLED_Show_Char(6, 38, '@', 12, 1);
//        else if(UI_Case == Frame_Min+3)   OLED_Show_Char(6, 50, '@', 12, 1);
//        OLED_Refresh_Gram();
//    }
/***********************************************/
