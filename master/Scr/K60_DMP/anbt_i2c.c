
#include "common.h"
////#include "MK60_i2c.h"
////#include "MK60_gpio.h"
#include "anbt_i2c.h"


#define u8 uint8_t
#define u32 uint32_t

//////#define I2C_SCL        PTE26
//////#define I2C_SDA        PTE27

#define SCL_H         Pin_Output_Config(SCL_Port, SCL_Pin, 1)
#define SCL_L         Pin_Output_Config(SCL_Port, SCL_Pin, 0)
//////#define SCL_DDR_OUT   PTXn_T(I2C_SCL,DDR) = 1
//////#define SCL_DDR_IN    PTXn_T(I2C_SCL,DDR) = 0

#define SDA_H         Pin_Output_Config(SDA_Port, SDA_Pin, 1)
#define SDA_L         Pin_Output_Config(SDA_Port, SDA_Pin, 0)
#define SDA_IN        Read_Input_State(SDA_Port, SDA_Pin)
//////#define SDA_DDR_OUT   PTXn_T(I2C_SDA,DDR) = 1
//////#define SDA_DDR_IN    PTXn_T(I2C_SDA,DDR) = 0
/*************************************************************************************************************
Բ�㲩ʿС���������2014������Դ��������:
��Դ��������ο�,Բ�㲩ʿ����Դ�����ṩ�κ���ʽ�ĵ���,Ҳ������ʹ�ø�Դ��������ֵ���ʧ����.
�û�������ѧϰ��Ŀ���޸ĺ�ʹ�ø�Դ����.
���û����޸ĸ�Դ����ʱ,�����Ƴ��ò��ְ�Ȩ��Ϣ�����뱣��ԭ������.

������Ϣ������ʹٷ���վwww.etootle.com, �ٷ�����:http://weibo.com/xiaosizhou
**************************************************************************************************************/

static void I2C_delay(void)
{
    volatile int i = 7;
    while (i)
        i--;
}

//////void ANBT_I2C_Delay(u32 dly)               
//////{
//////	while(--dly);	//dly=100: 8.75us; dly=100: 85.58 us (SYSCLK=72MHz)
//////}

uint8_t ANBT_I2C_START(void)
{
//    gpio_init  (I2C_SCL, GPO, 1); //��ʼ��SCL
//    gpio_init  (I2C_SDA, GPO, 1); //��ʼ��SDA

//    port_init_NoALT(I2C_SCL,ODO | PULLUP);
//    port_init_NoALT(I2C_SDA,ODO | PULLUP);
    
    Pin_Output_Config(SCL_Port, SCL_Pin, 1);
    Pin_Output_Config(SDA_Port, SDA_Pin, 1);
         
     SDA_H;
    SCL_H;
    I2C_delay();
    if (SDA_IN == 0)//Ϊ�ͽ���
        return 0;
    SDA_L;
    I2C_delay();
    if (SDA_IN != 0)//Ϊ�߽���
        return 0;
    SDA_L;
    I2C_delay();
    return 1; 
}

void ANBT_I2C_STOP(void)
{
 	ANBT_I2C_SDA_0; 
 	ANBT_I2C_NOP;
  // 
 	ANBT_I2C_SCL_1; 
 	ANBT_I2C_NOP;    
	//
 	ANBT_I2C_SDA_1;
 	ANBT_I2C_NOP;
}

void ANBT_I2C_SendACK(void)
{
 	ANBT_I2C_SDA_0;
 	ANBT_I2C_NOP;
 	ANBT_I2C_SCL_1;
 	ANBT_I2C_NOP;
 	ANBT_I2C_SCL_0; 
 	ANBT_I2C_NOP;  
}

void ANBT_I2C_SendNACK(void)
{
	ANBT_I2C_SDA_1;
	ANBT_I2C_NOP;
	ANBT_I2C_SCL_1;
	ANBT_I2C_NOP;
	ANBT_I2C_SCL_0; 
	ANBT_I2C_NOP;  
}

u8 ANBT_I2C_SendByte(u8 anbt_i2c_data)
{
 	u8 i;
 	
	ANBT_I2C_SCL_0;
 	for(i=0;i<8;i++)
 	{  
  		if(anbt_i2c_data&0x80)
        {
            ANBT_I2C_SDA_1;
        }
   		else
        {
            ANBT_I2C_SDA_0;
        }
			//
  		anbt_i2c_data<<=1;
  		ANBT_I2C_NOP;
			//
  		ANBT_I2C_SCL_1;
  		ANBT_I2C_NOP;
  		ANBT_I2C_SCL_0;
  		ANBT_I2C_NOP; 
 	}
	//
 	ANBT_I2C_SDA_1; 
 	ANBT_I2C_NOP;
 	ANBT_I2C_SCL_1;
 	ANBT_I2C_NOP;   
 	if(SDA_IN != 0)//Ϊ�߽���
 	{
  		ANBT_I2C_SCL_0;
  		return ANBT_I2C_NACK;
 	}
 	else
 	{
  		ANBT_I2C_SCL_0;
  		return ANBT_I2C_ACK;  
 	}    
}

u8 ANBT_I2C_ReceiveByte(void)
{
	u8 i,anbt_i2c_data;
	//
 	ANBT_I2C_SDA_1;
 	ANBT_I2C_SCL_0; 
 	anbt_i2c_data=0;
	//
 	for(i=0;i<8;i++)
 	{
  		ANBT_I2C_SCL_1;
  		ANBT_I2C_NOP; 
  		anbt_i2c_data<<=1;
			//
  		if(SDA_IN != 0)//Ϊ�߽���
            anbt_i2c_data|=0x01; 
  
  		ANBT_I2C_SCL_0;  
  		ANBT_I2C_NOP;         
 	}
	ANBT_I2C_SendNACK();
 	return anbt_i2c_data;
}

u8 ANBT_I2C_ReceiveByte_WithACK(void)
{
	u8 i,anbt_i2c_data;
	//
 	ANBT_I2C_SDA_1;
 	ANBT_I2C_SCL_0; 
 	anbt_i2c_data=0;
	//
 	for(i=0;i<8;i++)
 	{
  		ANBT_I2C_SCL_1;
  		ANBT_I2C_NOP; 
  		anbt_i2c_data<<=1;
			//
  		if(SDA_IN != 0)//Ϊ�߽���
            anbt_i2c_data|=0x01; 
  
  		ANBT_I2C_SCL_0;  
  		ANBT_I2C_NOP;         
 	}
	ANBT_I2C_SendACK();
 	return anbt_i2c_data;
}

void ANBT_I2C_Receive6Bytes(u8 *anbt_i2c_data_buffer)
{
	u8 i,j;
	u8 anbt_i2c_data;

	for(j=0;j<5;j++)
	{
		ANBT_I2C_SDA_1;
		ANBT_I2C_SCL_0; 
		anbt_i2c_data=0;
		//
		for(i=0;i<8;i++)
		{
  		ANBT_I2C_SCL_1;
  		ANBT_I2C_NOP; 
  		anbt_i2c_data<<=1;
			//
  		if(SDA_IN != 0)//Ϊ�߽���
            anbt_i2c_data|=0x01; 
  
  		ANBT_I2C_SCL_0;  
  		ANBT_I2C_NOP;         
		}
		anbt_i2c_data_buffer[j]=anbt_i2c_data;
		ANBT_I2C_SendACK();
	}
	//
	ANBT_I2C_SDA_1;
	ANBT_I2C_SCL_0; 
	anbt_i2c_data=0;
	for(i=0;i<8;i++)
	{
  	ANBT_I2C_SCL_1;
  	ANBT_I2C_NOP; 
  	anbt_i2c_data<<=1;
			//
  	if(SDA_IN != 0)//Ϊ�߽���
        anbt_i2c_data|=0x01; 
  
  	ANBT_I2C_SCL_0;  
  	ANBT_I2C_NOP;         
	}
	anbt_i2c_data_buffer[5]=anbt_i2c_data;
	ANBT_I2C_SendNACK();
}

void ANBT_I2C_Receive12Bytes(u8 *anbt_i2c_data_buffer)
{
	u8 i,j;
	u8 anbt_i2c_data;

	for(j=0;j<11;j++)
	{
		ANBT_I2C_SDA_1;
		ANBT_I2C_SCL_0; 
		anbt_i2c_data=0;
		//
		for(i=0;i<8;i++)
		{
  		ANBT_I2C_SCL_1;
  		ANBT_I2C_NOP; 
  		anbt_i2c_data<<=1;
			//
  		if(SDA_IN != 0)//Ϊ�߽���
            anbt_i2c_data|=0x01; 
  
  		ANBT_I2C_SCL_0;  
  		ANBT_I2C_NOP;         
		}
		anbt_i2c_data_buffer[j]=anbt_i2c_data;
		ANBT_I2C_SendACK();
	}
	//
	ANBT_I2C_SDA_1;
	ANBT_I2C_SCL_0; 
	anbt_i2c_data=0;
	for(i=0;i<8;i++)
	{
  	ANBT_I2C_SCL_1;
  	ANBT_I2C_NOP; 
  	anbt_i2c_data<<=1;
			//
  	if(SDA_IN != 0)//Ϊ�߽���
        anbt_i2c_data|=0x01; 
  
  	ANBT_I2C_SCL_0;  
  	ANBT_I2C_NOP;         
	}
	anbt_i2c_data_buffer[11]=anbt_i2c_data;
	ANBT_I2C_SendNACK();
}

void ANBT_I2C_Receive14Bytes(u8 *anbt_i2c_data_buffer)
{
	u8 i,j;
	u8 anbt_i2c_data;

	for(j=0;j<13;j++)
	{
		ANBT_I2C_SDA_1;
		ANBT_I2C_SCL_0; 
		anbt_i2c_data=0;
		//
		for(i=0;i<8;i++)
		{
  		ANBT_I2C_SCL_1;
  		ANBT_I2C_NOP; 
  		anbt_i2c_data<<=1;
			//
  		if(SDA_IN != 0)//Ϊ�߽���
            anbt_i2c_data|=0x01; 
  
  		ANBT_I2C_SCL_0;  
  		ANBT_I2C_NOP;         
		}
		anbt_i2c_data_buffer[j]=anbt_i2c_data;
		ANBT_I2C_SendACK();
	}
	//
	ANBT_I2C_SDA_1;
	ANBT_I2C_SCL_0; 
	anbt_i2c_data=0;
	for(i=0;i<8;i++)
	{
  	ANBT_I2C_SCL_1;
  	ANBT_I2C_NOP; 
  	anbt_i2c_data<<=1;
			//
  	if(SDA_IN != 0)//Ϊ�߽���
        anbt_i2c_data|=0x01; 
  
  	ANBT_I2C_SCL_0;  
  	ANBT_I2C_NOP;         
	}
	anbt_i2c_data_buffer[13]=anbt_i2c_data;
	ANBT_I2C_SendNACK();
}

void AnBT_DMP_Delay_us(uint32_t dly)
{
	uint8_t i;
	while(dly--) for(i=0;i<10;i++);
}
//
void AnBT_DMP_Delay_ms(uint32_t dly)
{
	while(dly--) AnBT_DMP_Delay_us(1000);
}
//

uint8_t AnBT_DMP_I2C_Write(uint8_t anbt_dev_addr, uint8_t anbt_reg_addr, uint8_t anbt_i2c_len, uint8_t *anbt_i2c_data_buf)
{		
		uint8_t i;
		ANBT_I2C_START();
		ANBT_I2C_SendByte(anbt_dev_addr << 1 | 0x00);					//Բ�㲩ʿ:����������д��ַ
		ANBT_I2C_SendByte(anbt_reg_addr);  //Բ�㲩ʿ:����������PWM��ַ
		for (i=0;i<anbt_i2c_len;i++) ANBT_I2C_SendByte(anbt_i2c_data_buf[i]); //Բ�㲩ʿ:����������PWMֵ
		ANBT_I2C_STOP();
		return 0x00;
}
u8 AnBT_DMP_I2C_Read(u8 anbt_dev_addr, u8 anbt_reg_addr, u8 anbt_i2c_len, u8 *anbt_i2c_data_buf)
{
	
		ANBT_I2C_START();
		ANBT_I2C_SendByte(anbt_dev_addr << 1 | 0x00);			//Բ�㲩ʿ:����������д��ַ
		ANBT_I2C_SendByte(anbt_reg_addr);  //Բ�㲩ʿ:����������ID��ַ
		ANBT_I2C_START();
		ANBT_I2C_SendByte(anbt_dev_addr << 1 | 0x01);      //Բ�㲩ʿ:���������Ƕ���ַ
		//
    while (anbt_i2c_len)
		{
			if (anbt_i2c_len==1) *anbt_i2c_data_buf =ANBT_I2C_ReceiveByte();  
      else *anbt_i2c_data_buf =ANBT_I2C_ReceiveByte_WithACK();
      anbt_i2c_data_buf++;
      anbt_i2c_len--;
    }
		ANBT_I2C_STOP();
    return 0x00;
}
