#include "control.h"






//uint16_t Value_Ind_L_Old = 0;
//uint16_t Value_Ind_R_Old = 0;
//int16_t Error_Ind = 0;
//int16_t Eroor_Ind_Old = 0;

//int16_t Value_End_L = 0;
//int16_t Value_End_R = 0;
//int16_t Error_End = 0;
//int16_t PreError[20];

//int AlllastError=0;
//int Speed_Slide[3]={0};//速度平滑参数

//int SpeedOUT;
//int32_t End_Integral = 0;   

float LR_Error = 0;
float LR1_Error = 0;
float LR2_Error = 0;
float LR3_Error = 0;

//uint8_t Do_it = 1;

//uint8_t Huan_Count_Flag = 0;
//uint16_t Huan_Count = 0;
//float Yaw_Huan = 0.00001;

//#define OUT 0
//#define IN 1






uint16_t CONTROL_Target_Angle = 0;
uint16_t CONTROL_Target_Speed = 0;
uint16_t CONTROL_AnglePID_P	 = 0;
uint16_t CONTROL_AnglePID_D   = 0;
uint16_t CONTROL_SpeedPID_P   = 0;
uint16_t CONTROL_SpeedPID_I   = 0;
uint16_t CONTROL_TurnPID_P    = 0;
uint16_t CONTROL_TurnPID_D    = 0;







int32_t Int_A_X = 0;
int32_t Int_A_Y = 0;
int32_t Int_A_Z = 0;
int32_t Int_G_X = 0;
int32_t Int_G_Y = 0;
int32_t Int_G_Z = 0;
#define AVE 5
int16_t Pre_A_X[AVE], Pre_A_Y[AVE], Pre_A_Z[AVE];
int16_t Pre_G_X[AVE], Pre_G_Y[AVE], Pre_G_Z[AVE];



void PIT_CH0_IRQHandler(void)
{
	PIT_CLR_Flag(PIT_CH0);  //清除中断标志位 
	
	/*中断内容--开始*/


	
	Get_Pose();	// 获取姿态（6050数据）
	Get_Ind();	// 获取电感值
	Get_End();	// 获取转速（编码器值）
	


	if( 1 == _Com_BT_ )	//计时与测距
	{
		Run_Time++;							// 计时	
		if( Ave_End>=0 )	//防止起跑时倒转导致Run_Distance出现负数
			Run_Distance += Ave_End;
	}

	
	
	
//	Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*(Gyro_Y - (Gyro_Z>0?Gyro_Z:-Gyro_Z)*0.45 );   //直立环
	Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*Gyro_Y;   //直立环


	LR3_Error = LR2_Error;
	LR2_Error = LR1_Error;
	LR1_Error = LR_Error;
	LR_Error =(5.043e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(-2.85e-06)*(float)Error_Ind*Error_Ind + 0.01201*(float)Error_Ind  -0.006396;  //角度18.8			
//	LR_Error = (float)(Value_Inductor_R - Value_Inductor_L)/(float)(Value_Inductor_L + Value_Inductor_R)*50;

	In_Huan();
									

//	Turn_PWM = LR_Error*CONTROL_TurnPID_P + GYRO.X/10*CONTROL_TurnPID_D;
//	Turn_PWM = (LR_Error*0.4+LR1_Error*0.3+LR2_Error*0.2+LR3_Error*0.1)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
	Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;

	Reed_Stop();	// 干簧管停车
								
	Go_or_Stop();	// PID值给电机和停车
							
	Beep_Task();	// 蜂鸣器任务（并行）
	Send_Upper();	// 上位机发送

}



uint8_t Just_Do_It(void)
{

    OLED_Clear();
    
	/********开电机********/
	if(!_Com_Debug_)
	{
		
		Motor_L_EN(Enable);
		Motor_R_EN(Enable);
	}

	// 计时与测距相关
	Run_Time_Flag = 1;
	Run_Time = 0;
	Run_Distance = 0;

    /**********************/
	

    OLED_Display_Off();	//关OLED
	Huan_Flag = 0;
	Huan_No = 1;	// 准备进第一个环
	Bt_Send = 1;
	
	uint16_t Index_Plan_Offset_1 = (_Com_Plan_-1)*40;
	
	CONTROL_Target_Angle = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Target_Angle_	];
	CONTROL_Target_Speed = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Target_Speed_	];
	CONTROL_AnglePID_P 	 = ALL_DATA[Index_Plan_Offset_1 + _INDEX_AnglePID_P_	];
	CONTROL_AnglePID_D 	 = ALL_DATA[Index_Plan_Offset_1 + _INDEX_AnglePID_D_	];
	CONTROL_SpeedPID_P 	 = ALL_DATA[Index_Plan_Offset_1 + _INDEX_SpeedPID_P_	];
	CONTROL_SpeedPID_I   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_SpeedPID_I_	];
	CONTROL_TurnPID_P    = ALL_DATA[Index_Plan_Offset_1 + _INDEX_TurnPID_P_		];
	CONTROL_TurnPID_D    = ALL_DATA[Index_Plan_Offset_1 + _INDEX_TurnPID_D_		];

	CONTROL_Huan50_Add   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Huan50_Add_	];
	CONTROL_InHuan50_Min = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan50_Min_	];
	CONTROL_InHuan50_Max = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan50_Max_	];
	
	CONTROL_Huan60_Add   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Huan60_Add_	];
	CONTROL_InHuan60_Min = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan60_Min_	];
	CONTROL_InHuan60_Max = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan60_Max_	];
	
	CONTROL_Huan70_Add   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Huan70_Add_	];
	CONTROL_InHuan70_Min = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan70_Min_	];
	CONTROL_InHuan70_Max = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan70_Max_	];
	
	CONTROL_Huan80_Add   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Huan80_Add_	];
	CONTROL_InHuan80_Min = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan80_Min_	];
	CONTROL_InHuan80_Max = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan80_Max_	];
	
	CONTROL_Huan90_Add   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Huan90_Add_	];
	CONTROL_InHuan90_Min = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan90_Min_	];
	CONTROL_InHuan90_Max = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan90_Max_	];
	
	CONTROL_Huan100_Add   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Huan100_Add_	];
	CONTROL_InHuan100_Min = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan100_Min_	];
	CONTROL_InHuan100_Max = ALL_DATA[Index_Plan_Offset_1 + _INDEX_InHuan100_Max_	];
	
	
	CONTROL_Huan1_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan1_Para_];
	CONTROL_Huan2_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan2_Para_];
	CONTROL_Huan3_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan3_Para_];
	CONTROL_Huan4_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan4_Para_];
	CONTROL_Huan5_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan5_Para_];
	CONTROL_Huan6_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan6_Para_];
	CONTROL_Huan7_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan7_Para_];
	CONTROL_Huan8_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan8_Para_];
	CONTROL_Huan9_Data	 = ALL_DATA[(_Com_Plan_-1)*40 + _INDEX_Huan9_Para_];
	
			
    while(1)
    {
//        {//彩虹灯
//			static uint16_t LED_Count = 0;
//            LED_Count = LED_Count==35 ? 0:LED_Count;
//            switch(LED_Count)
//            {
//                case  0: case  1: case  2: case  3: case  4:
//					LED_White_OFF(); 	LED_Orange_ON();	break;
//                case  5: case  6: case  7: case  8: case  9:
//					LED_Orange_OFF();  LED_Red_ON();    	break;
//                case 10: case 11: case 12: case 13: case 14:
//					LED_Red_OFF();     LED_Green_ON();  	break;
//                case 15: case 16: case 17: case 18: case 19:
//					LED_Green_OFF();   LED_Blue_ON();   	break;
//                case 20: case 21: case 22: case 23: case 24:
//					LED_Blue_OFF();    LED_Indigo_ON(); 	break;
//                case 25: case 26: case 27: case 28: case 29:
//					LED_Indigo_OFF();  LED_Purple_ON(); 	break;
//                case 30: case 31: case 32: case 33: case 34:
//					LED_Purple_OFF();  LED_White_ON();  	break;
//            }
//            LED_Count++;
//        }  

		/*******************保护相关*****************************/

		

		
		uint8_t Protect_Flag = 0;
		
		// 干簧管停车
		if( 0 == Read_Input_State(Reed2_Port, Reed2_Pin) )
		{
			Protect_Flag = 1;
			Stop_Flag = 1;
		}
		Reed_Stop();
#if 1
		if(1 == _Com_RunProtect_)
		{
			if( (Value_End_L>300)||(Value_End_L<-300)			// 转速保护
//				||Pitch<-40										// 角度保护
				||Value_Inductor_L<200||Value_Inductor_R<200	// 电感值保护
				
			  )
				Protect_Flag = 1;
		}
		/**************************距离/时间停车*****************************/
		if(	(_Com_RunTimeStop_!=0 && Run_Time*CON_PERIOD>_Com_RunTimeStop_*10)	||		// 100即1s   8.00
			(_Com_RunDisStop_!=0  && Run_Distance/DIS_RATIO>(float)_Com_RunDisStop_/100)		// 100即1米
		  )
		{
			Delay_ms(200);
			
			Protect_Flag = 1;
		}
#endif
		// 停车完，清相关标志位
		if( (Get_Key() || Protect_Flag) )
		{
			Huan_Flag = 0;
			Huan_No = 1;	// 准备进第一个环


			/****关电机****/
			Motor_L_EN(Disable);
			Motor_R_EN(Disable);
			
			Stop_Flag = 0;
			Bt_Send = 0;
			/**************/
			{	// 计时与测距相关
				Run_Time_Flag = 0;
				Run_Time = 0;
				Run_Distance = 0;
			}
			LED_White_OFF();   //关LED
			OLED_Display_On();//开OLED
			OLED_Init();
			return 0;
		}
 
    }
    
}

