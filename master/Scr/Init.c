#include "Init.h"



void All_Init(void)
{
    Buzzer_Init();	// ��������ʼ��
	LED_Init();
	FLASH_Init();	// flash�洢��ʼ��
	
//	Cache_ALL_DATA(); 			// ��������flash�е����ݵ�����
//	_Com_CountDown_ = 1;
//	_Com_Debug_ = 1; 		// �������´��ν��������Ա��ֵ
//	_Com_Buzzer_ = 1;
//	_Com_LED_ = 1;
//	FLASH_Erase_All_Data(); 	// ��ȫ���������ݵ���Ҷ
//	FLASH_Write_All_Data();		// д���������ݵ������ݵ���Ҷ
	
	Data_Init();	// ϵͳ������ʼ��
	

    	
    UART_Init(UART_1, 115200);
    
//	Pin_Output_Config(PTD,  PTD0,  1);
//	while(1)
//	{
//		Pin_Output_Set(PTD,   PTD0,   RESET);
//		Delay_ms(1000);
//		Pin_Output_Set(PTD,   PTD0,     SET);
//		Delay_ms(1000);
//	}

    OLED_Init();      //OLED��ʼ��
    OLED_Display_Off();
    Motor_Init();     //�����ʼ��


	
    Encoder_Init();   //��������ʼ��
    KEY_Init();
    AD_Init();        //���AD��ʼ��



    kalman1_init(&AD_Kalman[0],0,10);
    AD_Kalman[0].q = 9e-4;//��ʼ�������������Ϳ���
    AD_Kalman[0].r = 1e-2;

    kalman1_init(&AD_Kalman[1],0,10);
    AD_Kalman[1].q = 9e-4;
    AD_Kalman[1].r = 1e-2;


////    IIC_init();
////    while (MPU6050_Init());
////	Delay_ms(10);
////	while (MPU6050_Init());
	while(MPU_Init());
	
	
	OLED_Clear();
	OLED_Display_On();
	Beep_Time(100);
	
	
	
		
	PIT_Config(PIT_CH0, CON_PERIOD, 0);

    Delay_ms(1000);
	Pin_Output_Set(LED_Red_Port, LED_Red_Pin, SET);
}
