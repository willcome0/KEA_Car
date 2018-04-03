//说明见工程文件夹下的Doc文件夹内Readme.txt文件
#define GLOBLE_VAR  //只需在main.c中定义一次，用来防止全局变量的重复定义
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
