#ifndef __IOI2C_H
#define __IOI2C_H

#include "common.h"
#include "SKEAZ1284.h"

//官方板
#define SCL_Port   PTA
#define SCL_Pin    PTA3
#define SDA_Port   PTA
#define SDA_Pin    PTA2

////自己板
//#define SCL_Port   PTA
//#define SCL_Pin    PTA3
//#define SDA_Port   PTA
//#define SDA_Pin    PTA2

//IO方向设置
#define SDA_IN()     Pin_Input_Config(SDA_Port, SDA_Pin, 1)//输入模式
#define SDA_OUT()    Pin_Output_Config(SDA_Port, SDA_Pin, 1)//输出模式

//IO操作函数	 


#define IIC_SCL_H    Pin_Output_Config(SCL_Port, SCL_Pin, 1)
#define IIC_SCL_L    Pin_Output_Config(SCL_Port, SCL_Pin, 0)
#define IIC_SDA_H    Pin_Output_Config(SDA_Port, SDA_Pin, 1)
#define IIC_SDA_L    Pin_Output_Config(SDA_Port, SDA_Pin, 0)

#define READ_SDA     Read_Input_State(SDA_Port, SDA_Pin)

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
int IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
int IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

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
