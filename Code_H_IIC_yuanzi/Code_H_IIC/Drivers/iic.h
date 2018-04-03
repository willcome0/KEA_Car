#ifndef __IIC_H
#define __IIC_H
#include "common.h"

//自己板
#define SCL_Port   PTA
#define SCL_Pin    PTA3
#define SDA_Port   PTA
#define SDA_Pin    PTA2




//#define MPU_SDA_OUT()		Read_Input_State(SDA_Port, SDA_Pin)
#define MPU_IIC_SDA_L()		Pin_Output_Config(SDA_Port, SDA_Pin, 0)	// IO口输出低电平
#define MPU_IIC_SDA_H()		Pin_Output_Config(SDA_Port, SDA_Pin, 1)	// IO口输出高电平  
#define MPU_IIC_SCL_L()    	Pin_Output_Config(SCL_Port, SCL_Pin, 0)	// IO口输出低电平
#define MPU_IIC_SCL_H()		Pin_Output_Config(SCL_Port, SCL_Pin, 1)	// IO口输出高电平

#define MPU_SDA_OUT()	Pin_Output_Config(SDA_Port, SDA_Pin, 1)	// 输出方向
#define MPU_SDA_IN()   	Pin_Input_Config(SDA_Port, SDA_Pin, 1)	// 输入方向


//IO操作函数	 
//#define MPU_IIC_SCL    PBout(8) 		//SCL
//#define MPU_IIC_SDA    PBout(9) 		//SDA	 
#define MPU_READ_SDA   Read_Input_State(SDA_Port, SDA_Pin) 		//输入SDA 

//IIC所有操作函数
void MPU_IIC_Delay(void);				//MPU IIC延时函数
void MPU_IIC_Init(void);                //初始化IIC的IO口				 
void MPU_IIC_Start(void);				//发送IIC开始信号
void MPU_IIC_Stop(void);	  			//发送IIC停止信号
void MPU_IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t MPU_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void MPU_IIC_Ack(void);					//IIC发送ACK信号
void MPU_IIC_NAck(void);				//IIC不发送ACK信号

void IMPU_IC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
