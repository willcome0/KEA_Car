#include "data.h"

uint16_t uint16_TMEP = 0;

struct PLAN Plan1 = 
    {
        .Target.Angle = 30,
        .Target.Speed = 130,//200
        
        .Angle.P  = 640,//220
        .Angle.D  = 15,//60
        
        .Speed.P  = 0,//-400...-22
        .Speed.I  = 0,//-5
         
        .Turn.P   = 140,//50
        .Turn.D   = 30,//0.1
			
        .Turn.tp   = 10,//50  ��������ƫ��С����ƫ   -20�������   20�ҹ����  
        .Turn.td   = 1,//0  ���ֲ���
        .Safe_Angle = 38,
    };
//struct PLAN Plan1 = 
//    {
//        .Target.Angle = -20,
//        .Target.Speed = 80,//200
//        
//        .Angle.P  = 359,//220
//        .Angle.D  = 100,//60
//        
//        .Speed.P  = 600,//-400
//        .Speed.I  = -734,//-5
//         
//        .Turn.P   = 642,//50
//        .Turn.D   = 20,//0.1
//			
//        .Turn.tp   = 2,//50  ��������ƫ��С����ƫ   -20�������   20�ҹ����  
//        .Turn.td   = 1,//0  ���ֲ���
//        .Safe_Angle = 38,
//    };
struct PLAN Blue = 
    {
        .Target.Angle = 1,
        .Target.Speed = 1,
        
        .Angle.P  = 1,//ֱ������570//862
        .Angle.D  = 1,//180//201
        
        .Speed.P  = 1,
        .Speed.I  = 1,
         
        .Turn.P   = 1,
        .Turn.D   = 1,
        
        .Safe_Angle = 1,
    };
struct CON  Con;
	
void Data_Init(void)
{
	Cache_ALL_DATA();
	
}
int16_t Add_L = -50;



/*���ò˵�����*/
uint8_t Set_LED = 1;
uint8_t Set_Beep = 1;
uint8_t Bluetooth = 0;
    


volatile int16_t 	Value_End 	= 0;

/*********������̬���ȫ�ֱ���*********/

volatile int16_t 	Accel_X 	= 0;
volatile int16_t 	Accel_Y 	= 0;
volatile int16_t 	Accel_Z 	= 0;
volatile int16_t 	Gyro_X 		= 0;
volatile int16_t 	Gyro_Y 		= 0;
volatile int16_t 	Gyro_Z 		= 0;
volatile float 		Pitch 		= 0;
volatile float 		Roll 		= 0;
volatile float 		Yaw 		= 0;

uint32_t ABS(int32_t Num)
{
    return Num<0?-Num:Num;
}



