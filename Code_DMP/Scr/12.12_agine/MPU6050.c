#include "MPU6050.h"

float 
     Pitch = 0,
     Roll  = 0,
     Yaw   = 0;

S_FLOAT_XYZ 
	GYRO_Real,		// 陀螺仪转化后的数据
	ACC_Real,
    Angle;		// 加速度计转化后的数据

    
S_INT16_XYZ
	GYRO,			// 陀螺仪原始数据
	GYRO_Offset,	// 陀螺仪温飘
	ACC; 			// 加速度计数据


S_INT32_XYZ
	Tar_Ang_Vel,	// 目标角速度
	Tar_Ang_Vel_Last;	// 上次目标角速度
    
int32_t 
	Speed_Now = 0,	// 当前实际速度
	Speed_Min = 0,	// 左右最小速度
	Speed_Set = 0, 	// 目标设定速度
	Theory_Duty = 0,// 理论直立占空比
	Vel_Set = 0,	// 目标转向角速度
	Direct_Parameter = 0,// 转向系数
	Direct_Last = 0,
	Radius = 0;		// 目标转向半径


void Balance_Init(void)
{
//	Attitude_Angle.Y = 0;
//	Target_Angle_6050.Y = 0;
	Tar_Ang_Vel.Y = 0;
	Tar_Ang_Vel.Z = 0;
}



    
char Offset_OK = 0;
 
 
 
/*
 * 函数名：MPU6050_Init
 * 描述  ：陀螺仪初始化
 * 输入  ：无
 * 输出  ：0成功  1失败
 * 调用  ：外部调用
 */
uint8_t MPU6050_Init(void)
{ 
//	uint8_t res;
	
    Delay_ms(10);
	MPU6050_WR(MPU_PWR_MGMT1_REG,0X80);		// 复位MPU6050
  	Delay_ms(10);
	MPU6050_WR(MPU_PWR_MGMT1_REG,0X00);		// 唤醒MPU6050 
	Delay_ms(10);
	MPU6050_WR(MPU_PWR_MGMT1_REG,0X01);		// 设置CLKSEL,PLL X轴为参考
	Delay_ms(10);
	MPU6050_WR(MPU_GYRO_CFG_REG,3<<3);		// 陀螺仪传感器,±2000dps	// 0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
	Delay_ms(10);
	MPU6050_WR(MPU_ACCEL_CFG_REG,0<<3);		// 加速度传感器,±2g		// 0,±2g;1,±4g;2,±8g;3,±16g
	Delay_ms(10);
	MPU6050_WR(MPU_SAMPLE_RATE_REG,0X00);	// 设置MPU6050的采样率,8KHz
	Delay_ms(10);
	MPU6050_WR(MPU_CFG_REG,0X01);			// 设置数字低通滤波器,256Hz
	Delay_ms(100);

	if(MPU6050_ADRESS == MPU6050_RD(MPU_DEVICE_ID_REG))// 器件ID正确
	{
        Delay_ms(10);
		MPU6050_Offset();
        Delay_ms(10);
//		Balance_Init();
		return 0;
 	}
	else 
		return 1;

}

/*
 * 函数名：MPU6050_Offset
 * 描述  ：传感器采集零偏
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void MPU6050_Offset(void)
{
	uint8_t i, Count = 100;
	int32_t temp[3] = {0};
	
	GYRO_Offset.X = 0;
	GYRO_Offset.Y = 0;
	GYRO_Offset.Z = 0;
	
	for (i = 0; i < Count; i++)
	{
		MPU6050_GetData(&GYRO, &ACC);	// 读取陀螺仪数据
		Delay_ms(2);
		
//		temp[0] += ACC.X;
//		temp[1] += ACC.Y;
//		temp[2] += ACC.Z;
		
		temp[0] += GYRO.X;
		temp[1] += GYRO.Y;
		temp[2] += GYRO.Z;
	}
//	ACC_Offset.X = temp[0] / Count;
//	ACC_Offset.Y = temp[1] / Count;
//	ACC_Offset.Z = temp[2] / Count;
	
	GYRO_Offset.X = temp[0] / Count;
	GYRO_Offset.Y = temp[1] / Count;
	GYRO_Offset.Z = temp[2] / Count;
	
	Offset_OK = 1;
}

/*
 * 函数名：MPU6050_GetData
 * 描述  ：获得传感器所有数据
 * 输入  ：*GYRO 陀螺仪		*ACC 加速度计
 * 输出  ：无
 * 调用  ：外部调用
 */
void MPU6050_GetData(S_INT16_XYZ *GYRO, S_INT16_XYZ *ACC)
{
	if (Offset_OK)
	{
		ACC->X = GetData(MPU_ACCEL_XOUTH_REG);	// 获取加速度计原始数据
		ACC->Y = GetData(MPU_ACCEL_YOUTH_REG);
		ACC->Z = GetData(MPU_ACCEL_ZOUTH_REG);
		
		GYRO->X = GetData(MPU_GYRO_XOUTH_REG) - GYRO_Offset.X;	// 获取陀螺仪原始数据
		GYRO->Y = GetData(MPU_GYRO_YOUTH_REG) - GYRO_Offset.Y;
		GYRO->Z = GetData(MPU_GYRO_ZOUTH_REG) - GYRO_Offset.Z;
	}
	else
	{
		ACC->X = GetData(MPU_ACCEL_XOUTH_REG);	// 获取加速度计原始数据并归一化
		ACC->Y = GetData(MPU_ACCEL_YOUTH_REG);
		ACC->Z = GetData(MPU_ACCEL_ZOUTH_REG);
		
		GYRO->X = GetData(MPU_GYRO_XOUTH_REG);	// 获取陀螺仪原始数据并归一化
		GYRO->Y = GetData(MPU_GYRO_YOUTH_REG);
		GYRO->Z = GetData(MPU_GYRO_ZOUTH_REG);
	} 
}

/*
 * 函数名：GetData
 * 描述  ：获得16位数据
 * 输入  ：REG_Address 寄存器地址
 * 输出  ：返回寄存器数据
 * 调用  ：外部调用
 */
int16_t GetData(uint8_t REG_Address)
{
	uint8_t H, L;

	H = MPU6050_RD(REG_Address);
	L = MPU6050_RD(REG_Address+1);
	
	return ((H<<8)|L);   //合成数据
}


#define AcceRatio 	16384.0f
#define GyroRatio 	16.4f
#define Gyro_Gr		0.0010653	// 角速度变成弧度	此参数对应陀螺2000度每秒
#define ACC_FILTER_NUM 2		// 加速度计滤波深度
#define GYRO_FILTER_NUM 2		// 陀螺仪滤波深度

/*
 * 函数名：Data_Filter
 * 描述  ：数据滑动滤波
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Data_Filter(void)	// 数据滤波
{
    static int32_t ACC_X_BUF[ACC_FILTER_NUM], ACC_Y_BUF[ACC_FILTER_NUM], ACC_Z_BUF[ACC_FILTER_NUM];	// 滤波缓存数组
    static int32_t GYRO_X_BUF[GYRO_FILTER_NUM], GYRO_Y_BUF[GYRO_FILTER_NUM], GYRO_Z_BUF[GYRO_FILTER_NUM];
    
    uint8_t i;
	int32_t temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0, temp6 = 0;
	
    
    /*更新第一个滤波缓存数组*/
	ACC_X_BUF[0] = ACC.X;
	ACC_Y_BUF[0] = ACC.Y;
	ACC_Z_BUF[0] = ACC.Z;
	GYRO_X_BUF[0] = GYRO.X;
	GYRO_Y_BUF[0] = GYRO.Y;
	GYRO_Z_BUF[0] = GYRO.Z;
	
    /*原始数据 滑动平均滤波*/
	for(i=0;i<ACC_FILTER_NUM;i++)
	{
		temp1 += ACC_X_BUF[i];
		temp2 += ACC_Y_BUF[i];
		temp3 += ACC_Z_BUF[i];
	}
	for(i=0;i<GYRO_FILTER_NUM;i++)
	{
		temp4 += GYRO_X_BUF[i];
		temp5 += GYRO_Y_BUF[i];
		temp6 += GYRO_Z_BUF[i];
	}
	ACC_Real.X  = temp1 / ACC_FILTER_NUM  / AcceRatio;
	ACC_Real.Y  = temp2 / ACC_FILTER_NUM  / AcceRatio;
	ACC_Real.Z  = temp3 / ACC_FILTER_NUM  / AcceRatio;
	GYRO_Real.X = temp4 / GYRO_FILTER_NUM / GyroRatio;
	GYRO_Real.Y = temp5 / GYRO_FILTER_NUM / GyroRatio;
	GYRO_Real.Z = temp6 / GYRO_FILTER_NUM / GyroRatio;
	
    /*更新后几个滤波缓存数组*/
	for(i = 0; i < ACC_FILTER_NUM - 1; i++)
	{
		ACC_X_BUF[ACC_FILTER_NUM-1-i] = ACC_X_BUF[ACC_FILTER_NUM-2-i];
		ACC_Y_BUF[ACC_FILTER_NUM-1-i] = ACC_Y_BUF[ACC_FILTER_NUM-2-i];
		ACC_Z_BUF[ACC_FILTER_NUM-1-i] = ACC_Z_BUF[ACC_FILTER_NUM-2-i];
		
	}
	for(i = 0; i < GYRO_FILTER_NUM - 1; i++)
	{
		GYRO_X_BUF[GYRO_FILTER_NUM-1-i] = GYRO_X_BUF[GYRO_FILTER_NUM-2-i];
		GYRO_Y_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Y_BUF[GYRO_FILTER_NUM-2-i];
		GYRO_Z_BUF[GYRO_FILTER_NUM-1-i] = GYRO_Z_BUF[GYRO_FILTER_NUM-2-i];
	}
    
//    Get_Attitude();
//        Variable[3] = Pitch;
//        Variable[4] = Roll;
//        Variable[5] = Yaw;
//    
//	ACC_Real.Y = atan2(ACC_Real.X, ACC_Real.Z)*57.3;
//        Variable[1]=ACC_Real.Y;
//        Variable[2]=ACC.Y/100;   
}



/*
 * 函数名：Get_Attitude
 * 描述  ：姿态解算
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void Get_Attitude(void)	// 姿态解算
{
	IMUupdate(GYRO_Real.X*Gyro_Gr*GyroRatio, 
			  GYRO_Real.Y*Gyro_Gr*GyroRatio, 
			  GYRO_Real.Z*Gyro_Gr*GyroRatio, 
			  ACC_Real.X * AcceRatio, 
			  ACC_Real.Y * AcceRatio, 
			  ACC_Real.Z * AcceRatio);	// 姿态解算出欧拉角
}
void Get_Attitude_NoF(void)	// 姿态解算
{
	IMUupdate(GYRO.X*Gyro_Gr*GyroRatio, 
			  GYRO.Y*Gyro_Gr*GyroRatio, 
			  GYRO.Z*Gyro_Gr*GyroRatio, 
			  ACC.X * AcceRatio, 
			  ACC.Y * AcceRatio, 
			  ACC.Z * AcceRatio);	// 姿态解算出欧拉角
}

//===============================四元素============================================
#define Kp 1.6f //10.0f             	// proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.001f//1.2f // //0.008f  	// integral gain governs rate of convergence of gyroscope biases
#define halfT 0.005f                   	// half the sample period采样周期的一半
float q0 = 1, q1 = 0, q2 = 0, q3 = 0; 	// quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0; 	// scaled integral error
/*
 * 函数名：IMUupdate
 * 描述  ：四元素解算欧拉角
 * 输入  ：陀螺仪 加速度计
 * 输出  ：无
 * 调用  ：内部调用
 */
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
	float norm;
	float vx, vy, vz;
	float ex, ey, ez;

	// 先把这些用得到的值算好
	float q0q0 = q0*q0;
	float q0q1 = q0*q1;
	float q0q2 = q0*q2;
	float q1q1 = q1*q1;
	float q1q3 = q1*q3;
	float q2q2 = q2*q2;
	float q2q3 = q2*q3;
	float q3q3 = q3*q3;

//	if (ax*ay*az == 0)
//	{
//		return;
//	}
		
	norm = sqrt(ax*ax + ay*ay + az*az);	// acc数据归一化
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;

	// estimated direction of gravity and flux (v and w)	估计重力方向和流量/变迁
	vx = 2*(q1q3 - q0q2);									// 四元素中xyz的表示
	vy = 2*(q0q1 + q2q3);
	vz = q0q0 - q1q1 - q2q2 + q3q3 ;

	// error is sum of cross product between reference direction of fields and direction measured by sensors
	ex = (ay*vz - az*vy) ;		// 向量外积在相减得到差分就是误差
	ey = (az*vx - ax*vz) ;
	ez = (ax*vy - ay*vx) ;

	exInt = exInt + ex * Ki;	// 对误差进行积分
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	// adjusted gyroscope measurements
	gx = gx + Kp*ex + exInt;	// 将误差PI后补偿到陀螺仪，即补偿零点漂移
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;	// 这里的gz由于没有观测者进行矫正会产生漂移，表现出来的就是积分自增或自减

	// integrate quaternion rate and normalise	// 四元素的微分方程
	q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
	q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
	q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
	q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

	// normalise quaternion
	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;
	
	Pitch = asin(-2*q1*q3 + 2*q0*q2) * 57.3; // pitch
//	Roll = atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1)*57.3; // roll
	Yaw = atan2(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1)*57.3; // yaw

        Yaw = Yaw<0 ? 360 + Yaw : Yaw;
//	Attitude_Angle.Z = 0;
}

