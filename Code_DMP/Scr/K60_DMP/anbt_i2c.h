#ifndef __ANBT_I2C_H
#define __ANBT_I2C_H

//#include "MK60_uart.h"
//#include "MK60_SysTick.h"
#include "common.h"

/*****************************************************************************************
圆点博士STM32蓝牙4.0最小系统板AnBT库文件和例程源代码。和圆点博士STM32无线下载助手软件兼容。
该例程适用LGPL协议。用户可以自由转载使用该代码，但不得移除该部分版权信息
更多信息，请访问官方网站www.etootle.com
******************************************************************************************/


/*自己板*/
#define SCL_Port   PTA
#define SCL_Pin    PTA3
#define SDA_Port   PTA
#define SDA_Pin    PTA2


#define ANBT_I2C_SCL_0 		 Pin_Output_Config(SCL_Port, SCL_Pin, 0)
#define ANBT_I2C_SCL_1 		 Pin_Output_Config(SCL_Port, SCL_Pin, 1)
#define ANBT_I2C_SDA_0 		 Pin_Output_Config(SDA_Port, SDA_Pin, 0)
#define ANBT_I2C_SDA_1   	 Pin_Output_Config(SDA_Port, SDA_Pin, 1) 
//
#define ANBT_I2C_SDA_STATE   Read_Input_State(SDA_Port, SDA_Pin)
//////#define ANBT_I2C_DELAY 		 ANBT_I2C_Delay(100000)
#define ANBT_I2C_NOP		 Delay_us(1)
//
#define ANBT_I2C_READY		    0x00
#define ANBT_I2C_BUS_BUSY	    0x01	
#define ANBT_I2C_BUS_ERROR	    0x02
//
#define ANBT_I2C_NACK	        0x00 
#define ANBT_I2C_ACK		    0x01
//
void ANBT_I2C_Delay(uint32_t dly);
uint8_t ANBT_I2C_START(void);
void ANBT_I2C_STOP(void);
void ANBT_I2C_SendACK(void);
void ANBT_I2C_SendNACK(void);
uint8_t ANBT_I2C_SendByte(uint8_t anbt_i2c_data);
uint8_t ANBT_I2C_ReceiveByte_WithACK(void);
uint8_t ANBT_I2C_ReceiveByte(void);
void ANBT_I2C_Receive12Bytes(uint8_t *anbt_i2c_data_buffer);
void ANBT_I2C_Receive6Bytes(uint8_t *anbt_i2c_data_buffer);
void ANBT_I2C_Receive14Bytes(uint8_t *anbt_i2c_data_buffer);
uint8_t AnBT_DMP_I2C_Write(uint8_t anbt_dev_addr, uint8_t anbt_reg_addr, uint8_t anbt_i2c_len, uint8_t *anbt_i2c_data_buf);
uint8_t AnBT_DMP_I2C_Read(uint8_t anbt_dev_addr, uint8_t anbt_reg_addr, uint8_t anbt_i2c_len, uint8_t *anbt_i2c_data_buf);
void AnBT_DMP_Delay_us(uint32_t dly);
void AnBT_DMP_Delay_ms(uint32_t dly);



#endif  
