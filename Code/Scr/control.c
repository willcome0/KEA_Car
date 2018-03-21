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
int Speed_Slide[3]={0};//速度平滑参数

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
uint16_t CONTROL_Huan_Add     = 0;

void PIT_CH0_IRQHandler(void)
{
								PIT_CLR_Flag(PIT_CH0);  //清除中断标志位 
							//    Disable_PIT_CH0();
									/*中断内容--开始*/
    
								MPU6050_GetData(&GYRO, &ACC);   //获取原始数据
								Data_Filter();     //原始数据滤波
								Get_Attitude();    //获取姿态
							
  
								Angle_PWM = CONTROL_AnglePID_P*(Pitch + CONTROL_Target_Angle) + CONTROL_AnglePID_D/10*GYRO_Real.Y;   //直立环

    


								Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? -ftm_count_get(ftm0) :  ftm_count_get(ftm0); // 获取左编码器
								Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0?  ftm_count_get(ftm1) : -ftm_count_get(ftm1); // 获取右编码器

								int16_t Ave_End = (Value_End_L + Value_End_R)/2;	//计算平均转速
								
								if(Run_Time_Flag)	//计时与测距
								{
									Run_Time++;								// 计时	
									Run_Distance = Run_Distance + Ave_End;	// 记路程
								}									
								
    
   
					      Error_End =   CONTROL_Target_Speed - Ave_End;   //求速度偏差
								
                End_Integral = 0;	//积分清零
								
                for(uint8_t i=0; i<19; i++)
                {
                    PreError[i] = PreError[i+1]; 
                    End_Integral += PreError[i];
                }
                PreError[19] = Error_End;
                End_Integral += PreError[19];

  /*              PreError[4]=PreError[3];
                PreError[3]=PreError[2];
                PreError[2]=PreError[1];
                PreError[1]=PreError[0];
                PreError[0]=Error_End;//入速度误差积分队列
								AlllastError=(int)(PreError[0]+PreError[1]+PreError[2]+PreError[3]+PreError[4]);*/
								
								Speed_PWM = -Error_End*CONTROL_SpeedPID_P + End_Integral*CONTROL_SpeedPID_I/100;    //速度环
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
								
								//保护
//								if(Pitch>CONTROL_Target_Angle+3 && Pitch<CONTROL_Target_Angle-3)
//										Speed_PWM = 0;
    
								//    Value_Inductor_R = Get_Ind_V(AD_1); // 不用卡尔曼的
								//    Value_Inductor_L = Get_Ind_V(AD_2);
                                Value_Inductor_L = kalman1_filter(&AD_Kalman[1], Get_Ind_V(AD_3));	// 获取左电感
								Value_Inductor_R = kalman1_filter(&AD_Kalman[0], Get_Ind_V(AD_4));	// 获取右电感
								

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
//                                if(Yaw - Yaw_Huan > 100)//已入环岛
//                                    Huan_Flag = OUT;//出环岛标志
//                                else 
//                                    Huan_Flag = IN; //入环岛标志
                                if(Huan_Count_Flag)
                                    Huan_Count++;
//                                if(Huan_Count > 500 || Huan_Count == 0)//初步入环条件
//                                {
                                    
                                    if(Value_Inductor_R>1050//具体入环条件:在环、1S以内
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
//                                        Value_Inductor_L = Value_Inductor_L*CONTROL_Huan_Add/10;
                                    }
                                    else if(Huan_Count > 200) //2S之后
                                    {
                                        Huan_Count_Flag = 0;
                                        Huan_Count = 0;
                                    }
//                                }
//                                else//出环或正常
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
									
//                                if(Pitch>-16)
//									x =(8.77e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(9.936e-07)*(float)Error_Ind*Error_Ind + 0.008321*(float)Error_Ind   -0.7557;
//								else
//									x =(2.743e-08) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(2.896e-06)*(float)Error_Ind*Error_Ind + 0.01528*(float)Error_Ind  -1.906;  //角度18.8
					x =(5.043e-09) *(float)Error_Ind * (float)Error_Ind*Error_Ind +(-2.85e-06)*(float)Error_Ind*Error_Ind + 0.01201*(float)Error_Ind  -0.006396;  //角度18.8
//						x = -3573 + 5.121*(float)Value_Inductor_L + 1.226*(float)Value_Inductor_R -0.001796*(float)Value_Inductor_L*Value_Inductor_L - 0.00102*(float)Value_Inductor_L*Value_Inductor_R + 5.696e-06*(float)Value_Inductor_R*Value_Inductor_R;

//								x<-20?x=-20:x;
//								x>20?x=20:x;
                                
//								if(Value_Inductor_L<250&&Value_Inductor_R<920&&Value_Inductor_R>250) //右丢
//									x=-13,Beep_ON();
//								else if(Value_Inductor_L>400&&Value_Inductor_L<920&&Value_Inductor_R<400)
//									x=13,Beep_ON();
//								else
//									Beep_OFF();
		              

//          Turn_PWM = Error_Ind*Plan1.Turn.P/10 + (Error_Ind - Eroor_Ind_Old)*Plan1.Turn.D;
								Turn_PWM = x*CONTROL_TurnPID_P + (Error_Ind - Eroor_Ind_Old)*CONTROL_TurnPID_D;
								
								L_Final_PWM = Angle_PWM + Speed_PWM - Turn_PWM;
								R_Final_PWM = Angle_PWM + Speed_PWM + Turn_PWM;
//								L_Final_PWM = Do_it==0 ? 0:L_Final_PWM;
//								R_Final_PWM = Do_it==0 ? 0:R_Final_PWM;
     
    
								
								
								if(Stop_Flag == 1)		// 刹车
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
								
								
								
								
                                LED_White_OFF();
//    Pin_Output_Toggle(LED_Blue_Port, LED_Blue_Pin);
//    Pin_Output_Toggle(PTE, PTE0);

    /*中断内容--结束*/
//    Enable_PIT_CH0();
}


uint8_t Just_Do_It(void)
{
//    uint8_t str[25];
    
//    NVIC_EnableIRQ(PIT_CH0_IRQn);
//    NVIC->ISER[0] = (1 << ((uint32_t)(PIT_CH0_IRQn) & 0x1F));
    OLED_Clear();
    
//    Do_it = 1;
	/********开电机********/
    Motor_L_EN(Enable);
    Motor_R_EN(Enable);
	Run_Time_Flag = 1;
	Run_Time = 0;
	Run_Distance = 0;
    /**********************/
	
    uint8_t LED_Count = 0;
    OLED_Display_Off();	//关OLED
	

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
        {//彩虹灯
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
		/*******************保护相关*****************************/
		uint8_t Protect_Flag = 0;
		if(1 == _Com_RunProtect_)
		{
			if( (Value_End_L>350)||(Value_End_L<-350)			// 转速保护
//				||Pitch<-50										// 角度保护
				||Value_Inductor_L<250||Value_Inductor_R<250	// 电感值保护
				
			  )
				Protect_Flag = 1;
		}
		/*******************************************************/
		if(	(_Com_RunTimeStop_!=0 && Run_Time>_Com_RunTimeStop_)	||		// 100即1s   1.00
			(_Com_RunDisStop_!=0  && Run_Distance>(float)_Com_RunDisStop_*57.6)		// 100即1米
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
						/****关电机****/
						Run_Time_Flag = 0;
						Motor_L_EN(Disable);
						Motor_R_EN(Disable);
						
						Stop_Flag = 0;
						/**************/
                        LED_White_OFF();   //关LED
                        OLED_Display_On();//开OLED
						OLED_Init();
                        return 0;
        }
		
    Variable[0] = Value_End_L;  //左编码器
    Variable[1] = Value_End_R;  //右编码器
    Variable[2] = Pitch;  //俯仰角
    Variable[3] = Value_Inductor_L;  //左电磁
    Variable[4] = Value_Inductor_R;  //右电磁
    Variable[5] = Value_Inductor_R - Value_Inductor_L;
    Variable[6] = Yaw;  //航向角
        
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

