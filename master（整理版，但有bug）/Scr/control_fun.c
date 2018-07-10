#include "control_fun.h"

volatile uint8_t Huan_No = 1;	// 记录现在要过的是第几个环

/*****从flash中读取到的各种环的转弯参数*****/
volatile uint16_t CONTROL_Huan50_Add   = 0;
volatile uint16_t CONTROL_InHuan50_Min = 0;
volatile uint16_t CONTROL_InHuan50_Max = 0;

volatile uint16_t CONTROL_Huan60_Add   = 0;
volatile uint16_t CONTROL_InHuan60_Min = 0;
volatile uint16_t CONTROL_InHuan60_Max = 0;

volatile uint16_t CONTROL_Huan70_Add   = 0;
volatile uint16_t CONTROL_InHuan70_Min = 0;
volatile uint16_t CONTROL_InHuan70_Max = 0;

volatile uint16_t CONTROL_Huan80_Add   = 0;
volatile uint16_t CONTROL_InHuan80_Min = 0;
volatile uint16_t CONTROL_InHuan80_Max = 0;

volatile uint16_t CONTROL_Huan90_Add   = 0;
volatile uint16_t CONTROL_InHuan90_Min = 0;
volatile uint16_t CONTROL_InHuan90_Max = 0;

volatile uint16_t CONTROL_Huan100_Add   = 0;
volatile uint16_t CONTROL_InHuan100_Min = 0;
volatile uint16_t CONTROL_InHuan100_Max = 0;

volatile uint16_t CONTROL_Huan1_Data	= 0;
volatile uint16_t CONTROL_Huan2_Data	= 0;
volatile uint16_t CONTROL_Huan3_Data	= 0;
volatile uint16_t CONTROL_Huan4_Data	= 0;
volatile uint16_t CONTROL_Huan5_Data	= 0;
volatile uint16_t CONTROL_Huan6_Data	= 0;
volatile uint16_t CONTROL_Huan7_Data	= 0;
volatile uint16_t CONTROL_Huan8_Data	= 0;
volatile uint16_t CONTROL_Huan9_Data	= 0;
/*********************************************/

/*****判断环的形态后当前要入环的参数*****/
volatile uint16_t Now_Huan_Add = 0;
volatile uint16_t Now_InHuan_Min = 0;
volatile uint16_t Now_InHuan_Max = 0;
/****************************************/

// 判断环的形态（方向、大小）
void Judge_Huan_Form(void)
{
	switch( Huan_No )
	{
		case 1:	
				if( 0 != CONTROL_Huan1_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan1_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan1_Data%2==0 ? CONTROL_Huan1_Data-1 : CONTROL_Huan1_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 2:	
				if( 0 != CONTROL_Huan2_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan2_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan2_Data%2==0 ? CONTROL_Huan2_Data-1 : CONTROL_Huan2_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 3:	
				if( 0 != CONTROL_Huan3_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan3_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan3_Data%2==0 ? CONTROL_Huan3_Data-1 : CONTROL_Huan3_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 4:	
				if( 0 != CONTROL_Huan4_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan4_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan4_Data%2==0 ? CONTROL_Huan4_Data-1 : CONTROL_Huan4_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 5:	
				if( 0 != CONTROL_Huan5_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan5_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan5_Data%2==0 ? CONTROL_Huan5_Data-1 : CONTROL_Huan5_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 6:	
				if( 0 != CONTROL_Huan6_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan6_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan6_Data%2==0 ? CONTROL_Huan6_Data-1 : CONTROL_Huan6_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 7:	
				if( 0 != CONTROL_Huan7_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan7_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan7_Data%2==0 ? CONTROL_Huan7_Data-1 : CONTROL_Huan7_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 8:	
				if( 0 != CONTROL_Huan8_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan8_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan8_Data%2==0 ? CONTROL_Huan8_Data-1 : CONTROL_Huan8_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		case 9:	
				if( 0 != CONTROL_Huan9_Data)
				{
					// 环左右
					_Com_Huan_LR_ = CONTROL_Huan9_Data % 2;
					
					// 环大小
					switch( (CONTROL_Huan9_Data%2==0 ? CONTROL_Huan9_Data-1 : CONTROL_Huan9_Data)/2 )	// 偶数时除2 大1(不明白去看ui.c里的Plan_Judge_State)
					{
						case 0:	Now_Huan_Add =  CONTROL_Huan50_Add;	
								Now_InHuan_Min = CONTROL_InHuan50_Min;
								Now_InHuan_Max = CONTROL_InHuan50_Max;
								break;
						case 1:	Now_Huan_Add =  CONTROL_Huan60_Add;	
								Now_InHuan_Min = CONTROL_InHuan60_Min;
								Now_InHuan_Max = CONTROL_InHuan60_Max;
								break;
						case 2:	Now_Huan_Add =  CONTROL_Huan70_Add;	
								Now_InHuan_Min = CONTROL_InHuan70_Min;
								Now_InHuan_Max = CONTROL_InHuan70_Max;
								break;
						case 3:	Now_Huan_Add =  CONTROL_Huan80_Add;	
								Now_InHuan_Min = CONTROL_InHuan80_Min;
								Now_InHuan_Max = CONTROL_InHuan80_Max;
								break;
						case 4:	Now_Huan_Add =  CONTROL_Huan90_Add;	
								Now_InHuan_Min = CONTROL_InHuan90_Min;
								Now_InHuan_Max = CONTROL_InHuan90_Max;
								break;
						case 5:	Now_Huan_Add =  CONTROL_Huan100_Add;	
								Now_InHuan_Min = CONTROL_InHuan100_Min;
								Now_InHuan_Max = CONTROL_InHuan100_Max;
								break;
					}
				}
				break;
		default:	_Com_Huan_LR_ = 2;	// 不左拐也不右
	}
}


uint8_t Bt_Send = 0;
void Send_Upper(void)
{
	if( Bt_Send && _Com_BT_ )
	{
		Variable[0] = Run_Time_Flag;  //左编码器
		Variable[1] = Value_Inductor_R;  //右编码器
		Variable[2] = Value_Inductor_BL;  //俯仰角
		Variable[3] = Value_Inductor_BR;  //左电磁
		Send_Begin();
		Send_Variable();
	}
}

volatile int16_t Value_End_L = 0;
volatile int16_t Value_End_R = 0;
volatile int16_t Ave_End = 0;

void Get_End(void)
{
	Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? -ftm_count_get(ftm0) :  ftm_count_get(ftm0); // 获取左编码器
	Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : -ftm_count_get(ftm1); // 获取右编码器
	
	Ave_End = (Value_End_L + Value_End_R)/2;	//计算平均转速
	
	
	ftm_count_clean(ftm0);  //清除编码器计数
	ftm_count_clean(ftm1);
}

void Get_Pose(void)
{
	MPU_Get_Accel(&Accel_X, &Accel_Y, &Accel_Z);
	MPU_Get_Gyro(&Gyro_X, &Gyro_Y, &Gyro_Z);

	Get_Posture(&Pitch, &Accel_X, &Accel_Z, &Gyro_Y);
}

volatile uint16_t Value_Inductor_L = 0;
volatile uint16_t Value_Inductor_R = 0;
volatile uint16_t Value_Inductor_BL = 0;
volatile uint16_t Value_Inductor_BR = 0;
volatile int16_t Error_Ind = 0;
volatile int16_t Eroor_Ind_Old = 0;
void Get_Ind(void)
{
	Value_Inductor_L = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_3));	// 获取左电感
	Value_Inductor_R = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_4));	// 获取右电感
	Value_Inductor_BL = Get_Ind_V(AD_2);
	Value_Inductor_BR = Get_Ind_V(AD_1);
	
	Eroor_Ind_Old = Error_Ind;
	Error_Ind = Value_Inductor_R - Value_Inductor_L;
}

uint16_t BB_Times = 0;
void Beep_Task(void)
{
	if(BB_Times >= CON_PERIOD)
	{
		BB_Times -= CON_PERIOD;
		Beep_ON();
	}
	else
	{
		Beep_OFF();
	}
}

volatile int32_t Angle_PWM   = 0;
volatile int32_t Speed_PWM   = 0;
volatile int32_t Turn_PWM    = 0;
volatile int32_t L_Final_PWM = 0;
volatile int32_t R_Final_PWM = 0;
volatile uint8_t Stop_Flag   = 0;	// 刹车标志

void Go_or_Stop(void)
{
	if(Stop_Flag == 1)		// 刹车
	{
		if( Value_End_L >= 20 && Value_End_R >= 20 )
		{
			Motor_L_Go_V(1000);
			Motor_R_Go_V(1000);
//			Motor_L_EN(Disable);
//			Motor_R_EN(Disable);
		}
	}
	else					// 正常赋电机PWM
	{
		L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
		R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;
		
		if(L_Final_PWM<0)
		{
				L_Final_PWM = -L_Final_PWM;
				if(L_Final_PWM>=3150)
						L_Final_PWM = 3150;

				Motor_L_Go_V(L_Final_PWM);
				L_Final_PWM = 0;
		}
		else
		{
				if(L_Final_PWM>=3150)
						L_Final_PWM = 3150;

				Motor_L_Back_V(L_Final_PWM);
				L_Final_PWM = 0;
		}
		
		
		if(R_Final_PWM<0)
		{
				R_Final_PWM = -R_Final_PWM;
				if(R_Final_PWM>=3150)
						R_Final_PWM = 3150;

				Motor_R_Go_V(R_Final_PWM);
				R_Final_PWM = 0;
		}
		else
		{
				if(R_Final_PWM>=3150)
						R_Final_PWM = 3150;
				
				Motor_R_Back_V(R_Final_PWM);
				R_Final_PWM = 0;
				
		}
	}
}

void Reed_Stop(void)
{
	if( 0 == Read_Input_State(Reed2_Port, Reed2_Pin) )
	{
		Stop_Flag = 1;
		Beep_Time(200);
	}
}


volatile uint8_t Huan_Flag = 0;	// 记录环标志位

void In_Huan(void)
{
	static volatile uint32_t temp_time = 0;	// 用于临时计时 进
	static volatile uint32_t temp_dis = 0;
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
			if( 
				Value_End_L >= 20 	&&	// 车速
				Value_End_R >= 20 	&&
				Value_Inductor_L > _Com_Huan_Value_ &&
				Value_Inductor_R > _Com_Huan_Value_ &&
				( (Value_Inductor_BL > _Com_Huan_Value_ && Value_Inductor_BR < 100 ) ||
				  (Value_Inductor_BR > 1000 && Value_Inductor_BL < 100 )  )

		)
			{
				temp_time = Run_Time;
				temp_dis = Run_Distance;
				Huan_Flag ++;
				
				/*判定第几个环的左右和大小*/
				Judge_Huan_Form();
				
				// 开红灯
				LED_Red_ON();
			}
			break;
		}
		case 1:		// 检测到环标志
		{
			if(
				temp_time > 0		&& // 开电有跑过
				temp_dis > 0		&& // 开电有跑过
				(Run_Distance - temp_dis) > Now_InHuan_Min &&	// 识别到环后入环距离最小值
				(Run_Distance - temp_dis) < Now_InHuan_Max &&	// 识别到环后入环距离最大值
				Value_Inductor_L + Value_Inductor_R > (_Com_Huan_Value_ * 2 - 300 )  )
			{
				
				
				if(1 == _Com_Huan_LR_)		// 左入环
				{
//													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
					LR_Error = -Now_Huan_Add;
				}
				else if(0 == _Com_Huan_LR_)	// 右入环
				{
//													Value_Inductor_R = Value_Inductor_R*CONTROL_Huan_Add/10;
					LR_Error = Now_Huan_Add;
				}
				
		
				// 开绿灯，蜂鸣器响
				Beep_Time(5);
				LED_Red_OFF();
				LED_Green_ON();
			}
			else if ((Run_Distance - temp_dis) > _Com_InHuan_Max_)
			{
				LED_Green_OFF();
				LED_Blue_ON();
				
				Huan_Flag ++;
			}
			break;
		}
		
		case 2:		// 入环后，未出环标志
		{
			if(
				Run_Time - temp_time > 20			&&	// 已入环一定时间

				Run_Distance - temp_dis > Now_InHuan_Max	&&	// 识别到环后入环距离最大值
				Value_Inductor_L < _Com_Huan_Value_ 		&& 
				Value_Inductor_R < _Com_Huan_Value_   )
			{
				
				
				// 分5周期，把偏移打回来
				static uint8_t turn_back_time = 0;
				turn_back_time++;
				if( turn_back_time < 6 )
				{
					if( 1 == _Com_Huan_LR_ )		// 左入环
					{
						LR_Error = LR_Error*turn_back_time/5 - Now_Huan_Add*(5-turn_back_time)/5;
					}
					else if( 0 == _Com_Huan_LR_ )	// 右入环
					{
						LR_Error = LR_Error*turn_back_time/5 + Now_Huan_Add*(5-turn_back_time)/5;
					}
				}
				
				
				
			}
			if( Run_Distance - temp_dis > Now_InHuan_Max + 1000 )
				Huan_Flag ++;
			break;
		}
		
		case 3:		// 出环标志
		{
			if( 
//												Run_Time - temp_time > 50			&&	// 已入环一定时间
//												Run_Distance - temp_dis > 4000		&&	// 已入环一定距离
				Value_Inductor_L > _Com_Huan_Value_	&& 
				Value_Inductor_R > _Com_Huan_Value_  
			)
			{
				temp_time = 0;
				temp_dis = Run_Distance;
				
				
				// 按之前现象，还需给相反方向一个偏移
				if( 1 == _Com_Huan_LR_ )		// 左入环
				{
//													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
					LR_Error = _Com_HuanOut_L_Add_;
				}
				else if( 0 == _Com_Huan_LR_ )	// 右入环
				{
//													Value_Inductor_R = Value_Inductor_R*CONTROL_Huan_Add/10;
					LR_Error = -_Com_HuanOut_R_Add_;
				}
				
				
				Beep_Time(5);
				LED_Blue_OFF();

				
			}
			else if( temp_time == 0 && Run_Distance - temp_dis > _Com_HuanOut_AddDis_ )
			{
				Huan_Flag ++;
				LED_Purple_ON();
			}
			break;
		}
		case 4:		// 完全出环，清标志位
		{
			if( Run_Distance - temp_dis > 5000 )
			{
				Huan_Flag = 0;
				temp_time = 0;
				temp_dis = 0;
				
				Huan_No ++;
				
				LED_Purple_OFF();
				Beep_Time(200);
			}
			break;
		}
	}
}

volatile uint16_t Run_Time_Flag = 0;
volatile uint32_t Run_Time = 0;		//单位为中断周期
volatile uint32_t Run_Distance = 0;	//单位为脉冲（ 脉冲/5760 = 距离 ）
