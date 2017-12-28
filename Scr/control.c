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
int Speed_Slide[3]={0};//速度平滑参数

int SpeedOUT;
int32_t End_Integral = 0;    
float x=0;  
uint8_t Do_it = 0;

uint8_t Huan_Count = 0;
void PIT_CH0_IRQHandler(void)
{
								PIT_CLR_Flag(PIT_CH0);  //清除中断标志位 
							//    Disable_PIT_CH0();
									/*中断内容--开始*/
									

    
								MPU6050_GetData(&GYRO, &ACC);   //获取原始数据
								Data_Filter();     //原始数据滤波
								Get_Attitude();    //获取姿态
								


  
								Angle_PWM = Plan1.Angle.P*(Pitch - Plan1.Target.Angle) + Plan1.Angle.D/10*GYRO_Real.Y;   //直立环

    


								Value_End_L = End_Read_Dir(End_L)==0? -ftm_count_get(ftm0) : ftm_count_get(ftm0); //编码器采集
								Value_End_R = End_Read_Dir(End_R)==0? ftm_count_get(ftm1) : -ftm_count_get(ftm1); 


    
//                Error_End = Value_End_L + Value_End_R - Plan1.Target.Speed*2;     
					      Error_End =   Plan1.Target.Speed-(Value_End_L + Value_End_R)/2;   
//                Value_End_L =0; 
//								Value_End_R =0;		//保险起见
								
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
                PreError[0]=Error_End;//入速度误差积分队列
								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
								Speed_PWM = -Error_End*Plan1.Speed.P + AlllastError*Plan1.Speed.I/100;    //速度环
//								PreError[4]=PreError[3];
//                PreError[3]=PreError[2];
//                PreError[2]=PreError[1];
//                PreError[1]=PreError[0];
//                PreError[0]=Error_End;//入速度误差积分队列
								
//								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);
//								SpeedOUT =(int)(((Error_End)*Plan1.Speed.P * 0.1  +  AlllastError*Plan1.Speed.I*0.01));
								
								
//								Speed_Slide[1]=Speed_Slide[0];
//                Speed_Slide[0]=(int)(Speed_Slide[1]*0.6+Speed_PWM*0.4);//(有一点延时处理，需要更改)
//                Speed_PWM=(int)((Speed_Slide[0]-Speed_Slide[1])*10 +Speed_Slide[1]);
								
								
								ftm_count_clean(ftm0);  //清除编码器计数
								ftm_count_clean(ftm1);
								
								
								if(Pitch>Plan1.Target.Angle+3 && Pitch<Plan1.Target.Angle-3)
										Speed_PWM = 0;
    
								//    Value_Inductor_R = Get_Ind_V(AD_1);
								//    Value_Inductor_L = Get_Ind_V(AD_2);
								Value_Inductor_R = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_1));
								Value_Inductor_L = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_2));
								
								
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
								Eroor_Ind_Old = Error_Ind;
								Error_Ind = Value_Inductor_L - Value_Inductor_R;
                                
//		       f(x) = p1*x^3 + p2*x^2 + p3*x + p4
//Coefficients (with 95% confidence bounds):
//       p1 =   5.043e-09  (1.887e-09, 8.198e-09)
//       p2 =   -2.85e-06  (-3.911e-06, -1.788e-06)
//       p3 =     0.01201  (0.01121, 0.01282)rrb
//       p4 =   -0.006396  (-0.1843, 0.1716)
								x =(5.043e-09) *Error_Ind*Error_Ind*Error_Ind +(-2.85e-6)*Error_Ind*Error_Ind + 0.01201*Error_Ind  -0.006396 ;  //角度18.8
//								x<-20?x=-20:x;
//								x>20?x=20:x;
                                
								if(Value_Inductor_L<250&&Value_Inductor_R<920&&Value_Inductor_R>250) //右丢
									x=-13;
								if(Value_Inductor_L>400&&Value_Inductor_L<920&&Value_Inductor_R<400)
									x=13;
		              
//          Turn_PWM = Error_Ind*Plan1.Turn.P/10 + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
								Turn_PWM = x*Plan1.Turn.P + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
								
								L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
								R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;
								L_Final_PWM = Do_it==0 ? 0:L_Final_PWM;
								R_Final_PWM = Do_it==0 ? 0:R_Final_PWM;
     
    
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
								
								
								
								
								
								LED_Green_OFF();
//    Pin_Output_Toggle(LED_Blue_Port, LED_Blue_Pin);
//    Pin_Output_Toggle(PTE, PTE0);

    /*中断内容--结束*/
//    Enable_PIT_CH0();
}


uint8_t Just_Do_It(void)
{
    uint8_t str[25];
    
    NVIC_EnableIRQ(PIT_CH0_IRQn);
//    NVIC->ISER[0] = (1 << ((uint32_t)(PIT_CH0_IRQn) & 0x1F));
    OLED_Clear();
    
    Do_it = 1;
    while(1)
    {
        
        LED_Green_ON();
        
            
        switch(Get_Key()|(Value_End_L>450)|(Value_End_L<-450))
        {
            case Press_NULL:  break;
            
            default:        
                            FTM_PWM_set_CnV(ftm2, ftm_ch0, 0);
                            FTM_PWM_set_CnV(ftm2, ftm_ch5, 0);
                            
                            FTM_PWM_set_CnV(ftm2, ftm_ch2, 0);
                            FTM_PWM_set_CnV(ftm2, ftm_ch3, 0);
                        Do_it = 0;
                        PIT_CLR_Flag(PIT_CH0);
//                        NVIC_DisableIRQ(PIT_CH0_IRQn);
                        return 0;
        }
    Variable[0] = Value_End_L;  
    Variable[1] = Value_End_R; 
    Variable[2] = Pitch;
    Variable[3] = Value_Inductor_L;
    Variable[4] = Value_Inductor_R;
    Variable[5] = Value_Inductor_L - Value_Inductor_R;
        
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