#include "Init.h"



void All_Init(void)
{
    Buzzer_Init();	// ��������ʼ��
	FLASH_Init();	// flash�洢��ʼ��
//	
////	Cache_ALL_DATA(); 			// ��������flash�е����ݵ�����
////	_Com_CountDown_ = 1;
////	_Com_Debug_ = 1; 		// �������´��ν��������Ա��ֵ
////	FLASH_Erase_All_Data(); 	// ��ȫ���������ݵ���Ҷ
////	FLASH_Write_All_Data();		// д���������ݵ������ݵ���Ҷ
//	
	Data_Init();	// ϵͳ������ʼ��
//	
	Beep_ON();
	Delay_ms(50);
	Beep_OFF();
//    	
    UART_Init(UART_1, 9600);
    LED_Init();



    OLED_Init();      //OLED��ʼ��
    OLED_Display_Off();
    Motor_Init();     //�����ʼ��
	while(MPU_Init());
	while(mpu_dmp_init());
	PIT_Config(PIT_CH0, CON_PERIOD, 0);
//	
    Encoder_Init();   //��������ʼ��
    KEY_Init();
    AD_Init();        //���AD��ʼ��



    kalman1_init(&AD_Kalman[0],0,10);
    AD_Kalman[0].q = 9e-4;//��ʼ�������������Ϳ���
    AD_Kalman[0].r = 1e-2;

    kalman1_init(&AD_Kalman[1],0,10);
    AD_Kalman[1].q = 9e-4;
    AD_Kalman[1].r = 1e-2;

//    Delay_ms(10);
//    IIC_init();
//    while (MPU6050_Init());
//	Delay_ms(10);
//	while (MPU6050_Init());
//	


//    


	OLED_Clear();
	
	OLED_Display_On();
}
