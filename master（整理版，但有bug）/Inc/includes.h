//============================================================================
//文件名称：includes.h
//功能概要：工程总头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2014-12-10  V1.0
//芯片类型：KEA128
//============================================================================

#ifndef _INCLUDES_H  //防止重复定义（开头）
#define _INCLUDES_H

//包含使用到的构件头文件
#include "common.h"
#include "gpio.h"

//防止全局变量重复声明的前缀处理方法
#ifdef GLOBLE_VAR                 //GLOBLE_VAR在main.c文件中宏定义
#define G_VAR_PREFIX          //main.c文件中使用全局变量不加“extern”前缀
#else
#define G_VAR_PREFIX  extern  //其他文件中使用全局变量自动加“extern”前缀
#endif
//声明全局变量（全局变量类型前一律前缀G_VAR_PREFIX）
G_VAR_PREFIX char g_uart_num;


//定义宏常数
#define RUN_COUNTER_MAX   1500000ul   //小灯闪烁频率

#define BME_AND_MASK	(1<<26)//addr[28:26]=001指定了AND操作
#define BME_OR_MASK	    (1<<27)//addr[28:26]=010指定了OR操作
#define BME_SRAM_U_MASK	(1<<29)//addr[30：29]=01指定SRAM_U
#define BME_IO_MASK	    (1<<30)//addr[30：29]=10指定外设位
#define BME_SRAM_MASK	(1<<29)//addr[30：29]=01指定外设位

//addr[28:26]=010表示清除操作；addr[25:21]是“BIT”对应的位标志符
#define BME_LAC1_MASK(BIT)	(1<<27) | (BIT<<21
//addr[28:26]=010表示置位操作；addr[25:21]是“BIT”对应的位标志符
#define BME_LAS1_MASK(BIT)	(3<<26) | (BIT<<21)

#define BME_AND_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_AND_MASK| BME_IO_MASK)=w)
#define BME_OR_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_OR_MASK| BME_IO_MASK)=w)

#define SRAM_U  ((unsigned long int) 0x20000000) // SRAM_U位带区基地址
#define SRAM_U_B  ((unsigned long int ) 0x22000000) // SRAM_U位带别名区基地址


#define SET_SRAM_U(X,M,S) (*(volatile unsigned long int*) (SRAM_U_B+((X)-SRAM_U)*32+(M)*4)= (S))
#define BME_AND_SRAM(addr,w) (*(volatile unsigned long int*) ((addr)| BME_AND_MASK| BME_SRAM_MASK)=w)


//防止全局变量重复声明的前缀处理方法
#ifdef GLOBLE_VAR                 //GLOBLE_VAR在main.c文件中宏定义
#define G_VAR_PREFIX          //main.c文件中使用全局变量不加“extern”前缀
#else
#define G_VAR_PREFIX  extern  //其他文件中使用全局变量自动加“extern”前缀
#endif
//声明全局变量（全局变量类型前一律前缀G_VAR_PREFIX）
G_VAR_PREFIX char g_uart_num;
G_VAR_PREFIX uint32_t positive_pulse, negative_pulse;
G_VAR_PREFIX uint8_t counter_overflow;
G_VAR_PREFIX uint32_t timer_counter;
G_VAR_PREFIX float frequency, period;
G_VAR_PREFIX float decimals;


#endif              //防止重复定义（结尾）
