#include "pit.h"


/*************************************************************************
*��������  PIT_Config
*�������ܣ�PIT��ʱ���ж�����
*��ڲ����� pitno: PIT��
           ms: ��ʱ���ж�ʱ��
           priority: ���ȼ�
*����ֵ��  ��
*���ԣ�    K
*ʱ�䣺	   2017.11.19
*��ע��	   ��Ҫ��ȡ���̵��жϣ���С�� PIT_LDVAL(pitno) �ĸ�ֵ���ɡ��ٷ��Ĳ������÷ǳ��࣬�пտ��Կ������˴������
*������    PIT_Config(PIT_CH1, 1, 1);  PIT_CH1����1ms�жϣ����ȼ�Ϊ1
**************************************************************************/

void PIT_Config(uint8_t PIT_CHX, uint32_t ms, uint8_t priority)
{
    SIM_SCGC |= SIM_SCGC_PIT_MASK;  //ʹ��PITʱ����
    PIT_MCR &= ~PIT_MCR_MDIS_MASK;  //ʹ��PITģ��

    NVIC_DisableIRQ(PIT_CH_IRQ_NO + PIT_CHX);  //���ܸ��ж�

    //����PITģ��
    PIT_LDVAL(PIT_CHX) = BUS_CLK_KHZ * ms;
    PIT_TCTRL(PIT_CHX) |= (PIT_TCTRL_TIE_MASK);     //��pitģ���ж�
    PIT_TCTRL(PIT_CHX) |= (PIT_TCTRL_TEN_MASK);     //ʹ��pitģ������

    NVIC_SetPriority(PIT_CH_IRQ_NO + PIT_CHX, priority);
    
    NVIC_EnableIRQ(PIT_CH_IRQ_NO + PIT_CHX);   //ʹ�ܸ��ж�
}

/**************************************************************************/

/*********************PIT�жϷ�����***************************************/



void PIT_CH1_IRQHandler(void)
{
    PIT_CLR_Flag(PIT_CH1);  //����жϱ�־λ
//    Disable_PIT_CH1();
    /*�ж�����--��ʼ*/
//        MPU6050_GetData(&GYRO, &ACC);	// ��ȡ����������
//        Data_Filter();
    // ��ԭʼ���ݻ����˲�
    Pin_Output_Toggle(LED_Green_Port, LED_Green_Pin);


    
    Pin_Output_Toggle(PTE, PTE0);
    /*�ж�����--����*/
//    Enable_PIT_CH1();
}

