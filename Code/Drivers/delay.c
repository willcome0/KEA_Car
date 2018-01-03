#include "delay.h"
#include "common.h"

/*************************************************************************
*函数名：  SysTickInt_Config
*函数功能：系统滴答定时器中断初始化
*入口参数： int_ms: 设定中断时间（ms）
*返回值：  无
*检验：    K
*时间：	   2017.11.19
*备注：	   参照书上与逐飞
*举例：    SysTickInt_Init(10);   10ms中断一次
**************************************************************************/

void SysTickInt_Init(uint32_t int_ms)
{
	SysTick->CTRL = 0;   //设置前先关闭systick
	SysTick->VAL  = 0;   //清除计数器
    //根据计数频率，确定并设置重载寄存器的值
    if(0)              //0:内核时钟/16
    {
    	SysTick->LOAD = CORE_CLK_KHZ*int_ms/16;
     }
    else                            //1:内核时钟
    {
    	SysTick->LOAD = CORE_CLK_KHZ*int_ms;
//        clk_src_sel=1;              //防止入口参数错，提高程序健壮性
    }
    // 设定 SysTick优先级为2
    SCB->SHP[2] |=(0x02)<<30;

    //设置时钟源,允许中断,使能该模块,开始计数
    SysTick->CTRL = (1<<SysTick_CTRL_CLKSOURCE_Pos) |
    		     SysTick_CTRL_ENABLE_Msk |
				 SysTick_CTRL_TICKINT_Msk;
}

/*************************************************************************
*函数名：  SysTick_Handler
*函数功能：系统滴答定时器中断服务函数
*入口参数： 无
*返回值：  无
*检验：    K
*时间：	   2017.11.19
*备注：	   
*举例：    
**************************************************************************/

void SysTick_Handler(void)
{

    
}

/*************************************************************************
*函数名：  Delay_us
*函数功能：纳秒级延时
*入口参数： us: 设定延时时间（us）
*返回值：  无
*检验：    K
*时间：	   2017.11.19
*备注：	   参照书上与逐飞，用我垃圾逻辑仪测误差大概3us
*举例：    Delay_us(10);   延时10us
**************************************************************************/

//void Delay_us(uint32_t us)
//{	
//if(us == 0)  //要比那个2.5大
//    return;
//SysTick->CTRL = 0;   //设置前先关闭systick
//SysTick->VAL  = 0;   //清除计数器

////根据计数频率，确定并设置重载寄存器的值
//    SysTick->LOAD = CORE_CLK_KHZ/1000*us;
////SysTick->LOAD = 1;
////    // 设定 SysTick优先级为2
////    SCB->SHP[2] |=(0x02)<<30;

////设置时钟源,,使能该模块,开始计数
//SysTick->CTRL = (1<<SysTick_CTRL_CLKSOURCE_Pos) |
//                SysTick_CTRL_ENABLE_Msk;

//while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//等待时间到
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
*函数名：  Delay_us
*函数功能：PIT定时器中断配置
*入口参数：us: 定时器中断时间
*返回值：  无
*作者：    K
*时间：	   2017.11.19
*备注：	   虽然垃圾但真的很准，而且节省单片机资源。比系统滴答做的好用  
**************************************************************************/
void Delay_us(uint32_t us)
{
#if CLOCK_SETUP == 1 //80M主频的方案
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
*函数名：  Delay_us
*函数功能：毫秒级延时
*入口参数： ms: 设定延时时间（ms）
*返回值：  无
*检验：    K
*时间：	   2017.11.19
*备注：	   参照书上与逐飞
*举例：    Delay_ms(10);   延时10ms
**************************************************************************/

//void Delay_ms(uint32_t ms)
//{	
//    if(ms == 0)
//        return;
//    SysTick->CTRL = 0;   //设置前先关闭systick
//	SysTick->VAL  = 0;   //清除计数器
//    //根据计数频率，确定并设置重载寄存器的值

//    SysTick->LOAD = CORE_CLK_KHZ*ms;

////    // 设定 SysTick优先级为2
////    SCB->SHP[2] |=(0x02)<<30;

//    //设置时钟源,使能该模块,开始计数
//    SysTick->CTRL = (1<<SysTick_CTRL_CLKSOURCE_Pos) |
//    		     SysTick_CTRL_ENABLE_Msk;

//    while( !(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));//等待时间到
//}
/*************************************************************************
*函数名：  Delay_ms
*函数功能：PIT定时器中断配置
*入口参数：ms: 定时器中断时间
*返回值：  无
*作者：    K
*时间：	   2017.11.19
*备注：	   虽然垃圾但真的很准，而且节省单片机资源。比系统滴答做的好用  
**************************************************************************/
void Delay_ms(uint32_t ms)
{
#if CLOCK_SETUP == 1 //80M主频的方案
    for(uint16_t i=0; i<ms; i++)
#elif CLOCK_SETUP == 2 && CLOCK_SETUP == 0 //40M
    for(uint16_t i=0; i<ms; i++)
#endif
    {
        Delay_us(999);
        __ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");__ASM("nop");
    }
}