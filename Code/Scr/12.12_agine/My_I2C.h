#ifndef __MY_I2C_H__
#define __MY_I2C_H__
#include "common.h"
//#include "include.h"

#define My_SCL	PTD8	// ����SCL����
#define My_SDA	PTD9	// ����SDA����

#define ack 1      //��Ӧ��
#define no_ack 0   //��Ӧ��

typedef enum IIC
{
    IIC,
    SCCB
} IIC_type;

//�Լ���
#define SCL_Port   PTA
#define SCL_Pin    PTA3
#define SDA_Port   PTA
#define SDA_Pin    PTA2

#define SDA        	Read_Input_State(SDA_Port, SDA_Pin)
#define SDA0()     	Pin_Output_Config(SDA_Port, SDA_Pin, 0)	// IO������͵�ƽ
#define SDA1()     	Pin_Output_Config(SDA_Port, SDA_Pin, 1)	// IO������ߵ�ƽ  
#define SCL0()    	Pin_Output_Config(SCL_Port, SCL_Pin, 0)	// IO������͵�ƽ
#define SCL1()		Pin_Output_Config(SCL_Port, SCL_Pin, 1)	// IO������ߵ�ƽ
#define DIR_OUT()	Pin_Output_Config(SDA_Port, SDA_Pin, 1)	// �������
#define DIR_IN()   	Pin_Input_Config(SDA_Port, SDA_Pin, 1)	// ���뷽��

void  IIC_init(void);
void  IIC_start(void);
void  IIC_stop(void);
void  IIC_ack_main(uint8_t ack_main);
void  send_ch(uint8_t c);
uint8_t read_ch(uint8_t Ack);
int SCCB_WaitAck(void);
void  simiic_write_reg(uint8_t dev_add, uint8_t reg, uint8_t dat);
uint8_t simiic_read_reg(uint8_t dev_add, uint8_t reg, IIC_type type);
uint8_t simiic_write_len(uint8_t dev_add, uint8_t reg, uint8_t len, uint8_t *dat);
uint8_t simiic_read_len(uint8_t dev_add, uint8_t reg, uint8_t len, uint8_t *dat);

void My_Delay_Us(uint32_t us);

#endif
