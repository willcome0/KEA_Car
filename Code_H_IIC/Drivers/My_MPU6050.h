#ifndef     __MK60_MPU6050_H__
#define     __MK60_MPU6050_H__


#include "common.h"

/***************IIC接口 对接*******************/
//#define	i2c_init(a,b)			I2C_Init(a,b)
#define	i2c_write_reg(iic_n,s_add,add,data_)	i2c_write1(iic_n,s_add,add,data_)
//#define i2c_read_reg()


//定义IIC的端口和波特率
//****************************************
#define   I2C_n   IIC_0
#define   baud_n    400 * 1000

extern uint8_t data;

// 定义MPU6050内部地址
//****************************************
#define        SMPLRT_DIV                0x19        //陀螺仪采样率，典型值：0x07(125Hz)
#define        CONFIG                        0x1A        //低通滤波频率，典型值：0x06(5Hz)

#define        GYRO_CONFIG                0x1B        //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define        ACCEL_CONFIG                0x1C        //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

#define        ACCEL_XOUT_H                0x3B
#define        ACCEL_XOUT_L                0x3C
#define        ACCEL_YOUT_H                0x3D
#define        ACCEL_YOUT_L                0x3E
#define        ACCEL_ZOUT_H                0x3F
#define        ACCEL_ZOUT_L                0x40

#define        TEMP_OUT_H                0x41
#define        TEMP_OUT_L                0x42
#define        GYRO_XOUT_H                0x43
#define        GYRO_XOUT_L                0x44        
#define        GYRO_YOUT_H                0x45
#define        GYRO_YOUT_L                0x46
#define        GYRO_ZOUT_H                0x47
#define        GYRO_ZOUT_L                0x48

#define			PWR_MGMT_1                0x6B        //电源管理，典型值：0x00(正常启用)
#define			PWR_MGMT_2              0x6C
#define			WHO_AM_I                0x75        //IIC地址寄存器(默认数值0x68，只读)
#define			SlaveAddress                0x68        //IIC写入时的地址字节数据，+1为读取   0xD0  

//模拟IIC用0xD0作为地址
//硬件IIC用0x68作为地址
//实际上  0x68 是 0xD0 的高7位

extern uint8_t mpu6050_init(void);

extern int16_t mpu6050_ACCEL_X_data();
//extern int16_t mpu6050_ACCEL_Y_data();
//extern int16_t mpu6050_ACCEL_Z_data();

//extern int16_t mpu6050_GYRO_X_data();
//extern int16_t mpu6050_GYRO_Y_data();
//extern int16_t mpu6050_GYRO_Z_data();

extern int16_t mpu6050_TEMP_OUT_data();

#endif  //__MK60_MPU6050_H__