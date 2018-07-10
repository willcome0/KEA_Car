#ifndef __MY_I2C_H__
#define __MY_I2C_H__
#include "common.h"

//�Լ���
#define SCL_Port   PTA
#define SCL_Pin    PTA3
#define SDA_Port   PTA
#define SDA_Pin    PTA2




//#define MPU_SDA_OUT()		Read_Input_State(SDA_Port, SDA_Pin)
#define MPU_IIC_SDA_L()		Pin_Output_Config(SDA_Port, SDA_Pin, 0)	// IO������͵�ƽ
#define MPU_IIC_SDA_H()		Pin_Output_Config(SDA_Port, SDA_Pin, 1)	// IO������ߵ�ƽ  
#define MPU_IIC_SCL_L()    	Pin_Output_Config(SCL_Port, SCL_Pin, 0)	// IO������͵�ƽ
#define MPU_IIC_SCL_H()		Pin_Output_Config(SCL_Port, SCL_Pin, 1)	// IO������ߵ�ƽ

#define MPU_SDA_OUT()	Pin_Output_Config(SDA_Port, SDA_Pin, 1)	// �������
#define MPU_SDA_IN()   	Pin_Input_Config(SDA_Port, SDA_Pin, 1)	// ���뷽��


//IO��������	 
//#define MPU_IIC_SCL    PBout(8) 		//SCL
//#define MPU_IIC_SDA    PBout(9) 		//SDA	 
#define MPU_READ_SDA   Read_Input_State(SDA_Port, SDA_Pin) 		//����SDA 

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
