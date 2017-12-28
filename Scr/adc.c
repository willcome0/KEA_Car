#include "adc.h"

//===========================================================================
//函数名称：adc_init
//功能概要：初始化一个AD转换通道
//参数说明：channel：通道号
//       accurary：单端采样精度8-10-12
//===========================================================================

void ADC_Config(uint8_t channel)
{
    //1.打开ADC模块时钟
    SIM_SCGC |= SIM_SCGC_ADC_MASK;
    //开启引脚的AD功能
    ADC_APCTL1 |=0x0F;
    //选择总线时钟
    ADC_SC3 = (ADC_SC3 & ~ADC_SC3_ADICLK_MASK) | ADC_SC3_ADICLK(0x00);
    //输入时钟4分频
    ADC_SC3 = (ADC_SC3 & ~ADC_SC3_ADIV_MASK) | ADC_SC3_ADIV(0x10);
    //2.2 根据采样精度   定ADC_SC3_MODE位
	 ADC_SC3 |= ADC_SC3_MODE(2);       //选择12位转换模式

    ADC_SC2 = 0x00;
    //4.配置ADC_SC1：使能ADC，并设置为连续转换模式,使能外部引脚
    ADC_SC1|= ADC_SC1_ADCO_MASK;
    //选择采样通道
    ADC_SC1|=ADC_SC1_ADCH(channel);
}

//============================================================================
//函数名称：adc_readonce
//功能概要：对AD通道进行一次采样
//参数说明：channel：通道范围 0~31
//============================================================================
uint16_t ADC_Get(uint8_t channel)
{
    uint16_t ADCResult = 0;
    //设置SC1寄存器通道号
    ADC_SC1 = (ADC_SC1 & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(channel);
    
    //等待转换完成
    while(!(ADC_SC1 & ADC_SC1_COCO_MASK));

    //读取转换结果
    ADCResult = (uint16_t)ADC_R;
    //清ADC转换完成标志
    ADC_SC1 &= ~ADC_SC1_COCO_MASK;
    //返回读取结果
    return ADCResult;
}
//============================================================================
//函数名称：ad_mid
//函数返回：16位无符号的AD值，中值滤波后的结果(范围:0-4095)
//参数说明：channel：通道号
//功能概要：采样三次，取中值
//============================================================================
uint16_t ADC_Mid(uint8_t channel)
{
	uint16_t i,j,k,tmp;
	//1.取3次A/D转换结果
	i = ADC_Get(channel);
	j = ADC_Get(channel);
	k = ADC_Get(channel);
	//2.取中值
	if (i > j)
	{
	    tmp = i; i = j; j = tmp;
	}
	if (k > j)
	  tmp = j;
	else if(k > i)
	  tmp = k;
    else
      tmp = i;
	return tmp;
}

//============================================================================
//函数名称：ad_ave
//函数返回：16位无符号的AD值，中值+均值滤波后的结果(范围:0~4095)
//参数说明：channel：通道号
//      N:均值次数(范围:0~255)，每次调用中值滤波获得
//功能概要：中值+均值滤波,实际采样次数=3*N
//============================================================================
uint16_t ADC_Ave(uint8_t channel, int N)
{

	long int i;
	float tmp;
    int  j;

    i=0;
    for(j = 0; j < N; j++) i=i+(long int)ADC_Mid(channel);
    tmp =i / N;

    return (uint16_t)tmp;
}
