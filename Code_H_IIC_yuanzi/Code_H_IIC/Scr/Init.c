#include "Init.h"



void All_Init(void)
{
    Buzzer_Init();	// 蜂鸣器初始化
	FLASH_Init();	// flash存储初始化
//	
////	Cache_ALL_DATA(); 			// 缓存所有flash中的数据到数组
////	_Com_CountDown_ = 1;
////	_Com_Debug_ = 1; 		// 单独更新传参进的数组成员的值
////	FLASH_Erase_All_Data(); 	// 完全擦除存数据的扇叶
////	FLASH_Write_All_Data();		// 写入所有数据到存数据的扇叶
//	
	Data_Init();	// 系统变量初始化
//	
	Beep_ON();
	Delay_ms(50);
	Beep_OFF();
//    	
    UART_Init(UART_1, 9600);
    LED_Init();



    OLED_Init();      //OLED初始化
    OLED_Display_Off();
    Motor_Init();     //电机初始化
	while(MPU_Init());
	while(mpu_dmp_init());
	PIT_Config(PIT_CH0, CON_PERIOD, 0);
//	
    Encoder_Init();   //编码器初始化
    KEY_Init();
    AD_Init();        //电磁AD初始化



    kalman1_init(&AD_Kalman[0],0,10);
    AD_Kalman[0].q = 9e-4;//初始调这两个参数就可以
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
