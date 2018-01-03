#include "delay.h"
#include "common.h"

/*************************************************************************
*��������  SysTickInt_Config
*�������ܣ�ϵͳ�δ�ʱ���жϳ�ʼ��
*��ڲ����� int_ms: �趨�ж�ʱ�䣨ms��
*����ֵ��  ��
*���飺    K
*ʱ�䣺	   2017.11.19
*��ע��	   �������������
*������    SysTickInt_Init(10);   10ms�ж�һ��
**************************************************************************/

void SysTickInt_Init(uint32_t int_ms)
{
	SysTick->CTRL = 0;   //����ǰ�ȹر�systick
	SysTick->VAL  = 0;   //���������
    //���ݼ���Ƶ�ʣ�ȷ�����������ؼĴ�����ֵ
    if(0)              //0:�ں�ʱ��/16
    {
    	SysTick->LOAD = CORE_CLK_KHZ*int_ms/16;
     }
    else                            //1:�ں�ʱ��
    {
    	SysTick->LOAD = CORE_CLK_KHZ*int_ms;
//        clk_src_sel=1;              //��ֹ��ڲ�������߳���׳��
    }
    // �趨 SysTick���ȼ�Ϊ2
    SCB->SHP[2] |=(0x02)<<30;

    //����ʱ��Դ,�����ж�,ʹ�ܸ�ģ��,��ʼ����
    SysTick->CTRL = (1<<SysTick_CTRL_CLKSOURCE_Pos) |
    		     SysTick_CTRL_ENABLE_Msk |
				 SysTick_CTRL_TICKINT_Msk;
}

/*************************************************************************
*��������  SysTick_Handler
*�������ܣ�ϵͳ�δ�ʱ���жϷ�����
*��ڲ����� ��
*����ֵ��  ��
*���飺    K
*ʱ�䣺	   2017.11.19
*��ע��	   
*������    
**************************************************************************/

void SysTick_Handler(void)
{

    
}

/*************************************************************************
*��������  Delay_us
*�������ܣ����뼶��ʱ
*��ڲ����� us: �趨��ʱʱ�䣨us��
*����ֵ��  ��
*���飺    K
*ʱ�䣺	   2017.11.19
*��ע��	   ������������ɣ����������߼��ǲ������3us
*������    Delay_us(10);   ��ʱ10us
**************************************************************************/

//void Delay_us(uint32_t us)
//{	
//if(us == 0)  //Ҫ���Ǹ�2.5��
//    return;
//SysTick->CTRL = 0;   //����ǰ�ȹر�systick
//SysTick->VAL  = 0;   //���������

////���ݼ���Ƶ�ʣ�ȷ�����������ؼĴ�����ֵ
//    SysTick->LOAD = CORE_CLK_KHZ/1000*us;
////SysTick->LOAD = 1;
////    // �趨 SysTick���ȼ�Ϊ2
////    SCB->SHP[2] |=(0x02)<<30;

////����ʱ��Դ,,ʹ�ܸ�ģ��,��ʼ����
//SysTick->CTRL = (1<<SysTick_CTRL_CLKSOURCE_Pos) |
//                SysTick_CTRL_ENABLE_Msk;

//while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//�ȴ�ʱ�䵽
//}
//void Delay_us(uint32_t us)
//{	
////    for(uint16_t i=0; i<us; i++)
////    {
////        for(uint32_t j=0; j<1; j++)
////        {
////            __ASM("nop");
////        }
////    }
////    for(int8_t i=0; i<1; i++)
////    {
////        
////        __ASM("nop");
////    }
////    __ASM("nop");
////    __ASM("nop");
//}

/*************************************************************************
*��������  Delay_us
*�������ܣ�PIT��ʱ���ж�����
*��ڲ�����us: ��ʱ���ж�ʱ��
*����ֵ��  ��
*���ߣ�    K
*ʱ�䣺	   2017.11.19
*��ע��	   ��Ȼ��������ĺ�׼�����ҽ�ʡ��Ƭ����Դ����ϵͳ�δ����ĺ���  
**************************************************************************/
void Delay_us(uint32_t us)
{
#if CLOCK_SETUP == 1 //80M��Ƶ�ķ���
    for(uint16_t i=0; i<us*2; i++)
#elif CLOCK_SETUP == 2 && CLOCK_SETUP == 0 //40M
    for(uint16_t i=0; i<us; i++)
#endif
    {
		__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");
        __ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");

    }
}
/*************************************************************************
*��������  Delay_us
*�������ܣ����뼶��ʱ
*��ڲ����� ms: �趨��ʱʱ�䣨ms��
*����ֵ��  ��
*���飺    K
*ʱ�䣺	   2017.11.19
*��ע��	   �������������
*������    Delay_ms(10);   ��ʱ10ms
**************************************************************************/

//void Delay_ms(uint32_t ms)
//{	
//    if(ms == 0)
//        return;
//    SysTick->CTRL = 0;   //����ǰ�ȹر�systick
//	SysTick->VAL  = 0;   //���������
//    //���ݼ���Ƶ�ʣ�ȷ�����������ؼĴ�����ֵ

//    SysTick->LOAD = CORE_CLK_KHZ*ms;

////    // �趨 SysTick���ȼ�Ϊ2
////    SCB->SHP[2] |=(0x02)<<30;

//    //����ʱ��Դ,ʹ�ܸ�ģ��,��ʼ����
//    SysTick->CTRL = (1<<SysTick_CTRL_CLKSOURCE_Pos) |
//    		     SysTick_CTRL_ENABLE_Msk;

//    while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//�ȴ�ʱ�䵽
//}
/*************************************************************************
*��������  Delay_ms
*�������ܣ�PIT��ʱ���ж�����
*��ڲ�����ms: ��ʱ���ж�ʱ��
*����ֵ��  ��
*���ߣ�    K
*ʱ�䣺	   2017.11.19
*��ע��	   ��Ȼ��������ĺ�׼�����ҽ�ʡ��Ƭ����Դ����ϵͳ�δ����ĺ���  
**************************************************************************/
void Delay_ms(uint32_t ms)
{
#if CLOCK_SETUP == 1 //80M��Ƶ�ķ���
    for(uint16_t i=0; i<ms; i++)
#elif CLOCK_SETUP == 2 && CLOCK_SETUP == 0 //40M
    for(uint16_t i=0; i<ms; i++)
#endif
    {
        Delay_us(999);
        __ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");
    }
}