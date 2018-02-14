#include "Init.h"

void All_Init(void)
{
    Buzzer_Init();
	FLASH_Init();
	Data_Init();
	
    Beep_Time(50);
    UART_Init(UART_1, 9600);
    LED_Init();



    OLED_Init();      //OLED初始化
    OLED_Display_Off();
    Motor_Init();     //电机初始化

//    Encoder_Init();   //编码器初始化
    KEY_Init();
//    AD_Init();        //电磁AD初始化

    kalman1_init(&AD_Kalman[0],0,10);
    AD_Kalman[0].q = 9e-4;//初始调这两个参数就可以
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
