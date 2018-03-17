#ifndef PIT_H
#define PIT_H

#include "common.h"

//Ϊ����PIT�Ŵ���
//#define PIT_CH_IRQ_NO 22

#define PIT_CH0 0
#define PIT_CH1 1

/***********************************************************
 * 
 * PITʹ�������
 * 
 **********************************************************/
#define Enable_PIT_CH0()    NVIC_EnableIRQ(PIT_CH0_IRQn)
#define Enable_PIT_CH1()    NVIC_EnableIRQ(PIT_CH1_IRQn)

#define Disable_PIT_CH0()   NVIC_DisableIRQ(PIT_CH0_IRQn)
#define Disable_PIT_CH1()   NVIC_DisableIRQ(PIT_CH1_IRQn)

/***********************************************************
 * 
 * ����������궨��
 * 
 **********************************************************/
void PIT_Config(uint8_t pitno, uint32_t ms, uint8_t priority);
#define PIT_CLR_Flag(PIT_CHX)   PIT->CHANNEL[PIT_CHX].TFLG |= PIT_TFLG_TIF_MASK




#endif


