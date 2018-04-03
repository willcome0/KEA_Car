#include "upper.h"
#include "uart.h"

/******************ֻ���� ����������λ������***********************/
#define BYTE0(Temp)       (*(char *) (&Temp))         //0-7λ
#define BYTE1(Temp)       (*((char *)(&Temp) + 1))  //8-15λ
#define BYTE2(Temp)       (*((char *)(&Temp) + 2))  //16-23λ
#define BYTE3(Temp)       (*((char *)(&Temp) + 3))  //24-31λ
/******************************************************************/



/******************����������λ������***********************/
//void pit_hander();
float Variable[20];


int test_data1 = 0;
int test_data2 = 0;
int test_data3 = 0;


void my_putchar(char temp)
{
    UART_Send_Char(UART_1, temp);
}

/*����֪ͨ��λ���µ�һ�����ݿ�ʼ��Ҫ�������ݱ��뷢����*/

void Send_Begin(void)
{
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xae);
}


void Send_Variable(void)
{
    uint8_t ch=0;
    float temp=0;
    uint8_t Variable_num=10;
    
    my_putchar(0x55);
    my_putchar(0xaa);
    my_putchar(0xad);
    my_putchar(Variable_num);

    for(uint8_t i=0; i<Variable_num; i++)
    {
        temp=Variable[i];
        ch=BYTE0(temp);
        my_putchar(ch);
        ch=BYTE1(temp);
        my_putchar(ch);
        ch=BYTE2(temp);
        my_putchar(ch);
        ch=BYTE3(temp);
        my_putchar(ch);
    }
    my_putchar(0x0d);
}

void Enable_Interrupt(uint8_t vector_number)
{

	NVIC_ClearPendingIRQ((IRQn_Type)vector_number); 		/* Clear pending interrupt register */
	NVIC_EnableIRQ((IRQn_Type)vector_number); 				/* Enable required Interrupt */

}
/******************************************************************/


/*************************************************************************
*�� �� ����usart1_report_imu()
*�������ܣ�����������λ������
*ʱ    �䣺2017.8.6
*��    ע��BYTE0(XX)ʲô����
			����취��http://blog.sina.com.cn/s/blog_a3e25cc70102vhs5.html
**************************************************************************/
//#define BYTE0(Temp)       (*(char *)(&Temp))     
//#define BYTE1(Temp)       (*((char *)(&Temp) + 1))
//#define BYTE2(Temp)       (*((char *)(&Temp) + 2))
//#define BYTE3(Temp)       (*((char *)(&Temp) + 3))
	

uint8_t data_to_send[50];	//�������ݻ���
void ANO_DT_Send_Data(uint8_t *dataToSend , uint8_t length)
{
////	Usart2_Send(data_to_send, length);
//	HAL_UART_Transmit(&huart1, dataToSend, length, 0xFFFF);
    printf((char *)dataToSend);
}
void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, int32_t alt, uint8_t fly_model, uint8_t armed)
{
	uint8_t _cnt=0;
	__IO int16_t _temp;
	__IO int32_t _temp2 = alt;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	
	_temp = (int)(angle_rol*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_pit*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	
	data_to_send[_cnt++] = fly_model;
	
	data_to_send[_cnt++] = armed;
	
	data_to_send[3] = _cnt-4;
	
	uint8_t sum = 0;
	for(uint8_t i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	ANO_DT_Send_Data(data_to_send, _cnt);
}
void ANO_DT_Send_Senser(int16_t a_x,int16_t a_y,int16_t a_z,int16_t g_x,int16_t g_y,int16_t g_z,int16_t m_x,int16_t m_y,int16_t m_z,int32_t bar)
{
	uint8_t _cnt=0;
	__IO int16_t _temp;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	
	_temp = a_x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = g_x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = m_x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	uint8_t sum = 0;
	for(uint8_t i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	
	ANO_DT_Send_Data(data_to_send, _cnt);
}
/******************************************************************/

//�������ȡ�Ƕȷ���ѭ���Ｔ��
//	ANO_DT_Send_Status(Roll, Pitch, Yaw, 1, 1, 1);
//	ANO_DT_Send_Senser(Accel_X,Accel_Y,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z,1,1,1,0);
