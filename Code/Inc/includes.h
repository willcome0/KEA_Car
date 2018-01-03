//============================================================================
//�ļ����ƣ�includes.h
//���ܸ�Ҫ��������ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2014-12-10  V1.0
//оƬ���ͣ�KEA128
//============================================================================

#ifndef _INCLUDES_H  //��ֹ�ظ����壨��ͷ��
#define _INCLUDES_H

//����ʹ�õ��Ĺ���ͷ�ļ�
#include "common.h"
#include "gpio.h"

//��ֹȫ�ֱ����ظ�������ǰ׺������
#ifdef GLOBLE_VAR                 //GLOBLE_VAR��main.c�ļ��к궨��
#define G_VAR_PREFIX          //main.c�ļ���ʹ��ȫ�ֱ������ӡ�extern��ǰ׺
#else
#define G_VAR_PREFIX  extern  //�����ļ���ʹ��ȫ�ֱ����Զ��ӡ�extern��ǰ׺
#endif
//����ȫ�ֱ�����ȫ�ֱ�������ǰһ��ǰ׺G_VAR_PREFIX��
G_VAR_PREFIX char g_uart_num;


//����곣��
#define RUN_COUNTER_MAX   1500000ul   //С����˸Ƶ��

#define BME_AND_MASK	(1<<26)//addr[28:26]=001ָ����AND����
#define BME_OR_MASK	    (1<<27)//addr[28:26]=010ָ����OR����
#define BME_SRAM_U_MASK	(1<<29)//addr[30��29]=01ָ��SRAM_U
#define BME_IO_MASK	    (1<<30)//addr[30��29]=10ָ������λ
#define BME_SRAM_MASK	(1<<29)//addr[30��29]=01ָ������λ

//addr[28:26]=010��ʾ���������addr[25:21]�ǡ�BIT����Ӧ��λ��־��
#define BME_LAC1_MASK(BIT)	(1<<27) | (BIT<<21
//addr[28:26]=010��ʾ��λ������addr[25:21]�ǡ�BIT����Ӧ��λ��־��
#define BME_LAS1_MASK(BIT)	(3<<26) | (BIT<<21)

#define BME_AND_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_AND_MASK| BME_IO_MASK)=w)
#define BME_OR_IO(addr,w) (*(volatile unsigned long int*) ((addr)| BME_OR_MASK| BME_IO_MASK)=w)

#define SRAM_U  ((unsigned long int) 0x20000000) // SRAM_Uλ��������ַ
#define SRAM_U_B  ((unsigned long int ) 0x22000000) // SRAM_Uλ������������ַ


#define SET_SRAM_U(X,M,S) (*(volatile unsigned long int*) (SRAM_U_B+((X)-SRAM_U)*32+(M)*4)= (S))
#define BME_AND_SRAM(addr,w) (*(volatile unsigned long int*) ((addr)| BME_AND_MASK| BME_SRAM_MASK)=w)


//��ֹȫ�ֱ����ظ�������ǰ׺������
#ifdef GLOBLE_VAR                 //GLOBLE_VAR��main.c�ļ��к궨��
#define G_VAR_PREFIX          //main.c�ļ���ʹ��ȫ�ֱ������ӡ�extern��ǰ׺
#else
#define G_VAR_PREFIX  extern  //�����ļ���ʹ��ȫ�ֱ����Զ��ӡ�extern��ǰ׺
#endif
//����ȫ�ֱ�����ȫ�ֱ�������ǰһ��ǰ׺G_VAR_PREFIX��
G_VAR_PREFIX char g_uart_num;
G_VAR_PREFIX uint32_t positive_pulse, negative_pulse;
G_VAR_PREFIX uint8_t counter_overflow;
G_VAR_PREFIX uint32_t timer_counter;
G_VAR_PREFIX float frequency, period;
G_VAR_PREFIX float decimals;


#endif              //��ֹ�ظ����壨��β��
