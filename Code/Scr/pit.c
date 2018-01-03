#include "pit.h"


/*************************************************************************
*函数名：  PIT_Config
*函数功能：PIT定时器中断配置
*入口参数： pitno: PIT号
           ms: 定时器中断时间
           priority: 优先级
*返回值：  无
*测试：    K
*时间：	   2017.11.19
*备注：	   若要获取更短的中断，减小对 PIT_LDVAL(pitno) 的赋值即可。官方的参数设置非常多，有空可以看看。此处是逐飞
*举例：    PIT_Config(PIT_CH1, 1, 1);  PIT_CH1开启1ms中断，优先级为1
**************************************************************************/

void PIT_Config(uint8_t PIT_CHX, uint32_t ms, uint8_t priority)
{
    SIM_SCGC |= SIM_SCGC_PIT_MASK;  //使能PIT时钟门
    PIT_MCR &= ~PIT_MCR_MDIS_MASK;  //使能PIT模块

    NVIC_DisableIRQ(PIT_CH_IRQ_NO + PIT_CHX);  //禁能该中断

    //配置PIT模块
    PIT_LDVAL(PIT_CHX) = BUS_CLK_KHZ * ms;
    PIT_TCTRL(PIT_CHX) |= (PIT_TCTRL_TIE_MASK);     //开pit模块中断
    PIT_TCTRL(PIT_CHX) |= (PIT_TCTRL_TEN_MASK);     //使能pit模块运行

    NVIC_SetPriority(PIT_CH_IRQ_NO + PIT_CHX, priority);
    
    NVIC_EnableIRQ(PIT_CH_IRQ_NO + PIT_CHX);   //使能该中断
}

/**************************************************************************/

/*********************PIT中断服务函数***************************************/



void PIT_CH1_IRQHandler(void)
{
    uint8_t ch[30];
    PIT_CLR_Flag(PIT_CH1);  //清除中断标志位
//    Disable_PIT_CH1();
    /*中断内容--开始*/
//        MPU6050_GetData(&GYRO, &ACC);	// 读取陀螺仪数据
//        Data_Filter();
    // 对原始数据滑动滤波
    
//    Pin_Output_Toggle(LED_Green_Port, LED_Green_Pin);


//       int16_t Value_End_L = Read_Input_State(Dir_End_L_Port, Dir_End_L_Pin)==0? ftm_count_get(ftm0) : -ftm_count_get(ftm0); 
//       int16_t Value_End_R = Read_Input_State(Dir_End_R_Port, Dir_End_R_Pin)==0? ftm_count_get(ftm1) : -ftm_count_get(ftm1);
//            sprintf(ch,"L_编码器:%5d ", Value_End_L); 
//        OLED_Show_StrAll(0,  26, ch, 1);
//        sprintf(ch,"R_编码器:%5d ", Value_End_R);
////        sprintf(ch, "   2.  目标角度  %1.2f", (float)Plan1.Target.Speed/100);
//        OLED_Show_StrAll(0,  39, ch, 1);
//        
//        ftm_count_clean(ftm0);
//        ftm_count_clean(ftm1);
//        
//        OLED_Refresh_Gram();
    
    

    /*中断内容--结束*/
//    Enable_PIT_CH1();
}

