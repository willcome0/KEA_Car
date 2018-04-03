#ifndef     __MK60_MPU6050_H__
#define     __MK60_MPU6050_H__


#include "common.h"

/***************IIC�ӿ� �Խ�*******************/
//#define	i2c_init(a,b)			I2C_Init(a,b)
#define	i2c_write_reg(iic_n,s_add,add,data_)	i2c_write1(iic_n,s_add,add,data_)
//#define i2c_read_reg()


//����IIC�Ķ˿ںͲ�����
//****************************************
#define   I2C_n   IIC_0
#define   baud_n    400 * 1000

extern uint8_t data;

// ����MPU6050�ڲ���ַ
//****************************************
#define        SMPLRT_DIV                0x19        //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define        CONFIG                        0x1A        //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)

#define        GYRO_CONFIG                0x1B        //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define        ACCEL_CONFIG                0x1C        //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)

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

#define			PWR_MGMT_1                0x6B        //��Դ��������ֵ��0x00(��������)
#define			PWR_MGMT_2              0x6C
#define			WHO_AM_I                0x75        //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define			SlaveAddress                0x68        //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ   0xD0  

//ģ��IIC��0xD0��Ϊ��ַ
//Ӳ��IIC��0x68��Ϊ��ַ
//ʵ����  0x68 �� 0xD0 �ĸ�7λ

extern uint8_t mpu6050_init(void);

extern int16_t mpu6050_ACCEL_X_data();
//extern int16_t mpu6050_ACCEL_Y_data();
//extern int16_t mpu6050_ACCEL_Z_data();

//extern int16_t mpu6050_GYRO_X_data();
//extern int16_t mpu6050_GYRO_Y_data();
//extern int16_t mpu6050_GYRO_Z_data();

extern int16_t mpu6050_TEMP_OUT_data();

#endif  //__MK60_MPU6050_H__