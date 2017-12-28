#include "upper.h"
#include "uart.h"


#define BYTE0(Temp)       (*(char *)(&Temp))     
#define BYTE1(Temp)       (*((char *)(&Temp) + 1))
#define BYTE2(Temp)       (*((char *)(&Temp) + 2))
#define BYTE3(Temp)       (*((char *)(&Temp) + 3))

void pit_hander();
float Variable[20];


int test_data1 = 0;
int test_data2 = 0;
int test_data3 = 0;


void my_putchar(char temp)
{
    UART_Send_Char(UART_1, temp);
}

/*用来通知上位机新的一组数据开始，要保存数据必须发送它*/

void Send_Begin()
{
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xae);
}


void Send_Variable()
{
    uint8_t ch=0;
    float temp=0;
    uint8_t Variable_num=6;
    
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


