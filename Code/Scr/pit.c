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
//    uint8_t ch[30];
    PIT_CLR_Flag(PIT_CH1);  //����жϱ�־λ
//    Disable_PIT_CH1();
    /*�ж�����--��ʼ*/
//        MPU6050_GetData(&GYRO, &ACC);	// ��ȡ����������
//        Data_Filter();
    // ��ԭʼ���ݻ����˲�
    
//    Pin_Output_Toggle(LED_Green_Port, LED_Green_Pin);


//       int16_t Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? ftm_count_get(ftm0) : -ftm_count_get(ftm0); 
//       int16_t Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0? ftm_count_get(ftm1) : -ftm_count_get(ftm1);
//            sprintf(ch,"L_������:%5d ", Value_End_L); 
//        OLED_Show_StrAll(0,  26, ch, 1);
//        sprintf(ch,"R_������:%5d ", Value_End_R);
////        sprintf(ch, "   2.  Ŀ��Ƕ�  %1.2f", (float)Plan1.Target.Speed/100);
//        OLED_Show_StrAll(0,  39, ch, 1);
//        
//        ftm_count_clean(ftm0);
//        ftm_count_clean(ftm1);
//        
//        OLED_Refresh_Gram();
    
    

    /*�ж�����--����*/
//    Enable_PIT_CH1();
}
