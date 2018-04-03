#include "My_MPU6050.h"
//#include "MK60_i2c.h"
//#include "MK60_MPU6050.h"


uint8_t DATA_H,DATA_L;

//*********mpu6050��ʼ��*************************
uint8_t mpu6050_init(void)                                   //mpu6050��ʼ��
{
//	I2C_ConfigType  I2C_Config = {{0}};
//  	I2C_Config.u16Slt = 0;
//  	I2C_Config.u16F = 0xBC; 				/* Baud rate at 100 kbit/sec, MULT = 4 , ICR=60*/
//    I2C_Config.sSetting.bIntEn = 0;
//    I2C_Config.sSetting.bI2CEn = 1;
//    I2C_Config.sSetting.bMSTEn = 1;
//	
//  i2c_init(pI2C0, I2C_Config);
	uint8_t t_val = 0;
	i2c_init(0, 1, SlaveAddress, 100);
	
  i2c_write_reg(0,SlaveAddress,PWR_MGMT_1,0x00);     //�������״̬
  i2c_write_reg(0,SlaveAddress,SMPLRT_DIV,0x07);
  i2c_write_reg(0,SlaveAddress,CONFIG,0x06);

  //���������Ĵ�����������ת�������ݵľ���   0x08 ���ֵΪ 8192 (2^13)
  i2c_write_reg(0,SlaveAddress,GYRO_CONFIG,0x18);    //
  i2c_write_reg(0,SlaveAddress,ACCEL_CONFIG,0x01);   //

  i2c_read1(0,SlaveAddress,WHO_AM_I, &t_val);
  if(t_val == 0x68)
    return 0;
  else 
    return 1;
}

//*********�� ���ٶȼ�X�� ����*******************
int16_t mpu6050_ACCEL_X_data()                                    
{
  i2c_read1(0,SlaveAddress,ACCEL_XOUT_H, &DATA_H);
  i2c_read1(0,SlaveAddress,ACCEL_XOUT_L, &DATA_L);
  return (DATA_H<<8)+DATA_L;
}
//*********�� ���ٶȼ�Y�� ����*******************
int16_t mpu6050_ACCEL_Y_data()                                    
{
  i2c_read1(0,SlaveAddress,ACCEL_YOUT_H, &DATA_H);
  i2c_read1(0,SlaveAddress,ACCEL_YOUT_L, &DATA_H);
  return (DATA_H<<8)+DATA_L;
}
////*********�� ���ٶȼ�X�� ����*******************
//int16_t mpu6050_ACCEL_Z_data()                                    
//{
//  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_ZOUT_H);
//  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,ACCEL_ZOUT_L);
//  return (DATA_H<<8)+DATA_L;
//}
////*********�� �����Ǽ�X�� ����*******************
//int16_t mpu6050_GYRO_X_data()                                    
//{
//  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,GYRO_XOUT_H);
//  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,GYRO_XOUT_L);
//  return (DATA_H<<8)+DATA_L;
//}
////*********�� �����Ǽ�Y�� ����*******************
//int16_t mpu6050_GYRO_Y_data()                                    
//{
//  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,GYRO_YOUT_H);
//  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,GYRO_YOUT_L);
//  return (DATA_H<<8)+DATA_L;
//}
////*********�� �����Ǽ�Z�� ����*******************
//int16_t mpu6050_GYRO_Z_data()                                    
//{
//  DATA_H = i2c_read_reg(I2C_n,SlaveAddress,GYRO_ZOUT_H);
//  DATA_L = i2c_read_reg(I2C_n,SlaveAddress,GYRO_ZOUT_L);
//  return (DATA_H<<8)+DATA_L;
//}
//*********�� �¶� ����*******************
int16_t mpu6050_TEMP_OUT_data()                                    
{
  i2c_read1(0,SlaveAddress,TEMP_OUT_H, &DATA_H);
  i2c_read1(0,SlaveAddress,TEMP_OUT_L, &DATA_L);
  return (DATA_H<<8)+DATA_L;
}