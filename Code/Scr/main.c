//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
#define GLOBLE_VAR  //ֻ����main.c�ж���һ�Σ�������ֹȫ�ֱ������ظ�����
#include "includes.h"
#include "common.h"

#include "pit.h"
#include "math.h"

//#include  "anbt_i2c.h"
//#include  "anbt_dmp_mpu6050.h"
//#include  "anbt_dmp_driver.h"






//�������˲������뺯��
//float dt=0.001;//ע�⣺dt��ȡֵΪkalman�˲�������ʱ��
//float angle, angle_dot;//�ǶȺͽ��ٶ�
//float P[2][2] = {{ 1, 0 },
//                 { 0, 1 }};
//float Pdot[4] ={ 0,0,0,0};
//float Q_angle=0.001, Q_gyro=0.005; //�Ƕ��������Ŷ�,���ٶ��������Ŷ�
//float R_angle=0.5 ,C_0 = 1;
//float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;

////�������˲�
//float Kalman_Filter(float angle_m, float gyro_m)//angleAx �� gyroGy
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
//        angle += K_0 * angle_err; //���ŽǶ�
//        q_bias += K_1 * angle_err;
//        angle_dot = gyro_m-q_bias;//���Ž��ٶ�

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
	
//    ftm_pwm_init(ftm2,ftm_ch0,12500,0);//����ת//����ת���Ժ�ʹ��
//    ftm_pwm_init(ftm2,ftm_ch5,12500,300);
//
//    ftm_pwm_init(ftm2,ftm_ch2,12500,0);
//    ftm_pwm_init(ftm2,ftm_ch3,12500,300);//��


//    FTM_PWM_init(FTM_2, CH_0, 12.5, 20);   //APWM_2  PC0   FTM2_CH0   ��   ��
//    FTM_PWM_init(FTM_2, CH_5, 12.5, 1);    //APWM_1  PB5   FTM2_CH5

//    FTM_PWM_init(FTM_2, CH_2, 12.5, 20);    //BPWM_2  PC2   FTM2_CH2   ��   ��
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



//    Pin_Output_Config(PTE, PTE0, 1);//�����������������



//    Just_Do_It();







//    PIT_Config(PIT_CH0, 8, 0);//8ms�ж�
//    PIT_Config(PIT_CH1, 10, 0);
//LED_Blue_ON();
//    Pin_Output_Config(PTE, PTE0, 1);//��ƽ��ת����



		
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

//        MPU6050_GetData(&GYRO, &ACC);	// ��ȡ����������
//        Data_Filter();					// ��ԭʼ���ݻ����˲�
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



//     								MPU6050_GetData(&GYRO, &ACC);   //��ȡԭʼ����
//								Data_Filter();     //ԭʼ�����˲�
//								Get_Attitude();    //��ȡ��̬
//        sprintf(str, "PITCH: %3.2f    ", Pitch);
//        OLED_Show_Str(0, 20, str, 12, 1);
//        OLED_Refresh_Gram();

//        if((Read_Input_State(KEY_Left_Port, KEY_Left_Pin)==0) || (Read_Input_State(KEY_Up_Port, KEY_Up_Pin)==0) || (Read_Input_State(KEY_Down_Port, KEY_Down_Pin)==0))
//            LED_Green_ON();
//        else
//            LED_Green_OFF();
//        Get_Key();

/******************��ʾ���Դ���**********************/
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

//                printf("��ʹ�ˣ���\r\n");
//        /*********while ����*****************/
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
////    Pin_Output_Config(PTE, PTE4, 1);//ͨ��5
////    Pin_Output_Config(PTG, PTG6, 1);//ͨ��5
////    Pin_Output_Config(PTG, PTG5, 1);//ͨ��6
//    Pin_Output_Config(PTG, PTG4, 1);//ͨ��7
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

////    ftm_pwm_init(FTM_2,CH_2,13000,5000);  //A0�������50HZ PWM ռ�ձ�Ϊ�ٷ�֮��500/FTM0_PRECISON*100��
////    ftm_pwm_init(FTM_2,CH_3,13000,5000);//��

//    ftm_pwm_init(FTM_2,CH_0,13000,3000);
////    ftm_pwm_init(FTM_2,CH_5,13000,5000);//��

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
////            printf("����������\r\n");

//
////        Delay_1us;
////		Delay_1us;
////		Delay_1us;
////        Delay_ms(20);
////        OLED_Show_StrAll(0, 0, "this:", 1);
////        OLED_Refresh_Gram();
//
//
////        printf("�����¶ȣ�%d \r\n", Read_Temperature());
////        Read_DMP();
////        printf("���Ǹ����ǣ�%f \r\n", Pitch);
////        printf("���Ǻ���ǣ�%f \r\n", Roll);
//
////        Get_MPU_G();
////        printf("���ٶ�X��%f \r\n", Gyro_X);
////        printf("���ٶ�Y��%f \r\n", Gyro_Y);
////        printf("���ٶ�Z��%f \r\n", Gyro_Z);
//
////        Get_MPU_A();
////        printf("���ٶ�X��%f \r\n", Accel_X);
////        printf("���ٶ�Y��%f \r\n", Accel_Y);
////        printf("���ٶ�Z��%f \r\n", Accel_Z);

}

/********************************************************************************************
1��GPIO��Ū�ã�OLEDŪ�á�(17.11.18  20��03)
2��ʱ��Ī������
3�������ض���Ū�á�(11.18  21��39)
4��pit��ȫ���У��ж�һֱ����0.625us�����ɷ���һֱ��800KHz (11.19  16��39)
5��������PWT
6��ϵͳ�δ�ʱ��OK����ʱ����OK(11.19  17��20)
7��PIT OK������(11.19  19��32)
8��
9��OLED��ʾʱ��sprintf���и�����ʱ�Ứ��������ѡC/C++��One ELF Section per Function���ɽ������2017.12.7��







********************************************************************************************/
