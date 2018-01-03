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
int16_t PreError[5] = {0,0,0,0,0,};

int AlllastError=0;
int Speed_Slide[3]={0};//�ٶ�ƽ������

int SpeedOUT;
int32_t End_Integral = 0;    
float x=0;  
uint8_t Do_it = 1;

uint8_t Huan_Count_Flag = 0;
uint16_t Huan_Count = 0;
float Yaw_Huan = 0.00001;
#define OUT 0
#define IN 1
uint8_t Huan_Flag = OUT;

void PIT_CH0_IRQHandler(void)
{
								PIT_CLR_Flag(PIT_CH0);  //����жϱ�־λ 
							//    Disable_PIT_CH0();
									/*�ж�����--��ʼ*/
									

    
								MPU6050_GetData(&GYRO, &ACC);   //��ȡԭʼ����
								Data_Filter();     //ԭʼ�����˲�
								Get_Attitude();    //��ȡ��̬
								


  
								Angle_PWM = Plan1.Angle.P*(Pitch - Plan1.Target.Angle) + Plan1.Angle.D/10*GYRO_Real.Y;   //ֱ����

    


								Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? -ftm_count_get(ftm0) :  ftm_count_get(ftm0); //�������ɼ�
								Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : -ftm_count_get(ftm1);


    
//                Error_End = Value_End_L + Value_End_R - Plan1.Target.Speed*2;     
					      Error_End =   Plan1.Target.Speed-(Value_End_L + Value_End_R)/2;   
//                Value_End_L =0; 
//								Value_End_R =0;		//�������
								
                End_Integral = 0;
								
//                for(uint8_t i=0; i<19; i++)
//                {
//                    PreError[i] = PreError[i+1]; 
//                    End_Integral += PreError[i];
//                }
//                PreError[19] = Error_End;
//                End_Integral += PreError[19];
//                
                PreError[4]=PreError[3];
                PreError[3]=PreError[2];
                PreError[2]=PreError[1];
                PreError[1]=PreError[0];
                PreError[0]=Error_End;//���ٶ������ֶ���
								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
								Speed_PWM = -Error_End*Plan1.Speed.P + AlllastError*Plan1.Speed.I/100;    //�ٶȻ�
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
								
								
								if(Pitch>Plan1.Target.Angle+3 && Pitch<Plan1.Target.Angle-3)
										Speed_PWM = 0;
    
								//    Value_Inductor_R = Get_Ind_V(AD_1);
								//    Value_Inductor_L = Get_Ind_V(AD_2);
                                Value_Inductor_L = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_3));
								Value_Inductor_R = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_4));
								
//								Value_Inductor_R = Get_Ind_V(AD_1);
//								Value_Inductor_L = Get_Ind_V(AD_2);
								
//                                Beep_OFF();
//                                if(Value_Ind_L_Old + Value_Ind_R_Old>2000)
//                                {
//                                    Huan_Count++;
//                                    Huan_Count = Huan_Count>=10?10:Huan_Count;
//                                    Value_Inductor_L = Value_Inductor_L*(1-(float)Huan_Count/20);
////                                    Beep_ON();
//                                }
//                                else
//                                    Huan_Count=0;
//                                Value_Ind_L_Old = Value_Inductor_L;
//                                Value_Ind_R_Old = Value_Inductor_R;
                                Beep_OFF();
//                                if(Yaw - Yaw_Huan > 100)//���뻷��
//                                    Huan_Flag = OUT;//��������־
//                                else 
//                                    Huan_Flag = IN; //�뻷����־
                                if(Huan_Count_Flag)
                                    Huan_Count++;
//                                if(Huan_Count > 500 || Huan_Count == 0)//�����뻷����
//                                {
                                    
                                    if(Value_Inductor_R>1050//�����뻷����:�ڻ���1S����
                                        &&Pitch<-18
                                        &&Value_Inductor_L>1050
                                       && Huan_Count <80
//                                        &&100<Yaw
//                                        &&Yaw<160
    //                                    && Huan_Flag!=OUT
                                    )
                                    {
                                        Huan_Count_Flag = 1;
//                                        Huan_Count = 1;
                                        Yaw_Huan = Yaw;
                                        Beep_ON();
                                        Value_Inductor_L = Value_Inductor_L*Plan1.Turn.tp/10;
                                    }
                                    else if(Huan_Count > 200) //2S֮��
                                    {
                                        Huan_Count_Flag = 0;
                                        Huan_Count = 0;
                                    }
//                                }
//                                else//����������
//                                {
////                                    Huan_Count = 0;
//                                    Huan_Count_Flag = 0;
//                                }
                                
                                
                                
								Eroor_Ind_Old = Error_Ind;
								Error_Ind = Value_Inductor_R - Value_Inductor_L;
                                
//		       f(x) = p1*x^3 + p2*x^2 + p3*x + p4
//Coefficients (with 95% confidence bounds):
//       p1 =   5.043e-09  (1.887e-09, 8.198e-09)
//       p2 =   -2.85e-06  (-3.911e-06, -1.788e-06)
//       p3 =     0.01201  (0.01121, 0.01282)rrb
//       p4 =   -0.006396  (-0.1843, 0.1716)
                                x =(5.043e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(-2.85e-06)*(float)Error_Ind*Error_Ind + 0.01201*(float)Error_Ind  -0.006396;  //�Ƕ�18.8
//								x<-20?x=-20:x;
//								x>20?x=20:x;
                                
								if(Value_Inductor_L<250&&Value_Inductor_R<920&&Value_Inductor_R>250) //�Ҷ�
									x=-13;
								if(Value_Inductor_L>400&&Value_Inductor_L<920&&Value_Inductor_R<400)
									x=13;
		              

//          Turn_PWM = Error_Ind*Plan1.Turn.P/10 + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
								Turn_PWM = x*Plan1.Turn.P + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
								
								L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
								R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;
//								L_Final_PWM = Do_it==0 ? 0:L_Final_PWM;
//								R_Final_PWM = Do_it==0 ? 0:R_Final_PWM;
     
    
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
								
								
								
								
								
                                LED_White_OFF();
//    Pin_Output_Toggle(LED_Blue_Port, LED_Blue_Pin);
//    Pin_Output_Toggle(PTE, PTE0);

    /*�ж�����--����*/
//    Enable_PIT_CH0();
}


uint8_t Just_Do_It(void)
{
    uint8_t str[25];
    
//    NVIC_EnableIRQ(PIT_CH0_IRQn);
//    NVIC->ISER[0] = (1 << ((uint32_t)(PIT_CH0_IRQn) & 0x1F));
    OLED_Clear();
    
//    Do_it = 1;
    Motor_L_EN(Enable);
    Motor_R_EN(Enable);
    
    uint8_t LED_Count = 0;
    OLED_Display_Off();//��OLED
    while(1)
    {
        {//�ʺ��
            LED_Count = LED_Count==7 ? 0:LED_Count;
            switch(LED_Count)
            {
                case 0: LED_White_OFF();  LED_Orange_ON();  break;
                case 1: LED_Orange_OFF();  LED_Red_ON();    break;
                case 2: LED_Red_OFF();     LED_Green_ON();  break;
                case 3: LED_Green_OFF();   LED_Blue_ON();   break;
                case 4: LED_Blue_OFF();    LED_Indigo_ON(); break;
                case 5: LED_Indigo_OFF();  LED_Purple_ON(); break;
                case 6: LED_Purple_OFF();  LED_White_ON();  break;
            }
            LED_Count++;
        }  
//        LED_Purple_ON();
        
        switch(Get_Key()||(Value_End_L>350)||(Value_End_L<-350)
               ||Pitch<-50

                )
        {
            case Press_NULL:  break;
            
            default:        
//                            FTM_PWM_set_CnV(ftm2, ftm_ch0, 0);
//                            FTM_PWM_set_CnV(ftm2, ftm_ch5, 0);
//                            
//                            FTM_PWM_set_CnV(ftm2, ftm_ch2, 0);
//                            FTM_PWM_set_CnV(ftm2, ftm_ch3, 0);
//                        Do_it = 0;
                            Motor_L_EN(Disable);
                            Motor_R_EN(Disable);
//                        PIT_CLR_Flag(PIT_CH0);
//                        LED_White_OFF();   //��LED
                        OLED_Display_On();//��OLED
//                        NVIC_DisableIRQ(PIT_CH0_IRQn);
                        return 0;
        }
    Variable[0] = Value_End_L;  //�������
    Variable[1] = Value_End_R;  //�ұ�����
    Variable[2] = Pitch;  //������
    Variable[3] = Value_Inductor_L;  //����
    Variable[4] = Value_Inductor_R;  //�ҵ��
    Variable[5] = Value_Inductor_R - Value_Inductor_L;
    Variable[6] = Yaw;  //�����
        
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