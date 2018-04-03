//说明见工程文件夹下的Doc文件夹内Readme.txt文件
#define GLOBLE_VAR  //只需在main.c中定义一次，用来防止全局变量的重复定义
#include "includes.h"
#include "common.h"

#include "pit.h"
#include "math.h"

//#include  "anbt_i2c.h"
//#include  "anbt_dmp_mpu6050.h"
//#include  "anbt_dmp_driver.h"






//卡尔曼滤波参数与函数
//float dt=0.001;//注意：dt的取值为kalman滤波器采样时间
//float angle, angle_dot;//角度和角速度
//float P[2][2] = {{ 1, 0 },
//                 { 0, 1 }};
//float Pdot[4] ={ 0,0,0,0};
//float Q_angle=0.001, Q_gyro=0.005; //角度数据置信度,角速度数据置信度
//float R_angle=0.5 ,C_0 = 1;
//float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;

////卡尔曼滤波
//float Kalman_Filter(float angle_m, float gyro_m)//angleAx 和 gyroGy
//{
//        angle+=(gyro_m-q_bias) * dt;
//        angle_err = angle_m - angle;
//        Pdot[0]=Q_angle - P[0][1] - P[1][0];
//        Pdot[1]=- P[1][1];
//        Pdot[2]=- P[1][1];
//        Pdot[3]=Q_gyro;
//        P[0][0] += Pdot[0] * dt;
//        P[0][1] += Pdot[1] * dt;
//        P[1][0] += Pdot[2] * dt;
//        P[1][1] += Pdot[3] * dt;
//        PCt_0 = C_0 * P[0][0];
//        PCt_1 = C_0 * P[1][0];
//        E = R_angle + C_0 * PCt_0;
//        K_0 = PCt_0 / E;
//        K_1 = PCt_1 / E;
//        t_0 = PCt_0;
//        t_1 = C_0 * P[0][1];
//        P[0][0] -= K_0 * t_0;
//        P[0][1] -= K_0 * t_1;
//        P[1][0] -= K_1 * t_0;
//        P[1][1] -= K_1 * t_1;
//        angle += K_0 * angle_err; //最优角度
//        q_bias += K_1 * angle_err;
//        angle_dot = gyro_m-q_bias;//最优角速度

//        return angle;
//}







int main(void)
{
	All_Init();
//	uint8_t Con_1[4];
//	Con_1[0] = 1;
//	Con_1[1] = 2;
//	Con_1[2] = 3;
//	Con_1[3] = 4;
//	FLASH_WriteSector(DATA_FLASH, (const uint8_t *)Con_1, 4, 400);
	
//    ftm_pwm_init(ftm2,ftm_ch0,12500,0);//大，正转//正反转绝对好使过
//    ftm_pwm_init(ftm2,ftm_ch5,12500,300);
//
//    ftm_pwm_init(ftm2,ftm_ch2,12500,0);
//    ftm_pwm_init(ftm2,ftm_ch3,12500,300);//低


//    FTM_PWM_init(FTM_2, CH_0, 12.5, 20);   //APWM_2  PC0   FTM2_CH0   主   左
//    FTM_PWM_init(FTM_2, CH_5, 12.5, 1);    //APWM_1  PB5   FTM2_CH5

//    FTM_PWM_init(FTM_2, CH_2, 12.5, 20);    //BPWM_2  PC2   FTM2_CH2   主   右
//    FTM_PWM_init(FTM_2, CH_3, 12.5, 1);    //BPWM_1  PC3   FTM2_CH3
//
//    FTM_PWM_set_CnV(FTM_2, CH_0, 1);
//    FTM_PWM_set_CnV(FTM_2, CH_5, 800);

//    FTM_PWM_set_CnV(FTM_2, CH_2, 1);
//    FTM_PWM_set_CnV(FTM_2, CH_3, 300);

//    IIC_Init();
//    MPU6050_initialize();




//    IIC_init();
//    while (MPU6050_Init());
//        IIC_init();
//    while (MPU6050_Init());



//    Pin_Output_Config(PTE, PTE0, 1);//左编码器处测试引脚



//    Just_Do_It();







//    PIT_Config(PIT_CH0, 8, 0);//8ms中断
//    PIT_Config(PIT_CH1, 10, 0);
//LED_Blue_ON();
//    Pin_Output_Config(PTE, PTE0, 1);//电平反转配置



		
//    FLASH_EraseSector(FLASH_SECTOR_NUM - 1);
//		uint32_t write2 = 123456789;
		
		
		
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,0);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,16);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,32);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,48);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,64);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,80);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,496);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,500);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,504);		
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 1,(const uint8_t *)&write2,4,508);
//		
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,0);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,16);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,32);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,48);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,64);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,80);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,496);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,500);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,504);		
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 2,(const uint8_t *)&write2,4,508);
//		
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,0);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,16);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,32);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,48);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,64);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,80);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,496);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,500);
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,504);		
//		FLASH_WriteSector(FLASH_SECTOR_NUM - 3,(const uint8_t *)&write2,4,508);
		
	uint8_t GO = 0;
    while(1)
    {
//    UI_Read_Ind();
//        if(Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0)
//            LED_Green_ON();
//        else
//            LED_Green_OFF();

//        MPU6050_GetData(&GYRO, &ACC);	// 读取陀螺仪数据
//        Data_Filter();					// 对原始数据滑动滤波
//
//
////        Get_Attitude();

//


////     sprintf(temp_str, "Pitch: %7d  ", ACC.Y);
////     OLED_Show_Str(0, 33, temp_str, 12, 1);
//
////     sprintf(temp_str, "Pitch: %7.3f  ", Attitude_Angle.Y);
////     OLED_Show_Str(0, 46, temp_str, 12, 1);
////
////     OLED_Refresh_Gram();
////        printf("eeee");
//
////        Variable[0]=Attitude_Angle.Y;
////        Variable[1]=ACC_Real.Y;
//
//        Send_Begin();
//        Send_Variable();
//     printf("emmmm\r\n");



//     								MPU6050_GetData(&GYRO, &ACC);   //获取原始数据
//								Data_Filter();     //原始数据滤波
//								Get_Attitude();    //获取姿态
//        sprintf(str, "PITCH: %3.2f    ", Pitch);
//        OLED_Show_Str(0, 20, str, 12, 1);
//        OLED_Refresh_Gram();

//        if((Read_Input_State(KEY_Left_Port, KEY_Left_Pin)==0) || (Read_Input_State(KEY_Up_Port, KEY_Up_Pin)==0) || (Read_Input_State(KEY_Down_Port, KEY_Down_Pin)==0))
//            LED_Green_ON();
//        else
//            LED_Green_OFF();
//        Get_Key();

/******************显示测试代码**********************/
//		uint8_t str[30];
//		sprintf(str, "%d", Run_Time/100);
//		OLED_Show_Str(0, 46, str, 12, 1);
//		OLED_Refresh_Gram();
		

        switch(GO)
        {
            case  0:   GO = UI_Main();      break;
            case  1:   GO = UI_Go();        break;
            case  2:   GO = UI_Plan();      break;
            case  3:   GO = UI_Driver();    break;
            case  4:   GO = UI_Set();       break;

            case 31:   GO = UI_MPU6050();   break;
            case 32:   GO = UI_Read_Ind();  break;
            case 33:   GO = UI_Read_End();  break;

            default:   GO = UI_Main();
        }
//while(1)
//{
//	LED_Blue_ON();
//	Delay_ms(2000);
//	LED_Blue_OFF();
//	Delay_ms(2000);
//}


//LED_Red_ON();
//Delay_ms(100);
//LED_Red_OFF();
//Delay_ms(100);

//LED_Green_ON();
//Delay_ms(100);
//LED_Green_OFF();
//Delay_ms(100);

//LED_Blue_ON();
//Delay_ms(1000);
//LED_Blue_OFF();
//Delay_ms(1000);

//                printf("好使了！！\r\n");
//        /*********while 测试*****************/
//        sprintf(str, "%5d  %5d", GO,GO);
//        GO++;
//        OLED_Show_StrAll(0,  50, str, 1);
//        OLED_Refresh_Gram();
//        /***********************************/
//
//        short ax, ay, az, gx, gy, gz;
//        S_Get_MPU_G(&gx, &gy, &gz);
//        S_Get_MPU_A(&ax, &ay, &az);
//        ay = atan2(ax, az)*57.3;

////        Pitch = yijiehubu(ay, gy);

////        Variable[0]=test_data1;

////        Send_Begin();
////        Send_Variable();

//            uint8_t str[32];
//            sprintf(str, "TEMP: %4d", Read_Temperature());
//            OLED_Show_Str(0, 34, str, 12, 1);
//            sprintf(str, "PITCH: %4d    ", (int)yijiehubu(ay, gy));
//            OLED_Show_Str(0, 22, str, 12, 1);
//            OLED_Refresh_Gram();
//        printf("Pitch: %f\r\n", yijiehubu(ay, gy));
    }



////    while(DMP_Init());

////    pit_init(0, &PIT_Config0);
////    enable_pit_int(PIT_CH0);
//
////    PIT_Config(PIT_CH0, 10, 0);
////    PIT_Config(PIT_CH1, 1, 1);
//

//
////    Pin_Output_Config(PTH, PTH0, 1);
////
////    Pin_Output_Config(PTE, PTE4, 1);//通道5
////    Pin_Output_Config(PTG, PTG6, 1);//通道5
////    Pin_Output_Config(PTG, PTG5, 1);//通道6
//    Pin_Output_Config(PTG, PTG4, 1);//通道7
//
////    Pin_Output_Config(PTD, PTD4, 1);
////    Pin_Output_Config(PTD, PTD3, 1);
////
////    Pin_Output_Config(PTC, PTC0, 1);
//
////    systick_init(1);
//
////    FTM_PWM_init(FTM_2,CHANNEL0,1,70);
////    FTM_PWM_set_duty(FTM_2,CHANNEL0,70);

////    ftm_pwm_init(FTM_2,CH_2,13000,5000);  //A0引脚输出50HZ PWM 占空比为百分之（500/FTM0_PRECISON*100）
////    ftm_pwm_init(FTM_2,CH_3,13000,5000);//能

//    ftm_pwm_init(FTM_2,CH_0,13000,3000);
////    ftm_pwm_init(FTM_2,CH_5,13000,5000);//能

////    Pin_Output_Config(PTC, PTC2, 1);
////    Pin_Output_Config(PTC, PTC3, 0);
////    Pin_Output_Config(PTB, PTB4, 1);
////    Pin_Output_Config(PTB, PTB5, 0);
//
////    ftm_pwm_init(FTM_0,CH_0,13000,8000);

////
////    ftm_pwm_init(FTM_0,CH_1,13000,2000);

//
//    while(1)
//    {
////        Delay_us(4);
////        Pin_Output_Toggle(PTD, PTD5);
////        Pin_Output_Toggle(PTH, PTH0);
////        Pin_Output_Toggle(PTH, PTH1);
////            printf("哈哈哈哈哈\r\n");

//
////        Delay_1us;
////		Delay_1us;
////		Delay_1us;
////        Delay_ms(20);
////        OLED_Show_StrAll(0, 0, "this:", 1);
////        OLED_Refresh_Gram();
//
//
////        printf("这是温度：%d \r\n", Read_Temperature());
////        Read_DMP();
////        printf("这是俯仰角：%f \r\n", Pitch);
////        printf("这是横滚角：%f \r\n", Roll);
//
////        Get_MPU_G();
////        printf("角速度X：%f \r\n", Gyro_X);
////        printf("角速度Y：%f \r\n", Gyro_Y);
////        printf("角速度Z：%f \r\n", Gyro_Z);
//
////        Get_MPU_A();
////        printf("加速度X：%f \r\n", Accel_X);
////        printf("加速度Y：%f \r\n", Accel_Y);
////        printf("加速度Z：%f \r\n", Accel_Z);

}

/********************************************************************************************
1、GPIO库弄好，OLED弄好。(17.11.18  20：03)
2、时钟莫名奇妙
3、串口重定义弄好。(11.18  21：39)
4、pit完全不行，中断一直都是0.625us。生成方波一直是800KHz (11.19  16：39)
5、先跳过PWT
6、系统滴答定时器OK，延时函数OK(11.19  17：20)
7、PIT OK！！！(11.19  19：32)
8、
9、OLED显示时，sprintf中有浮点数时会花屏。不勾选C/C++中One ELF Section per Function即可解决。（2017.12.7）







********************************************************************************************/
