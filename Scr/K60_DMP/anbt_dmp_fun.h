/*****************************************************************************************
圆点博士STM32蓝牙4.0最小系统板AnBT库文件和例程源代码。和圆点博士STM32无线下载助手软件兼容。
该例程适用LGPL协议。用户可以自由转载使用该代码，但不得移除该部分版权信息
更多信息，请访问官方网站www.etootle.com
******************************************************************************************/
int mpu_write_mem(unsigned short mem_addr, unsigned short length, unsigned char *data);
int mpu_read_mem(unsigned short mem_addr, unsigned short length,  unsigned char *data);
int mpu_get_accel_sens(unsigned short *sens);
int mpu_get_accel_fsr(unsigned char *fsr);
int mpu_read_fifo_stream(unsigned short length, unsigned char *data, unsigned char *more);
int mpu_reset_fifo(void);
//
uint8_t AnBT_DMP_MPU6050_DEV_CFG(void);
uint8_t AnBT_DMP_MPU6050_Init(void);		
void AnBT_DMP_MPU6050_SEND_DATA_FUN(void);





