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
void CountDown(uint16_t time)
{
    OLED_Clear();

    for(uint8_t i=time; i!=0; i--)
    {
        Beep_Time(50);
        OLED_Show_Char48_64(40, 0, i+'0', Normal);
        OLED_Refresh_Gram();
        //考虑到最后一秒蜂鸣器时常
        if(1 == i)
        {
            Delay_ms(800);
            continue;
        }
        Delay_ms(800);

    }
    Beep_Time(200);
    OLED_Refresh_Gram();
}

uint8_t UI_Go(void)
{
    int8_t GO_Time = 1;
	OLED_Clear();

    for(;;)
    {
		uint8_t str[30];
		sprintf(str, "%.3f           %.3f", (float)Run_Distance/5760, (float)Run_Time/100);
		OLED_Show_Str(0, 40, str, 12, 1);
		sprintf(str, "%.3f", (float)Run_Distance/Run_Time/57.6);
		OLED_Show_Str(0, 53, str, 12, 1);
		
        OLED_Show_Str(6,  0, "<", 12, Normal);
        OLED_Show_Char48_64(40, 0, _Com_CountDown_+'0', Normal);
		
        switch (Get_Key())
        {
            case Press_Up:      _Com_CountDown_++;
                                _Com_CountDown_ = _Com_CountDown_>=5?5:_Com_CountDown_;
                                /******************更新并保存数据***********************/

                                uint16_TMEP = _Com_CountDown_;
                                Cache_ALL_DATA();           // 缓存所有flash中的数据到数组
                                _Com_CountDown_ = uint16_TMEP;   // 更新该数组成员的值
                                FLASH_Erase_All_Data();     // 完全擦除存数据的扇叶
                                FLASH_Write_All_Data();     // 写入所有数据到存数据的扇叶

                                /******************************************************/
                                break;

            case Press_Down:    _Com_CountDown_ = _Com_CountDown_==0?1:_Com_CountDown_;
								_Com_CountDown_--;
                                
                                /******************更新并保存数据***********************/

                                uint16_TMEP = _Com_CountDown_;
                                Cache_ALL_DATA();           // 缓存所有flash中的数据到数组
                                _Com_CountDown_ = uint16_TMEP;   // 更新该数组成员的值
                                FLASH_Erase_All_Data();     // 完全擦除存数据的扇叶
                                FLASH_Write_All_Data();     // 写入所有数据到存数据的扇叶

                                /******************************************************/
                                break;

            case Press_Mid:     CountDown(_Com_CountDown_);
                                Just_Do_It();
                                break;

            case Press_Left:    
								Run_Time = 0;
								Run_Distance = 0;
								return 0;

            case Press_Right:   break;
        }

        OLED_Refresh_Gram();
    }
}

void Chang_Value_End(uint8_t UI_Case, uint8_t Frame_Min, int16_t *Value, uint8_t Div_Num)
{
    int16_t temp_value = *Value;
    temp_value = temp_value>9999 ? 9999:temp_value;
	temp_value = temp_value<1 ? 1:temp_value;
    uint8_t ch[25];

    for(;;)
    {

        if(1 == Div_Num)
        {
            sprintf(ch, "%4d", temp_value);
            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
        }
        else
        {
            if(10  == Div_Num)
                sprintf(ch, "%2.1f", (float)temp_value/Div_Num);
            else if(100 == Div_Num)
                sprintf(ch, "%1.2f", (float)temp_value/Div_Num);

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
                sprintf(ch, "%4d", temp_value);
                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
            }
            else
            {
                if(10  == Div_Num)
                    sprintf(ch, "%2.1f", (float)temp_value/Div_Num);
                else if(100 == Div_Num)
                    sprintf(ch, "%1.2f", (float)temp_value/Div_Num);

                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
            }
            OLED_Refresh_Gram();
            break;
        }
        OLED_Refresh_Gram();
    }
}
void Chang_Value(uint8_t UI_Case, uint8_t Frame_Min, int16_t *Value, uint8_t Div_Num)
{
    int16_t temp_value = *Value;
    temp_value = temp_value>9999 ? 9999:temp_value;
	temp_value = temp_value<1 ? 1:temp_value;
    uint8_t ch[25];

    for(;;)
    {

//        if(1 == Div_Num)
//        {
            sprintf(ch, "%4d ", temp_value);
            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
//        }
//        else
//        {
//            if(10  == Div_Num)
//                sprintf(ch, "%2.1f", (float)temp_value/Div_Num);
//            else if(100 == Div_Num)
//                sprintf(ch, "%1.2f", (float)temp_value/Div_Num);

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

            case Press_Left:    value_ok_flag = 1;
				                temp_value = *Value;
                                break;

            case Press_Right:	for(;;)
								{
									temp_value += Value_End_L;	//增加编码器数值
									temp_value = temp_value>9999 ? 9999:temp_value;
									temp_value = temp_value<0 ? 0:temp_value;
									
									switch(Get_Key())//编码器调节
									{
										case Press_Left:
														temp_value = *Value;
														goto break_for_1;	// 跳出该for
														break;
										case Press_Mid:	
														/******************更新并保存数据***********************/

														Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
														*Value = temp_value; 		// 单独更新传参进的数组成员的值
														FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
														FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶

														/******************************************************/
														goto break_for_1;	// 跳出该for
														break;
											
										

									}
										sprintf(ch, "%4d#", temp_value);
										OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
										OLED_Refresh_Gram();
								}
								break_for_1: ;
								break;
        }



        if(1 == value_ok_flag)
        {
//            if(1 == Div_Num)
//            {
			sprintf(ch, "%4d ", temp_value);
			OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
//            }
//            else
//            {
//                if(10  == Div_Num)
//                    sprintf(ch, "%2.1f", (float)temp_value/Div_Num);
//                else if(100 == Div_Num)
//                    sprintf(ch, "%1.2f", (float)temp_value/Div_Num);

//                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);
//            }
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
	switch(_Com_Plan_)
	{
		case 1:	sprintf(in_ch [0], "  <    方  案  一     ");	break;
		case 2:	sprintf(in_ch [0], "  <    方  案  二     ");	break;
		case 3:	sprintf(in_ch [0], "  <    方  案  三     ");	break;
		case 4:	sprintf(in_ch [0], "  <    方  案  四     ");	break;
		case 5:	sprintf(in_ch [0], "  <    方  案  五     ");	break;
		default: 												break;
	}
    sprintf(in_ch [1], "   1.  目标角度  %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_	]);
    sprintf(in_ch [2], "   2.  目标速度  %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Speed_	]);
    sprintf(in_ch [3], "   3.  角 度 P   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_AnglePID_P_		]);
    sprintf(in_ch [4], "   4.  角 度 D   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_AnglePID_D_		]);
    sprintf(in_ch [5], "   5.  速 度 P   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_SpeedPID_P_		]);
    sprintf(in_ch [6], "   6.  速 度 I   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_SpeedPID_I_		]);
    sprintf(in_ch [7], "   7.  转 向 P   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_TurnPID_P_		]);
    sprintf(in_ch [8], "   8.  转 向 D   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_TurnPID_D_   	]);
    sprintf(in_ch [9], "   9.  HuanAdd   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan_Add_]);
    sprintf(in_ch[10], "   10. td        %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_]);
    sprintf(in_ch[11], "   11. XXXXXXX   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_]);
    sprintf(in_ch[12], "   12. XXXXXXX   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_]);
    sprintf(in_ch[13], "   13. XXXXXXX   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_]);
    sprintf(in_ch[14], "   14. XXXXXXX   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_]);
    sprintf(in_ch[15], "   15. XXXXXXX   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_]);
    sprintf(in_ch[16], "   16. XXXXXXX   %4d  ",    ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Target_Angle_]);
}

uint8_t UI_Plan(void)
{
    uint8_t UI_Case = 1;
    uint8_t Case_Temp = 0;
    uint8_t Frame_Min = 1;
    uint8_t Frame_Temp = 0;
    uint8_t Should_Refresh = 0;//用于更改值后刷新
    uint8_t ch[25];
	uint16_t Index_Plan_Offset = (_Com_Plan_-1)*40;

    uint8_t UI_Menu[20][30];

	back: ;
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
								UI_Case=UI_Case<1?16:UI_Case;
								break;
			
			case Press_Down: 	UI_Case++;
								UI_Case=UI_Case>16?1:UI_Case;
								break;
			
			case Press_Left:	return 0;
			
			case Press_Right:	uint8_t TEMP_GRAM_1[OLED_X_MAX][8];
								for(uint8_t i=0; i<OLED_X_MAX; i++)
									for(uint8_t j=0; j<8; j++)
										TEMP_GRAM_1[i][j] = OLED_GRAM[i][j];
			
								uint8_t UI_Case_1 = 1;
								uint8_t Break_Flag = 0;
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
										case Press_Right:	uint8_t TEMP_GRAM_2[OLED_X_MAX][8];
															for(uint8_t i=0; i<OLED_X_MAX; i++)
																for(uint8_t j=0; j<8; j++)
																	TEMP_GRAM_2[i][j] = OLED_GRAM[i][j];
										
															uint8_t UI_Case_2 = 1;
															uint8_t Break_Flag_1 = 0;
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
																	switch(_Com_Plan_)
																	{
																		case 1:	sprintf(Temp_Str[0], " 方案二 ");
																				sprintf(Temp_Str[1], " 方案三 ");
																				sprintf(Temp_Str[2], " 方案四 ");
																				sprintf(Temp_Str[3], " 方案五 ");
																				break;
																		case 2:	sprintf(Temp_Str[0], " 方案一 ");
																				sprintf(Temp_Str[1], " 方案三 ");
																				sprintf(Temp_Str[2], " 方案四 ");
																				sprintf(Temp_Str[3], " 方案五 ");
																				break;
																		case 3:	sprintf(Temp_Str[0], " 方案一 ");
																				sprintf(Temp_Str[1], " 方案二 ");
																				sprintf(Temp_Str[2], " 方案四 ");
																				sprintf(Temp_Str[3], " 方案五 ");
																				break;
																		case 4:	sprintf(Temp_Str[0], " 方案一 ");
																				sprintf(Temp_Str[1], " 方案二 ");
																				sprintf(Temp_Str[2], " 方案三 ");
																				sprintf(Temp_Str[3], " 方案五 ");
																				break;
																		case 5:	sprintf(Temp_Str[0], " 方案一 ");
																				sprintf(Temp_Str[1], " 方案二 ");
																				sprintf(Temp_Str[2], " 方案三 ");
																				sprintf(Temp_Str[3], " 方案四 ");
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
																						goto back;
																						break;
																						
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
						case  1:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Target_Angle_	],  Normal);   break;
						case  2:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Target_Speed_	],  Normal);   break;
						case  3:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_AnglePID_P_	],  Normal);   break;
						case  4:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_AnglePID_D_	],  Normal);   break;
						case  5:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_SpeedPID_P_	],  Normal);   break;
						case  6:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_SpeedPID_I_	],  Normal);   break;
						case  7:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_TurnPID_P_		],  Normal);   break;
						case  8:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_TurnPID_D_		],  Normal);   break;
						case  9:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Huan_Add_		],	Normal);   break;
						case  10:	Chang_Value(UI_Case, Frame_Min, &ALL_DATA[Index_Plan_Offset + _INDEX_Target_Angle_	],	Normal);  break;
//						case  11:   Chang_Value(UI_Case, Frame_Min, &DATA_11, DATA_P_11);  break;
//						case  12:   Chang_Value(UI_Case, Frame_Min, &DATA_12, DATA_P_12);  break;
//						case  13:   Chang_Value(UI_Case, Frame_Min, &DATA_13, DATA_P_13);  break;
//						case  14:   Chang_Value(UI_Case, Frame_Min, &DATA_14, DATA_P_14);  break;
//						case  15:   Chang_Value(UI_Case, Frame_Min, &DATA_15, DATA_P_15);  break;
//						case  16:   Chang_Value(UI_Case, Frame_Min, &DATA_16, DATA_P_16);  break;
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
            Should_Refresh == 0;
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

    OLED_Clear();
    uint8_t UI_Menu[10][30] =
                  {
                    "  <     外  设       ",
                    "    1.  陀 螺 仪     ",
                    "    2.  电 感 值     ",
                    "    3.  编码器值     ",
                    "    4.  XXXXXXX      ",
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
			case Press_Up:   UI_Case--;  break;
            case Press_Down: UI_Case++;  break;
			case Press_Left: return 0;
			case Press_Mid:		//按中
				switch(UI_Case)
				{
					case 1:		return 31;
					case 2:		return 32;
					case 3:		return 33;
					case 4:		return 34;
					default:	return 0;//防止真出现其他情况
				}
		}
        UI_Case=UI_Case<1?9:UI_Case;
        UI_Case=UI_Case>9?1:UI_Case;
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
        case 0:   sprintf(Judge_ch, "OFF");  break;
        case 1:   sprintf(Judge_ch, "ON ");  break;
        default:  sprintf(Judge_ch, "???");
    }

}
/*只用于UI_Set()函数*/
void Write_State(uint8_t in_ch[][30])
{
    uint8_t Judge_ch[4] = "";
    uint8_t UnSet = 77;

    sprintf(in_ch[0], "  <     设  置       ");
    Judge_State(Judge_ch, _Com_LED_);
    sprintf(in_ch[1], "   1.  L E D      %s", Judge_ch);
    Judge_State(Judge_ch, _Com_Buzzer_);
    sprintf(in_ch[2], "   2.  蜂 鸣 器   %s", Judge_ch);
    Judge_State(Judge_ch, _Com_BT_);
    sprintf(in_ch[3], "   3.  蓝  牙     %s", Judge_ch);

    Judge_State(Judge_ch, _Com_Run_);
    sprintf(in_ch[4], "   4.  R U N      %s", Judge_ch);
    Judge_State(Judge_ch, _Com_RunProtect_);
    sprintf(in_ch[5], "   5.  Protect    %s", Judge_ch);
//    Judge_State(Judge_ch, _Com_RunTimeStop_);
//    sprintf(in_ch[6], "   6.  TimeStop   %s", Judge_ch);
   sprintf(in_ch [6], "   6.  TimeStop  %4d  ", _Com_RunTimeStop_);
	
   sprintf(in_ch [7], "   7.  Dis Stop  %4d  ", _Com_RunDisStop_ );
//    Judge_State(Judge_ch, _Com_XX3_);
//    sprintf(in_ch[7], "   7.  X X 3      %s", Judge_ch);
    Judge_State(Judge_ch, _Com_XX4_);
    sprintf(in_ch[8], "   8.  X X 4      %s", Judge_ch);
    Judge_State(Judge_ch, _Com_XX5_);
    sprintf(in_ch[9], "   9.  X X 5      %s", Judge_ch);
//    Judge_State(Judge_ch, Set_XXXX);
//    sprintf(in_ch[2], "     2. XXXX     %s", Judge_ch);
}

//uint8_t U8_DATA[4];
//uint32_t CLEAN_DATA = 0xFFFFFFFF;
void Chang_State(uint8_t UI_Case, uint8_t Frame_Min, uint16_t *Value)
{
    int8_t temp_value = *Value;
    uint8_t ch[25];
	uint8_t Which_4B = (UI_Case-1)/2; 	// 判断属于哪4字节空间里，flash写数据一次至少4字节;
										// 这里的哪是指从公共参数开始，即偏移量400开始。
    for(;;)
    {
        Judge_State(ch, temp_value);	// 判断并写入ON/OFF
        OLED_Show_Str(108, (UI_Case-Frame_Min+1)*13, ch, 12, Toggle);	// 显示ON/OFF

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
            OLED_Show_Str(108, (UI_Case-Frame_Min+1)*13, ch, 12, Normal);	// 更新状态（ON/OFF）
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


    OLED_Clear();
    uint8_t UI_Menu[10][30];
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
			case Press_Up:   UI_Case--;  break;
            case Press_Down: UI_Case++;  break;
			case Press_Left: return 0;
			case Press_Mid:		//按中
				switch(UI_Case)
				{
					case 1:  Chang_State(UI_Case, Frame_Min, &_Com_LED_);   				break;
					case 2:  Chang_State(UI_Case, Frame_Min, &_Com_Buzzer_); 				break;
					case 3:  Chang_State(UI_Case, Frame_Min, &_Com_BT_);  					break;
					case 4:	 Chang_State(UI_Case, Frame_Min, &_Com_Run_);  					break;
					case 5:	 Chang_State(UI_Case, Frame_Min, &_Com_RunProtect_);  			break;
					case 6:	 Chang_Value(UI_Case, Frame_Min, &_Com_RunTimeStop_,  Normal);	break;
					case 7:	 Chang_Value(UI_Case, Frame_Min, &_Com_RunDisStop_ ,  Normal);	break;
					case 8:	 Chang_State(UI_Case, Frame_Min, &_Com_XX4_);  					break;
					case 9:	 Chang_State(UI_Case, Frame_Min, &_Com_XX5_);  					break;


					default:	return 0;//防止真出现其他情况
				}
		}
        UI_Case=UI_Case<1?9:UI_Case;
        UI_Case=UI_Case>9?1:UI_Case;
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
            Write_State(UI_Menu);
            Should_Refresh == 0;
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
    }
}





uint8_t UI_Read_Ind(void)
{
    uint32_t Ind_L = 0;
    uint32_t Ind_R = 0;

    uint32_t Ind_L_Integral = 0;
    uint32_t Ind_R_Integral = 0;

    uint16_t Pre_L_Integral[10] = {0,0,0,0,0,0,0,0,0,0,};
    uint16_t Pre_R_Integral[10] = {0,0,0,0,0,0,0,0,0,0,};

    int16_t L_R = 0;
    uint8_t ch[20] = "";
    float error_dis = 0;
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
            sprintf(str, "AD_L:%4d  AD_R:%4d", Value_Inductor_L, Value_Inductor_R);
            OLED_Show_Str(0, 12, str, 12, 1);
//            sprintf(str, "AD1-2  :%4d ", Value_Inductor_L-Value_Inductor_R);
//            OLED_Show_Str(0, 25, str, 12, 1);
		    sprintf(str, "AD_3:%4d  AD_4:%4d", Get_Ind_V(AD_3), Get_Ind_V(AD_4));
            OLED_Show_Str(0, 25, str, 12, 1);


		       sprintf(str, "PITCH: %3.2f   x:%f ", Pitch,x);
           OLED_Show_Str(0,45, str, 12, 1);

//            sprintf(str, "Pitch:%2.1f", Pitch );
//            OLED_Show_Str(0, 38, str, 12, 1);

//           sprintf(str, "BAT:%2.2f", (float)Get_Ind_V(5)/410*1.78);
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
    uint32_t temp_tem = 0;

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


//        sprintf(str, "TEMP: %4d", Read_Temperature());
//        OLED_Show_Str(0, 34, str, 12, 1);
//
//        Get_Angle();
//        printf("Pitch: %f\r\n",Pitch);
        sprintf(str, "PITCH: %3.2f    ", Pitch);
        OLED_Show_Str(0, 20, str, 12, 1);
        sprintf(str, "G_Y: %5d    ", GYRO.Y);
        OLED_Show_Str(0, 33, str, 12, 1);
        sprintf(str, "Yaw: %d    ", Yaw);
        OLED_Show_Str(0, 46, str, 12, 1);

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

        sprintf(ch,"L_编码器:%5d ", Value_End_L);
        OLED_Show_StrAll(0,  26, ch, 1);
        sprintf(ch,"R_编码器:%5d ", Value_End_R);
//        sprintf(ch, "   2.  目标角度  %1.2f", (float)Plan1.Target.Speed/100);
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
//        /*判断框的范围*/
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