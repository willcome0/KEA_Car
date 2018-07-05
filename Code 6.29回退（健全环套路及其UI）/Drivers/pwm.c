

#include "pwm.h"



static FTM_Type * const FTMX[] = FTM_BASES;

void ftm_pwm_mux(FTMn ftmn, FTM_CHn ch)
{
    switch(ftmn)
    {
//        case ftm0:
//        {
//            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
//            switch(ch)
//            {
//                case ftm_ch0:
//                {
//                    if(FTM0_CH0_PIN == PTA0)
//                    {
//                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS0_MASK;
//                    }
//                    else if(FTM0_CH0_PIN == PTB2)
//                    {
//                        SIM->PINSEL |= SIM_PINSEL_FTM0PS0_MASK;
//                    }
//                }break;
//                
//                case ftm_ch1:
//                {
//                    if(FTM0_CH1_PIN == PTA1)
//                    {
//                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS1_MASK;
//                    }
//                    else if(FTM0_CH1_PIN == PTB3)
//                    {
//                        SIM->PINSEL |= SIM_PINSEL_FTM0PS1_MASK;
//                    }
//                }break;
//            }
//        }break;
        
        case ftm1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
            switch(ch)
            {
                case ftm_ch0:
                {
                    if(FTM1_CH0_PIN == PTC4)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS0_MASK;
                    }
                    else if(FTM1_CH0_PIN == PTH2)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM1PS0_MASK;
                    }
                }break;

                case ftm_ch1:
                {
                    if(FTM1_CH1_PIN == PTC5)
                    {
                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS1_MASK;
                    }
                    else if(FTM1_CH1_PIN == PTE7)
                    {
                        SIM->PINSEL |= SIM_PINSEL_FTM1PS1_MASK;
                    }
                }break;
            }
        }break;
        
        case ftm2:
        {
            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //����FTM����ʱ��
            switch(ch)
            {
                case ftm_ch0:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS0_MASK;       
                    if(FTM2_CH0_PIN == PTC0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(0);
                    }
                    else if(FTM2_CH0_PIN == PTH0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(1);
                    }
                    else if(FTM2_CH0_PIN == PTF0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(2);
                    }
                }break;
                
                case ftm_ch1:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS1_MASK;       
                    if(FTM2_CH1_PIN == PTC1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(0);
                    }
                    else if(FTM2_CH1_PIN == PTH1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(1);
                    }
                    else if(FTM2_CH1_PIN == PTF1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(2);
                    }
                }break;
                
                case ftm_ch2:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS2_MASK;       
                    if(FTM2_CH2_PIN == PTC2)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(0);
                    }
                    else if(FTM2_CH2_PIN == PTD0)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(1);
                    }
                    else if(FTM2_CH2_PIN == PTG4)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(2);
                    }
                }break;
                
                case ftm_ch3:
                {
                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS3_MASK;       
                    if(FTM2_CH3_PIN == PTC3)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(0);
                    }
                    else if(FTM2_CH3_PIN == PTD1)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(1);
                    }
                    else if(FTM2_CH3_PIN == PTG5)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(2);
                    }
                }break;
                
                case ftm_ch4:
                { 
                    if(FTM2_CH4_PIN == PTB4)
                    {
                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK; 
                    }
                    else if(FTM2_CH4_PIN == PTG6)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK;
                    }
                }break;
                
                case ftm_ch5:
                {
                    if(FTM2_CH5_PIN == PTB5)
                    {
                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK;     
                    }
                    else if(FTM2_CH5_PIN == PTG7)
                    {
                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK;
                    }
                }break;
            }
 
        }break;
    }
}


uint16_t period_[3];
//-------------------------------------------------------------------------------------------------------------------
//  @brief      FTM��ʼ��
//  @param      ftmn            ѡ��ģ��
//  @param      ch              ѡ��ͨ��
//  @param      freq            ��Ҫ���õ�Ƶ�ʣ���λHZ��
//  @param      duty            ��Ҫ���õ�ռ�ձ�
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_init(ftm0,ftm_ch0,50,500);		//ftm0ģ�飬0ͨ����50HZ���ٷ�֮50��ռ�ձ�
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_init(FTMn ftmn, FTM_CHn ch, uint32_t freq, uint32_t duty)
{
    uint32_t clk_hz ;
    uint16_t mod;
    uint8_t  ps;
    uint16_t cv;
    
    ftm_pwm_mux(ftmn,ch);
    
    // �� CPWMS = 0 �����ض���
    clk_hz = 40000*1000;
    //clk_hz/(ps*mod) = freq        =>>     clk_hz/freq = (ps*mod)      =>>
    //clk_hz/freq < ((1<<n)*65536)  =>>    (clk_hz/freq)/65536 < (1>>n) =>> ((clk_hz/freq)/65536)>>n < 1
    mod = (clk_hz >> 16 ) / freq ;          // ��ʱ�� mod ����һ��
    ps = 0;
    while((mod >> ps) >= 1)                 // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
        ps++;
    if(ps>0x07) return ;                    //�������÷�Χ��ֱ�Ӳ�����������������ԭ��һ��������PWMƵ��̫�ͣ���������Ƶ��̫�ߵ���
    
    mod = (clk_hz >> ps) / freq;            // �� MOD ��ֵ
    period_[ftmn] = mod;
    switch(ftmn)                            // ��ֵ CNTIN ��Ϊ0 �������ȣ�CnV - CNTIN ���� CnV ���� �������ˡ�
    {
        // EPWM������ �� MOD - CNTIN + 0x0001 == MOD - 0 + 1
        // �� CnV = (MOD - 0 + 1) * ռ�ձ� = (MOD - 0 + 1) * duty/ FTM_PRECISON
		case ftm0:
			cv = (duty * (mod - 0 + 1)) / FTM0_PRECISON;
			break;

		case ftm1:
			cv = (duty * (mod - 0 + 1)) / FTM1_PRECISON;
			break;

		case ftm2:
			cv = (duty * (mod - 0 + 1)) / FTM2_PRECISON;
			break;
		default:
			break;
    }
    
//    FTMX[ftmn]->MOD = mod;                  //����PWM����
    FTMX[ftmn]->MOD = 3199;                  //����PWM����
    
    FTMX[ftmn]->CONTROLS[ch].CnSC &= ~FTM_CnSC_ELSA_MASK;
    FTMX[ftmn]->CONTROLS[ch].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
    
    // set FTM clock to system clock 
    FTMX[ftmn]->SC = ( 0
                       //| FTM_SC_CPWMS_MASK       //0�����ض��� ��1�� ���Ķ��� ��ע���˱�ʾ 0��
//                       | FTM_SC_PS(ps)             //��Ƶ���ӣ���Ƶϵ�� = 2^PS
                       | FTM_SC_PS(0)             //��Ƶ���ӣ���Ƶϵ�� = 2^PS
                       | FTM_SC_CLKS(1)            //ʱ��ѡ�� 0��ûѡ��ʱ�ӣ����ã� 1��bus ʱ�ӣ� 2��MCGFFCLK�� 3��EXTCLK�� ��SIM_SOPT4 ѡ������ܽ� FTM_CLKINx��
                       //| FTM_SC_TOIE_MASK        //����ж�ʹ�ܣ�ע���˱�ʾ ��ֹ����жϣ�
                     );

    
    if(ftm2 == ftmn)FTMX[ftmn]->CNTIN = 0;         //���ü�������ֵ��һ��û������;������
//    FTMX[ftmn]->CONTROLS[ch].CnV = cv;             //����ռ�ձ�
	cv = 1600;
    FTMX[ftmn]->CONTROLS[ch].CnV = cv;             //����ռ�ձ�
    
    FTMX[ftmn]->CNT = 0;                           //��������д����ֵ�������CNTIN��ֵ
    
}

const FTM_MemMapPtr FTM_ARR[]={FTM0_BASE_PTR,FTM1_BASE_PTR,FTM2_BASE_PTR};

void FTM_PWM_set_CnV(FTMn ftmNo, FTM_CHn channel, uint16_t cnv)
{
    FTMX[ftmNo]->CONTROLS[channel].CnV = cnv;
//    FTM_CnV_REG(FTM_ARR[ftmNo], channel) = cnv;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ռ�ձ�����
//  @param      ftmn            ѡ��ģ��
//  @param      ch              ѡ��ͨ��
//  @param      duty            ��Ҫ���õ�ռ�ձ�
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_duty(ftm0,ftm_ch0,500);		//ftm0ģ�飬0ͨ�����ٷ�֮50��ռ�ձ�
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_duty(FTMn ftmn, FTM_CHn ch, uint32_t duty)
{
    uint32_t cv;
    //ռ�ձ� = (CnV-CNTIN)/(MOD-CNTIN+1)
    switch(ftmn)
    {
    case ftm0:
        cv = (duty * (period_[ftmn] - 0 + 1)) / FTM0_PRECISON;
        break;

    case ftm1:
        cv = (duty * (period_[ftmn] - 0 + 1)) / FTM1_PRECISON;
        break;

    case ftm2:
        cv = (duty * (period_[ftmn] - 0 + 1)) / FTM2_PRECISON;
        break;

    default:
        break;
    }
    
    FTMX[ftmn]->CONTROLS[ch].CnV = cv;      //����ռ�ձ�
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ƶ������
//  @param      ftmn            ѡ��ģ��
//  @param      freq            ��Ҫ���õ�Ƶ�ʣ���λHZ��
//  @return     void
//  @since      v2.0
//  Sample usage:               ftm_pwm_freq(ftm0,50);		//ftm0ģ�飬50HZ
//-------------------------------------------------------------------------------------------------------------------
void ftm_pwm_freq(FTMn ftmn, uint32_t freq)
{
    uint32_t clk_hz;        //busƵ��/2
    uint32_t mod;
    uint8_t ps;

    // �� CPWMS = 0 �����ض���
    clk_hz = 40000 * 1000 ;
    
    //clk_hz/(ps*mod) = freq        =>>     clk_hz/freq = (ps*mod)      =>>
    //clk_hz/freq < ((1<<n)*65536)  =>>    (clk_hz/freq)/65536 < (1>>n) =>> ((clk_hz/freq)/65536)>>n < 1
    mod = (clk_hz >> 16 ) / freq ;          // ��ʱ�� mod ����һ��
    ps = 0;
    while((mod >> ps) >= 1)                 // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
        ps++;
    if(ps>0x07) return ;                    //�������÷�Χ��ֱ�Ӳ�����������������ԭ��һ��������PWMƵ��̫�ͣ���������Ƶ��̫�ߵ���
    
    mod = (clk_hz >> ps) / freq;            // �� MOD ��ֵ
    period_[ftmn] = mod;
    
    
    FTMX[ftmn]->MOD = mod;                  //����PWM����
    
    // set FTM clock to system clock 
    FTMX[ftmn]->SC = ( 0
                       //| FTM_SC_CPWMS_MASK       //0�����ض��� ��1�� ���Ķ��� ��ע���˱�ʾ 0��
                       | FTM_SC_PS(ps)             //��Ƶ���ӣ���Ƶϵ�� = 2^PS
                       | FTM_SC_CLKS(1)            //ʱ��ѡ�� 0��ûѡ��ʱ�ӣ����ã� 1��bus ʱ�ӣ� 2��MCGFFCLK�� 3��EXTCLK�� ��SIM_SOPT4 ѡ������ܽ� FTM_CLKINx��
                       //| FTM_SC_TOIE_MASK        //����ж�ʹ�ܣ�ע���˱�ʾ ��ֹ����жϣ�
                     );

    
    if(ftm2 == ftmn)FTMX[ftmn]->CNTIN = 0;  //���ü�������ֵ��һ��û������;������
    FTMX[ftmn]->CNT = 0;                    //��������д����ֵ�������CNTIN��ֵ
}


void ftm_count_mux(FTMn ftmn)
{
    
    switch(ftmn)
    {
        case ftm0:
        {
            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;      //����ⲿʱ������ѡ��
            if(FTM0_COUNT_PIN == PTA5)
            {
                 Pin_Output_Config(PTA, PTA5, Pull_Up);
							
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(0);     //ѡ���ⲿʱ���������� A5
            }
            
            else if(FTM0_COUNT_PIN == PTE0)
            {
             
							 Pin_Output_Config(PTE, PTE0, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);     //ѡ���ⲿʱ���������� E0
            }
            
            else if(FTM0_COUNT_PIN == PTE7)
            {  
           
							  Pin_Output_Config(PTE, PTE7, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(2);     //ѡ���ⲿʱ���������� E7
            }
        }break;
        
        case ftm1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;      //����ⲿʱ������ѡ��
            if(FTM1_COUNT_PIN == PTA5)
            {
                Pin_Output_Config(PTA, PTA5, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(0);     //ѡ���ⲿʱ���������� A5
            }
            
            else if(FTM1_COUNT_PIN == PTE0)
            {
                 Pin_Output_Config(PTE, PTE0, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(1);     //ѡ���ⲿʱ���������� E0
            }
            
            else if(FTM1_COUNT_PIN == PTE7)
            {
                Pin_Output_Config(PTE, PTE7, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);     //ѡ���ⲿʱ���������� E7
            }
        }break;
        
        case ftm2:
        {
            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM2CLKPS_MASK;      //����ⲿʱ������ѡ��
            FTM2->CNTIN = 0;
            if(FTM2_COUNT_PIN == PTA5)
            {
                Pin_Output_Config(PTA, PTA5, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(0);     //ѡ���ⲿʱ���������� A5
            }
            
            else if(FTM2_COUNT_PIN == PTE0)
            {
               Pin_Output_Config(PTE, PTE0, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(1);     //ѡ���ⲿʱ���������� E0
            }
            
            else if(FTM2_COUNT_PIN == PTE7)
            {
                 Pin_Output_Config(PTE, PTE7, Pull_Up);
                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(2);     //ѡ���ⲿʱ���������� E7
            }
        }break;
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ⲿ������ʼ��  ��ȡ����ֵ�����ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//  @param      ftmn            ѡ��ģ��
//  @return     void
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ftm_count_init(FTMn ftmn)
{
    ftm_count_mux(ftmn);                                    //���Ÿ��� �������� ������Ӧ����ʱ��
    
    FTMX[ftmn]->SC |= FTM_SC_PS(0);	                        //��Ƶϵ��	
    FTMX[ftmn]->SC |= FTM_SC_CLKS(3);                       //ѡ���ⲿʱ����ΪFTM����ʱ��
                
    FTMX[ftmn]->CNT = 0;                                    //���س�ʼ��ֵ
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ֵ      ���ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//  @param      ftmn            ѡ��ģ��
//  @return     uint16          ���ؼ���ֵ
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
uint16_t ftm_count_get(FTMn ftmn)
{
    return FTMX[ftmn]->CNT ;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ֵ      ���ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//  @param      ftmn            ѡ��ģ��
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void ftm_count_clean(FTMn ftmn)
{
    FTMX[ftmn]->CNT = 0;
}


//#include "pwm.h"

////FTM0��FTM1��FTM2��ַӳ��
//const FTM_MemMapPtr FTM_ARR[]={FTM0_BASE_PTR,FTM1_BASE_PTR,FTM2_BASE_PTR};
//static FTM_Type * const FTMX[] = FTM_BASES;

//static uint16_t MOD_VALUE;


////============================================================================
////�������ƣ�FTM_PWM_init
////�������أ���
////����˵����ftmNo:FTMģ��ţ�FTM_0��FTM_1��FTM_2
////          channel:ѡ��ͨ���ţ�FTM0��FTM1��ͨ��0��ͨ��1
////                             FTM2:ͨ��0��1��2��3��4��5
////          freq������PWM��Ƶ�ʣ���λΪKHz��ȡֵ��0.012��1500
////          duty��ռ�ձȣ�����ȡ�������õ�freqֵ������Ϊfreq/1500��
////���ܸ�Ҫ����ʼ��PWMģ��
////============================================================================
//void FTM_PWM_init(FTMn ftmNo, FTM_CHn channel, float freq, float duty)
//{
//	uint16_t duty_channel;
//	uint16_t mod;

//	//��ֹģ���Խ��
//		if(ftmNo>2) ftmNo=2;

//	//����modֵ�����ڣ�ms) = MOD / 1500
//	if(freq <= 0.012)
//		mod = 0xFFFF;
//	else if(freq>1500)
//		mod=0;
//	else
//		mod = 1500 / freq;

//	//��ֹ����Խ��
//	if(duty > 100)
//		duty = 100;
//	if(duty < 0)
//		duty = 0;

//	switch(ftmNo)
//	{
//		case FTM_0:

//			#if(FTM0_CHANNEL0_GROUP == 1)
//				//��������PTA0ΪFTM0ͨ��0����
//				SIM_PINSEL0 &= ~SIM_PINSEL_FTM0PS0_MASK;
//			#endif

//			#if(FTM0_CHANNEL0_GROUP == 2)
//				//��������PTB2ΪFTM0ͨ��0����
//				SIM_PINSEL0 |= SIM_PINSEL_FTM0PS0_MASK;
//			#endif

//			#if(FTM0_CHANNEL1_GROUP == 1)
//				//��������PTA1ΪFTM0ͨ��1����
//				SIM_PINSEL0 &= ~SIM_PINSEL_FTM0PS1_MASK;
//			#endif

//			#if(FTM0_CHANNEL1_GROUP == 2)
//			    //��������PTB3ΪFTM0ͨ��1����
//			    SIM_PINSEL0 |= SIM_PINSEL_FTM0PS1_MASK;
//			#endif

//			//ʹ��FTM0������ʱ��
//			SIM_SCGC |= SIM_SCGC_FTM0_MASK;
//			break;

//		case FTM_1:
//            #if(FTM1_CHANNEL0_GROUP==1)     //��������PTC4ΪFTM1ͨ��0����
//				SIM_PINSEL0 &= ~SIM_PINSEL_FTM1PS0_MASK;
//			#endif

//			#if(FTM1_CHANNEL0_GROUP==2)     //��������PTH2ΪFTM1ͨ��0����
//				SIM_PINSEL0 |= SIM_PINSEL_FTM1PS0_MASK;
//			#endif

//			#if(FTM1_CHANNEL1_GROUP==1)     //��������PTC5ΪFTM1ͨ��1����
//				SIM_PINSEL0 &= ~SIM_PINSEL_FTM1PS1_MASK;
//			#endif

//			#if(FTM1_CHANNEL1_GROUP==2)     //��������PTE7ΪFTM1ͨ��1����
//				SIM_PINSEL0 |= SIM_PINSEL_FTM1PS1_MASK;
//			#endif

//			SIM_SCGC |= SIM_SCGC_FTM1_MASK; //ʹ��FTM1������ʱ��
//			break;

//		case FTM_2:
///**FTM2 CH_0***************************************************/
//			#if(FTM2_CHANNEL0_GROUP==1)     //��������PTC0ΪFTM2ͨ��0����
//				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS0_MASK;
//			#endif

//			#if(FTM2_CHANNEL0_GROUP==2)     //��������PTH0ΪFTM2ͨ��0����
//				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS0(1);
//			#endif

//			#if(FTM2_CHANNEL0_GROUP==3)     //��������PTF0ΪFTM2ͨ��0����
//				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS0(2);
//			#endif
//        
///**FTM2 CH_1***************************************************/
//			#if(FTM2_CHANNEL1_GROUP==1)      //��������PTC1ΪFTM2ͨ��1����
//				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS1_MASK;
//			#endif

//			#if(FTM2_CHANNEL1_GROUP==2)      //��������PTH1ΪFTM2ͨ��1����
//				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS1(1);
//            #endif
//  
//		    #if(FTM2_CHANNEL1_GROUP==3)      //��������PTF1ΪFTM2ͨ��1����
//                SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS1(2);
//            #endif
//            
///**FTM2 CH_2***************************************************/
//            #if(FTM2_CHANNEL2_GROUP==1)      //��������PTC2ΪFTM2ͨ��2����
//				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS2_MASK;
//			#endif

//			#if(FTM2_CHANNEL2_GROUP==2)      //��������PTD0ΪFTM2ͨ��2����
//				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS2(1);
//            #endif

//            #if(FTM2_CHANNEL2_GROUP==3)      //��������PTG4ΪFTM2ͨ��2����
//			       SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS2(2);
//            #endif

///**FTM2 CH_3***************************************************/
//			#if(FTM2_CHANNEL3_GROUP==1)      //��������PTC3ΪFTM2ͨ��3����
//				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS3_MASK;
//			#endif
//            
//			#if(FTM2_CHANNEL3_GROUP==2)      //��������PTD1ΪFTM2ͨ��3����
//				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS3(1);
//			#endif

//			#if(FTM2_CHANNEL3_GROUP==3)      //��������PTG5ΪFTM2ͨ��3����
//			   SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS3(2);
//			#endif
//            
///**FTM2 CH_4***************************************************/
//			#if(FTM2_CHANNEL4_GROUP==1)      //��������PTB4ΪFTM2ͨ��4����
//				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK;
//			#endif

//			#if(FTM2_CHANNEL4_GROUP==2)      //��������PTG6ΪFTM2ͨ��4����
//				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK;
//			#endif
//            
///**FTM2 CH_5***************************************************/
//			#if(FTM2_CHANNEL5_GROUP==1)      //��������PTB5ΪFTM2ͨ��5����
//				SIM_PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK;
//			#endif

//			#if(FTM2_CHANNEL5_GROUP==2)      //��������PTG7ΪFTM2ͨ��5����
//				SIM_PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK;
//			#endif

//			SIM_SCGC |= SIM_SCGC_FTM2_MASK;  //ʹ��FTM2������ʱ��
//			break;
//	}

//    //д������ֹ
//    FTM_ARR[ftmNo]->MODE |= FTM_MODE_WPDIS_MASK;
//    //����ʱ��Ƶ��24MHz,��Ƶ����16,��Ƶ��Ϊ1.5MHz
////    FTM_ARR[ftmNo]->SC |= FTM_SC_PS(4);
//    FTM_ARR[ftmNo]->SC |= FTM_SC_PS(0);
//    //����룬�ȸߵ�ƽ��͵�ƽ
//    FTM_CnSC_REG(FTM_ARR[ftmNo], channel) |= FTM_CnSC_ELSB_MASK;
//    //���ض���
//    FTM_CnSC_REG(FTM_ARR[ftmNo], channel) &= ~FTM_CnSC_ELSA_MASK;
//    FTM_CnSC_REG(FTM_ARR[ftmNo], channel) |= FTM_CnSC_MSB_MASK;
//    //����������
//    FTM_ARR[ftmNo]->CNT=0;
//    //�жϽ�ֹ
//    FTM_ARR[ftmNo]->SC &=  ~FTM_SC_TOIE_MASK;
//    //FTM2ʹ��
//    FTM_ARR[ftmNo]->MODE &= ~FTM_MODE_FTMEN_MASK;
//    //������Ҫ�����ͨ������������ͨ��
//    FTM_ARR[ftmNo]->OUTMASK = (0xFE << channel);
//    //��ֹ˫���ز�׽ģʽ
//    FTM_ARR[ftmNo]->COMBINE = 0;
//    //FTM2������ʼֵΪ0
//    FTM_ARR[ftmNo]->CNTIN = 0;
//    //����=(MOD-CNTIN+1)*ʱ������=2.5ms
//    FTM_ARR[ftmNo]->MOD = mod;
////    FTM_ARR[ftmNo]->MOD = 1599;
//    MOD_VALUE = mod;
//    //����ͨ���Ĵ�����ֵ������ռ�ձ�
//    duty_channel = (uint16_t)((float)mod * duty / 100);
//    //����ͨ��ֵ�Ĵ���
//    FTM_CnV_REG(FTM_ARR[ftmNo], channel) = duty_channel;
////    FTM_CnV_REG(FTM_ARR[ftmNo], channel) = 800;
//    //ʹ������ʱ��
//    FTM_ARR[ftmNo]->SC |= FTM_SC_CLKS(1);
//}

////============================================================================
////�������ƣ�FTM_PWM_set_duty
////�������أ���
////����˵����ftmNo:FTMģ��ţ�FTM_0��FTM_1��FTM_2
////          channel:ѡ��ͨ���ţ�FTM0��FTM1��ͨ��0��ͨ��1
////                             FTM2:ͨ��0��1��2��3��4��5
////          duty��ռ�ձȣ�����ȡ�������õ�modֵ������Ϊ1/mod��
////���ܸ�Ҫ����ʼ��PWMģ��
////============================================================================
//void FTM_PWM_set_duty(FTMn ftmNo, FTM_CHn channel, float duty)
//{
//	uint16_t duty_channel;

//	if(duty > 100)
//		duty = 100;
//	if(duty < 0)
//		duty = 0;
//    //д������ֹ
//    // FTM_ARR[ftmNo]->MODE |= FTM_MODE_WPDIS_MASK;
//    //����ͨ���Ĵ�����ֵ������ռ�ձ�
//    duty_channel = (uint16_t)((float)MOD_VALUE * duty / 100);
//    //����ͨ��ֵ�Ĵ���
//    FTM_CnV_REG(FTM_ARR[ftmNo], channel) = duty_channel;
//}

//void FTM_PWM_set_CnV(FTMn ftmNo, FTM_CHn channel, uint16_t cnv)
//{
//    FTM_CnV_REG(FTM_ARR[ftmNo], channel) = cnv;
//}
/////*********************************************************************************************************************
//// * COPYRIGHT NOTICE
//// * Copyright (c) 2017,��ɿƼ�
//// * All rights reserved.
//// * ��������QQȺ��179029047
//// *
//// * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
//// * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
//// *
//// * @file       		KEA128_ftm
//// * @company	   		�ɶ���ɿƼ����޹�˾
//// * @author     		��ɿƼ�(QQ3184284598)
//// * @version    		v2.0
//// * @Software 		IAR 7.7 or MDK 5.23
//// * @Target core		S9KEA128AMLK
//// * @Taobao   		https://seekfree.taobao.com/
//// * @date       		2017-11-6
//// ********************************************************************************************************************/

////#include "pwm.h"




////static FTM_Type * const FTMX[] = FTM_BASES;

////void ftm_pwm_mux(FTMn FTM_X, FTM_CHn CH_X)
////{
////    switch(FTM_X)
////    {
////        case FTM_0:
////        {
////            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
////            switch(CH_X)
////            {
////                case CH_0:
////                {
////                    if(FTM0_CH0_PIN == PTA0)
////                    {
////                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS0_MASK;
////                    }
////                    else if(FTM0_CH0_PIN == PTB2)
////                    {
////                        SIM->PINSEL |= SIM_PINSEL_FTM0PS0_MASK;
////                    }
////                }break;
////                
////                case CH_1:
////                {
////                    if(FTM0_CH1_PIN == PTA1)
////                    {
////                        SIM->PINSEL &= ~SIM_PINSEL_FTM0PS1_MASK;
////                    }
////                    else if(FTM0_CH1_PIN == PTB3)
////                    {
////                        SIM->PINSEL |= SIM_PINSEL_FTM0PS1_MASK;
////                    }
////                }break;
////            }
////        }break;
////        
////        case FTM_1:
////        {
////            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
////            switch(CH_X)
////            {
////                case CH_0:
////                {
////                    if(FTM1_CH0_PIN == PTC4)
////                    {
////                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS0_MASK;
////                    }
////                    else if(FTM1_CH0_PIN == PTH2)
////                    {
////                        SIM->PINSEL |= SIM_PINSEL_FTM1PS0_MASK;
////                    }
////                }break;

////                case CH_1:
////                {
////                    if(FTM1_CH1_PIN == PTC5)
////                    {
////                        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS1_MASK;
////                    }
////                    else if(FTM1_CH1_PIN == PTE7)
////                    {
////                        SIM->PINSEL |= SIM_PINSEL_FTM1PS1_MASK;
////                    }
////                }break;
////            }
////        }break;
////        
////        case FTM_2:
////        {
////            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //����FTM����ʱ��
////            switch(CH_X)
////            {
////                case CH_0:
////                {
////                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS0_MASK;       
////                    if(FTM2_CH0_PIN == PTC0)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(0);
////                    }
////                    else if(FTM2_CH0_PIN == PTH0)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(1);
////                    }
////                    else if(FTM2_CH0_PIN == PTF0)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(2);
////                    }
////                }break;
////                
////                case CH_1:
////                {
////                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS1_MASK;       
////                    if(FTM2_CH1_PIN == PTC1)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(0);
////                    }
////                    else if(FTM2_CH1_PIN == PTH1)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(1);
////                    }
////                    else if(FTM2_CH1_PIN == PTF1)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(2);
////                    }
////                }break;
////                
////                case CH_2:
////                {
////                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS2_MASK;       
//////                    if(FTM2_CH2_PIN == PTC2)
////                    if(1)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(0);
////                    }
//////                    else if(FTM2_CH2_PIN == PTD0)
//////                    {
//////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(1);
//////                    }
//////                    else if(FTM2_CH2_PIN == PTG4)
//////                    {
//////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(2);
//////                    }
////                }break;
////                
////                case CH_3:
////                {
////                    SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS3_MASK;       
//////                    if(FTM2_CH3_PIN == PTC3)
////                    if(1)
////                    {
////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(0);
////                        
////                    }
//////                    else if(FTM2_CH3_PIN == PTD1)
//////                    {
//////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(1);
//////                    }
//////                    else if(FTM2_CH3_PIN == PTG5)
//////                    {
//////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(2);
//////                    }
////                }break;
////                
////                case CH_4:
////                { 
//////                    if(FTM2_CH4_PIN == PTB4)
////                    if(1)
////                    {
////                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK; 
////                    }
//////                    else if(FTM2_CH4_PIN == PTG6)
//////                    {
//////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK;
//////                    }
////                }break;
////                
////                case CH_5:
////                {
//////                    if(FTM2_CH5_PIN == PTB5)
////                    if(1)
////                    {
////                        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK;
//////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK;                        
////                    }
//////                    else if(FTM2_CH5_PIN == PTG7)
//////                    {
//////                        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK;
//////                    }
////                }break;
////            }
//// 
////        }break;
////    }
////}


////uint16_t perioddd[3];
//////-------------------------------------------------------------------------------------------------------------------
//////  @brief      FTM��ʼ��
//////  @param      ftmn            ѡ��ģ��
//////  @param      ch              ѡ��ͨ��
//////  @param      freq            ��Ҫ���õ�Ƶ�ʣ���λHZ��
//////  @param      duty            ��Ҫ���õ�ռ�ձ�
//////  @return     void
//////  @since      v2.0
//////  Sample usage:               ftm_pwm_init(ftm0,ftm_ch0,50,500);		//ftm0ģ�飬0ͨ����50HZ���ٷ�֮50��ռ�ձ�
//////   �������������������������д�������ʱ�Ȳ���
//////-------------------------------------------------------------------------------------------------------------------
////void ftm_pwm_init(FTMn FTM_X, FTM_CHn ch, uint32_t freq, uint32_t duty)
////{
////    uint32_t clk_hz ;
////    uint16_t mod;
////    uint8_t  ps;
////    uint16_t cv;
////    
////    ftm_pwm_mux(FTM_X, ch);
////    
////    // �� CPWMS = 0 �����ض���
////    clk_hz = DEFAULT_SYSTEM_CLOCK/2;  //����ʱ��Ϊϵͳʱ�ӵ�һ��
////    //clk_hz/(ps*mod) = freq        =>>     clk_hz/freq = (ps*mod)      =>>
////    //clk_hz/freq < ((1<<n)*65536)  =>>    (clk_hz/freq)/65536 < (1>>n) =>> ((clk_hz/freq)/65536)>>n < 1
////    mod = (clk_hz >> 16 ) / freq ;          // ��ʱ�� mod ����һ��
////    ps = 0;
////    while((mod >> ps) >= 1)                 // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
////        ps++;
////    if(ps>0x07) return ;                    //�������÷�Χ��ֱ�Ӳ�����������������ԭ��һ��������PWMƵ��̫�ͣ���������Ƶ��̫�ߵ���
////    
////    mod = (clk_hz >> ps) / freq;            // �� MOD ��ֵ
////    perioddd[FTM_X] = mod;
////    switch(FTM_2)                            // ��ֵ CNTIN ��Ϊ0 �������ȣ�CnV - CNTIN ���� CnV ���� �������ˡ�
////    {
////        // EPWM������ �� MOD - CNTIN + 0x0001 == MOD - 0 + 1
////        // �� CnV = (MOD - 0 + 1) * ռ�ձ� = (MOD - 0 + 1) * duty/ FTM_PRECISON
////    case FTM_0:
////        cv = (duty * (mod - 0 + 1)) / FTM0_PRECISON;
////        break;

////    case FTM_1:
////        cv = (duty * (mod - 0 + 1)) / FTM1_PRECISON;
////        break;

////    case FTM_2:
////        cv = (duty * (mod - 0 + 1)) / FTM2_PRECISON;
////        break;
////    default:
////        break;
////    }
////    
////    FTMX[FTM_X]->MOD = mod;                  //����PWM����
////    
////    FTMX[FTM_X]->CONTROLS[ch].CnSC &= ~FTM_CnSC_ELSA_MASK;
////    FTMX[FTM_X]->CONTROLS[ch].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
////    
////    //����FTMʱ��
////    FTMX[FTM_X]->SC = ( 0
////                       //| FTM_SC_CPWMS_MASK       //0�����ض��� ��1�� ���Ķ��� ��ע���˱�ʾ 0��
////                       | FTM_SC_PS(ps)             //��Ƶ���ӣ���Ƶϵ�� = 2^PS
////                       | FTM_SC_CLKS(1)            //ʱ��ѡ�� 0��ûѡ��ʱ�ӣ����ã� 1��bus ʱ�ӣ� 2��MCGFFCLK�� 3��EXTCLK�� ��SIM_SOPT4 ѡ������ܽ� FTM_CLKINx��
////                       //| FTM_SC_TOIE_MASK        //����ж�ʹ�ܣ�ע���˱�ʾ ��ֹ����жϣ�
////                     );

////    
////    if(FTM_2 == FTM_X)
////        FTMX[FTM_X]->CNTIN = 0;         //���ü�������ֵ��һ��û������;������
////    FTMX[FTM_X]->CONTROLS[ch].CnV = cv;             //����ռ�ձ�
////    FTMX[FTM_X]->CNT = 0;                           //��������д����ֵ�������CNTIN��ֵ
////    
////}


//////-------------------------------------------------------------------------------------------------------------------
//////  @brief      ռ�ձ�����
//////  @param      ftmn            ѡ��ģ��
//////  @param      ch              ѡ��ͨ��
//////  @param      duty            ��Ҫ���õ�ռ�ձ�
//////  @return     void
//////  @since      v2.0
//////  Sample usage:               ftm_pwm_duty(ftm0,ftm_ch0,500);		//ftm0ģ�飬0ͨ�����ٷ�֮50��ռ�ձ�
//////-------------------------------------------------------------------------------------------------------------------
////void ftm_pwm_duty(FTMn FTM_X, FTM_CHn ch, uint32_t duty)
////{
////    uint32_t cv;
////    //ռ�ձ� = (CnV-CNTIN)/(MOD-CNTIN+1)
////    switch(FTM_X)
////    {
////    case FTM_0:
////        cv = (duty * (perioddd[FTM_X] - 0 + 1)) / FTM0_PRECISON;
////        break;

////    case FTM_1:
////        cv = (duty * (perioddd[FTM_X] - 0 + 1)) / FTM1_PRECISON;
////        break;

////    case FTM_2:
////        cv = (duty * (perioddd[FTM_X] - 0 + 1)) / FTM2_PRECISON;
////        break;

////    default:
////        break;
////    }
////    
////    FTMX[FTM_X]->CONTROLS[ch].CnV = cv;      //����ռ�ձ�
////}

//////-------------------------------------------------------------------------------------------------------------------
//////  @brief      Ƶ������
//////  @param      ftmn            ѡ��ģ��
//////  @param      freq            ��Ҫ���õ�Ƶ�ʣ���λHZ��
//////  @return     void
//////  @since      v2.0
//////  Sample usage:               ftm_pwm_freq(ftm0,50);		//ftm0ģ�飬50HZ
//////-------------------------------------------------------------------------------------------------------------------
////void ftm_pwm_freq(FTMn FTM_X, uint32_t Freq)
////{
////    uint32_t Mod;
////    uint8_t Div = 0;

////    Mod = (BUS_CLK_KHZ >> 16 ) / Freq ;   // ��ʱ�� mod ����һ��

////    while((Mod >> Div) >= 1)              // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
////        Div++;
////    if(Div>0x07)                          //�������÷�Χ��ֱ�Ӳ�����������������ԭ��һ��������PWMƵ��̫�ͣ���������Ƶ��̫�ߵ���
////        return ;
////    
////    Mod = (BUS_CLK_KHZ >> Div) / Freq;            // �� MOD ��ֵ
////    perioddd[FTM_X] = Mod;
////    
////    
////    FTMX[FTM_X]->MOD = Mod;                  //����PWM����
////    
////    // set FTM clock to system clock 
////    FTMX[FTM_X]->SC = ( 0
////                       //| FTM_SC_CPWMS_MASK       //0�����ض��� ��1�� ���Ķ��� ��ע���˱�ʾ 0��
////                       | FTM_SC_PS(Div)             //��Ƶ���ӣ���Ƶϵ�� = 2��Div�η�
////                       | FTM_SC_CLKS(1)            //ʱ��ѡ�� 0��ûѡ��ʱ�ӣ����ã� 1��bus ʱ�ӣ� 2��MCGFFCLK�� 3��EXTCLK�� ��SIM_SOPT4 ѡ������ܽ� FTM_CLKINx��
////                       //| FTM_SC_TOIE_MASK        //����ж�ʹ�ܣ�ע���˱�ʾ ��ֹ����жϣ�
////                     );

////    
////    if(FTM_2 == FTM_X)            //���ü�������ֵ��һ��û������;������
////        FTMX[FTM_X]->CNTIN = 0;
////    FTMX[FTM_X]->CNT = 0;         //��������д����ֵ�������CNTIN��ֵ
////}

//////#define PTX(PTX_n)  (PTX_n>>5)  //��ȡģ��� PTX_n/32
//////#define PTn(PTX_n)  (PTX_n&0x1f)//��ȡ���ź� PTX_n%32


//void FTM_Count_Mux(FTMn ftmn)
//{
////    switch(ftmn)
////    {
////        case FTM_0:
////        {
////            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
////            SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;      //����ⲿʱ������ѡ��
////            if(FTM0_COUNT_PIN == PTA5)
////            {
////                Pin_Pull_State(PTA, PTA5, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(0);     //ѡ���ⲿʱ���������� A5
////            }
////            
////            else if(FTM0_COUNT_PIN == PTE0)
////            {
////                Pin_Pull_State(PTE, PTE0, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);     //ѡ���ⲿʱ���������� E0
////            }
////            
////            else if(FTM0_COUNT_PIN == PTE7)
////            {
////                Pin_Pull_State(PTE, PTE7, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(2);     //ѡ���ⲿʱ���������� E7
////            }
////        }break;
////        
////        case FTM_1:
////        {
////            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
////            SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;      //����ⲿʱ������ѡ��
////            if(FTM1_COUNT_PIN == PTA5)
////            {
////                Pin_Pull_State(PTA, PTA5, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(0);     //ѡ���ⲿʱ���������� A5
////            }
////            
////            else if(FTM1_COUNT_PIN == PTE0)
////            {
////                Pin_Pull_State(PTE, PTE0, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(1);     //ѡ���ⲿʱ���������� E0
////            }
////            
////            else if(FTM1_COUNT_PIN == PTE7)
////            {
////                Pin_Pull_State(PTE, PTE7, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);     //ѡ���ⲿʱ���������� E7
////            }
////        }break;
////        
////        case FTM_2:
////        {
////            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //����FTM����ʱ��
////            SIM->PINSEL &= ~SIM_PINSEL_FTM2CLKPS_MASK;      //����ⲿʱ������ѡ��
////            FTM2->CNTIN = 0;
////            if(FTM2_COUNT_PIN == PTA5)
////            {
////                Pin_Pull_State(PTA, PTA5, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(0);     //ѡ���ⲿʱ���������� A5
////            }
////            
////            else if(FTM2_COUNT_PIN == PTE0)
////            {
////                Pin_Pull_State(PTE, PTE0, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(1);     //ѡ���ⲿʱ���������� E0
////            }
////            
////            else if(FTM2_COUNT_PIN == PTE7)
////            {
////                Pin_Pull_State(PTE, PTE7, Pull_Up);
////                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(2);     //ѡ���ⲿʱ���������� E7
////            }
////        }break;
////    }
//    switch(ftmn)
//    {
//        case FTM_0:
//        {
//            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
//            SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;      //����ⲿʱ������ѡ��
//            if(FTM0_COUNT_PIN == PTA5)
//            {
//                Pin_Pull_State(PTA, PTA5, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(0);     //ѡ���ⲿʱ���������� A5
//            }
//            
//            else if(FTM0_COUNT_PIN == PTE0)
//            {
//                Pin_Pull_State(PTE, PTE0, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);     //ѡ���ⲿʱ���������� E0
//            }
//            
//            else if(FTM0_COUNT_PIN == PTE7)
//            {
//                Pin_Pull_State(PTE, PTE7, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(2);     //ѡ���ⲿʱ���������� E7
//            }
//        }break;
//        
//        case FTM_1:
//        {
//            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
//            SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;      //����ⲿʱ������ѡ��
//            if(FTM1_COUNT_PIN == PTA5)
//            {
//                Pin_Pull_State(PTA, PTA5, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(0);     //ѡ���ⲿʱ���������� A5
//            }
//            
//            else if(FTM1_COUNT_PIN == PTE0)
//            {
//                Pin_Pull_State(PTE, PTE0, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(1);     //ѡ���ⲿʱ���������� E0
//            }
//            
//            else if(FTM1_COUNT_PIN == PTE7)
//            {
//                Pin_Pull_State(PTE, PTE7, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);     //ѡ���ⲿʱ���������� E7
//            }
//        }break;
//        
//        case FTM_2:
//        {
//            SIM->SCGC |= SIM_SCGC_FTM2_MASK;                //����FTM����ʱ��
//            SIM->PINSEL &= ~SIM_PINSEL_FTM2CLKPS_MASK;      //����ⲿʱ������ѡ��
//            FTM2->CNTIN = 0;
//            if(FTM2_COUNT_PIN == PTA5)
//            {
//                Pin_Pull_State(PTA, PTA5, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(0);     //ѡ���ⲿʱ���������� A5
//            }
//            
//            else if(FTM2_COUNT_PIN == PTE0)
//            {
//                Pin_Pull_State(PTE, PTE0, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(1);     //ѡ���ⲿʱ���������� E0
//            }
//            
//            else if(FTM2_COUNT_PIN == PTE7)
//            {
//                Pin_Pull_State(PTE, PTE7, Pull_Up);
//                SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(2);     //ѡ���ⲿʱ���������� E7
//            }
//        }break;
//    }
//}

//////-------------------------------------------------------------------------------------------------------------------
//////  @brief      �ⲿ������ʼ��  ��ȡ����ֵ�����ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//////  @param      ftmn            ѡ��ģ��
//////  @return     void
//////  @since      v2.0
//////  Sample usage:               
//////-------------------------------------------------------------------------------------------------------------------
//void ftm_count_init(FTMn ftmn)
//{
//    FTM_Count_Mux(ftmn);                                    //���Ÿ��� �������� ������Ӧ����ʱ��
//    
//    FTMX[ftmn]->SC |= FTM_SC_PS(0);	                        //��Ƶϵ��	
//    FTMX[ftmn]->SC |= FTM_SC_CLKS(3);                       //ѡ���ⲿʱ����ΪFTM����ʱ��
//                
//    FTMX[ftmn]->CNT = 0;                                    //���س�ʼ��ֵ
//}

//////-------------------------------------------------------------------------------------------------------------------
//////  @brief      ��ȡ����ֵ      ���ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//////  @param      ftmn            ѡ��ģ��
//////  @return     uint16_t          ���ؼ���ֵ
//////  @since      v2.0
//////  Sample usage:               
//////-------------------------------------------------------------------------------------------------------------------
//uint16_t ftm_count_get(FTMn ftmn)
//{
//    return FTMX[ftmn]->CNT ;
//}

//////-------------------------------------------------------------------------------------------------------------------
//////  @brief      �������ֵ      ���ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//////  @param      ftmn            ѡ��ģ��
//////  @since      v2.0
//////  Sample usage:               
//////-------------------------------------------------------------------------------------------------------------------
//void ftm_count_clean(FTMn ftmn)
//{
//    FTMX[ftmn]->CNT = 0;
//}

