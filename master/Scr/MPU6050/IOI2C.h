#ifndef __IOI2C_H
#define __IOI2C_H

#include "common.h"
#include "SKEAZ1284.h"

//�ٷ���
#define SCL_Port   PTA
#define SCL_Pin    PTA3
#define SDA_Port   PTA
#define SDA_Pin    PTA2

////�Լ���
//#define SCL_Port   PTA
//#define SCL_Pin    PTA3
//#define SDA_Port   PTA
//#define SDA_Pin    PTA2

//IO��������
#define SDA_IN()     Pin_Input_Config(SDA_Port, SDA_Pin, 1)//����ģʽ
#define SDA_OUT()    Pin_Output_Config(SDA_Port, SDA_Pin, 1)//���ģʽ

//IO��������	 


#define IIC_SCL_H    Pin_Output_Config(SCL_Port, SCL_Pin, 1)
#define IIC_SCL_L    Pin_Output_Config(SCL_Port, SCL_Pin, 0)
#define IIC_SDA_H    Pin_Output_Config(SDA_Port, SDA_Pin, 1)
#define IIC_SDA_L    Pin_Output_Config(SDA_Port, SDA_Pin, 0)

#define READ_SDA     Read_Input_State(SDA_Port, SDA_Pin)

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
int IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
int IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 
unsigned char I2C_Readkey(unsigned char I2C_Addr);

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data);
u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data);
u8 IICwriteBit(u8 dev,u8 reg,u8 bitNum,u8 data);
u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data);

int i2cWrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

#endif

//------------------End of File----------------------------
