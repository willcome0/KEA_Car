#include "adc.h"

//===========================================================================
//�������ƣ�adc_init
//���ܸ�Ҫ����ʼ��һ��ADת��ͨ��
//����˵����channel��ͨ����
//       accurary�����˲�������8-10-12
//===========================================================================

void ADC_Config(uint8_t channel)
{
    //1.��ADCģ��ʱ��
    SIM_SCGC |= SIM_SCGC_ADC_MASK;
    //�������ŵ�AD����
    ADC_APCTL1 |=0x0F;
    //ѡ������ʱ��
    ADC_SC3 = (ADC_SC3 & ~ADC_SC3_ADICLK_MASK) | ADC_SC3_ADICLK(0x00);
    //����ʱ��4��Ƶ
    ADC_SC3 = (ADC_SC3 & ~ADC_SC3_ADIV_MASK) | ADC_SC3_ADIV(0x10);
    //2.2 ���ݲ�������   ��ADC_SC3_MODEλ
	 ADC_SC3 |= ADC_SC3_MODE(2);       //ѡ��12λת��ģʽ

    ADC_SC2 = 0x00;
    //4.����ADC_SC1��ʹ��ADC��������Ϊ����ת��ģʽ,ʹ���ⲿ����
    ADC_SC1|= ADC_SC1_ADCO_MASK;
    //ѡ�����ͨ��
    ADC_SC1|=ADC_SC1_ADCH(channel);
}

//============================================================================
//�������ƣ�adc_readonce
//���ܸ�Ҫ����ADͨ������һ�β���
//����˵����channel��ͨ����Χ 0~31
//============================================================================
uint16_t ADC_Get(uint8_t channel)
{
    uint16_t ADCResult = 0;
    //����SC1�Ĵ���ͨ����
    ADC_SC1 = (ADC_SC1 & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(channel);
    
    //�ȴ�ת�����
    while(!(ADC_SC1 & ADC_SC1_COCO_MASK));

    //��ȡת�����
    ADCResult = (uint16_t)ADC_R;
    //��ADCת����ɱ�־
    ADC_SC1 &= ~ADC_SC1_COCO_MASK;
    //���ض�ȡ���
    return ADCResult;
}
//============================================================================
//�������ƣ�ad_mid
//�������أ�16λ�޷��ŵ�ADֵ����ֵ�˲���Ľ��(��Χ:0-4095)
//����˵����channel��ͨ����
//���ܸ�Ҫ���������Σ�ȡ��ֵ
//============================================================================
uint16_t ADC_Mid(uint8_t channel)
{
	uint16_t i,j,k,tmp;
	//1.ȡ3��A/Dת�����
	i = ADC_Get(channel);
	j = ADC_Get(channel);
	k = ADC_Get(channel);
	//2.ȡ��ֵ
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
//�������ƣ�ad_ave
//�������أ�16λ�޷��ŵ�ADֵ����ֵ+��ֵ�˲���Ľ��(��Χ:0~4095)
//����˵����channel��ͨ����
//      N:��ֵ����(��Χ:0~255)��ÿ�ε�����ֵ�˲����
//���ܸ�Ҫ����ֵ+��ֵ�˲�,ʵ�ʲ�������=3*N
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
