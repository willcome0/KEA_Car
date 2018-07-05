#ifndef __MPU6050_H
#define __MPU6050_H

#include "common.h"
#include "SKEAZ1284.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpmap.h"
#include "dmpkey.h"
#define devAddr  0xD0

#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW

#define MPU6050_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC     0x07
#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC     0x09
#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL     0x14
#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL     0x16
#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL     0x18
#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_FF_THR           0x1D
#define MPU6050_RA_FF_DUR           0x1E
#define MPU6050_RA_MOT_THR          0x1F
#define MPU6050_RA_MOT_DUR          0x20
#define MPU6050_RA_ZRMOT_THR        0x21
#define MPU6050_RA_ZRMOT_DUR        0x22
#define MPU6050_RA_FIFO_EN          0x23
#define MPU6050_RA_I2C_MST_CTRL     0x24
#define MPU6050_RA_I2C_SLV0_ADDR    0x25
#define MPU6050_RA_I2C_SLV0_REG     0x26
# define MPU6050_RA_I2C_SLV0_CTRL    0x27
#define MPU6050_RA_I2C_SLV1_ADDR    0x28
#define MPU6050_RA_I2C_SLV1_REG     0x29
#define MPU6050_RA_I2C_SLV1_CTRL    0x2A
#define MPU6050_RA_I2C_SLV2_ADDR    0x2B
#define MPU6050_RA_I2C_SLV2_REG     0x2C
#define MPU6050_RA_I2C_SLV2_CTRL    0x2D
#define MPU6050_RA_I2C_SLV3_ADDR    0x2E
#define MPU6050_RA_I2C_SLV3_REG     0x2F
#define MPU6050_RA_I2C_SLV3_CTRL    0x30
#define MPU6050_RA_I2C_SLV4_ADDR    0x31
#define MPU6050_RA_I2C_SLV4_REG     0x32
#define MPU6050_RA_I2C_SLV4_DO      0x33
#define MPU6050_RA_I2C_SLV4_CTRL    0x34
#define MPU6050_RA_I2C_SLV4_DI      0x35
#define MPU6050_RA_I2C_MST_STATUS   0x36
#define MPU6050_RA_INT_PIN_CFG      0x37
#define MPU6050_RA_INT_ENABLE       0x38
#define MPU6050_RA_DMP_INT_STATUS   0x39
#define MPU6050_RA_INT_STATUS       0x3A
#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_TEMP_OUT_L       0x42
#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS    0x61
#define MPU6050_RA_I2C_SLV0_DO      0x63
#define MPU6050_RA_I2C_SLV1_DO      0x64
#define MPU6050_RA_I2C_SLV2_DO      0x65
#define MPU6050_RA_I2C_SLV3_DO      0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU6050_RA_SIGNAL_PATH_RESET    0x68
#define MPU6050_RA_MOT_DETECT_CTRL      0x69
#define MPU6050_RA_USER_CTRL        0x6A
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C
#define MPU6050_RA_BANK_SEL         0x6D
#define MPU6050_RA_MEM_START_ADDR   0x6E
#define MPU6050_RA_MEM_R_W          0x6F
#define MPU6050_RA_DMP_CFG_1        0x70
#define MPU6050_RA_DMP_CFG_2        0x71
#define MPU6050_RA_FIFO_COUNTH      0x72
#define MPU6050_RA_FIFO_COUNTL      0x73
#define MPU6050_RA_FIFO_R_W         0x74
#define MPU6050_RA_WHO_AM_I         0x75

#define MPU6050_TC_PWR_MODE_BIT     7
#define MPU6050_TC_OFFSET_BIT       6
#define MPU6050_TC_OFFSET_LENGTH    6
#define MPU6050_TC_OTP_BNK_VLD_BIT  0

#define MPU6050_VDDIO_LEVEL_VLOGIC  0
#define MPU6050_VDDIO_LEVEL_VDD     1

#define MPU6050_CFG_EXT_SYNC_SET_BIT    5
#define MPU6050_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU6050_CFG_DLPF_CFG_BIT    2
#define MPU6050_CFG_DLPF_CFG_LENGTH 3

#define MPU6050_EXT_SYNC_DISABLED       0x0
#define MPU6050_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU6050_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU6050_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU6050_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU6050_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU6050_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU6050_DLPF_BW_256         0x00
#define MPU6050_DLPF_BW_188         0x01
#define MPU6050_DLPF_BW_98          0x02
#define MPU6050_DLPF_BW_42          0x03
#define MPU6050_DLPF_BW_20          0x04
#define MPU6050_DLPF_BW_10          0x05
#define MPU6050_DLPF_BW_5           0x06

#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x01
#define MPU6050_GYRO_FS_1000        0x02
#define MPU6050_GYRO_FS_2000        0x03

#define MPU6050_ACONFIG_XA_ST_BIT           7
#define MPU6050_ACONFIG_YA_ST_BIT           6
#define MPU6050_ACONFIG_ZA_ST_BIT           5
#define MPU6050_ACONFIG_AFS_SEL_BIT         4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
#define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_ACCEL_FS_4          0x01
#define MPU6050_ACCEL_FS_8          0x02
#define MPU6050_ACCEL_FS_16         0x03

#define MPU6050_DHPF_RESET          0x00
#define MPU6050_DHPF_5              0x01
#define MPU6050_DHPF_2P5            0x02
#define MPU6050_DHPF_1P25           0x03
#define MPU6050_DHPF_0P63           0x04
#define MPU6050_DHPF_HOLD           0x07

#define MPU6050_TEMP_FIFO_EN_BIT    7
#define MPU6050_XG_FIFO_EN_BIT      6
#define MPU6050_YG_FIFO_EN_BIT      5
#define MPU6050_ZG_FIFO_EN_BIT      4
#define MPU6050_ACCEL_FIFO_EN_BIT   3
#define MPU6050_SLV2_FIFO_EN_BIT    2
#define MPU6050_SLV1_FIFO_EN_BIT    1
#define MPU6050_SLV0_FIFO_EN_BIT    0

#define MPU6050_MULT_MST_EN_BIT     7
#define MPU6050_WAIT_FOR_ES_BIT     6
#define MPU6050_SLV_3_FIFO_EN_BIT   5
#define MPU6050_I2C_MST_P_NSR_BIT   4
#define MPU6050_I2C_MST_CLK_BIT     3
#define MPU6050_I2C_MST_CLK_LENGTH  4

#define MPU6050_CLOCK_DIV_348       0x0
#define MPU6050_CLOCK_DIV_333       0x1
#define MPU6050_CLOCK_DIV_320       0x2
#define MPU6050_CLOCK_DIV_308       0x3
#define MPU6050_CLOCK_DIV_296       0x4
#define MPU6050_CLOCK_DIV_286       0x5
#define MPU6050_CLOCK_DIV_276       0x6
#define MPU6050_CLOCK_DIV_267       0x7
#define MPU6050_CLOCK_DIV_258       0x8
#define MPU6050_CLOCK_DIV_500       0x9
#define MPU6050_CLOCK_DIV_471       0xA
#define MPU6050_CLOCK_DIV_444       0xB
#define MPU6050_CLOCK_DIV_421       0xC
#define MPU6050_CLOCK_DIV_400       0xD
#define MPU6050_CLOCK_DIV_381       0xE
#define MPU6050_CLOCK_DIV_364       0xF

#define MPU6050_I2C_SLV_RW_BIT      7
#define MPU6050_I2C_SLV_ADDR_BIT    6
#define MPU6050_I2C_SLV_ADDR_LENGTH 7
#define MPU6050_I2C_SLV_EN_BIT      7
#define MPU6050_I2C_SLV_BYTE_SW_BIT 6
#define MPU6050_I2C_SLV_REG_DIS_BIT 5
#define MPU6050_I2C_SLV_GRP_BIT     4
#define MPU6050_I2C_SLV_LEN_BIT     3
#define MPU6050_I2C_SLV_LEN_LENGTH  4

#define MPU6050_I2C_SLV4_RW_BIT         7
#define MPU6050_I2C_SLV4_ADDR_BIT       6
#define MPU6050_I2C_SLV4_ADDR_LENGTH    7
#define MPU6050_I2C_SLV4_EN_BIT         7
#define MPU6050_I2C_SLV4_INT_EN_BIT     6
#define MPU6050_I2C_SLV4_REG_DIS_BIT    5
#define MPU6050_I2C_SLV4_MST_DLY_BIT    4
#define MPU6050_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU6050_MST_PASS_THROUGH_BIT    7
#define MPU6050_MST_I2C_SLV4_DONE_BIT   6
#define MPU6050_MST_I2C_LOST_ARB_BIT    5
#define MPU6050_MST_I2C_SLV4_NACK_BIT   4
#define MPU6050_MST_I2C_SLV3_NACK_BIT   3
#define MPU6050_MST_I2C_SLV2_NACK_BIT   2
#define MPU6050_MST_I2C_SLV1_NACK_BIT   1
#define MPU6050_MST_I2C_SLV0_NACK_BIT   0

#define MPU6050_INTCFG_INT_LEVEL_BIT        7
#define MPU6050_INTCFG_INT_OPEN_BIT         6
#define MPU6050_INTCFG_LATCH_INT_EN_BIT     5
#define MPU6050_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU6050_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT    1
#define MPU6050_INTCFG_CLKOUT_EN_BIT        0

#define MPU6050_INTMODE_ACTIVEHIGH  0x00
#define MPU6050_INTMODE_ACTIVELOW   0x01

#define MPU6050_INTDRV_PUSHPULL     0x00
#define MPU6050_INTDRV_OPENDRAIN    0x01

#define MPU6050_INTLATCH_50USPULSE  0x00
#define MPU6050_INTLATCH_WAITCLEAR  0x01

#define MPU6050_INTCLEAR_STATUSREAD 0x00
#define MPU6050_INTCLEAR_ANYREAD    0x01

#define MPU6050_INTERRUPT_FF_BIT            7
#define MPU6050_INTERRUPT_MOT_BIT           6
#define MPU6050_INTERRUPT_ZMOT_BIT          5
#define MPU6050_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU6050_INTERRUPT_I2C_MST_INT_BIT   3
#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT   2
#define MPU6050_INTERRUPT_DMP_INT_BIT       1
#define MPU6050_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU6050_DMPINT_5_BIT            5
#define MPU6050_DMPINT_4_BIT            4
#define MPU6050_DMPINT_3_BIT            3
#define MPU6050_DMPINT_2_BIT            2
#define MPU6050_DMPINT_1_BIT            1
#define MPU6050_DMPINT_0_BIT            0

#define MPU6050_MOTION_MOT_XNEG_BIT     7
#define MPU6050_MOTION_MOT_XPOS_BIT     6
#define MPU6050_MOTION_MOT_YNEG_BIT     5
#define MPU6050_MOTION_MOT_YPOS_BIT     4
#define MPU6050_MOTION_MOT_ZNEG_BIT     3
#define MPU6050_MOTION_MOT_ZPOS_BIT     2
#define MPU6050_MOTION_MOT_ZRMOT_BIT    0

#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU6050_PATHRESET_GYRO_RESET_BIT    2
#define MPU6050_PATHRESET_ACCEL_RESET_BIT   1
#define MPU6050_PATHRESET_TEMP_RESET_BIT    0

#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT       5
#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define MPU6050_DETECT_FF_COUNT_BIT             3
#define MPU6050_DETECT_FF_COUNT_LENGTH          2
#define MPU6050_DETECT_MOT_COUNT_BIT            1
#define MPU6050_DETECT_MOT_COUNT_LENGTH         2

#define MPU6050_DETECT_DECREMENT_RESET  0x0
#define MPU6050_DETECT_DECREMENT_1      0x1
#define MPU6050_DETECT_DECREMENT_2      0x2
#define MPU6050_DETECT_DECREMENT_4      0x3

#define MPU6050_USERCTRL_DMP_EN_BIT             7
#define MPU6050_USERCTRL_FIFO_EN_BIT            6
#define MPU6050_USERCTRL_I2C_MST_EN_BIT         5
#define MPU6050_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU6050_USERCTRL_DMP_RESET_BIT          3
#define MPU6050_USERCTRL_FIFO_RESET_BIT         2
#define MPU6050_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU6050_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU6050_PWR1_DEVICE_RESET_BIT   7
#define MPU6050_PWR1_SLEEP_BIT          6
#define MPU6050_PWR1_CYCLE_BIT          5
#define MPU6050_PWR1_TEMP_DIS_BIT       3
#define MPU6050_PWR1_CLKSEL_BIT         2
#define MPU6050_PWR1_CLKSEL_LENGTH      3

#define MPU6050_CLOCK_INTERNAL          0x00
#define MPU6050_CLOCK_PLL_XGYRO         0x01
#define MPU6050_CLOCK_PLL_YGYRO         0x02
#define MPU6050_CLOCK_PLL_ZGYRO         0x03
#define MPU6050_CLOCK_PLL_EXT32K        0x04
#define MPU6050_CLOCK_PLL_EXT19M        0x05
#define MPU6050_CLOCK_KEEP_RESET        0x07

#define MPU6050_PWR2_LP_WAKE_CTRL_BIT       7
#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH    2
#define MPU6050_PWR2_STBY_XA_BIT            5
#define MPU6050_PWR2_STBY_YA_BIT            4
#define MPU6050_PWR2_STBY_ZA_BIT            3
#define MPU6050_PWR2_STBY_XG_BIT            2
#define MPU6050_PWR2_STBY_YG_BIT            1
#define MPU6050_PWR2_STBY_ZG_BIT            0

#define MPU6050_WAKE_FREQ_1P25      0x0
#define MPU6050_WAKE_FREQ_2P5       0x1
#define MPU6050_WAKE_FREQ_5         0x2
#define MPU6050_WAKE_FREQ_10        0x3

#define MPU6050_BANKSEL_PRFTCH_EN_BIT       6
#define MPU6050_BANKSEL_CFG_USER_BANK_BIT   5
#define MPU6050_BANKSEL_MEM_SEL_BIT         4
#define MPU6050_BANKSEL_MEM_SEL_LENGTH      5

#define MPU6050_WHO_AM_I_BIT        6
#define MPU6050_WHO_AM_I_LENGTH     6


#define MPU_SELF_TESTX_REG		0X0D	//自检寄存器X
#define MPU_SELF_TESTY_REG		0X0E	//自检寄存器Y
#define MPU_SELF_TESTZ_REG		0X0F	//自检寄存器Z
#define MPU_SELF_TESTA_REG		0X10	//自检寄存器A
#define MPU_SAMPLE_RATE_REG		0X19	//采样频率分频器
#define MPU_CFG_REG				0X1A	//配置寄存器
#define MPU_GYRO_CFG_REG		0X1B	//陀螺仪配置寄存器
#define MPU_ACCEL_CFG_REG		0X1C	//加速度计配置寄存器
#define MPU_MOTION_DET_REG		0X1F	//运动检测阀值设置寄存器
#define MPU_FIFO_EN_REG			0X23	//FIFO使能寄存器
#define MPU_I2CMST_CTRL_REG		0X24	//IIC主机控制寄存器
#define MPU_I2CSLV0_ADDR_REG	0X25	//IIC从机0器件地址寄存器
#define MPU_I2CSLV0_REG			0X26	//IIC从机0数据地址寄存器
#define MPU_I2CSLV0_CTRL_REG	0X27	//IIC从机0控制寄存器
#define MPU_I2CSLV1_ADDR_REG	0X28	//IIC从机1器件地址寄存器
#define MPU_I2CSLV1_REG			0X29	//IIC从机1数据地址寄存器
#define MPU_I2CSLV1_CTRL_REG	0X2A	//IIC从机1控制寄存器
#define MPU_I2CSLV2_ADDR_REG	0X2B	//IIC从机2器件地址寄存器
#define MPU_I2CSLV2_REG			0X2C	//IIC从机2数据地址寄存器
#define MPU_I2CSLV2_CTRL_REG	0X2D	//IIC从机2控制寄存器
#define MPU_I2CSLV3_ADDR_REG	0X2E	//IIC从机3器件地址寄存器
#define MPU_I2CSLV3_REG			0X2F	//IIC从机3数据地址寄存器
#define MPU_I2CSLV3_CTRL_REG	0X30	//IIC从机3控制寄存器
#define MPU_I2CSLV4_ADDR_REG	0X31	//IIC从机4器件地址寄存器
#define MPU_I2CSLV4_REG			0X32	//IIC从机4数据地址寄存器
#define MPU_I2CSLV4_DO_REG		0X33	//IIC从机4写数据寄存器
#define MPU_I2CSLV4_CTRL_REG	0X34	//IIC从机4控制寄存器
#define MPU_I2CSLV4_DI_REG		0X35	//IIC从机4读数据寄存器

#define MPU_I2CMST_STA_REG		0X36	//IIC主机状态寄存器
#define MPU_INTBP_CFG_REG		0X37	//中断/旁路设置寄存器
#define MPU_INT_EN_REG			0X38	//中断使能寄存器
#define MPU_INT_STA_REG			0X3A	//中断状态寄存器

#define MPU_ACCEL_XOUTH_REG		0X3B	//加速度值,X轴高8位寄存器
#define MPU_ACCEL_XOUTL_REG		0X3C	//加速度值,X轴低8位寄存器
#define MPU_ACCEL_YOUTH_REG		0X3D	//加速度值,Y轴高8位寄存器
#define MPU_ACCEL_YOUTL_REG		0X3E	//加速度值,Y轴低8位寄存器
#define MPU_ACCEL_ZOUTH_REG		0X3F	//加速度值,Z轴高8位寄存器
#define MPU_ACCEL_ZOUTL_REG		0X40	//加速度值,Z轴低8位寄存器

#define MPU_TEMP_OUTH_REG		0X41	//温度值高八位寄存器
#define MPU_TEMP_OUTL_REG		0X42	//温度值低8位寄存器

#define MPU_GYRO_XOUTH_REG		0X43	//陀螺仪值,X轴高8位寄存器
#define MPU_GYRO_XOUTL_REG		0X44	//陀螺仪值,X轴低8位寄存器
#define MPU_GYRO_YOUTH_REG		0X45	//陀螺仪值,Y轴高8位寄存器
#define MPU_GYRO_YOUTL_REG		0X46	//陀螺仪值,Y轴低8位寄存器
#define MPU_GYRO_ZOUTH_REG		0X47	//陀螺仪值,Z轴高8位寄存器
#define MPU_GYRO_ZOUTL_REG		0X48	//陀螺仪值,Z轴低8位寄存器

#define MPU_I2CSLV0_DO_REG		0X63	//IIC从机0数据寄存器
#define MPU_I2CSLV1_DO_REG		0X64	//IIC从机1数据寄存器
#define MPU_I2CSLV2_DO_REG		0X65	//IIC从机2数据寄存器
#define MPU_I2CSLV3_DO_REG		0X66	//IIC从机3数据寄存器

#define MPU_I2CMST_DELAY_REG	0X67	//IIC主机延时管理寄存器
#define MPU_SIGPATH_RST_REG		0X68	//信号通道复位寄存器
#define MPU_MDETECT_CTRL_REG	0X69	//运动检测控制寄存器
#define MPU_USER_CTRL_REG		0X6A	//用户控制寄存器
#define MPU_PWR_MGMT1_REG		0X6B	//电源管理寄存器1
#define MPU_PWR_MGMT2_REG		0X6C	//电源管理寄存器2 
#define MPU_FIFO_CNTH_REG		0X72	//FIFO计数寄存器高八位
#define MPU_FIFO_CNTL_REG		0X73	//FIFO计数寄存器低八位
#define MPU_FIFO_RW_REG			0X74	//FIFO读写寄存器
#define MPU_DEVICE_ID_REG		0X75	//器件ID寄存器

#define MPU_ADDR				0X68

extern float Gyro_X, Gyro_Y, Gyro_Z;
extern float Accel_X, Accel_Y, Accel_Z;


extern	short gyro[3], accel[3];
extern int16_t Gx_offset,Gy_offset,Gz_offset;
extern float Acc1G_Values;
extern float Pitch, Roll, Yaw;
extern	int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
//供外部调用的API
uint8_t MPU6050_initialize(void); //初始化
uint8_t MPU6050_testConnection(void); //检测MPU6050是否存在
//读取ADC值
void MPU6050_getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
void MPU6050_getlastMotion6(int16_t* ax, int16_t* ay, 
		int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
uint8_t MPU6050_getDeviceID(void); //读取MPU6050的ID
void MPU6050_InitGyro_Offset(void);//初始化陀螺仪偏置
uint8_t DMP_Init(void);
float Read_DMP(void);
int Read_Temperature(void);
#endif
//#ifndef __MPU6050_H
//#define __MPU6050_H

//#include "common.h"
//#include "SKEAZ1284.h"

//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
//#include "dmpmap.h"
//#include "dmpkey.h"
//#include "math.h"
//#define devAddr  0xD0

//#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
//#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
//#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW

//#define MPU6050_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
//#define MPU6050_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
//#define MPU6050_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
//#define MPU6050_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
//#define MPU6050_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
//#define MPU6050_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
//#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
//#define MPU6050_RA_XA_OFFS_L_TC     0x07
//#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
//#define MPU6050_RA_YA_OFFS_L_TC     0x09
//#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
//#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
//#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
//#define MPU6050_RA_XG_OFFS_USRL     0x14
//#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
//#define MPU6050_RA_YG_OFFS_USRL     0x16
//#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
//#define MPU6050_RA_ZG_OFFS_USRL     0x18
//#define MPU6050_RA_SMPLRT_DIV       0x19
//#define MPU6050_RA_CONFIG           0x1A
//#define MPU6050_RA_GYRO_CONFIG      0x1B
//#define MPU6050_RA_ACCEL_CONFIG     0x1C
//#define MPU6050_RA_FF_THR           0x1D
//#define MPU6050_RA_FF_DUR           0x1E
//#define MPU6050_RA_MOT_THR          0x1F
//#define MPU6050_RA_MOT_DUR          0x20
//#define MPU6050_RA_ZRMOT_THR        0x21
//#define MPU6050_RA_ZRMOT_DUR        0x22
//#define MPU6050_RA_FIFO_EN          0x23
//#define MPU6050_RA_I2C_MST_CTRL     0x24
//#define MPU6050_RA_I2C_SLV0_ADDR    0x25
//#define MPU6050_RA_I2C_SLV0_REG     0x26
//# define MPU6050_RA_I2C_SLV0_CTRL    0x27
//#define MPU6050_RA_I2C_SLV1_ADDR    0x28
//#define MPU6050_RA_I2C_SLV1_REG     0x29
//#define MPU6050_RA_I2C_SLV1_CTRL    0x2A
//#define MPU6050_RA_I2C_SLV2_ADDR    0x2B
//#define MPU6050_RA_I2C_SLV2_REG     0x2C
//#define MPU6050_RA_I2C_SLV2_CTRL    0x2D
//#define MPU6050_RA_I2C_SLV3_ADDR    0x2E
//#define MPU6050_RA_I2C_SLV3_REG     0x2F
//#define MPU6050_RA_I2C_SLV3_CTRL    0x30
//#define MPU6050_RA_I2C_SLV4_ADDR    0x31
//#define MPU6050_RA_I2C_SLV4_REG     0x32
//#define MPU6050_RA_I2C_SLV4_DO      0x33
//#define MPU6050_RA_I2C_SLV4_CTRL    0x34
//#define MPU6050_RA_I2C_SLV4_DI      0x35
//#define MPU6050_RA_I2C_MST_STATUS   0x36
//#define MPU6050_RA_INT_PIN_CFG      0x37
//#define MPU6050_RA_INT_ENABLE       0x38
//#define MPU6050_RA_DMP_INT_STATUS   0x39
//#define MPU6050_RA_INT_STATUS       0x3A
//#define MPU6050_RA_ACCEL_XOUT_H     0x3B
//#define MPU6050_RA_ACCEL_XOUT_L     0x3C
//#define MPU6050_RA_ACCEL_YOUT_H     0x3D
//#define MPU6050_RA_ACCEL_YOUT_L     0x3E
//#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
//#define MPU6050_RA_ACCEL_ZOUT_L     0x40
//#define MPU6050_RA_TEMP_OUT_H       0x41
//#define MPU6050_RA_TEMP_OUT_L       0x42
//#define MPU6050_RA_GYRO_XOUT_H      0x43
//#define MPU6050_RA_GYRO_XOUT_L      0x44
//#define MPU6050_RA_GYRO_YOUT_H      0x45
//#define MPU6050_RA_GYRO_YOUT_L      0x46
//#define MPU6050_RA_GYRO_ZOUT_H      0x47
//#define MPU6050_RA_GYRO_ZOUT_L      0x48
//#define MPU6050_RA_EXT_SENS_DATA_00 0x49
//#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
//#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
//#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
//#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
//#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
//#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
//#define MPU6050_RA_EXT_SENS_DATA_07 0x50
//#define MPU6050_RA_EXT_SENS_DATA_08 0x51
//#define MPU6050_RA_EXT_SENS_DATA_09 0x52
//#define MPU6050_RA_EXT_SENS_DATA_10 0x53
//#define MPU6050_RA_EXT_SENS_DATA_11 0x54
//#define MPU6050_RA_EXT_SENS_DATA_12 0x55
//#define MPU6050_RA_EXT_SENS_DATA_13 0x56
//#define MPU6050_RA_EXT_SENS_DATA_14 0x57
//#define MPU6050_RA_EXT_SENS_DATA_15 0x58
//#define MPU6050_RA_EXT_SENS_DATA_16 0x59
//#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
//#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
//#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
//#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
//#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
//#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
//#define MPU6050_RA_EXT_SENS_DATA_23 0x60
//#define MPU6050_RA_MOT_DETECT_STATUS    0x61
//#define MPU6050_RA_I2C_SLV0_DO      0x63
//#define MPU6050_RA_I2C_SLV1_DO      0x64
//#define MPU6050_RA_I2C_SLV2_DO      0x65
//#define MPU6050_RA_I2C_SLV3_DO      0x66
//#define MPU6050_RA_I2C_MST_DELAY_CTRL   0x67
//#define MPU6050_RA_SIGNAL_PATH_RESET    0x68
//#define MPU6050_RA_MOT_DETECT_CTRL      0x69
//#define MPU6050_RA_USER_CTRL        0x6A
//#define MPU6050_RA_PWR_MGMT_1       0x6B
//#define MPU6050_RA_PWR_MGMT_2       0x6C
//#define MPU6050_RA_BANK_SEL         0x6D
//#define MPU6050_RA_MEM_START_ADDR   0x6E
//#define MPU6050_RA_MEM_R_W          0x6F
//#define MPU6050_RA_DMP_CFG_1        0x70
//#define MPU6050_RA_DMP_CFG_2        0x71
//#define MPU6050_RA_FIFO_COUNTH      0x72
//#define MPU6050_RA_FIFO_COUNTL      0x73
//#define MPU6050_RA_FIFO_R_W         0x74
//#define MPU6050_RA_WHO_AM_I         0x75

//#define MPU6050_TC_PWR_MODE_BIT     7
//#define MPU6050_TC_OFFSET_BIT       6
//#define MPU6050_TC_OFFSET_LENGTH    6
//#define MPU6050_TC_OTP_BNK_VLD_BIT  0

//#define MPU6050_VDDIO_LEVEL_VLOGIC  0
//#define MPU6050_VDDIO_LEVEL_VDD     1

//#define MPU6050_CFG_EXT_SYNC_SET_BIT    5
//#define MPU6050_CFG_EXT_SYNC_SET_LENGTH 3
//#define MPU6050_CFG_DLPF_CFG_BIT    2
//#define MPU6050_CFG_DLPF_CFG_LENGTH 3

//#define MPU6050_EXT_SYNC_DISABLED       0x0
//#define MPU6050_EXT_SYNC_TEMP_OUT_L     0x1
//#define MPU6050_EXT_SYNC_GYRO_XOUT_L    0x2
//#define MPU6050_EXT_SYNC_GYRO_YOUT_L    0x3
//#define MPU6050_EXT_SYNC_GYRO_ZOUT_L    0x4
//#define MPU6050_EXT_SYNC_ACCEL_XOUT_L   0x5
//#define MPU6050_EXT_SYNC_ACCEL_YOUT_L   0x6
//#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L   0x7

//#define MPU6050_DLPF_BW_256         0x00
//#define MPU6050_DLPF_BW_188         0x01
//#define MPU6050_DLPF_BW_98          0x02
//#define MPU6050_DLPF_BW_42          0x03
//#define MPU6050_DLPF_BW_20          0x04
//#define MPU6050_DLPF_BW_10          0x05
//#define MPU6050_DLPF_BW_5           0x06

//#define MPU6050_GCONFIG_FS_SEL_BIT      4
//#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

//#define MPU6050_GYRO_FS_250         0x00
//#define MPU6050_GYRO_FS_500         0x01
//#define MPU6050_GYRO_FS_1000        0x02
//#define MPU6050_GYRO_FS_2000        0x03

//#define MPU6050_ACONFIG_XA_ST_BIT           7
//#define MPU6050_ACONFIG_YA_ST_BIT           6
//#define MPU6050_ACONFIG_ZA_ST_BIT           5
//#define MPU6050_ACONFIG_AFS_SEL_BIT         4
//#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
//#define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
//#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

//#define MPU6050_ACCEL_FS_2          0x00
//#define MPU6050_ACCEL_FS_4          0x01
//#define MPU6050_ACCEL_FS_8          0x02
//#define MPU6050_ACCEL_FS_16         0x03

//#define MPU6050_DHPF_RESET          0x00
//#define MPU6050_DHPF_5              0x01
//#define MPU6050_DHPF_2P5            0x02
//#define MPU6050_DHPF_1P25           0x03
//#define MPU6050_DHPF_0P63           0x04
//#define MPU6050_DHPF_HOLD           0x07

//#define MPU6050_TEMP_FIFO_EN_BIT    7
//#define MPU6050_XG_FIFO_EN_BIT      6
//#define MPU6050_YG_FIFO_EN_BIT      5
//#define MPU6050_ZG_FIFO_EN_BIT      4
//#define MPU6050_ACCEL_FIFO_EN_BIT   3
//#define MPU6050_SLV2_FIFO_EN_BIT    2
//#define MPU6050_SLV1_FIFO_EN_BIT    1
//#define MPU6050_SLV0_FIFO_EN_BIT    0

//#define MPU6050_MULT_MST_EN_BIT     7
//#define MPU6050_WAIT_FOR_ES_BIT     6
//#define MPU6050_SLV_3_FIFO_EN_BIT   5
//#define MPU6050_I2C_MST_P_NSR_BIT   4
//#define MPU6050_I2C_MST_CLK_BIT     3
//#define MPU6050_I2C_MST_CLK_LENGTH  4

//#define MPU6050_CLOCK_DIV_348       0x0
//#define MPU6050_CLOCK_DIV_333       0x1
//#define MPU6050_CLOCK_DIV_320       0x2
//#define MPU6050_CLOCK_DIV_308       0x3
//#define MPU6050_CLOCK_DIV_296       0x4
//#define MPU6050_CLOCK_DIV_286       0x5
//#define MPU6050_CLOCK_DIV_276       0x6
//#define MPU6050_CLOCK_DIV_267       0x7
//#define MPU6050_CLOCK_DIV_258       0x8
//#define MPU6050_CLOCK_DIV_500       0x9
//#define MPU6050_CLOCK_DIV_471       0xA
//#define MPU6050_CLOCK_DIV_444       0xB
//#define MPU6050_CLOCK_DIV_421       0xC
//#define MPU6050_CLOCK_DIV_400       0xD
//#define MPU6050_CLOCK_DIV_381       0xE
//#define MPU6050_CLOCK_DIV_364       0xF

//#define MPU6050_I2C_SLV_RW_BIT      7
//#define MPU6050_I2C_SLV_ADDR_BIT    6
//#define MPU6050_I2C_SLV_ADDR_LENGTH 7
//#define MPU6050_I2C_SLV_EN_BIT      7
//#define MPU6050_I2C_SLV_BYTE_SW_BIT 6
//#define MPU6050_I2C_SLV_REG_DIS_BIT 5
//#define MPU6050_I2C_SLV_GRP_BIT     4
//#define MPU6050_I2C_SLV_LEN_BIT     3
//#define MPU6050_I2C_SLV_LEN_LENGTH  4

//#define MPU6050_I2C_SLV4_RW_BIT         7
//#define MPU6050_I2C_SLV4_ADDR_BIT       6
//#define MPU6050_I2C_SLV4_ADDR_LENGTH    7
//#define MPU6050_I2C_SLV4_EN_BIT         7
//#define MPU6050_I2C_SLV4_INT_EN_BIT     6
//#define MPU6050_I2C_SLV4_REG_DIS_BIT    5
//#define MPU6050_I2C_SLV4_MST_DLY_BIT    4
//#define MPU6050_I2C_SLV4_MST_DLY_LENGTH 5

//#define MPU6050_MST_PASS_THROUGH_BIT    7
//#define MPU6050_MST_I2C_SLV4_DONE_BIT   6
//#define MPU6050_MST_I2C_LOST_ARB_BIT    5
//#define MPU6050_MST_I2C_SLV4_NACK_BIT   4
//#define MPU6050_MST_I2C_SLV3_NACK_BIT   3
//#define MPU6050_MST_I2C_SLV2_NACK_BIT   2
//#define MPU6050_MST_I2C_SLV1_NACK_BIT   1
//#define MPU6050_MST_I2C_SLV0_NACK_BIT   0

//#define MPU6050_INTCFG_INT_LEVEL_BIT        7
//#define MPU6050_INTCFG_INT_OPEN_BIT         6
//#define MPU6050_INTCFG_LATCH_INT_EN_BIT     5
//#define MPU6050_INTCFG_INT_RD_CLEAR_BIT     4
//#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT  3
//#define MPU6050_INTCFG_FSYNC_INT_EN_BIT     2
//#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT    1
//#define MPU6050_INTCFG_CLKOUT_EN_BIT        0

//#define MPU6050_INTMODE_ACTIVEHIGH  0x00
//#define MPU6050_INTMODE_ACTIVELOW   0x01

//#define MPU6050_INTDRV_PUSHPULL     0x00
//#define MPU6050_INTDRV_OPENDRAIN    0x01

//#define MPU6050_INTLATCH_50USPULSE  0x00
//#define MPU6050_INTLATCH_WAITCLEAR  0x01

//#define MPU6050_INTCLEAR_STATUSREAD 0x00
//#define MPU6050_INTCLEAR_ANYREAD    0x01

//#define MPU6050_INTERRUPT_FF_BIT            7
//#define MPU6050_INTERRUPT_MOT_BIT           6
//#define MPU6050_INTERRUPT_ZMOT_BIT          5
//#define MPU6050_INTERRUPT_FIFO_OFLOW_BIT    4
//#define MPU6050_INTERRUPT_I2C_MST_INT_BIT   3
//#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT   2
//#define MPU6050_INTERRUPT_DMP_INT_BIT       1
//#define MPU6050_INTERRUPT_DATA_RDY_BIT      0

//// TODO: figure out what these actually do
//// UMPL source code is not very obivous
//#define MPU6050_DMPINT_5_BIT            5
//#define MPU6050_DMPINT_4_BIT            4
//#define MPU6050_DMPINT_3_BIT            3
//#define MPU6050_DMPINT_2_BIT            2
//#define MPU6050_DMPINT_1_BIT            1
//#define MPU6050_DMPINT_0_BIT            0

//#define MPU6050_MOTION_MOT_XNEG_BIT     7
//#define MPU6050_MOTION_MOT_XPOS_BIT     6
//#define MPU6050_MOTION_MOT_YNEG_BIT     5
//#define MPU6050_MOTION_MOT_YPOS_BIT     4
//#define MPU6050_MOTION_MOT_ZNEG_BIT     3
//#define MPU6050_MOTION_MOT_ZPOS_BIT     2
//#define MPU6050_MOTION_MOT_ZRMOT_BIT    0

//#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
//#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
//#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
//#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
//#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
//#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

//#define MPU6050_PATHRESET_GYRO_RESET_BIT    2
//#define MPU6050_PATHRESET_ACCEL_RESET_BIT   1
//#define MPU6050_PATHRESET_TEMP_RESET_BIT    0

//#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT       5
//#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH    2
//#define MPU6050_DETECT_FF_COUNT_BIT             3
//#define MPU6050_DETECT_FF_COUNT_LENGTH          2
//#define MPU6050_DETECT_MOT_COUNT_BIT            1
//#define MPU6050_DETECT_MOT_COUNT_LENGTH         2

//#define MPU6050_DETECT_DECREMENT_RESET  0x0
//#define MPU6050_DETECT_DECREMENT_1      0x1
//#define MPU6050_DETECT_DECREMENT_2      0x2
//#define MPU6050_DETECT_DECREMENT_4      0x3

//#define MPU6050_USERCTRL_DMP_EN_BIT             7
//#define MPU6050_USERCTRL_FIFO_EN_BIT            6
//#define MPU6050_USERCTRL_I2C_MST_EN_BIT         5
//#define MPU6050_USERCTRL_I2C_IF_DIS_BIT         4
//#define MPU6050_USERCTRL_DMP_RESET_BIT          3
//#define MPU6050_USERCTRL_FIFO_RESET_BIT         2
//#define MPU6050_USERCTRL_I2C_MST_RESET_BIT      1
//#define MPU6050_USERCTRL_SIG_COND_RESET_BIT     0

//#define MPU6050_PWR1_DEVICE_RESET_BIT   7
//#define MPU6050_PWR1_SLEEP_BIT          6
//#define MPU6050_PWR1_CYCLE_BIT          5
//#define MPU6050_PWR1_TEMP_DIS_BIT       3
//#define MPU6050_PWR1_CLKSEL_BIT         2
//#define MPU6050_PWR1_CLKSEL_LENGTH      3

//#define MPU6050_CLOCK_INTERNAL          0x00
//#define MPU6050_CLOCK_PLL_XGYRO         0x01
//#define MPU6050_CLOCK_PLL_YGYRO         0x02
//#define MPU6050_CLOCK_PLL_ZGYRO         0x03
//#define MPU6050_CLOCK_PLL_EXT32K        0x04
//#define MPU6050_CLOCK_PLL_EXT19M        0x05
//#define MPU6050_CLOCK_KEEP_RESET        0x07

//#define MPU6050_PWR2_LP_WAKE_CTRL_BIT       7
//#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH    2
//#define MPU6050_PWR2_STBY_XA_BIT            5
//#define MPU6050_PWR2_STBY_YA_BIT            4
//#define MPU6050_PWR2_STBY_ZA_BIT            3
//#define MPU6050_PWR2_STBY_XG_BIT            2
//#define MPU6050_PWR2_STBY_YG_BIT            1
//#define MPU6050_PWR2_STBY_ZG_BIT            0

//#define MPU6050_WAKE_FREQ_1P25      0x0
//#define MPU6050_WAKE_FREQ_2P5       0x1
//#define MPU6050_WAKE_FREQ_5         0x2
//#define MPU6050_WAKE_FREQ_10        0x3

//#define MPU6050_BANKSEL_PRFTCH_EN_BIT       6
//#define MPU6050_BANKSEL_CFG_USER_BANK_BIT   5
//#define MPU6050_BANKSEL_MEM_SEL_BIT         4
//#define MPU6050_BANKSEL_MEM_SEL_LENGTH      5

//#define MPU6050_WHO_AM_I_BIT        6
//#define MPU6050_WHO_AM_I_LENGTH     6
//extern	short gyro[3], accel[3];
//extern int16_t Gx_offset,Gy_offset,Gz_offset;
//extern float Acc1G_Values;
//extern float Pitch,Roll; 
////供外部调用的API
//void MPU6050_initialize(void); //初始化
//uint8_t MPU6050_testConnection(void); //检测MPU6050是否存在
////读取ADC值
//void MPU6050_getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
//void MPU6050_getlastMotion6(int16_t* ax, int16_t* ay, 
//		int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
//uint8_t MPU6050_getDeviceID(void); //读取MPU6050的ID
//void MPU6050_InitGyro_Offset(void);//初始化陀螺仪偏置
//void DMP_Init(void);
//void Read_DMP(void);
//int Read_Temperature(void);
//#endif
