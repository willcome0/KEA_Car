//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
#define GLOBLE_VAR  //ֻ����main.c�ж���һ�Σ�������ֹȫ�ֱ������ظ�����
#include "includes.h"
#include "common.h"

#include "pit.h"
#include "math.h"



//I2C_Type* pI2C0 = (I2C_Type*)I2C0;

int main(void)
{
	All_Init();
	
	Delay_ms(100);
	/*************************************/

	

	/*************************************/
	
	Delay_ms(100);
	while(mpu6050_init());
	
	Beep_Time(1000);
	
	uint8_t GO = 0;
    while(1)
    {	
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
    }

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
