#include "control.h"


int32_t Angle_PWM;
int32_t Speed_PWM;
int32_t Turn_PWM;
int32_t L_Final_PWM;
int32_t R_Final_PWM;
uint16_t Value_Inductor_L = 0;
uint16_t Value_Inductor_R = 0;

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

uint16_t Now_Huan_Add = 0;
uint16_t Now_InHuan_Min = 0;
uint16_t Now_InHuan_Max = 0;

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

void PIT_CH0_IRQHandler(void)
{
								PIT_CLR_Flag(PIT_CH0);  //����жϱ�־λ 
							//    Disable_PIT_CH0();
									/*�ж�����--��ʼ*/

//								MPU6050_GetData(&GYRO, &ACC);   //��ȡԭʼ����
//								Data_Filter();     //ԭʼ�����˲�
//								Get_Attitude();    //��ȡ��̬
							
//								if(_Com_Debug_)
//									(float)CONTROL_Target_Angle = (float)CONTROL_Target_Angle + (Pitch + (float)CONTROL_Target_Angle)/4;
								MPU_Get_Accel(&Accel_X, &Accel_Y, &Accel_Z);
								MPU_Get_Gyro(&Gyro_X, &Gyro_Y, &Gyro_Z);
	
//								Gyro_Y += (Gyro_Z>0? -Gyro_Z : Gyro_Z)*0.2 ;


	
								Get_Posture(&Pitch, &Accel_X, &Accel_Z, &Gyro_Y);
//								Get_Posture(&Pitch, &Accel_Y, &Accel_Z, &Gyro_X);
//								Get_Posture(&Roll,	&Accel_Y, &Accel_Z, &Gyro_X);
//								Get_Posture(&Yaw,	&Accel_X, &Accel_Y, &Gyro_Z);
	
//	Int_A_X = 0;
//	Int_A_Y = 0;
//	Int_A_Z = 0;
//	Int_G_X = 0;
//	Int_G_Y = 0;
//	Int_G_Z = 0;	
//	for(uint8_t i=0; i<AVE-1; i++)
//	{
//		Pre_A_X[i] = Pre_A_X[i+1];
//		Int_A_X += Pre_A_X[i];
//		
//		Pre_A_Y[i] = Pre_A_Y[i+1];
//		Int_A_Y += Pre_A_Y[i];
//		
//		Pre_A_Z[i] = Pre_A_Z[i+1];
//		Int_A_Z += Pre_A_Z[i];
//		
//		Pre_G_X[i] = Pre_G_X[i+1];
//		Int_G_X += Pre_G_X[i];
//		
//		Pre_G_Y[i] = Pre_G_Y[i+1];
//		Int_G_Y += Pre_G_Y[i];
//		
//		Pre_G_Z[i] = Pre_G_Z[i+1];
//		Int_G_Z += Pre_G_Z[i];
//	}
//	Pre_A_X[AVE-1] = Accel_X;
//	Int_A_X += Pre_A_X[AVE-1];
//	Accel_X = Int_A_X/AVE;
//	
//	Pre_A_Y[AVE-1] = Accel_Y;
//	Int_A_Y += Pre_A_Y[AVE-1];
//	Accel_Y = Int_A_Y/AVE;
//	
//	Pre_A_Z[AVE-1] = Accel_Z;
//	Int_A_Z += Pre_A_Z[AVE-1];
//	Accel_Z = Int_A_Z/AVE;
//	
//	Pre_G_X[AVE-1] = Gyro_X;
//	Int_G_X += Pre_G_X[AVE-1];
//	Gyro_X = Int_G_X/AVE;
//	
//	Pre_G_Y[AVE-1] = Gyro_Y;
//	Int_G_Y += Pre_G_Y[AVE-1];
//	Gyro_Y = Int_G_Y/AVE;
//	
//	Pre_G_Z[AVE-1] = Gyro_Z;
//	Int_G_Z += Pre_G_Z[AVE-1];
//	Gyro_Z = Int_G_Z/AVE;

#if 1
Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*(Gyro_Y - (Gyro_Z>0?Gyro_Z:-Gyro_Z)*0.45 );   //ֱ����
//Angle_PWM = (float)CONTROL_AnglePID_P*(-Pitch + (float)CONTROL_Target_Angle) + (float)CONTROL_AnglePID_D/100*Gyro_Y;   //ֱ����



								Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? -ftm_count_get(ftm0) :  ftm_count_get(ftm0); // ��ȡ�������
//								Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : -ftm_count_get(ftm1); // ��ȡ�ұ�����
								Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : ftm_count_get(ftm1); // ��ȡ�ұ�����
								
								int16_t Ave_End = (Value_End_L + Value_End_R)/2;	//����ƽ��ת��
								
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



//								PreError[4]=PreError[3];
//                PreError[3]=PreError[2];
//                PreError[2]=PreError[1];
//                PreError[1]=PreError[0];
//                PreError[0]=Error_End;//���ٶ������ֶ���
								
//								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
//								SpeedOUT =(int)(((Error_End)*Plan1.Speed.P * 0.1  +  AlllastError*Plan1.Speed.I*0.01));
								
								
//								Speed_Slide[1]=Speed_Slide[0];
//                Speed_Slide[0]=(int)(Speed_Slide[1]*0.6+Speed_PWM*0.4);//(��һ����ʱ������Ҫ����)
//                Speed_PWM=(int)((Speed_Slide[0]-Speed_Slide[1])*10 +Speed_Slide[1]);
								
								
								ftm_count_clean(ftm0);  //�������������
								ftm_count_clean(ftm1);
								
								//����
//								if(Pitch>CONTROL_Target_Angle+3 && Pitch<CONTROL_Target_Angle-3)
//										Speed_PWM = 0;
    
								//    Value_Inductor_R = Get_Ind_V(AD_1); // ���ÿ�������
								//    Value_Inductor_L = Get_Ind_V(AD_2);
                                Value_Inductor_L = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_3));	// ��ȡ����
								Value_Inductor_R = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_4));	// ��ȡ�ҵ��
//								Value_Inductor_BL = kalman1_filter(&AD_Kalman[2], Get_Ind_V(AD_1));	// ��ȡ����
//								Value_Inductor_BR = kalman1_filter(&AD_Kalman[0], 99);	// ��ȡ�ҵ��
								Value_Inductor_BL = Get_Ind_V(AD_1);
								Value_Inductor_BR = Get_Ind_V(AD_2);
//								 Value_Inductor_L = Get_Ind_V(AD_3);	// ��ȡ����
//								Value_Inductor_R = Get_Ind_V(AD_4);	// ��ȡ�ҵ��
//								Value_Inductor_BL = Get_Ind_V(AD_1);
//								Value_Inductor_BR = Get_Ind_V(AD_2);

                                
                                
                                
								Eroor_Ind_Old = Error_Ind;
								Error_Ind = Value_Inductor_R - Value_Inductor_L;
                                
					LR3_Error = LR2_Error;
					LR2_Error = LR1_Error;
					LR1_Error = LR_Error;
					LR_Error =(5.043e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(-2.85e-06)*(float)Error_Ind*Error_Ind + 0.01201*(float)Error_Ind  -0.006396;  //�Ƕ�18.8
					
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
											if( 
												Value_End_L >= 20 	&&	// ����
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
												
												/*�ж��ڼ����������Һʹ�С*/
												switch( Huan_No )
												{
													case 1:	
															if( 0 != CONTROL_Huan1_Data)
															{
																// ������
																_Com_Huan_LR_ = CONTROL_Huan1_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan1_Data%2==0 ? CONTROL_Huan1_Data-1 : CONTROL_Huan1_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan2_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan2_Data%2==0 ? CONTROL_Huan2_Data-1 : CONTROL_Huan2_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan3_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan3_Data%2==0 ? CONTROL_Huan3_Data-1 : CONTROL_Huan3_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan4_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan4_Data%2==0 ? CONTROL_Huan4_Data-1 : CONTROL_Huan4_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan5_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan5_Data%2==0 ? CONTROL_Huan5_Data-1 : CONTROL_Huan5_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan6_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan6_Data%2==0 ? CONTROL_Huan6_Data-1 : CONTROL_Huan6_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan7_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan7_Data%2==0 ? CONTROL_Huan7_Data-1 : CONTROL_Huan7_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan8_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan8_Data%2==0 ? CONTROL_Huan8_Data-1 : CONTROL_Huan8_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
																// ������
																_Com_Huan_LR_ = CONTROL_Huan9_Data % 2;
																
																// ����С
																switch( (CONTROL_Huan9_Data%2==0 ? CONTROL_Huan9_Data-1 : CONTROL_Huan9_Data)/2 )	// ż��ʱ��2 ��1(������ȥ��ui.c���Plan_Judge_State)
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
													default:	_Com_Huan_LR_ = 2;	// �����Ҳ����
												}
												
												// �����
												LED_Red_ON();
											}
											break;
										}
										case 1:		// ��⵽����־
										{
											if(
												temp_time > 0		&& // �������ܹ�
												temp_dis > 0		&& // �������ܹ�
												(Run_Distance - temp_dis) > Now_InHuan_Min &&	// ʶ�𵽻����뻷������Сֵ
												(Run_Distance - temp_dis) < Now_InHuan_Max &&	// ʶ�𵽻����뻷�������ֵ
												Value_Inductor_L + Value_Inductor_R > (_Com_Huan_Value_ * 2 - 300 )  )
											{
												
												
												if(1 == _Com_Huan_LR_)		// ���뻷
												{
//													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
													LR_Error = -Now_Huan_Add;
												}
												else if(0 == _Com_Huan_LR_)	// ���뻷
												{
//													Value_Inductor_R = Value_Inductor_R*CONTROL_Huan_Add/10;
													LR_Error = Now_Huan_Add;
												}
												
										
												// ���̵ƣ���������
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
										
										case 2:		// �뻷��δ������־
										{
											if(
												Run_Time - temp_time > 20			&&	// ���뻷һ��ʱ��

												Run_Distance - temp_dis > Now_InHuan_Max	&&	// ʶ�𵽻����뻷�������ֵ
												Value_Inductor_L < _Com_Huan_Value_ 		&& 
												Value_Inductor_R < _Com_Huan_Value_   )
											{
												
												
												// ��5���ڣ���ƫ�ƴ����
												static uint8_t turn_back_time = 0;
												turn_back_time++;
												if( turn_back_time < 6 )
												{
													if( 1 == _Com_Huan_LR_ )		// ���뻷
													{
														LR_Error = LR_Error*turn_back_time/5 - Now_Huan_Add*(5-turn_back_time)/5;
													}
													else if( 0 == _Com_Huan_LR_ )	// ���뻷
													{
														LR_Error = LR_Error*turn_back_time/5 + Now_Huan_Add*(5-turn_back_time)/5;
													}
												}
												
												
												
											}
											if( Run_Distance - temp_dis > Now_InHuan_Max + 1000 )
												Huan_Flag ++;
											break;
										}
										
										case 3:		// ������־
										{
											if( 
//												Run_Time - temp_time > 50			&&	// ���뻷һ��ʱ��
//												Run_Distance - temp_dis > 4000		&&	// ���뻷һ������
												Value_Inductor_L > _Com_Huan_Value_	&& 
												Value_Inductor_R > _Com_Huan_Value_  
											)
											{
												temp_time = 0;
												temp_dis = Run_Distance;
												
												
												// ��֮ǰ���󣬻�����෴����һ��ƫ��
												if( 1 == _Com_Huan_LR_ )		// ���뻷
												{
//													Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
													LR_Error = _Com_HuanOut_L_Add_;
												}
												else if( 0 == _Com_Huan_LR_ )	// ���뻷
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
										case 4:		// ��ȫ���������־λ
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
									/*��д�� ����*/
									
//          Turn_PWM = Error_Ind*Plan1.Turn.P/10 + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
//								Turn_PWM = LR_Error*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
//								Turn_PWM = LR_Error*CONTROL_TurnPID_P + GYRO.X/10*CONTROL_TurnPID_D;
								Turn_PWM = (LR_Error*0.4+LR1_Error*0.3+LR2_Error*0.2+LR3_Error*0.1)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
//								Turn_PWM = (LR_Error)*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
								#if	0
									if(Turn_PWM>0)
									{
										L_Final_PWM = Angle_PWM + Speed_PWM - 1.3*Turn_PWM;
										R_Final_PWM = Angle_PWM + Speed_PWM + 0.7*Turn_PWM;
									}
									else
									{
										L_Final_PWM = Angle_PWM + Speed_PWM - 0.7*Turn_PWM;
										R_Final_PWM = Angle_PWM + Speed_PWM + 1.3*Turn_PWM;
									}
								#else
									L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
									R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;
								#endif
								
									
									
//								L_Final_PWM = Do_it==0 ? 0:L_Final_PWM;
//								R_Final_PWM = Do_it==0 ? 0:R_Final_PWM;
     
    
							if( 0 == Read_Input_State(Reed2_Port, Reed2_Pin) )
							{
								Stop_Flag = 1;
								Beep_Time(100);
							}					
								
							if(Stop_Flag == 1)		// ɲ��
							{
								if( Value_End_L >= 20 && Value_End_R >= 20 )
								{
									Motor_L_Go_V(1000);
									Motor_R_Go_V(1000);
								}
							}
							else					// ���������PWM
							{
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

//		{
//            LED_Count = LED_Count==240 ? 0:LED_Count;
//            switch(LED_Count)
//            {
//                case  0*20: printf("###A%02.3f##", Pitch);			break;
//                case  1*20: printf("###B%02.3f##", Yaw);    			break;
//                case  2*20: printf("###C%6d##", Value_Inductor_L);  	break;
//                case  3*20: printf("###D%6d##", Value_Inductor_R);   break;
//                case  4*20: printf("###E%6d##", Value_End_L); 		break;
//                case  5*20: printf("###F%6d##", Value_End_R); 		break;
//                case  6*20: printf("###G%6d##", (uint16_t)Gyro_X);  	break;
//				case  7*20: printf("###H%6d##", (uint16_t)Gyro_Y);  	break;
//				case  8*20: printf("###I%6d##", (uint16_t)Gyro_Z);  	break;
//				case  9*20: printf("###J%6d##", (uint16_t)Accel_X);  break;
//				case 10*20: printf("###K%6d##", (uint16_t)Accel_Y);  break;
//				case 11*20: printf("###L%6d##", (uint16_t)Accel_Z);  break;
//            }
//            LED_Count++;
//        }


//    LED_White_OFF();
//    Pin_Output_Toggle(LED_Blue_Port, LED_Blue_Pin);
//    Pin_Output_Toggle(PTE, PTE0);


		
	if( Bt_Send )
	{
		Variable[0] = Value_Inductor_L;  //�������
		Variable[1] = Value_Inductor_R;  //�ұ�����
		Variable[2] = Value_Inductor_BL;  //������
		Variable[3] = Value_Inductor_BR;  //����
		Send_Begin();
		Send_Variable();
	}
    /*�ж�����--����*/
//    Enable_PIT_CH0();
}



uint8_t Just_Do_It(void)
{
//    uint8_t str[25];
    
//    NVIC_EnableIRQ(PIT_CH0_IRQn);
//    NVIC->ISER[0] = (1 << ((uint32_t)(PIT_CH0_IRQn) & 0x1F));
    OLED_Clear();
    
//    Do_it = 1;
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
//        {//�ʺ��
//            LED_Count = LED_Count==35 ? 0:LED_Count;
//            switch(LED_Count)
//            {
//                case  0: LED_White_OFF(); 	LED_Orange_ON();	break;
//                case  5: LED_Orange_OFF();  LED_Red_ON();    	break;
//                case 10: LED_Red_OFF();     LED_Green_ON();  	break;
//                case 15: LED_Green_OFF();   LED_Blue_ON();   	break;
//                case 20: LED_Blue_OFF();    LED_Indigo_ON(); 	break;
//                case 25: LED_Indigo_OFF();  LED_Purple_ON(); 	break;
//                case 30: LED_Purple_OFF();  LED_White_ON();  	break;
//            }
//            LED_Count++;
//        }  
//        LED_Purple_ON();
		/*******************�������*****************************/
//		LED_White_OFF();
		

		
		uint8_t Protect_Flag = 0;
		if( 0 == Read_Input_State(Reed2_Port, Reed2_Pin) )
		{
			Protect_Flag = 1;
			Stop_Flag = 1;
		}
#if 1
		if(1 == _Com_RunProtect_)
		{
			if( (Value_End_L>300)||(Value_End_L<-300)			// ת�ٱ���
//				||Pitch<-40										// �Ƕȱ���
				||Value_Inductor_L<200||Value_Inductor_R<200	// ���ֵ����
				
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
			
//						Motor_L_Go_V(500);
//						Motor_R_Go_V(500);
						/****�ص��****/
						Run_Time_Flag = 0;
						Motor_L_EN(Disable);
						Motor_R_EN(Disable);
						
						Stop_Flag = 0;
						Bt_Send = 0;
						/**************/
                        LED_White_OFF();   //��LED
                        OLED_Display_On();//��OLED
						OLED_Init();
                        return 0;
        }
		
//    Variable[0] = Gyro_X;  //�������
//    Variable[1] = Gyro_Y;  //�ұ�����
//    Variable[2] = Gyro_Z;  //������
//    Variable[3] = Accel_X;  //����
//		
//    Variable[4] = Accel_Y;  //�ҵ��
//    Variable[5] = Accel_Z;
//    Variable[6] = Pitch;  //�����
////    Variable[7] = Roll;
////	Variable[8] = Yaw;
//	Variable[7] = Run_Distance;
//	Variable[8] = _Com_InHuan_Max_;
//		
//		
//	Variable[9]  = Angle_PWM;
//	Variable[10] = Speed_PWM;
//	Variable[11] = Turn_PWM;
////	Variable[12] = L_Final_PWM;
////	Variable[13] = R_Final_PWM;
////	Variable[14] = Value_End_L;
////	Variable[15] = Value_End_R;	
//	Variable[12] = Value_Inductor_L;
//	Variable[13] = Value_Inductor_R;
//	Variable[14] = Value_Inductor_BL;
//	Variable[15] = Value_Inductor_BR;	
//	
//    Send_Begin();
//    Send_Variable();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


//        sprintfsprintf(str, "%2.1f %3d     ", Pitch, (int)(Value_End_L+Value_End_R)/2);
//        OLED_Show_Str(0, 0, str, 24, 1);
//        
//        sprintf(str, "%4d %4d      ", Value_Inductor_L, Value_Inductor_R);
//        OLED_Show_Str(0, 30, str, 24, 1);
//        
//        OLED_Refresh_Gram();
        
    }
    
}

