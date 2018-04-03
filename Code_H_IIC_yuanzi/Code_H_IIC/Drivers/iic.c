#include "iic.h"

 
 //MPU IIC 延时函数
void MPU_IIC_Delay(void)
{
	Delay_us(2);
}

//初始化IIC
void MPU_IIC_Init(void)
{					     
    Pin_Output_Config(SCL_Port, SCL_Pin, 1);
    Pin_Output_Config(SDA_Port, SDA_Pin, 1);
}
//产生IIC起始信号
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda线输出
	MPU_IIC_SDA_H();	  	  
	MPU_IIC_SCL_H();
	MPU_IIC_Delay();
 	MPU_IIC_SDA_L();//START:when CLK is high,DATA change form high to low 
	MPU_IIC_Delay();
	MPU_IIC_SCL_L();//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda线输出
	MPU_IIC_SCL_L();
	MPU_IIC_SDA_L();//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_IIC_SCL_H(); 
	MPU_IIC_SDA_H();//发送I2C总线结束信号
	MPU_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t MPU_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	MPU_SDA_IN();      //SDA设置为输入  
	MPU_IIC_SDA_H();MPU_IIC_Delay();	   
	MPU_IIC_SCL_H();MPU_IIC_Delay();	 
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL_L();//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL_L();
	MPU_SDA_OUT();
	MPU_IIC_SDA_L();
	MPU_IIC_Delay();
	MPU_IIC_SCL_H();
	MPU_IIC_Delay();
	MPU_IIC_SCL_L();
}
//不产生ACK应答		    
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL_L();
	MPU_SDA_OUT();
	MPU_IIC_SDA_H();
	MPU_IIC_Delay();
	MPU_IIC_SCL_H();
	MPU_IIC_Delay();
	MPU_IIC_SCL_L();
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void MPU_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	MPU_SDA_OUT(); 	    
    MPU_IIC_SCL_L();//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {        
		if(((txd&0x80)>>7) == 0)
		{
			MPU_IIC_SDA_L();
		}
		else
		{
			MPU_IIC_SDA_H();
		}
        txd<<=1; 	  
		MPU_IIC_SCL_H();
		MPU_IIC_Delay(); 
		MPU_IIC_SCL_L();
		MPU_IIC_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL_L(); 
        MPU_IIC_Delay();
		MPU_IIC_SCL_H();
        receive<<=1;
        if(MPU_READ_SDA)
			receive++;   
		MPU_IIC_Delay(); 
    }					 
    if (!ack)
        MPU_IIC_NAck();//发送nACK
    else
        MPU_IIC_Ack(); //发送ACK   
    return receive;
}



