/*****************************************************************************************
Բ�㲩ʿSTM32����4.0��Сϵͳ��AnBT���ļ�������Դ���롣��Բ�㲩ʿSTM32������������������ݡ�
����������LGPLЭ�顣�û���������ת��ʹ�øô��룬�������Ƴ��ò��ְ�Ȩ��Ϣ
������Ϣ������ʹٷ���վwww.etootle.com
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





