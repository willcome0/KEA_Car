#include "control.h"


int32_t Angle_PWM;
int32_t Speed_PWM;
int32_t Turn_PWM;
int32_t L_Final_PWM;
int32_t R_Final_PWM;
uint16_t Value_Inductor_L = 0;
uint16_t Value_Inductor_R = 0;
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

uint8_t Do_it = 1;

uint8_t Huan_Count_Flag = 0;
uint16_t Huan_Count = 0;
float Yaw_Huan = 0.00001;
#define OUT 0
#define IN 1
uint8_t Huan_Flag = OUT;
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
uint16_t CONTROL_Huan_Add     = 0;

uint32_t temp_time = 0;	// ������ʱ��ʱ ��
//uint32_t out_time = 0;	// ������ʱ��ʱ ��
uint32_t temp_dis = 0;

volatile float Pitch = 0, Roll = 0, Yaw = 0;
volatile float Pitch1 = 0, Roll1 = 0, Yaw1 = 0;
volatile short Gyro[3] = {0};
volatile short Accel[3] = {0};


////===============================��Ԫ��============================================
//#define Kp 1.6f //10.0f             	// proportional gain governs rate of convergence to accelerometer/magnetometer
//#define Ki 0.001f//1.2f // //0.008f  	// integral gain governs rate of convergence of gyroscope biases
//#define halfT 0.005f                   	// half the sample period�������ڵ�һ��
//float q0 = 1, q1 = 0, q2 = 0, q3 = 0; 	// quaternion elements representing the estimated orientation
//float exInt = 0, eyInt = 0, ezInt = 0; 	// scaled integral error
///*
// * ��������IMUupdate
// * ����  ����Ԫ�ؽ���ŷ����
// * ����  �������� ���ٶȼ�
// * ���  ����
// * ����  ���ڲ�����
// */
//void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
//{
//	float norm;
//	float vx, vy, vz;
//	float ex, ey, ez;

//	// �Ȱ���Щ�õõ���ֵ���
//	float q0q0 = q0*q0;
//	float q0q1 = q0*q1;
//	float q0q2 = q0*q2;
//	float q1q1 = q1*q1;
//	float q1q3 = q1*q3;
//	float q2q2 = q2*q2;
//	float q2q3 = q2*q3;
//	float q3q3 = q3*q3;

////	if (ax*ay*az == 0)
////	{
////		return;
////	}
//		
//	norm = sqrt(ax*ax + ay*ay + az*az);	// acc���ݹ�һ��
//	ax = ax / norm;
//	ay = ay / norm;
//	az = az / norm;

//	// estimated direction of gravity and flux (v and w)	�����������������/��Ǩ
//	vx = 2*(q1q3 - q0q2);									// ��Ԫ����xyz�ı�ʾ
//	vy = 2*(q0q1 + q2q3);
//	vz = q0q0 - q1q1 - q2q2 + q3q3 ;

//	// error is sum of cross product between reference direction of fields and direction measured by sensors
//	ex = (ay*vz - az*vy) ;		// �������������õ���־������
//	ey = (az*vx - ax*vz) ;
//	ez = (ax*vy - ay*vx) ;

//	exInt = exInt + ex * Ki;	// �������л���
//	eyInt = eyInt + ey * Ki;
//	ezInt = ezInt + ez * Ki;

//	// adjusted gyroscope measurements
//	gx = gx + Kp*ex + exInt;	// �����PI�󲹳��������ǣ����������Ư��
//	gy = gy + Kp*ey + eyInt;
//	gz = gz + Kp*ez + ezInt;	// �����gz����û�й۲��߽��н��������Ư�ƣ����ֳ����ľ��ǻ����������Լ�

//	// integrate quaternion rate and normalise	// ��Ԫ�ص�΢�ַ���
//	q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
//	q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
//	q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
//	q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

//	// normalise quaternion
//	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
//	q0 = q0 / norm;
//	q1 = q1 / norm;
//	q2 = q2 / norm;
//	q3 = q3 / norm;
//	
//	Pitch1 = asin(-2*q1*q3 + 2*q0*q2) * 57.3; // pitch
//	Yaw1 = atan2(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1)*57.3; // yaw

//    Yaw1 = Yaw1<0 ? 360 + Yaw1 : Yaw1;
////	Attitude_Angle.Z = 0;
//}
float K1 =0.02; 
float angle, angle_dot; 
void Yijielvbo(float angle_m, float gyro_m)
{
   angle = K1 * angle_m+ (1-K1) * (angle + gyro_m * 0.005);
}
void PIT_CH0_IRQHandler(void)
{
//	Debug_Pin1_Toggle();
//	Debug_Pin2_H();
			PIT_CLR_Flag(PIT_CH0);  //����жϱ�־λ



			
//			MPU_Get_Gyroscope(&Gyro_X, &Gyro_Y, &Gyro_Z);//0.52ms
//			MPU_Get_Gyroscope(&Gyro_X, &Gyro_Y, &Gyro_Z);//0.52ms
//			MPU_Get_Gyroscope(&Gyro_X, &Gyro_Y, &Gyro_Z);//0.52ms
//                for(uint16_t i=0; i<20; i++)
//                {
//                    PreError[i] = PreError[i+1]; 
//                    End_Integral += PreError[i];
//                }

//							//    Disable_PIT_CH0();
//									/*�ж�����--��ʼ*/
//    
//								MPU6050_GetData(&GYRO, &ACC);   //��ȡԭʼ����
//								Data_Filter();     //ԭʼ�����˲�
//								Get_Attitude();    //��ȡ��̬
							
//								if(_Com_Debug_)
//									(float)CONTROL_Target_Angle = (float)CONTROL_Target_Angle + (Pitch + (float)CONTROL_Target_Angle)/4;
								mpu_dmp_get_data(&Pitch,&Roll,&Yaw);//2.96ms
								Yijielvbo(atan2(Accel[0],Accel[2])*180/3.14,-Gyro[1]/16.4);
								Angle_PWM = CONTROL_AnglePID_P*(-angle + (float)CONTROL_Target_Angle) + CONTROL_AnglePID_D/10*Gyro[1];   //ֱ����




//								Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? -ftm_count_get(ftm0) :  ftm_count_get(ftm0); // ��ȡ�������
//								Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : -ftm_count_get(ftm1); // ��ȡ�ұ�����

//								int16_t Ave_End = (Value_End_L + Value_End_R)/2;	//����ƽ��ת��
//								
//								if(Run_Time_Flag)	//��ʱ����
//								{
//									Run_Time++;								// ��ʱ	
//									Run_Distance += Ave_End;	// ��·��
//								}								
///*	��ʱ��Ҫ�ٶȻ�						
//    
//   
//					      Error_End =   CONTROL_Target_Speed - Ave_End;   //���ٶ�ƫ��
//								
//                End_Integral = 0;	//��������
//								
//                for(uint8_t i=0; i<19; i++)
//                {
//                    PreError[i] = PreError[i+1]; 
//                    End_Integral += PreError[i];
//                }
//                PreError[19] = Error_End;
//                End_Integral += PreError[19];

////                PreError[4]=PreError[3];
////                PreError[3]=PreError[2];
////                PreError[2]=PreError[1];
////                PreError[1]=PreError[0];
////                PreError[0]=Error_End;//���ٶ������ֶ���
////								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
//								
//								Speed_PWM = -Error_End*CONTROL_SpeedPID_P + End_Integral*CONTROL_SpeedPID_I/100;    //�ٶȻ�
//*/				
//				
//				
//				
////								PreError[4]=PreError[3];
////                PreError[3]=PreError[2];
////                PreError[2]=PreError[1];
////                PreError[1]=PreError[0];
////                PreError[0]=Error_End;//���ٶ������ֶ���
//								
////								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
////								SpeedOUT =(int)(((Error_End)*Plan1.Speed.P * 0.1  +  AlllastError*Plan1.Speed.I*0.01));
//								
//								
////								Speed_Slide[1]=Speed_Slide[0];
////                Speed_Slide[0]=(int)(Speed_Slide[1]*0.6+Speed_PWM*0.4);//(��һ����ʱ������Ҫ����)
////                Speed_PWM=(int)((Speed_Slide[0]-Speed_Slide[1])*10 +Speed_Slide[1]);
//								
//								
//								ftm_count_clean(ftm0);  //�������������
//								ftm_count_clean(ftm1);
//								
//								//����
////								if(Pitch>CONTROL_Target_Angle+3 && Pitch<CONTROL_Target_Angle-3)
////										Speed_PWM = 0;
//    
//								//    Value_Inductor_R = Get_Ind_V(AD_1); // ���ÿ�������
//								//    Value_Inductor_L = Get_Ind_V(AD_2);
//                                Value_Inductor_L = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_3));	// ��ȡ����
//								Value_Inductor_R = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_4));	// ��ȡ�ҵ��
//								

////                                if(Value_Ind_L_Old + Value_Ind_R_Old>2000)
////                                {
////                                    Huan_Count++;
////                                    Huan_Count = Huan_Count>=10?10:Huan_Count;
////                                    Value_Inductor_L = Value_Inductor_L*(1-(float)Huan_Count/20);
//////                                    Beep_ON();
////                                }
////                                else
////                                    Huan_Count=0;
////                                Value_Ind_L_Old = Value_Inductor_L;
////                                Value_Ind_R_Old = Value_Inductor_R;
////                                Beep_OFF();
//								
//								
////                                if(Yaw - Yaw_Huan > 100)//���뻷��
////                                    Huan_Flag = OUT;//��������־
////                                else 
////                                    Huan_Flag = IN; //�뻷����־
////                                if(Huan_Count_Flag)
////                                    Huan_Count++;
//////                                if(Huan_Count > 500 || Huan_Count == 0)//�����뻷����
//////                                {
////                                    
////                                    if(Value_Inductor_R>1050//�����뻷����:�ڻ���1S����
////                                        &&Pitch<-18
////                                        &&Value_Inductor_L>1050
////                                       && Huan_Count <80
//////                                        &&100<Yaw
//////                                        &&Yaw<160
////    //                                    && Huan_Flag!=OUT
////                                    )
////                                    {
////                                        Huan_Count_Flag = 1;
//////                                        Huan_Count = 1;
////                                        Yaw_Huan = Yaw;
////                                        Beep_ON();
////                                        Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
////                                    }
////                                    else if(Huan_Count > 200) //2S֮��
////                                    {
////                                        Huan_Count_Flag = 0;
////                                        Huan_Count = 0;
////                                    }
//									
//									
//									/********�»�***************/
//									if(Value_Inductor_R>1000
//                                        &&Pitch<-22
//                                        &&Value_Inductor_L>1000
//										&& Huan_Flag == OUT)
//									{
//										Huan_Flag = IN;
//										temp_time = Run_Time;
////										temp_dis = Run_Distance;
//									}
//									if(
//										temp_time != 0 && 
//										Huan_Flag != OUT &&
//										((Run_Time - temp_time)*CON_PERIOD > 80 - Value_End_R/2.5) &&
//										((Run_Time - temp_time)*CON_PERIOD < 600 - Value_End_R/2.5) &&	//ԭ600
//										Value_Inductor_L + Value_Inductor_R > 1800
//										
//									)
//									{
//										Beep_Time(CON_PERIOD);
//										if(0 == _Com_Huan_LR_)
//											Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
//										else if(1 == _Com_Huan_LR_)
//											Value_Inductor_R = Value_Inductor_R*CONTROL_Huan_Add/10;
//									}
//									else if(temp_time != 0 && 
//										(Run_Time - temp_time)*CON_PERIOD > 3300)
//									{
//										Beep_Time(100);
//										temp_time = 0;
//										Huan_Flag = OUT;
//									}
//									/*�»�����*/
//									
//									
////									if(temp_dis != 0 &&
////										(Run_Distance - temp_dis)/576 > 10
////									)
////									{
////										Huan_Flag = OUT;
////									}
//									
////                                }
////                                else//����������
////                                {
//////                                    Huan_Count = 0;
////                                    Huan_Count_Flag = 0;
////                                }
//                                
//                                
//                                
//								Eroor_Ind_Old = Error_Ind;
//								Error_Ind = Value_Inductor_R - Value_Inductor_L;
//                                
////		       f(x) = p1*x^3 + p2*x^2 + p3*x + p4
////Coefficients (with 95% confidence bounds):
////       p1 =   5.043e-09  (1.887e-09, 8.198e-09)
////       p2 =   -2.85e-06  (-3.911e-06, -1.788e-06)
////       p3 =     0.01201  (0.01121, 0.01282)rrb
////       p4 =   -0.006396  (-0.1843, 0.1716)
//									
////                                if(Pitch>-16)
////									x =(8.77e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(9.936e-07)*(float)Error_Ind*Error_Ind + 0.008321*(float)Error_Ind   -0.7557;
////								else
////									x =(2.743e-08) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(2.896e-06)*(float)Error_Ind*Error_Ind + 0.01528*(float)Error_Ind  -1.906;  //�Ƕ�18.8

//					LR_Error =(5.043e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(-2.85e-06)*(float)Error_Ind*Error_Ind + 0.01201*(float)Error_Ind  -0.006396;  //�Ƕ�18.8
////						x = -3573 + 5.121*(float)Value_Inductor_L + 1.226*(float)Value_Inductor_R -0.001796*(float)Value_Inductor_L*Value_Inductor_L - 0.00102*(float)Value_Inductor_L*Value_Inductor_R + 5.696e-06*(float)Value_Inductor_R*Value_Inductor_R;

////								x<-20?x=-20:x;
////								x>20?x=20:x;
//                                
////								if(Value_Inductor_L<250&&Value_Inductor_R<920&&Value_Inductor_R>250) //�Ҷ�
////									x=-13,Beep_ON();
////								else if(Value_Inductor_L>400&&Value_Inductor_L<920&&Value_Inductor_R<400)
////									x=13,Beep_ON();
////								else
////									Beep_OFF();
//		              

////          Turn_PWM = Error_Ind*Plan1.Turn.P/10 + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
////								Turn_PWM = LR_Error*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
////								Turn_PWM = LR_Error*CONTROL_TurnPID_P + GYRO.X/10*CONTROL_TurnPID_D;
//								Turn_PWM = LR_Error*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
//								
								L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
								R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;
//								L_Final_PWM = Do_it==0 ? 0:L_Final_PWM;
//								R_Final_PWM = Do_it==0 ? 0:R_Final_PWM;
     
    
								
								
								if(Stop_Flag == 1)		// ɲ��
								{
									Motor_L_Go_V(1000);
									Motor_R_Go_V(1000);
								}
								
								else
									{
								if(L_Final_PWM<0)
								{
										L_Final_PWM = -L_Final_PWM;
										if(L_Final_PWM>=3150)
												L_Final_PWM = 3150;
						//        Motor_Set_Go_Speed(L_Final_PWM, R_Final_PWM);
										Motor_L_Go_V(L_Final_PWM);
								}
								else
								{
										if(L_Final_PWM>=3150)
												L_Final_PWM = 3150;
						//        Motor_Set_Back_Speed(L_Final_PWM, R_Final_PWM);
										Motor_L_Back_V(L_Final_PWM);
								}
								
								
								if(R_Final_PWM<0)
								{
										R_Final_PWM = -R_Final_PWM;
										if(R_Final_PWM>=3150)
												R_Final_PWM = 3150;
						//        Motor_Set_Go_Speed(L_Final_PWM, R_Final_PWM);
										Motor_R_Go_V(R_Final_PWM);
								}
								else
								{
										if(R_Final_PWM>=3150)
												R_Final_PWM = 3150;
						//        Motor_Set_Back_Speed(L_Final_PWM, R_Final_PWM);
										Motor_R_Back_V(R_Final_PWM);
								}
							}
								

								if(BB_Times >= CON_PERIOD)
								{
									BB_Times -= CON_PERIOD;
									Beep_ON();
								}
								else
								{
									Beep_OFF();
								}

								


//			Debug_Pin2_L();		
			
    /*�ж�����--����*/
//    Enable_PIT_CH0();
}


uint8_t Just_Do_It(void)
{

    OLED_Clear();
    
//    Do_it = 1;
	/********�����********/
    Motor_L_EN(Enable);
    Motor_R_EN(Enable);
	Run_Time_Flag = 1;
	Run_Time = 0;
	Run_Distance = 0;
    /**********************/
	
    uint8_t LED_Count = 0;
    OLED_Display_Off();	//��OLED
	

	uint16_t Index_Plan_Offset_1 = (_Com_Plan_-1)*40;
	
	CONTROL_Target_Angle = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Target_Angle_	];
	CONTROL_Target_Speed = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Target_Speed_	];
	CONTROL_AnglePID_P 	 = ALL_DATA[Index_Plan_Offset_1 + _INDEX_AnglePID_P_	];
	CONTROL_AnglePID_D 	 = ALL_DATA[Index_Plan_Offset_1 + _INDEX_AnglePID_D_	];
	CONTROL_SpeedPID_P 	 = ALL_DATA[Index_Plan_Offset_1 + _INDEX_SpeedPID_P_	];
	CONTROL_SpeedPID_I   = ALL_DATA[Index_Plan_Offset_1 + _INDEX_SpeedPID_I_	];
	CONTROL_TurnPID_P    = ALL_DATA[Index_Plan_Offset_1 + _INDEX_TurnPID_P_		];
	CONTROL_TurnPID_D    = ALL_DATA[Index_Plan_Offset_1 + _INDEX_TurnPID_D_		];
	CONTROL_Huan_Add     = ALL_DATA[Index_Plan_Offset_1 + _INDEX_Huan_Add_		];
	

								
    while(1)
    {

        {//�ʺ��
            LED_Count = LED_Count==35 ? 0:LED_Count;
            switch(LED_Count)
            {
                case 0: LED_White_OFF();  LED_Orange_ON();  break;
                case 5: LED_Orange_OFF();  LED_Red_ON();    break;
                case 10: LED_Red_OFF();     LED_Green_ON();  break;
                case 15: LED_Green_OFF();   LED_Blue_ON();   break;
                case 20: LED_Blue_OFF();    LED_Indigo_ON(); break;
                case 25: LED_Indigo_OFF();  LED_Purple_ON(); break;
                case 30: LED_Purple_OFF();  LED_White_ON();  break;
            }
            LED_Count++;
        }  
//        LED_Purple_ON();
		/*******************�������*****************************/
		uint8_t Protect_Flag = 0;
		if(1 == _Com_RunProtect_)
		{
			if( (Value_End_L>300)||(Value_End_L<-300)			// ת�ٱ���
				||Pitch<-40										// �Ƕȱ���
				||Value_Inductor_L<100||Value_Inductor_R<100	// ���ֵ����
				
			  )
				Protect_Flag = 1;
		}
		/*******************************************************/
		if(	(_Com_RunTimeStop_!=0 && Run_Time*CON_PERIOD>_Com_RunTimeStop_*10)	||		// 800��8s   8.00
			(_Com_RunDisStop_!=0  && Run_Distance>(float)_Com_RunDisStop_*57.6)		// 100��1��
		  )
		{
			Stop_Flag = 1;
			Run_Time_Flag = 0;
			Delay_ms(200);
			
			Protect_Flag = 1;
		}
        switch(Get_Key() || Protect_Flag)
        {
            case Press_NULL:  break;
            
            default:        
						/****�ص��****/
						Run_Time_Flag = 0;
						Motor_L_EN(Disable);
						Motor_R_EN(Disable);
						
						Stop_Flag = 0;
						/**************/
                        LED_White_OFF();   //��LED
                        OLED_Display_On();//��OLED
						OLED_Init();
                        return 0;
        }
    Variable[0] = Pitch;  //�������
    Variable[1] = 20;  //�ұ�����
    Variable[2] = -angle;  //������
//    Variable[0] = Value_End_L;  //�������
//    Variable[1] = Value_End_R;  //�ұ�����
//    Variable[2] = Pitch;  //������
    Variable[3] = Value_Inductor_L;  //����
    Variable[4] = Value_Inductor_R;  //�ҵ��
    Variable[5] = Value_Inductor_R - Value_Inductor_L;
//    Variable[6] = Yaw;  //�����
        
    Send_Begin();
    Send_Variable();
	

		
//        sprintf(str, "%2.1f %3d     ", Pitch, (int)(Value_End_L+Value_End_R)/2);
//        OLED_Show_Str(0, 0, str, 24, 1);
//        
//        sprintf(str, "%4d %4d      ", Value_Inductor_L, Value_Inductor_R);
//        OLED_Show_Str(0, 30, str, 24, 1);
//        
//        OLED_Refresh_Gram();
    }
    
}

