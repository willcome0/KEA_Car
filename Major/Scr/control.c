#include "control.h"


int32_t Angle_PWM;
int32_t Speed_PWM;
int32_t Turn_PWM;
int32_t L_Final_PWM;
int32_t R_Final_PWM;
uint16_t Value_Inductor_L = 0;
uint16_t Value_Inductor_L_last1 = 0;
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
int Speed_Slide[3]={0};//�ٶ�ƽ������

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
uint8_t Huan_Flag = 0;	// ��¼����־λ
uint8_t Huan_No = 1;	// ��¼����Ҫ�����ǵڼ�����
uint8_t Run_Time_Flag = 0;
uint32_t Run_Time = 0;		//��λΪ�ж�����
uint32_t Run_Distance = 0;	//��λΪ���壨 ����/5760 = ���� ��

uint8_t Stop_Flag = 0; // ɲ����־

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

uint16_t Now_InHuan_Add = 0;
uint16_t Now_InHuan_Min = 0;
uint16_t Now_InHuan_Max = 0;

uint16_t Now_OutHuan_Add = 0;
uint16_t Now_OutHuan_Min = 0;
uint16_t Now_OutHuan_Max = 0;

uint32_t temp_time = 0;	// ������ʱ��ʱ ��
//uint32_t out_time = 0;	// ������ʱ��ʱ ��
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


/*����*/
uint16_t Ind_Queue[4][80];	// 4�����ͷ�����Ϊ80
float IndL_rake_Queue[40];
float IndR_rake_Queue[40];
uint8_t Bigger_Count = 0;	// ��¼�����������
uint8_t Bigger_Error_Count = 0;	// ��¼��������������������д���
uint8_t May_Max_Flag = 0;	// Ҳ�����ֵ�Ƿ�ֵ����һ�������ж�
uint32_t Max_Time = 0;		// ��ֵʱ��Time
uint32_t Max_Time_Last = 0;	// �ϴεķ�ֵ

int16_t Ave_End_Last1, Ave_End_Last2, Ave_End_Last3, Ave_End_Last4;
int16_t Ave_End;
uint8_t May_LR = 0;	// ����Ϊ��/�ң�0Ϊ�ޣ�1Ϊ��2Ϊ��
uint32_t May_LR_Dis = 0;	// ����Ϊ��/��ʱ��·��
uint8_t Sure_LR = 0;	// ȷ�����ң�0Ϊ�ޣ�1Ϊ��2Ϊ��

uint8_t Final_Mode = 0;	// ����ģʽ

uint8_t Protect_Flag = 0;


void Huan_Get_Data(uint8_t Huan_NoX_Data)
{
	if( 0 != Huan_NoX_Data)
	{
		// ����С
		switch( (Huan_NoX_Data%2==0 ? Huan_NoX_Data-1 : Huan_NoX_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
		{
			case 0:	Now_InHuan_Add = _Huan50_In_Add;	
					Now_InHuan_Min = _Huan50_In_Min;
					Now_InHuan_Max = _Huan50_In_Max;
					
					Now_OutHuan_Add = _Huan50_Out_Add;	
					Now_OutHuan_Min = _Huan50_Out_Min;
					Now_OutHuan_Max = _Huan50_Out_Max;
					break;
			case 1:	Now_InHuan_Add = _Huan60_In_Add;	
					Now_InHuan_Min = _Huan60_In_Min;
					Now_InHuan_Max = _Huan60_In_Max;
					
					Now_OutHuan_Add = _Huan60_Out_Add;	
					Now_OutHuan_Min = _Huan60_Out_Min;
					Now_OutHuan_Max = _Huan60_Out_Max;
					break;
			case 2:	Now_InHuan_Add = _Huan70_In_Add;	
					Now_InHuan_Min = _Huan70_In_Min;
					Now_InHuan_Max = _Huan70_In_Max;
					
					Now_OutHuan_Add = _Huan70_Out_Add;	
					Now_OutHuan_Min = _Huan70_Out_Min;
					Now_OutHuan_Max = _Huan70_Out_Max;
					break;
			case 3:	Now_InHuan_Add = _Huan80_In_Add;	
					Now_InHuan_Min = _Huan80_In_Min;
					Now_InHuan_Max = _Huan80_In_Max;
					
					Now_OutHuan_Add = _Huan80_Out_Add;	
					Now_OutHuan_Min = _Huan80_Out_Min;
					Now_OutHuan_Max = _Huan80_Out_Max;
					break;
			case 4:	Now_InHuan_Add = _Huan90_In_Add;	
					Now_InHuan_Min = _Huan90_In_Min;
					Now_InHuan_Max = _Huan90_In_Max;
					
					Now_OutHuan_Add = _Huan90_Out_Add;	
					Now_OutHuan_Min = _Huan90_Out_Min;
					Now_OutHuan_Max = _Huan90_Out_Max;
					break;
			case 5:	Now_InHuan_Add = _Huan100_In_Add;	
					Now_InHuan_Min = _Huan100_In_Min;
					Now_InHuan_Max = _Huan100_In_Max;
					
					Now_OutHuan_Add = _Huan100_Out_Add;	
					Now_OutHuan_Min = _Huan100_Out_Min;
					Now_OutHuan_Max = _Huan100_Out_Max;
					break;
		}
	}
}
// �жϻ�����̬�����򡢴�С��
void Judge_Huan_Form(void)
{
	switch( Huan_No )
	{
		case 1: Huan_Get_Data(CONTROL_Huan1_Data);	break;
		case 2: Huan_Get_Data(CONTROL_Huan2_Data);	break;
		case 3: Huan_Get_Data(CONTROL_Huan3_Data);	break;
		case 4: Huan_Get_Data(CONTROL_Huan4_Data);	break;
		case 5: Huan_Get_Data(CONTROL_Huan5_Data);	break;
		case 6: Huan_Get_Data(CONTROL_Huan6_Data);	break;
		case 7: Huan_Get_Data(CONTROL_Huan7_Data);	break;
		case 8: Huan_Get_Data(CONTROL_Huan8_Data);	break;
		case 9: Huan_Get_Data(CONTROL_Huan9_Data);	break;
	}
}

void PIT_CH0_IRQHandler(void)
{
								PIT_CLR_Flag(PIT_CH0);  //����жϱ�־λ 

									/*�ж�����--��ʼ*/

								MPU_Get_Accel(&Accel_X, &Accel_Y, &Accel_Z);
								MPU_Get_Gyro(&Gyro_X, &Gyro_Y, &Gyro_Z);

	
								Get_Posture(&Pitch, &Accel_X, &Accel_Z, &Gyro_Y);

#if 1



								Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? -ftm_count_get(ftm0) :  ftm_count_get(ftm0); // ��ȡ�������
								Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : -ftm_count_get(ftm1); // ��ȡ�ұ�����
								
//								Ave_End_Last4 = Ave_End_Last3;
//								Ave_End_Last3 = Ave_End_Last2;
//								Ave_End_Last2 = Ave_End_Last1;
//								Ave_End_Last1 = Ave_End;
								Ave_End = (Value_End_L + Value_End_R)/2;	
//								Ave_End = (Ave_End + Ave_End_Last1 + Ave_End_Last2 + Ave_End_Last3 + Ave_End_Last4)/5;	// ת���˲�
								
								if(Run_Time_Flag)	//��ʱ����
								{
									Run_Time++;							// ��ʱ	
									if(Run_Distance<10 && Ave_End<0)	//��ֹ����ʱ��ת����Run_Distance���ָ���
										Ave_End = 0;
									Run_Distance += Ave_End;			// ��·��
								}		
//	��ʱ��Ҫ�ٶȻ�						
    
				#if 0
				Error_End =   Ave_End - CONTROL_Target_Speed;   //���ٶ�ƫ��
								
                End_Integral = 0;	//��������
								
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
//                PreError[0]=Error_End;//���ٶ������ֶ���
//								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
								
				Speed_PWM = Error_End*CONTROL_SpeedPID_P + End_Integral*CONTROL_SpeedPID_I/100;    //�ٶȻ�
				#endif



								ftm_count_clean(ftm0);  //�������������
								ftm_count_clean(ftm1);
								

								Value_Inductor_L_last1 = Value_Inductor_L;
								Value_Inductor_R_last1 = Value_Inductor_R;
                                Value_Inductor_L = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_3));	// ��ȡ����
								Value_Inductor_R = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_4));	// ��ȡ�ҵ��
								Value_Inductor_BL = Get_Ind_V(AD_2);
								Value_Inductor_BR = Get_Ind_V(AD_1);


                                
                                
                                

					
//				LR_Error = (float)(Value_Inductor_R - Value_Inductor_L)/(float)(Value_Inductor_L + Value_Inductor_R)*50;


//									if( 
//										Value_End_L >= 25 	&&	// ����
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


	static float IndL_rake = 0;		// BL ���ֵб��
	static float IndL_rake_Last = 0;	
	static float IndL_rake_Last2 = 0;	
	static float IndL_rake_Last3 = 0;
	
	static float IndR_rake = 0;		// BR ���ֵб��
	static float IndR_rake_Last = 0;	
	static float IndR_rake_Last2 = 0;	
	static float IndR_rake_Last3 = 0;
		
	static uint8_t IndL_rake_Max = 0;	// ���ֵ
	static uint8_t IndL_rake_start = 0;
	static uint8_t IndL_rake_end = 0;
	static uint8_t IndL_rake_out = 0;	// ����ʱ�õ�

	static uint8_t IndR_rake_Max = 0;	// ���ֵ
	static uint8_t IndR_rake_start = 0;
	static uint8_t IndR_rake_end = 0;
	static uint8_t IndR_rake_out = 0;	// ����ʱ�õ�
	
	IndL_rake_Last3 = IndL_rake_Last2;	IndR_rake_Last3 = IndR_rake_Last2;
	IndL_rake_Last2 = IndL_rake_Last;	IndR_rake_Last2 = IndR_rake_Last;
	IndL_rake_Last = IndL_rake;			IndR_rake_Last = IndR_rake;
		
	IndL_rake = (float)((float)Value_Inductor_BL-Ind_Queue[2][(Run_Time-1)%80])*200/Ave_End;
	IndR_rake = (float)((float)Value_Inductor_BR-Ind_Queue[3][(Run_Time-1)%80])*200/Ave_End;
		
	IndL_rake = (IndL_rake+IndL_rake_Last+IndL_rake_Last2+IndL_rake_Last3)/4;	// ��б������ƽ��һЩ
	IndR_rake = (IndR_rake+IndR_rake_Last+IndR_rake_Last2+IndR_rake_Last3)/4;	// ��б������ƽ��һЩ
	
	IndL_rake_Queue[Run_Time%40] = IndL_rake;
	IndR_rake_Queue[Run_Time%40] = IndR_rake;
	{
		Ind_Queue[0][Run_Time%80] = Value_Inductor_L;
		Ind_Queue[1][Run_Time%80] = Value_Inductor_R;
		Ind_Queue[2][Run_Time%80] = Value_Inductor_BL;
		Ind_Queue[3][Run_Time%80] = Value_Inductor_BR;
		
		uint8_t index_last1 = (Run_Time-1)%80;
		uint8_t index_last2 = (Run_Time-2)%80;	// ����Ϊ���ֵ
		uint8_t index_last3 = (Run_Time-3)%80;
		
		if( Value_Inductor_BL - Value_Inductor_BR > 450 && 
			Value_Inductor_L > 600 && Value_Inductor_R > 600 )		// ����������
		{
			May_LR = 1;
			May_LR_Dis = Run_Distance;
		}
		else if( Value_Inductor_BR - Value_Inductor_BL > 450 && 
			Value_Inductor_L > 600 && Value_Inductor_R > 600 )	// ����������
		{
			May_LR = 2;
			May_LR_Dis = Run_Distance;
		}
		
//		if( Ind_Queue[2][index_last2] > Ind_Queue[2][index_last3] )
//		{
//			Bigger_Count++;
//			if( Bigger_Count > 15 && Ind_Queue[2][index_last2] > 900 &&	// ����������
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
//					Ind_rake_start = Run_Time;		// ���
//					Ind_rake_end = 0;
//				}
//				if( Ind_rake_Last > 0 && Ind_rake_start != 0 ) 	// ���������
//				{
//					if( Ind_rake > Ind_rake_Queue[Ind_rake_Max%40] )
//						Ind_rake_Max = Run_Time;	// ��ߵ�
//				}
//			}

//			if( Ind_rake <= 0 && 
//				(Ind_rake_Last >= 0 || Ind_rake_Last2 >= 0 || Ind_rake_Last3 >= 0) && 
//				Value_Inductor_BL > 850 && 
//				Ind_rake_start != 0)		// ��������ߵ�
//			{
//				Ind_rake_start = 0;
//				Ind_rake_Max = 0;
//				Ind_rake_end = Run_Time;	// �յ�
//				Beep_Time(100);
//			}

//		}

	}
		Variable[0] = Value_Inductor_L;  //�������
		Variable[1] = Value_Inductor_R;  //�ұ�����
//		Variable[2] = IndL_rake_Queue[Run_Time%40];  //������	// б��
		Variable[2] = Value_Inductor_BL;
		Variable[3] = Value_Inductor_BR;  //����
	
	
	if( CONTROL_InHuan90_Min < Run_Time && Run_Time < CONTROL_InHuan90_Max && _Com_Go_Mode_ == 1)
	{
//		int16_t count_t = (CONTROL_InHuan90_Max - CONTROL_InHuan90_Min)/2;
//		if( CONTROL_InHuan90_Min <= Run_Time && Run_Time <= CONTROL_InHuan90_Min + count_t )
//			Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + CONTROL_Target_Angle - (CONTROL_Target_Angle - CONTROL_Huan90_Add)*(Run_Time-CONTROL_InHuan90_Min)/count_t ) + (float)CONTROL_AnglePID_D/100*(Gyro_Y);   //ֱ����
//		else if( CONTROL_InHuan90_Min + count_t < Run_Time && Run_Time < CONTROL_InHuan90_Max )
//			Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + CONTROL_Huan90_Add + (CONTROL_Target_Angle - CONTROL_Huan90_Add)*(Run_Time-CONTROL_InHuan90_Min-count_t)/count_t ) + (float)CONTROL_AnglePID_D/100*(Gyro_Y);
		Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + CONTROL_Huan90_Add) + (float)CONTROL_AnglePID_D/100*(Gyro_Y);
	}
	else
		Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*(Gyro_Y - (Gyro_Z>0?Gyro_Z:-Gyro_Z)*0.005 );   //ֱ����
//	Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*Gyro_Y;   //ֱ����
	
	Eroor_Ind_Old = Error_Ind;
	Error_Ind = Value_Inductor_R - Value_Inductor_L;


									
									/*��д��*/
									switch( Huan_Flag )
									{
										case 0:		// δ�뻷��־�����ж���һ�����Ĵ�С������
										{
//											if(
//												Run_Time > 0 		&& 
//												Run_Distance > 0	&& 
//												temp_time == 0		&&
//												temp_dis == 0		&& 
////												Pitch >= 18 		&&
//												Value_End_L >= 20 	&&	// ����
//												Value_End_R >= 20 	&&
//												Value_Inductor_L > _Com_Huan_Value_	&& 
//												Value_Inductor_R > _Com_Huan_Value_  )
											
//											if( 
//												Value_End_L >= 20 	&&	// ����
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
			Variable[1] = 10;
			if( IndL_rake >= 0 && 
				May_LR == 1 && 
				Sure_LR == 0 && 
				Run_Distance - May_LR_Dis > 1000 &&		// �˴���С��Ӧ�ò�һ��	 ��ԭ�ȵ�50��ʱ�ǣ�1200��2600��
				Run_Distance - May_LR_Dis < 6000 )		// ���￼�ǵĴ�
			{
				May_LR = 0;
				May_LR_Dis = 0;
				if( (IndL_rake_Last <= 0 || IndL_rake_Last2 <= 0 || IndL_rake_Last3 <= 0) && 
					Value_Inductor_BL <= 400 && temp_time == 0 )	// ����㴥��
				{
					Judge_Huan_Form();
					
					IndL_rake_start = Run_Time;		// ���	// ��Ӧ���ֵ�������ֵ
					IndL_rake_end = 0;
					
					Sure_LR = 1;
					
					Beep_Time(100);
					temp_time = Run_Time-1;
					temp_dis = Run_Distance;
					Huan_Flag ++;
					LED_Red_ON();
					
					Variable[0] = 10;
				}
//				if( Ind_rake_Last > 0 && Ind_rake_start != 0 ) 	// ���������
//				{
//					if( Ind_rake > Ind_rake_Queue[Ind_rake_Max%40] )
//						Ind_rake_Max = Run_Time;	// ��ߵ�	// ��Ӧ���ֵ����б�����ĵط�
//				}
			}

//			if( Ind_rake <= 0 && 
//				(Ind_rake_Last >= 0 || Ind_rake_Last2 >= 0 || Ind_rake_Last3 >= 0) && 
//				Value_Inductor_BL > 850 && 
//				Ind_rake_start != 0)		// ��������ߵ�
//			{
//				Ind_rake_start = 0;
//				Ind_rake_Max = 0;
//				Ind_rake_end = Run_Time;	// �յ�	// ��Ӧ���ֵ�������ֵ
//				Beep_Time(100);

//				temp_time++;
//				temp_dis = Run_Distance;
//				Huan_Flag ++;
//				LED_Blue_ON();
//			}

			if( IndR_rake >= 0 &&
				May_LR == 2 && 
				Sure_LR == 0 && 
				Run_Distance - May_LR_Dis > 1000 &&		// �˴���С��Ӧ�ò�һ��	 ��ԭ�ȵ�50��ʱ�ǣ�1200��2600��
				Run_Distance - May_LR_Dis < 6000 )
			{
				May_LR = 0;
				May_LR_Dis = 0;
				if( (IndR_rake_Last <= 0 || IndR_rake_Last2 <= 0 || IndR_rake_Last3 <= 0) && 
					Value_Inductor_BR <= 400 && temp_time == 0 )	
				{
					Judge_Huan_Form();
					
					IndR_rake_start = Run_Time;		// ���
					IndR_rake_end = 0;
					
					Sure_LR = 2;
					
					Beep_Time(100);
					temp_time = Run_Time-1;
					temp_dis = Run_Distance;
					Huan_Flag ++;
					LED_Green_ON();
					
					Variable[0] = 10;
				}
//				if( Ind_rake_Last > 0 && Ind_rake_start != 0 ) 	// ���������
//				{
//					if( Ind_rake > Ind_rake_Queue[Ind_rake_Max%40] )
//						Ind_rake_Max = Run_Time;	// ��ߵ�
//				}
			}
		}
												// �����
//												LED_Red_ON();

											break;
										}
										case 1:		// ��⵽����־
										{
											
//											if(
//												temp_time > 0		&& // �������ܹ�
//												temp_dis > 0		&& // �������ܹ�
//												(Run_Distance - temp_dis) > CONTROL_InHuan50_Min &&	// ʶ�𵽻����뻷������Сֵ
//												(Run_Distance - temp_dis) < CONTROL_InHuan50_Max &&	// ʶ�𵽻����뻷�������ֵ
//												Value_Inductor_L > 800 &&
//												Value_Inductor_R > 800
//												
//											)
//											{
//												
//												
//												if(1 == _Com_Huan_LR_)		// ���뻷
//												{
////													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
//													LR_Error = -CONTROL_Huan50_Add;
//												}
//												else if(0 == _Com_Huan_LR_)	// ���뻷
//												{
////													Value_Inductor_R = Value_Inductor_R*CONTROL_Huan_Add/10;
//													LR_Error = CONTROL_Huan50_Add;
//												}
//												
//										
//												// ���̵ƣ���������
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
											if( temp_time != 0 && dis_ < Now_InHuan_Max)		// ��С����ĵ�
											{
//												Turn_PWM = -( 0.00191*time_*time_*time_-0.1395*time_*time_+2.449*time_+Ave_End/2)*CONTROL_TurnPID_D;	// 35
												if(time_>10)
													time_ = 10;
//												Error_Ind = Value_Inductor_R - Value_Inductor_L*( ((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)*((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)/CONTROL_Huan50_Add )*time_/10;
												if( 1 == Sure_LR )		// ���뻷
												{
													Error_Ind = (float)Value_Inductor_R/( (((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)*((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)/Now_InHuan_Add )*time_/10 ) - Value_Inductor_L;
												}
												else if( 2 == Sure_LR )	// ���뻷
												{
													Error_Ind = Value_Inductor_R - (float)Value_Inductor_L/( (((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)*((float)Value_Inductor_L/100+(float)Value_Inductor_R/100)/Now_InHuan_Add )*time_/10 ) ;
												}
//												Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + Error_D*CONTROL_TurnPID_D;	
												Beep_Time(5);
											}
											else
											{
												Huan_Flag ++;
												temp_time = Run_Time;
												temp_dis = Run_Distance;
												
												LED_Red_OFF();
												LED_Green_OFF();
											}
											break;
										}
										
										case 2:		// �뻷��δ������־	// ����һ��BR��ֵ
										{
//										if(
////												Run_Time - temp_time > 20			&&	// ���뻷һ��ʱ��

////												Run_Distance - temp_dis > CONTROL_InHuan50_Max	&&	// ʶ�𵽻����뻷�������ֵ
//											Value_Inductor_L < _Com_Huan_Value_ 		&& 
//											Value_Inductor_R < _Com_Huan_Value_   )
//										{
//											
//											
//											// ��5���ڣ���ƫ�ƴ����
//											static uint8_t turn_back_time = 0;
//											turn_back_time++;
//											if( turn_back_time < 6 )
//											{
//												if( 1 == _Com_Huan_LR_ )		// ���뻷
//												{
//													LR_Error = LR_Error*turn_back_time/5 - CONTROL_Huan50_Add*(5-turn_back_time)/5;
//												}
//												else if( 0 == _Com_Huan_LR_ )	// ���뻷
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


//											if( 
////												Run_Distance - temp_dis > 8000 && 
//												(Sure_LR == 2 &&
//												IndL_rake > 110 && 		// ���뻷�ж�
//												IndL_rake_Last > 110 &&
//												IndL_rake_Last2 > 110 &&
//												IndL_rake_Last3 > 110 &&
//												Value_Inductor_BL > 650) || 
//												(Sure_LR == 1 &&
//												IndR_rake > 110 &&  		// ���뻷�ж�
//												IndR_rake_Last > 110 &&
//												IndR_rake_Last2 > 110 &&
//												IndR_rake_Last3 > 110 &&
//												Value_Inductor_BR > 650)
//											)
											if(	
											   (Sure_LR == 1 &&
												IndR_rake <= 0 && 		// ���뻷
												IndR_rake_Last > 0 && 
												IndR_rake_Last2 > 0 &&
												IndR_rake_Last3 > 0 &&
												Value_Inductor_L > _Com_Huan_Value_-100 && 		// ���������жϣ�Խ��Խ�����״�����
												Value_Inductor_BL > _Com_Huan_Value_-100  && 
												Value_Inductor_BR > _Com_Huan_Value_-100  ) || 
												(Sure_LR == 2 &&		
												IndL_rake <= 0 && 		// ���뻷
												IndL_rake_Last > 0 && 
												IndL_rake_Last2 > 0 &&
												IndL_rake_Last3 > 0 &&
												Value_Inductor_R > _Com_Huan_Value_-100  && 
												Value_Inductor_BL > _Com_Huan_Value_-100  && 
												Value_Inductor_BR > _Com_Huan_Value_-100  )
											)
											{
												Huan_Flag ++;
												temp_time = Run_Time-1;
												temp_dis = Run_Distance;
												
												LED_Red_OFF();
												LED_Green_OFF();
												
												LED_Blue_ON();
												
												Variable[2] = 200;
												
//												Stop_Flag = 1;
											}
											break;
										}
										
										case 3:		// ������־
										{
//											if(
////												Run_Time - temp_time > 50			&&	// ���뻷һ��ʱ��
////												Run_Distance - temp_dis > 4000		&&	// ���뻷һ������
//												Value_Inductor_L > _Com_Huan_Value_	 &&
//											Value_Inductor_BL > _Com_Huan_Value_
//											)
//											{
//												temp_time = 0;
//												temp_dis = Run_Distance;
//												
//												
////												// ��֮ǰ���󣬻�����෴����һ��ƫ��
////												if( 1 == _Com_Huan_LR_ )		// ���뻷
////												{
//////													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
////													LR_Error = _Com_HuanOut_L_Add_;
////												}
////												else if( 0 == _Com_Huan_LR_ )	// ���뻷
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
											if( Run_Distance - temp_dis > Now_OutHuan_Min && 
												Run_Distance - temp_dis < Now_OutHuan_Max )
											{
												Variable[2] = 500;
												if( 1 == Sure_LR )
													Error_Ind = IndR_rake*10/Now_OutHuan_Add;
//													Error_Ind = -Error_Ind;
												else if( 2 == Sure_LR )
													Error_Ind = -IndL_rake*10/Now_OutHuan_Add;
//													 Error_Ind = -Error_Ind;

											}
											else if( Run_Distance - temp_dis > Now_OutHuan_Max)
											{
												Huan_Flag++;
												temp_time = Run_Time;
												temp_dis = Run_Distance;
												LED_Blue_OFF();
												LED_Red_ON();
											}
											break;
										}
										case 4:		// ��ȫ���������־λ
										{
											if( Run_Distance - temp_dis > 3000 )
											{
												Huan_Flag = 0;
												temp_time = 0;
												temp_dis = 0;
												
												Sure_LR = 0;
												
												Huan_No ++;

												if( Huan_No > _Com_Huan_Num_ )
													Huan_No = 1;
												LED_Red_OFF();
												
												Beep_Time(200);
											}
											break;
										}
									}
									/*��д�� ����*/
									
//          Turn_PWM = Error_Ind*Plan1.Turn.P/10 + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
//								Turn_PWM = LR_Error*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
//								Turn_PWM = LR_Error*CONTROL_TurnPID_P + GYRO.X/10*CONTROL_TurnPID_D;
//								Turn_PWM = (LR_Error*0.4+LR1_Error*0.3+LR2_Error*0.2+LR3_Error*0.1)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
									

	LR3_Error = LR2_Error;
	LR2_Error = LR1_Error;
	LR1_Error = LR_Error;
//	Eroor_Ind_Old = Error_Ind;
	LR_Error =(5.043e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(-2.85e-06)*(float)Error_Ind*Error_Ind + 0.01201*(float)Error_Ind  -0.006396;  //�Ƕ�18.8
	float Error_D = Error_Ind - Eroor_Ind_Old;
	Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + Error_D*CONTROL_TurnPID_D;
									

								L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
								R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;

	
//	if( _Com_Go_Mode_ == 2 && 	// ��������
//		Final_Mode == 0 &&
//		Run_Time != 0 &&
//		Value_Inductor_L < 10 && Value_Inductor_R < 10 && 
//		Value_Inductor_BL < 10 && Value_Inductor_BR < 10 )	
//	{
//		Final_Mode = 1;
//		LED_Green_ON();
//		L_Final_PWM = 0;
//		R_Final_PWM = 0;
//	}
//	else if( _Com_Go_Mode_ == 2 && 
//			 Final_Mode == 1 && 
//			 (Value_Inductor_L > 400 || Value_Inductor_R > 400 || Value_Inductor_BL > 400 || Value_Inductor_BR > 400) )
//	{
//		Final_Mode = 2;
//	}		
	
	// ����ģʽ
     switch(Final_Mode)
	 {
		 static uint16_t time_1 = 0;
		 case 0:
			if( _Com_Go_Mode_ == 2 && 	// �����ȴ� �����ź�
				Run_Time != 0 &&
				Value_Inductor_L < 10 && Value_Inductor_R < 10 && 
				Value_Inductor_BL < 10 && Value_Inductor_BR < 10 )
			{
				Final_Mode++;
				LED_Green_ON();

			}
			break;
		 case 1:
			 if(_Com_Go_Mode_ == 2 &&	// �ȴ������ź�
				Value_Inductor_L < 50 && Value_Inductor_R < 50 && Value_Inductor_BL < 50 && Value_Inductor_BR< 50 )
			 {
				L_Final_PWM = 0;
				R_Final_PWM = 0; 
			 }
			 else if( Value_Inductor_L > 500 || Value_Inductor_R > 500 || Value_Inductor_BL > 500 || Value_Inductor_BR > 500 )
			 {
				 LED_Green_OFF();
				 time_1 = Run_Time;
				 Final_Mode++;
			 }
			 break;
		 case 2:						// ���������У��ȴ�ͣ���ź�
			if(	Value_Inductor_L == 0 && Value_Inductor_R == 0 && Value_Inductor_BL <= 5 && Value_Inductor_BR <= 5 && time_1 != 0 && Run_Time - time_1 > 500 && 
				Ind_Queue[0][(Run_Time-1)%80] == 0 && Ind_Queue[0][(Run_Time-2)%80] == 0 && Ind_Queue[0][(Run_Time-3)%80] == 0 && 
				Ind_Queue[1][(Run_Time-1)%80] == 0 && Ind_Queue[1][(Run_Time-2)%80] == 0 && Ind_Queue[1][(Run_Time-3)%80] == 0)
			{
				Final_Mode++;
				LED_Red_ON();
				Beep_Time(300);
				Stop_Flag = 1;
				time_1 = Run_Time;
//						Motor_L_EN(Disable);
//						Motor_R_EN(Disable);
//				Protect_Flag = 1;
			}
			break;
		 case 3:
			if( Run_Time - time_1 > 200 )
			{
				Motor_L_EN(Disable);
				Motor_R_EN(Disable);
				Final_Mode = 0;
				LED_Red_OFF();
			}
			
			break;
//		 case 3:
//			break;
	 }
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
								
							if(Stop_Flag == 1)		// ɲ��
							{
								L_Final_PWM = -(Value_End_L+Value_End_R)*60;
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

//		if(Ind_rake_start != 0)
//			Variable[4] = Ind_rake_Queue[Ind_rake_Max%40];	//�Ƕ�	// ���ֵ
//		else
//			Variable[4] = LR_Error;

		Variable[3] = Error_Ind;
//		Variable[4] = IndL_rake;	// BLб��			-400,400
//		Variable[5] = IndR_rake;	// BRб��			-400,400
//		Variable[4] = Error_Ind;	// ƫ��				-2000,2000
		Variable[4] = Pitch;	// ���ƫ�L-R��		-10,40
		Variable[5] = Huan_No;		// �ٶ�				-30,120
		Send_Begin();
		Send_Variable();
	}
	
    /*�ж�����--����*/
//    Enable_PIT_CH0();
}



uint8_t Just_Do_It(void)
{
    OLED_Clear();

	/********�����********/
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
    OLED_Display_Off();	//��OLED
	Huan_Flag = 0;
	Huan_No = 1;	// ׼������һ����
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
		

	Protect_Flag = 0;
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
			if( (
				(Ave_End>250) || 
				(Value_End_L<-80) || (Value_End_R<-80) ||
				(Value_Inductor_L==0 && Value_Inductor_R==0 &&
				Value_Inductor_BL<20 && Value_Inductor_BR<20 &&
				Ind_Queue[0][(Run_Time-1)%80] == 0 && Ind_Queue[0][(Run_Time-2)%80] == 0 && Ind_Queue[0][(Run_Time-3)%80] == 0 && 
				Ind_Queue[1][(Run_Time-1)%80] == 0 && Ind_Queue[1][(Run_Time-2)%80] == 0 && Ind_Queue[1][(Run_Time-3)%80] == 0)
				) &&
				Run_Time > 400 &&
				_Com_Go_Mode_ != 2
			  )
				Protect_Flag = 1;
		}
		/**************************����/ʱ��ͣ��*****************************/
		if(	(_Com_RunTimeStop_!=0 && Run_Time*CON_PERIOD>_Com_RunTimeStop_*10)	||		// 100��1s   8.00
			(_Com_RunDisStop_!=0  && Run_Distance/DIS_RATIO>(float)_Com_RunDisStop_/100)		// 100��1��
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
						Huan_No = 1;	// ׼������һ����
			

						/****�ص��****/
						Run_Time_Flag = 0;
						Final_Mode = 0;
						
						Bt_Send = 0;
						/**************/
                        LED_White_OFF();   //��LED
                        OLED_Display_On();//��OLED
						OLED_Init();
						
						Delay_ms(300);
						Motor_L_EN(Disable);
						Motor_R_EN(Disable);
						Stop_Flag = 0;
                        return 0;
        }
		

    }
    
}

