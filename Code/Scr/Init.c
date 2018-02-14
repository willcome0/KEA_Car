#include "Init.h"

void All_Init(void)
{
    Buzzer_Init();
	FLASH_Init();
	Data_Init();
	
    Beep_Time(50);
    UART_Init(UART_1, 9600);
    LED_Init();



    OLED_Init();      //OLED��ʼ��
    OLED_Display_Off();
    Motor_Init();     //�����ʼ��

//    Encoder_Init();   //��������ʼ��
    KEY_Init();
//    AD_Init();        //���AD��ʼ��

    kalman1_init(&AD_Kalman[0],0,10);
    AD_Kalman[0].q = 9e-4;//��ʼ�������������Ϳ���
    AD_Kalman[0].r = 1e-2;//

    kalman1_init(&AD_Kalman[1],0,10);
    AD_Kalman[1].q = 9e-4;
    AD_Kalman[1].r = 1e-2;

    Delay_ms(10);
    IIC_init();
    while (MPU6050_Init());
	
	Beep_Time(100);
    

	
	OLED_Clear();
	
	OLED_Display_On();
}
