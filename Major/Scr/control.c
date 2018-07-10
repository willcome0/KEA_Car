#include "control.h"


int32_t Angle_PWM;
int32_t Speed_PWM;
int32_t Turn_PWM;
int32_t L_Final_PWM;
int32_t R_Final_PWM;
uint16_t Value_Inductor_L = 0;
uint16_t Value_Inductor_R = 0;
uint16_t Value_Inductor_R_last1 = 0;

uint16_t Value_Inductor_BL = 0;
uint16_t Value_Inductor_BR = 0;
uint16_t Value_Ind_L_Old = 0;
uint16_t Value_Ind_R_Old = 0;
int16_t Error_Ind = 0;
int16_t Eroor_Ind_Old = 0;

int16_t Value_End_L = 0;
int16_t Value_End_R = 0;

int16_t Error_End = 0;
int16_t PreError[20];

int AlllastError=0;
int Speed_Slide[3]={0};//速度平滑参数

int SpeedOUT;
int32_t End_Integral = 0;   

float LR_Error = 0;
float LR1_Error = 0;
float LR2_Error = 0;
float LR3_Error = 0;

uint8_t Do_it = 1;

//uint8_t Huan_Count_Flag = 0;
//uint16_t Huan_Count = 0;
float Yaw_Huan = 0.00001;
#define OUT 0
#define IN 1
uint8_t Huan_Flag = 0;	// 记录环标志位
uint8_t Huan_No = 1;	// 记录现在要过的是第几个环
uint8_t Run_Time_Flag = 0;
uint32_t Run_Time = 0;		//单位为中断周期
uint32_t Run_Distance = 0;	//单位为脉冲（ 脉冲/5760 = 距离 ）

uint8_t Stop_Flag = 0; // 刹车标志

uint16_t CONTROL_Target_Angle = 0;
uint16_t CONTROL_Target_Speed = 0;
uint16_t CONTROL_AnglePID_P	 = 0;
uint16_t CONTROL_AnglePID_D   = 0;
uint16_t CONTROL_SpeedPID_P   = 0;
uint16_t CONTROL_SpeedPID_I   = 0;
uint16_t CONTROL_TurnPID_P    = 0;
uint16_t CONTROL_TurnPID_D    = 0;

uint16_t CONTROL_Huan50_Add   = 0;
uint16_t CONTROL_InHuan50_Min = 0;
uint16_t CONTROL_InHuan50_Max = 0;

uint16_t CONTROL_Huan60_Add   = 0;
uint16_t CONTROL_InHuan60_Min = 0;
uint16_t CONTROL_InHuan60_Max = 0;

uint16_t CONTROL_Huan70_Add   = 0;
uint16_t CONTROL_InHuan70_Min = 0;
uint16_t CONTROL_InHuan70_Max = 0;

uint16_t CONTROL_Huan80_Add   = 0;
uint16_t CONTROL_InHuan80_Min = 0;
uint16_t CONTROL_InHuan80_Max = 0;

uint16_t CONTROL_Huan90_Add   = 0;
uint16_t CONTROL_InHuan90_Min = 0;
uint16_t CONTROL_InHuan90_Max = 0;

uint16_t CONTROL_Huan100_Add   = 0;
uint16_t CONTROL_InHuan100_Min = 0;
uint16_t CONTROL_InHuan100_Max = 0;

uint16_t CONTROL_Huan1_Data	  = 0;
uint16_t CONTROL_Huan2_Data	  = 0;
uint16_t CONTROL_Huan3_Data	  = 0;
uint16_t CONTROL_Huan4_Data	  = 0;
uint16_t CONTROL_Huan5_Data	  = 0;
uint16_t CONTROL_Huan6_Data	  = 0;
uint16_t CONTROL_Huan7_Data	  = 0;
uint16_t CONTROL_Huan8_Data	  = 0;
uint16_t CONTROL_Huan9_Data	  = 0;

uint16_t Now_Huan_Add = 0;
uint16_t Now_InHuan_Min = 0;
uint16_t Now_InHuan_Max = 0;

uint32_t temp_time = 0;	// 用于临时计时 进
//uint32_t out_time = 0;	// 用于临时计时 出
uint32_t temp_dis = 0;

int32_t Int_A_X = 0;
int32_t Int_A_Y = 0;
int32_t Int_A_Z = 0;
int32_t Int_G_X = 0;
int32_t Int_G_Y = 0;
int32_t Int_G_Z = 0;
#define AVE 5
int16_t Pre_A_X[AVE], Pre_A_Y[AVE], Pre_A_Z[AVE];
int16_t Pre_G_X[AVE], Pre_G_Y[AVE], Pre_G_Z[AVE];


uint16_t LED_Count = 0;

uint8_t Bt_Send = 0;


/*队列*/
uint16_t Ind_Queue[4][80];	// 4个电磁头，深度为80
float IndL_rake_Queue[40];
float IndR_rake_Queue[40];
uint8_t Bigger_Count = 0;	// 记录连续增大次数
uint8_t Bigger_Error_Count = 0;	// 记录连续增大过程中允许误判次数
uint8_t May_Max_Flag = 0;	// 也许这个值是峰值，进一步进行判断
uint32_t Max_Time = 0;		// 峰值时的Time
uint32_t Max_Time_Last = 0;	// 上次的峰值

int16_t Ave_End_Last1, Ave_End_Last2, Ave_End_Last3, Ave_End_Last4;
int16_t Ave_End;
uint8_t May_LR = 0;	// 可能为左/右，0为无，1为左，2为右
uint32_t May_LR_Dis = 0;	// 可能为左/右时的路程
uint8_t Sure_LR = 0;	// 确定左右，0为无，1为左，2为右
void PIT_CH0_IRQHandler(void)
{
								PIT_CLR_Flag(PIT_CH0);  //清除中断标志位 

									/*中断内容--开始*/

								MPU_Get_Accel(&Accel_X, &Accel_Y, &Accel_Z);
								MPU_Get_Gyro(&Gyro_X, &Gyro_Y, &Gyro_Z);

	
								Get_Posture(&Pitch, &Accel_X, &Accel_Z, &Gyro_Y);

#if 1



								Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? -ftm_count_get(ftm0) :  ftm_count_get(ftm0); // 获取左编码器
								Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : -ftm_count_get(ftm1); // 获取右编码器
								 
//								Ave_End_Last4 = Ave_End_Last3;
//								Ave_End_Last3 = Ave_End_Last2;
//								Ave_End_Last2 = Ave_End_Last1;
//								Ave_End_Last1 = Ave_End;
								Ave_End = (Value_End_L + Value_End_R)/2;	
//								Ave_End = (Ave_End + Ave_End_Last1 + Ave_End_Last2 + Ave_End_Last3 + Ave_End_Last4)/5;	// 转速滤波
								
								if(Run_Time_Flag)	//计时与测距
								{
									Run_Time++;							// 计时	
									if(Run_Distance<10 && Ave_End<0)	//防止起跑时倒转导致Run_Distance出现负数
										Ave_End = 0;
									Run_Distance += Ave_End;			// 记路程
								}		
//	暂时不要速度环						
    
				#if 0
				Error_End =   Ave_End - CONTROL_Target_Speed;   //求速度偏差
								
                End_Integral = 0;	//积分清零
								
                for(uint8_t i=0; i<19; i++)
                {
                    PreError[i] = PreError[i+1]; 
                    End_Integral += PreError[i];
                }
                PreError[19] = Error_End;
                End_Integral += PreError[19];

//                PreError[4]=PreError[3];
//                PreError[3]=PreError[2];
//                PreError[2]=PreError[1];
//                PreError[1]=PreError[0];
//                PreError[0]=Error_End;//入速度误差积分队列
//								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
								
				Speed_PWM = Error_End*CONTROL_SpeedPID_P + End_Integral*CONTROL_SpeedPID_I/100;    //速度环
				#endif



								ftm_count_clean(ftm0);  //清除编码器计数
								ftm_count_clean(ftm1);
								

								Value_Inductor_R_last1 = Value_Inductor_R;
                                Value_Inductor_L = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_3));	// 获取左电感
								Value_Inductor_R = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_4));	// 获取右电感
								Value_Inductor_BL = Get_Ind_V(AD_2);
								Value_Inductor_BR = Get_Ind_V(AD_1);


                                
                                
                                

					
//				LR_Error = (float)(Value_Inductor_R - Value_Inductor_L)/(float)(Value_Inductor_L + Value_Inductor_R)*50;


//									if( 
//										Value_End_L >= 25 	&&	// 车速
//										Value_End_R >= 25 	&&
//										Value_Inductor_L >900 &&
//										Value_Inductor_R > 900 &&
//										( (Value_Inductor_BL > 1000 && Value_Inductor_BR < 100 ) ||
//										  (Value_Inductor_BR > 1000 && Value_Inductor_BL < 100 )  )
// 
//										)
//									{
//										Beep_Time(100);
//									}


	static float IndL_rake = 0;		// BL 电磁值斜率
	static float IndL_rake_Last = 0;	
	static float IndL_rake_Last2 = 0;	
	static float IndL_rake_Last3 = 0;
	
	static float IndR_rake = 0;		// BR 电磁值斜率
	static float IndR_rake_Last = 0;	
	static float IndR_rake_Last2 = 0;	
	static float IndR_rake_Last3 = 0;
		
	static uint8_t IndL_rake_Max = 0;	// 最大值
	static uint8_t IndL_rake_start = 0;
	static uint8_t IndL_rake_end = 0;
	static uint8_t IndL_rake_out = 0;	// 出环时用的

	static uint8_t IndR_rake_Max = 0;	// 最大值
	static uint8_t IndR_rake_start = 0;
	static uint8_t IndR_rake_end = 0;
	static uint8_t IndR_rake_out = 0;	// 出环时用的
	
	IndL_rake_Last3 = IndL_rake_Last2;	IndR_rake_Last3 = IndR_rake_Last2;
	IndL_rake_Last2 = IndL_rake_Last;	IndR_rake_Last2 = IndR_rake_Last;
	IndL_rake_Last = IndL_rake;			IndR_rake_Last = IndR_rake;
		
	IndL_rake = (float)((float)Value_Inductor_BL-Ind_Queue[2][(Run_Time-1)%80])*200/Ave_End;
	IndR_rake = (float)((float)Value_Inductor_BR-Ind_Queue[3][(Run_Time-1)%80])*200/Ave_End;
		
	IndL_rake = (IndL_rake+IndL_rake_Last+IndL_rake_Last2+IndL_rake_Last3)/4;	// 将斜率曲线平滑一些
	IndR_rake = (IndR_rake+IndR_rake_Last+IndR_rake_Last2+IndR_rake_Last3)/4;	// 将斜率曲线平滑一些
	
	IndL_rake_Queue[Run_Time%40] = IndL_rake;
	IndR_rake_Queue[Run_Time%40] = IndR_rake;
	{
		Ind_Queue[0][Run_Time%80] = Value_Inductor_L;
		Ind_Queue[1][Run_Time%80] = Value_Inductor_R;
		Ind_Queue[2][Run_Time%80] = Value_Inductor_BL;
		Ind_Queue[3][Run_Time%80] = Value_Inductor_BR;
		
		uint8_t index_last1 = (Run_Time-1)%80;
		uint8_t index_last2 = (Run_Time-2)%80;	// 可能为最大值
		uint8_t index_last3 = (Run_Time-3)%80;
		
		if( Value_Inductor_BL - Value_Inductor_BR > 450 )		// 环可能在左
		{
			May_LR = 1;
			May_LR_Dis = Run_Distance;
		}
		else if( Value_Inductor_BR - Value_Inductor_BL > 450 )	// 环可能在右
		{
			May_LR = 2;
			May_LR_Dis = Run_Distance;
		}
		
//		if( Ind_Queue[2][index_last2] > Ind_Queue[2][index_last3] )
//		{
//			Bigger_Count++;
//			if( Bigger_Count > 15 && Ind_Queue[2][index_last2] > 900 &&	// 连续增次数
//				Value_Inductor_BL < Ind_Queue[2][index_last1] &&
//				Value_Inductor_BL < Ind_Queue[2][index_last2] )
//			{
//				Max_Time_Last = Max_Time;
//				Max_Time = Run_Time-2;
//			}
//		}
//		else
//		{
//			Bigger_Error_Count++;
//			if( Bigger_Error_Count>3 && Bigger_Count<=15 )
//			{
//				Bigger_Count = 0;
//			}
//		}
//		if( Max_Time - Max_Time_Last < 70  && 
//			Max_Time - Max_Time_Last > 30  && 
//			Ind_Queue[0][Max_Time%80] > 800 && 
//			Ind_Queue[1][Max_Time%80] > 800 && 
//			Ind_Queue[1][(Max_Time-20)%80] < 500 && 
//			Ind_Queue[3][Max_Time%80] < 800 )
//		{
//			Beep_Time(100);
//		}
		
		
//		if( )
		
//		else
//		{
//			Bigger_Error_Count++;
//			if( Bigger_Error_Count > 2 )
//			{
//				Bigger_Count = 0;
//				Bigger_Error_Count = 0;
//			}
//		}
		
		
//		if( Value_Inductor_L > 800 && Value_Inductor_R > 800 )
//		{
//			if( Ind_rake >= 0 )
//			{
//				if( (Ind_rake_Last <= 0 || Ind_rake_Last2 <= 0 || Ind_rake_Last3 <= 0) && 
//					Value_Inductor_BL <= 400 )	
//				{
//					Ind_rake_start = Run_Time;		// 起点
//					Ind_rake_end = 0;
//				}
//				if( Ind_rake_Last > 0 && Ind_rake_start != 0 ) 	// 且已有起点
//				{
//					if( Ind_rake > Ind_rake_Queue[Ind_rake_Max%40] )
//						Ind_rake_Max = Run_Time;	// 最高点
//				}
//			}

//			if( Ind_rake <= 0 && 
//				(Ind_rake_Last >= 0 || Ind_rake_Last2 >= 0 || Ind_rake_Last3 >= 0) && 
//				Value_Inductor_BL > 850 && 
//				Ind_rake_start != 0)		// 且已有最高点
//			{
//				Ind_rake_start = 0;
//				Ind_rake_Max = 0;
//				Ind_rake_end = Run_Time;	// 终点
//				Beep_Time(100);
//			}

//		}

	}
	Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*(Gyro_Y - (Gyro_Z>0?Gyro_Z:-Gyro_Z)*0.25 );   //直立环
//	Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*Gyro_Y;   //直立环
	
	Eroor_Ind_Old = Error_Ind;
	Error_Ind = Value_Inductor_R - Value_Inductor_L;
				
				
									
									/*重写环*/
									switch( Huan_Flag )
									{
										case 0:		// 未入环标志。并判断下一个环的大小、方向
										{
//											if(
//												Run_Time > 0 		&& 
//												Run_Distance > 0	&& 
//												temp_time == 0		&&
//												temp_dis == 0		&& 
////												Pitch >= 18 		&&
//												Value_End_L >= 20 	&&	// 车速
//												Value_End_R >= 20 	&&
//												Value_Inductor_L > _Com_Huan_Value_	&& 
//												Value_Inductor_R > _Com_Huan_Value_  )
											
//											if( 
//												Value_End_L >= 20 	&&	// 车速
//												Value_End_R >= 20 	&&
//												Value_Inductor_L > _Com_Huan_Value_ &&
//												Value_Inductor_R > _Com_Huan_Value_ &&
//												( (Value_Inductor_BL > _Com_Huan_Value_ && Value_Inductor_BR < 100 ) ||
//												  (Value_Inductor_BR > 1000 && Value_Inductor_BL < 100 )  )
// 
//										)
//											{
//												temp_time = Run_Time;
//												temp_dis = Run_Distance;
//												Huan_Flag ++;
//											}	
											
		if( Value_Inductor_L > _Com_Huan_Value_ && Value_Inductor_R > _Com_Huan_Value_ )
		{
			if( IndL_rake >= 0 && 
				May_LR == 1 && 
				Sure_LR == 0 && 
				Run_Distance - May_LR_Dis > 1200 &&
				Run_Distance - May_LR_Dis < 2600 )
			{
				May_LR = 0;
				May_LR_Dis = 0;
				if( (IndL_rake_Last <= 0 || IndL_rake_Last2 <= 0 || IndL_rake_Last3 <= 0) && 
					Value_Inductor_BL <= 400 && temp_time == 0 )	
				{
					IndL_rake_start = Run_Time;		// 起点	// 对应电磁值就是最低值
					IndL_rake_end = 0;
					
					Sure_LR = 1;
					
					Beep_Time(100);
					temp_time = Run_Time-1;
					temp_dis = Run_Distance;
					Huan_Flag ++;
					LED_Red_ON();
				}
//				if( Ind_rake_Last > 0 && Ind_rake_start != 0 ) 	// 且已有起点
//				{
//					if( Ind_rake > Ind_rake_Queue[Ind_rake_Max%40] )
//						Ind_rake_Max = Run_Time;	// 最高点	// 对应电磁值就是斜率最大的地方
//				}
			}

//			if( Ind_rake <= 0 && 
//				(Ind_rake_Last >= 0 || Ind_rake_Last2 >= 0 || Ind_rake_Last3 >= 0) && 
//				Value_Inductor_BL > 850 && 
//				Ind_rake_start != 0)		// 且已有最高点
//			{
//				Ind_rake_start = 0;
//				Ind_rake_Max = 0;
//				Ind_rake_end = Run_Time;	// 终点	// 对应电磁值就是最大值
//				Beep_Time(100);

//				temp_time++;
//				temp_dis = Run_Distance;
//				Huan_Flag ++;
//				LED_Blue_ON();
//			}

			if( IndR_rake >= 0 &&
				May_LR == 2 && 
				Sure_LR == 0 && 
				Run_Distance - May_LR_Dis > 1200 &&
				Run_Distance - May_LR_Dis < 2600 )
			{
				May_LR = 0;
				May_LR_Dis = 0;
				if( (IndR_rake_Last <= 0 || IndR_rake_Last2 <= 0 || IndR_rake_Last3 <= 0) && 
					Value_Inductor_BR <= 400 && temp_time == 0 )	
				{
					IndR_rake_start = Run_Time;		// 起点
					IndR_rake_end = 0;
					
					Sure_LR = 2;
					
					Beep_Time(100);
					temp_time = Run_Time-1;
					temp_dis = Run_Distance;
					Huan_Flag ++;
					LED_Green_ON();
				}
//				if( Ind_rake_Last > 0 && Ind_rake_start != 0 ) 	// 且已有起点
//				{
//					if( Ind_rake > Ind_rake_Queue[Ind_rake_Max%40] )
//						Ind_rake_Max = Run_Time;	// 最高点
//				}
			}
		}
												// 开红灯
//												LED_Red_ON();

											break;
										}
										case 1:		// 检测到环标志
										{
											
//											if(
//												temp_time > 0		&& // 开电有跑过
//												temp_dis > 0		&& // 开电有跑过
//												(Run_Distance - temp_dis) > CONTROL_InHuan50_Min &&	// 识别到环后入环距离最小值
//												(Run_Distance - temp_dis) < CONTROL_InHuan50_Max &&	// 识别到环后入环距离最大值
//												Value_Inductor_L > 800 &&
//												Value_Inductor_R > 800
//												
//											)
//											{
//												
//												
//												if(1 == _Com_Huan_LR_)		// 左入环
//												{
////													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
//													LR_Error = -CONTROL_Huan50_Add;
//												}
//												else if(0 == _Com_Huan_LR_)	// 右入环
//												{
////													Value_Inductor_R = Value_Inductor_R*CONTROL_Huan_Add/10;
//													LR_Error = CONTROL_Huan50_Add;
//												}
//												
//										
//												// 开绿灯，蜂鸣器响
//												Beep_Time(5);
//												LED_Red_OFF();
//												LED_Green_ON();
//											}
//											else if ( Value_Inductor_L < 800 && Value_Inductor_R < 800 )
//											{
//												LED_Green_OFF();
//												LED_Blue_ON();
//												
//												Huan_Flag ++;
//											}

//											LR_Error = -LR_REEOR_Array[temp_time];
											
											uint8_t time_ = Run_Time-temp_time;
											uint16_t dis_ = Run_Distance - temp_dis;
											if( temp_time != 0 && dis_ < CONTROL_InHuan50_Max)
											{
//												Turn_PWM = -( 0.00191*time_*time_*time_-0.1395*time_*time_+2.449*time_+Ave_End/2)*CONTROL_TurnPID_D;	// 35
												if(time_>10)
													time_ = 10;
//												Error_Ind = Value_Inductor_R - Value_Inductor_L*( ((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)*((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)/CONTROL_Huan50_Add )*time_/10;
												if( 1 == Sure_LR )		// 左入环
												{
													Error_Ind = (float)Value_Inductor_R/( (((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)*((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)/CONTROL_Huan50_Add )*time_/10 ) - Value_Inductor_L;
												}
												else if( 2 == Sure_LR )	// 右入环
												{
													Error_Ind = Value_Inductor_R - (float)Value_Inductor_L/( (((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)*((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)/CONTROL_Huan50_Add )*time_/10 ) ;
												}
//												Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + Error_D*CONTROL_TurnPID_D;	
												Beep_Time(5);
											}
											else
											{
												Huan_Flag ++;
												temp_time = Run_Time;
												temp_dis = Run_Distance;
											}
											break;
										}
										
										case 2:		// 入环后，未出环标志	// 检测第一个BR峰值
										{
//										if(
////												Run_Time - temp_time > 20			&&	// 已入环一定时间

////												Run_Distance - temp_dis > CONTROL_InHuan50_Max	&&	// 识别到环后入环距离最大值
//											Value_Inductor_L < _Com_Huan_Value_ 		&& 
//											Value_Inductor_R < _Com_Huan_Value_   )
//										{
//											
//											
//											// 分5周期，把偏移打回来
//											static uint8_t turn_back_time = 0;
//											turn_back_time++;
//											if( turn_back_time < 6 )
//											{
//												if( 1 == _Com_Huan_LR_ )		// 左入环
//												{
//													LR_Error = LR_Error*turn_back_time/5 - CONTROL_Huan50_Add*(5-turn_back_time)/5;
//												}
//												else if( 0 == _Com_Huan_LR_ )	// 右入环
//												{
//													LR_Error = LR_Error*turn_back_time/5 + CONTROL_Huan50_Add*(5-turn_back_time)/5;
//												}
//											}
//											
//										}


//											if( Run_Distance - temp_dis > 10000 )
//											{
//												Huan_Flag ++;
//												temp_time = Run_Time;
//												temp_dis = Run_Distance;
//												LED_Blue_OFF();
//												
//											}
											if( 
//												Run_Distance - temp_dis > 8000 && 
												(Sure_LR == 2 &&
												IndL_rake > 110 && 		// 右入环判断
												IndL_rake_Last > 110 &&
												IndL_rake_Last2 > 110 &&
												IndL_rake_Last3 > 110 &&
												Value_Inductor_BL > 650) || 
												(Sure_LR == 1 &&
												IndR_rake > 110 &&  		// 左入环判断
												IndR_rake_Last > 110 &&
												IndR_rake_Last2 > 110 &&
												IndR_rake_Last3 > 110 &&
												Value_Inductor_BR > 650)
											)
											{
												Huan_Flag ++;
												temp_time = Run_Time-1;
												temp_dis = Run_Distance;
												LED_Blue_OFF();
												LED_Green_OFF();
												LED_Purple_ON();
											}
											break;
										}
										
										case 3:		// 出环标志
										{
//											if( 
////												Run_Time - temp_time > 50			&&	// 已入环一定时间
////												Run_Distance - temp_dis > 4000		&&	// 已入环一定距离
//												Value_Inductor_L > _Com_Huan_Value_	 &&
//											Value_Inductor_BL > _Com_Huan_Value_
//											)
//											{
//												temp_time = 0;
//												temp_dis = Run_Distance;
//												
//												
////												// 按之前现象，还需给相反方向一个偏移
////												if( 1 == _Com_Huan_LR_ )		// 左入环
////												{
//////													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
////													LR_Error = _Com_HuanOut_L_Add_;
////												}
////												else if( 0 == _Com_Huan_LR_ )	// 右入环
////												{
//////													Value_Inductor_R = Value_Inductor_R*CONTROL_Huan_Add/10;
////													LR_Error = -_Com_HuanOut_R_Add_;
////												}
//												float x = 0;
//												if(Error_Ind - Eroor_Ind_Old>50)
//													x = 50;
//												else if(Error_Ind - Eroor_Ind_Old<-50)
//													x = -50;
//												else 
//													x = Error_Ind - Eroor_Ind_Old;
//												Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
//												
//												Beep_Time(5);
//												LED_Blue_OFF();

//												
//											}
//											else if( temp_time == 0 && Run_Distance - temp_dis > _Com_HuanOut_AddDis_ )
//											{
//												Huan_Flag ++;
//												LED_Purple_ON();
//											}


//											if( Value_Inductor_BR > 900 &&
//												Value_Inductor_BL < 700 &&
//												Value_Inductor_R  < 600 &&
//												temp_time == 0)
//											{
//												temp_time ++;
//												LED_Purple_ON();
//												Beep_Time(100);
//												LED_Blue_OFF();
//											}
//											if( temp_time != 0 && temp_time < 60 )
//												Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*(CONTROL_TurnPID_D-8);
////												Turn_PWM = -( 0.00191*temp_time*temp_time*temp_time-0.1395*temp_time*temp_time+2.449*temp_time+19.377)*CONTROL_TurnPID_D;
//											else
//											{
//												LED_Purple_OFF();
//												temp_time = 0;
//												Huan_Flag ++;
//											}
//											temp_time++;
//											Huan_Flag ++;




//if( Value_Inductor_BR > 900 &&
//	Value_Inductor_BL < 700 &&
//	Value_Inductor_R  < 600 &&
//	temp_time == 0)
//{
//	temp_time = Run_Time;
//	temp_dis = Run_Distance;
//}
//	if( temp_time != 0 )
//	{
//		Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*(CONTROL_TurnPID_D)/2;
//		Beep_Time(5);
//	}

////Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch-5 + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*(Gyro_Y);
//if( Run_Distance - temp_dis > 4000 )
//{
//	Huan_Flag ++;
//	temp_time = Run_Time;
//	temp_dis = Run_Distance;
//}
//											uint8_t time_ = Run_Time-temp_time;
//											uint16_t dis_ = Run_Distance - temp_dis;
//											if( temp_time != 0 && dis_ < CONTROL_InHuan50_Min )
//											{
////												Turn_PWM = -( 0.00191*time_*time_*time_-0.1395*time_*time_+2.449*time_+Ave_End/2-14)*CONTROL_TurnPID_D;	// 16
//												if(time_>10)
//													time_ = 10;
//												Error_Ind = (float)Value_Inductor_R/( (float)(CONTROL_Huan60_Add/((float)Value_Inductor_L/100)*((float)Value_Inductor_L/100) )*time_/10 ) - Value_Inductor_L;
//												Beep_Time(5);
//											}
//											else 
//												if( Value_Inductor_L > _Com_Huan_Value_ && Value_Inductor_R > _Com_Huan_Value_)
//											{
//												Huan_Flag ++;
//												temp_time = Run_Time;
//												temp_dis = Run_Distance;
//												LED_Purple_OFF();
//												LED_Red_ON();
//											}
//											if((float)((float)Value_Inductor_R-Ind_Queue[1][(Run_Time-1)%80])*200/Ave_End)
//											{

//												int16_t xielv = Value_Inductor_R - Value_Inductor_R_last1;

//													Value_Inductor_R = Value_Inductor_R*2 - Value_Inductor_R_last1;

//												Error_Ind = Value_Inductor_R - xielv/3*2 - Value_Inductor_L;
//												Stop_Flag = 1;
//											}

//											if( Error_Ind < -200 )
//												Error_Ind = Error_Ind - (Error_Ind - Eroor_Ind_Old)/2;
											if( Run_Distance - temp_dis > CONTROL_InHuan60_Min && 
												Run_Distance - temp_dis < CONTROL_InHuan60_Max )
											{
												if( 1 == Sure_LR )
													Error_Ind = _Com_HuanOut_L_Add_;
												else if( 2 == Sure_LR )
													Error_Ind = -_Com_HuanOut_R_Add_ ;
											}
											else if( Run_Distance - temp_dis > CONTROL_InHuan60_Max)
											{
												Huan_Flag++;
												temp_time = Run_Time;
												temp_dis = Run_Distance;
											}
											break;
										}
										case 4:		// 完全出环，清标志位
										{
											if( Run_Distance - temp_dis > 8000 )
											{
												Huan_Flag = 0;
												temp_time = 0;
												temp_dis = 0;
												
												Sure_LR = 0;
												
												Huan_No ++;
												LED_Blue_OFF();
												LED_Red_OFF();
												
												Beep_Time(200);
											}
											break;
										}
									}
									/*重写环 结束*/
									
//          Turn_PWM = Error_Ind*Plan1.Turn.P/10 + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
//								Turn_PWM = LR_Error*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
//								Turn_PWM = LR_Error*CONTROL_TurnPID_P + GYRO.X/10*CONTROL_TurnPID_D;
//								Turn_PWM = (LR_Error*0.4+LR1_Error*0.3+LR2_Error*0.2+LR3_Error*0.1)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
									

	LR3_Error = LR2_Error;
	LR2_Error = LR1_Error;
	LR1_Error = LR_Error;
//	Eroor_Ind_Old = Error_Ind;
	LR_Error =(5.043e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(-2.85e-06)*(float)Error_Ind*Error_Ind + 0.01201*(float)Error_Ind  -0.006396;  //角度18.8
	float Error_D = Error_Ind - Eroor_Ind_Old;
	Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + Error_D*CONTROL_TurnPID_D;
									
								L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
								R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;

								
									
									
     
//											if( Huan_Flag == 3 )
//											{
//												L_Final_PWM = -(Value_End_L+Value_End_R)*100;
//												R_Final_PWM = L_Final_PWM;
//											}
							if( 0 == Read_Input_State(Reed2_Port, Reed2_Pin) )
							{
								Stop_Flag = 1;
								Beep_Time(300);
							}		
								
							if(Stop_Flag == 1)		// 刹车
							{
								L_Final_PWM = -(Value_End_L+Value_End_R)*100;
								R_Final_PWM = L_Final_PWM;
							}

								if(L_Final_PWM<0)
								{
										L_Final_PWM = -L_Final_PWM;
										if(L_Final_PWM>=3150)
												L_Final_PWM = 3150;
						//        Motor_Set_Go_Speed(L_Final_PWM, R_Final_PWM);
										Motor_L_Go_V(L_Final_PWM);
										L_Final_PWM = 0;
								}
								else
								{
										if(L_Final_PWM>=3150)
												L_Final_PWM = 3150;
						//        Motor_Set_Back_Speed(L_Final_PWM, R_Final_PWM);
										Motor_L_Back_V(L_Final_PWM);
										L_Final_PWM = 0;
								}
								
								
								if(R_Final_PWM<0)
								{
										R_Final_PWM = -R_Final_PWM;
										if(R_Final_PWM>=3150)
												R_Final_PWM = 3150;
						//        Motor_Set_Go_Speed(L_Final_PWM, R_Final_PWM);
										Motor_R_Go_V(R_Final_PWM);
										R_Final_PWM = 0;
								}
								else
								{
										if(R_Final_PWM>=3150)
												R_Final_PWM = 3150;
						//        Motor_Set_Back_Speed(L_Final_PWM, R_Final_PWM);
										Motor_R_Back_V(R_Final_PWM);
										R_Final_PWM = 0;
										
								}

								
#endif

								if(BB_Times >= CON_PERIOD)
								{
									BB_Times -= CON_PERIOD;
									Beep_ON();
								}
								else
								{
									Beep_OFF();
								}

		
	
								
	

								
	if( Bt_Send && _Com_BT_ && Stop_Flag == 0 )
	{
		Variable[0] = Value_Inductor_L;  //左编码器
		Variable[1] = Value_Inductor_R;  //右编码器
//		Variable[2] = IndL_rake_Queue[Run_Time%40];  //俯仰角	// 斜率
		Variable[2] = Value_Inductor_BL;
		Variable[3] = Value_Inductor_BR;  //左电磁
//		if(Ind_rake_start != 0)
//			Variable[4] = Ind_rake_Queue[Ind_rake_Max%40];	//角度	// 最大值
//		else
//			Variable[4] = LR_Error;
//		Variable[4] = (float)((float)Value_Inductor_L-Ind_Queue[0][(Run_Time-1)%80])*200/Ave_End;	// 转速
//		Variable[5] = (float)((float)Value_Inductor_R-Ind_Queue[1][(Run_Time-1)%80])*200/Ave_End;
		Variable[4] = IndL_rake;
		Variable[5] = IndR_rake;
		Send_Begin();
		Send_Variable();
	}
	
    /*中断内容--结束*/
//    Enable_PIT_CH0();
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


	Run_Time_Flag = 1;
	Run_Time = 0;
	Run_Distance = 0;
    /**********************/
	
    uint8_t LED_Count = 0;
    OLED_Display_Off();	//关OLED
	Huan_Flag = 0;
	Huan_No = 1;	// 准备进第一个环
	Bt_Send = 1;
	
	{
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
	}
		

	
    while(1)
    {

		uint8_t Protect_Flag = 0;
		if( 0 == Read_Input_State(Reed2_Port, Reed2_Pin) )
		{
			Stop_Flag = 1;
		}
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
			Stop_Flag = 1;
			Run_Time_Flag = 0;
			Delay_ms(200);
			
			Protect_Flag = 1;
		}
#endif
        switch(Get_Key() || Protect_Flag)
        {
            case Press_NULL:  break;
            
            default:     
						Huan_Flag = 0;
						Huan_No = 1;	// 准备进第一个环
			

						/****关电机****/
						Run_Time_Flag = 0;

						
						Bt_Send = 0;
						/**************/
                        LED_White_OFF();   //关LED
                        OLED_Display_On();//开OLED
						OLED_Init();
						
						Delay_ms(300);
						Motor_L_EN(Disable);
						Motor_R_EN(Disable);
						Stop_Flag = 0;
                        return 0;
        }
		

    }
    
}

