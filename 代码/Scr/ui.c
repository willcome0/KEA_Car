#include "ui.h"


uint8_t UI_Main(void)
{
    volatile uint8_t UI_Case = 1;	
    uint8_t Case_Temp = 0;
	OLED_Clear(); 
    OLED_Show_StrAll(0,  0, "      主  菜  单      ", 1);
	OLED_Show_StrAll(0, 13, "        发 车         ", 1);
	OLED_Show_StrAll(0, 26, "        方 案         ", 1);
	OLED_Show_StrAll(0, 39, "        外 设         ", 1);
	OLED_Show_StrAll(0, 52, "        设 置         ", 1);
//    OLED_Show_StrZH12_12(0, 20, "。主菜单发车方案设置", 0);
	for(;;)
	{
		Case_Temp = UI_Case;
		switch (Get_Key())
		{

			case Press_Up:   UI_Case--;  break;
			case Press_Down: UI_Case++;  break;				
			case Press_Mid:
				switch(UI_Case)
				{
					case 1:		return 1;
					case 2:		return 2;
					case 3:		return 3;
					case 4:		return 4;
					default:	return 0;//防止真出现其他情况
				}
                break;
                    default: break;
		}
        
        UI_Case=UI_Case<1?4:UI_Case;
        UI_Case=UI_Case>4?1:UI_Case;
        
		if(Case_Temp != UI_Case)
		{
			OLED_Show_Char(32, 12, ' ', 12, 1);
            OLED_Show_Char(32, 25, ' ', 12, 1);
            OLED_Show_Char(32, 38, ' ', 12, 1);
            OLED_Show_Char(32, 50, ' ', 12, 1);
		}
		switch (UI_Case)//判断所处菜单号，显示对应指示
		{
            case 1: OLED_Show_Char(32, 12, '@', 12, 1);  break;
            case 2: OLED_Show_Char(32, 25, '@', 12, 1);  break;
            case 3: OLED_Show_Char(32, 38, '@', 12, 1);  break;
            case 4: OLED_Show_Char(32, 50, '@', 12, 1);  break;
		}
		OLED_Refresh_Gram();
	}
}    
/*倒计时函数，只用于发车菜单中*/
void CountDown(uint8_t time)
{
    OLED_Clear(); 

    for(uint8_t i=time; i!=0; i--)
    {
        Beep_Time(50);
        OLED_Show_Char48_64(40, 0, i+'0', 1);
        OLED_Refresh_Gram();
        //考虑到最后一秒蜂鸣器时常
        if(1 == i)
        {
            Delay_ms(800);
            continue;
        }
        Delay_ms(950);

    }
//    Logo_CarGo();
    Beep_Time(300);
    OLED_Refresh_Gram();
    Pin_Output_Toggle(PTE, PTE0);
}
uint8_t UI_Go(void)
{
    int8_t GO_Time = 1;
	OLED_Clear();
    
    for(;;)
    {
        OLED_Show_Str(6,  0, "<", 12, 1);
        OLED_Show_Char48_64(40, 0, GO_Time+'0', 1);
        switch (Get_Key())
        {
            case Press_Up:   GO_Time++;  break;
            case Press_Down: GO_Time--;  break;
            case Press_Mid:  CountDown(GO_Time);  Just_Do_It();
            case Press_Left: return 0;
            case Press_Right:break;
        }
        GO_Time = GO_Time>=5?5:GO_Time;
        GO_Time = GO_Time<=0?0:GO_Time;
        OLED_Refresh_Gram();
    }
}  


void Chang_Value(uint8_t UI_Case, uint8_t Frame_Min, int16_t *Value, uint8_t Div_Num)
{
    int16_t temp_value = *Value;
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
            sprintf(ch, "%1.2f", (float)temp_value/Div_Num);
            OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
        }
        uint8_t value_ok_flag = 0;
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
                *Value = temp_value;
                break;
            case Press_Left:
                value_ok_flag = 1;
                break;
        }
        temp_value = temp_value> 999? 999:temp_value;
        //调试阶段先不管好不好看
        temp_value = temp_value<-999?-999:temp_value;
        
        
        if(1 == value_ok_flag)
        {
            if(1 == Div_Num)
            {
                sprintf(ch, "%4d", temp_value);
                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 1);
            }
            else
            {
                sprintf(ch, "%1.2f", (float)temp_value/Div_Num);
                OLED_Show_Str(102, (UI_Case-Frame_Min+1)*13, ch, 12, 1);
            }
            OLED_Refresh_Gram();
            break;
        }
        OLED_Refresh_Gram();
    }
}
void Write_Value(uint8_t in_ch[][30])
{
//                       "123456789012345678901"
    sprintf(in_ch [0], "  <     方  案       ");
    sprintf(in_ch [1], "   1.  目标角度  %4d  ", Plan1.Target.Angle);
    sprintf(in_ch [2], "   2.  目标速度  %4d  ", Plan1.Target.Speed);
    sprintf(in_ch [3], "   3.  角 度 P   %4d  ", Plan1.Angle.P);
    sprintf(in_ch [4], "   4.  角 度 D   %2.1f  ", (float)Plan1.Angle.D/10);
    sprintf(in_ch [5], "   5.  速 度 P   %4d  ", Plan1.Speed.P);
    sprintf(in_ch [6], "   6.  速 度 I   %2.1f  ", (float)Plan1.Speed.I/100);
    sprintf(in_ch [7], "   7.  转 向 P   %4d  ", Plan1.Turn.P);
    sprintf(in_ch [8], "   8.  转 向 D   %4d  ", Plan1.Turn.D);
    sprintf(in_ch [9], "   9.  tp        %4d  ", Plan1.Turn.tp);
    sprintf(in_ch[10], "   10. td        %4d  ", Plan1.Turn.td);
    sprintf(in_ch[11], "   11. XXXXXXX   %4d  ", 0);
    sprintf(in_ch[12], "   12. XXXXXXX   %4d  ", 0);
    sprintf(in_ch[13], "   13. XXXXXXX   %4d  ", 0);
    sprintf(in_ch[14], "   14. XXXXXXX   %4d  ", 0);
    sprintf(in_ch[15], "   15. XXXXXXX   %4d  ", 0);
    sprintf(in_ch[16], "   16. XXXXXXX   %4d  ", 0);
    
//    Judge_State(Judge_ch, Set_XXXX);
//    sprintf(in_ch[2], "     2. XXXX     %s", Judge_ch);
}

uint8_t UI_Plan(void)
{
    uint8_t UI_Case = 1;
    uint8_t Case_Temp = 0;
    uint8_t Frame_Min = 1;
    uint8_t Frame_Temp = 0;
    uint8_t Should_Refresh = 0;//用于更改值后刷新
    uint8_t ch[25];
    
    OLED_Clear(); 
    uint8_t UI_Menu[20][30];
    
    Write_Value(UI_Menu);
    OLED_Show_StrAll(0,  0, UI_Menu[0],           1);
    OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   1);
    OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], 1);
    OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], 1);
    OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], 1);
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
					case  1:	Chang_Value(UI_Case, Frame_Min, &Plan1.Target.Angle,  1);  break;
					case  2:	Chang_Value(UI_Case, Frame_Min, &Plan1.Target.Speed,  1);  break;
					case  3:	Chang_Value(UI_Case, Frame_Min, &Plan1.Angle.P,   1);  break;
					case  4:	Chang_Value(UI_Case, Frame_Min, &Plan1.Angle.D, 10);  break;
                    case  5:	Chang_Value(UI_Case, Frame_Min, &Plan1.Speed.P,   1);  break;
                    case  6:	Chang_Value(UI_Case, Frame_Min, &Plan1.Speed.I, 100);  break;
                    case  7:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.P,    1);  break;
                    case  8:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.D,  1);  break;
                    case  9:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.tp,  1);  break;
                    case  10:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.td,  1);  break;
//                    case  9:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;
//                    case 10:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;
//                    case 11:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;
//                    case 12:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;
//                    case 13:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;
//                    case 14:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;
//                    case 15:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;
//                    case 16:	Chang_Value(UI_Case, Frame_Min, &Plan1.Turn.I,  100); break;

				}
		}
        UI_Case=UI_Case<1?16:UI_Case;
        UI_Case=UI_Case>16?1:UI_Case;
        /*判断框的范围*/
        Frame_Min = UI_Case<Frame_Min?UI_Case:Frame_Min;
        Frame_Min = UI_Case-3>Frame_Min?UI_Case-3:Frame_Min;
        if(Case_Temp != UI_Case || Should_Refresh == 1)  
        {
            OLED_Show_Char(6, 12, ' ', 12, 1);
            OLED_Show_Char(6, 25, ' ', 12, 1);
            OLED_Show_Char(6, 38, ' ', 12, 1);
            OLED_Show_Char(6, 50, ' ', 12, 1);
            /*状态写入UI_Menu里*/
            Write_Value(UI_Menu);
            Should_Refresh == 0;
        }

        if(Frame_Temp != Frame_Min)  
        {
            /*显示菜单*/
            OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   1);
            OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], 1);
            OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], 1);
            OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], 1);
        }
        /*显示指示器*/
        if(UI_Case == Frame_Min)          OLED_Show_Char(6, 12, '@', 12, 1);
        else if(UI_Case == Frame_Min+1)   OLED_Show_Char(6, 25, '@', 12, 1);
        else if(UI_Case == Frame_Min+2)   OLED_Show_Char(6, 38, '@', 12, 1);
        else if(UI_Case == Frame_Min+3)   OLED_Show_Char(6, 50, '@', 12, 1);
        OLED_Refresh_Gram();
    }
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
    OLED_Show_StrAll(0,  0, UI_Menu[0], 1);
    OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   1);
    OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], 1);
    OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], 1);
    OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], 1);
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
            OLED_Show_Char(12, 12, ' ', 12, 1);
            OLED_Show_Char(12, 25, ' ', 12, 1);
            OLED_Show_Char(12, 38, ' ', 12, 1);
            OLED_Show_Char(12, 50, ' ', 12, 1);
        }
        if(Frame_Temp != Frame_Min)  
        {
            /*显示菜单*/
            OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min], 1);
            OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], 1);
            OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], 1);
            OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], 1);
        }
        /*显示指示器*/
        if(UI_Case == Frame_Min)          OLED_Show_Char(12, 12, '@', 12, 1);
        else if(UI_Case == Frame_Min+1)   OLED_Show_Char(12, 25, '@', 12, 1);
        else if(UI_Case == Frame_Min+2)   OLED_Show_Char(12, 38, '@', 12, 1);
        else if(UI_Case == Frame_Min+3)   OLED_Show_Char(12, 50, '@', 12, 1);
        OLED_Refresh_Gram();
    }
}  
void Judge_State(uint8_t Judge_ch[], uint8_t state)
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
    Judge_State(Judge_ch, Set_LED);
    sprintf(in_ch[1], "   1.  L E D      %s", Judge_ch);
    Judge_State(Judge_ch, Set_Beep);
    sprintf(in_ch[2], "   2.  蜂 鸣 器   %s", Judge_ch);
    Judge_State(Judge_ch, Bluetooth);
    sprintf(in_ch[3], "   3.  蓝  牙     %s", Judge_ch);
    
    Judge_State(Judge_ch, UnSet);
    sprintf(in_ch[4], "   4.  XXXXXXX    %s", Judge_ch);
    Judge_State(Judge_ch, UnSet);
    sprintf(in_ch[5], "   5.  XXXXXXX    %s", Judge_ch);
    Judge_State(Judge_ch, UnSet);
    sprintf(in_ch[6], "   6.  XXXXXXX    %s", Judge_ch);
    Judge_State(Judge_ch, UnSet);
    sprintf(in_ch[7], "   7.  XXXXXXX    %s", Judge_ch);
    Judge_State(Judge_ch, UnSet);
    sprintf(in_ch[8], "   8.  XXXXXXX    %s", Judge_ch);
    Judge_State(Judge_ch, UnSet);
    sprintf(in_ch[9], "   9.  XXXXXXX    %s", Judge_ch);
//    Judge_State(Judge_ch, Set_XXXX);
//    sprintf(in_ch[2], "     2. XXXX     %s", Judge_ch);
}

void Chang_State(uint8_t UI_Case, uint8_t Frame_Min, uint8_t *Value)
{
    int8_t temp_value = *Value;
    uint8_t ch[25];
    
    for(;;)
    {
        Judge_State(ch, temp_value);
        OLED_Show_Str(108, (UI_Case-Frame_Min+1)*13, ch, 12, 0);
        
        uint8_t value_ok_flag = 0;
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
                *Value = temp_value;
                break;
            case Press_Left:
                value_ok_flag = 1;
                break;
        }
        temp_value = temp_value>1?0:temp_value;
        temp_value = temp_value<0?1:temp_value;
        
        
        if(1 == value_ok_flag)
        {
            Judge_State(ch, temp_value);
            OLED_Show_Str(108, (UI_Case-Frame_Min+1)*13, ch, 12, 1);
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
    OLED_Show_StrAll(0,  0, UI_Menu[0],           1);
    OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   1);
    OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], 1);
    OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], 1);
    OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], 1);
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
					case 1:  Chang_State(UI_Case, Frame_Min, &Set_LED);   break;
					case 2:  Chang_State(UI_Case, Frame_Min, &Set_Beep);  break;
					case 3:  Chang_State(UI_Case, Frame_Min, &Bluetooth);  break;
					case 4:		return 0;
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
            OLED_Show_Char(6, 12, ' ', 12, 1);
            OLED_Show_Char(6, 25, ' ', 12, 1);
            OLED_Show_Char(6, 38, ' ', 12, 1);
            OLED_Show_Char(6, 50, ' ', 12, 1);
            /*状态写入UI_Menu里*/
            Write_State(UI_Menu);
            Should_Refresh == 0;
        }

        if(Frame_Temp != Frame_Min)  
        {
            /*显示菜单*/
            OLED_Show_StrAll(0, 13, UI_Menu[Frame_Min],   1);
            OLED_Show_StrAll(0, 26, UI_Menu[Frame_Min+1], 1);
            OLED_Show_StrAll(0, 39, UI_Menu[Frame_Min+2], 1);
            OLED_Show_StrAll(0, 52, UI_Menu[Frame_Min+3], 1);
        }
        /*显示指示器*/
        if(UI_Case == Frame_Min)          OLED_Show_Char(6, 12, '@', 12, 1);
        else if(UI_Case == Frame_Min+1)   OLED_Show_Char(6, 25, '@', 12, 1);
        else if(UI_Case == Frame_Min+2)   OLED_Show_Char(6, 38, '@', 12, 1);
        else if(UI_Case == Frame_Min+3)   OLED_Show_Char(6, 50, '@', 12, 1);
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
        sprintf(str, "Yaw: %3.2f    ", Yaw);
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