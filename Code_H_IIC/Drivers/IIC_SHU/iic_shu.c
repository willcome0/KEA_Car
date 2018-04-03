//============================================================================
//�ļ����ƣ�i2c.c
//���ܸ�Ҫ��i2c�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2013-05-4   V2.1
//        2015-01-21   V3.0
//============================================================================
#include  "iic_shu.h"

static const uint16_t iic_data[]={300,0x14,150,0x54,100,0x1f,75,0x25,50,0x5f};
static void send_signal(uint8_t Signal,uint8_t I2C_No);
static uint8_t wait(uint8_t x,uint8_t I2C_No);
static I2C_MemMapPtr i2c_get_base_address(uint8_t I2C_No);
uint8_t data1[12]="Version3.4\n";
static uint8_t Num_flag=0;
//===========================================================================
//�������ƣ�i2c_init                                                        
//���ܸ�Ҫ����ʼ��IICXģ�顣                                     
//����˵����I2C_No:ģ���,��ȡֵΪ0,1
//        Mode ģʽ  1������     0���ӻ�
//        address ��ģ���ʼ����ַ    ��Χ(1~255)
//        BaudRateΪ�����ʣ��䵥λΪbps����ȡֵΪ50,75,100,150,300
//�������أ���                                                                  
//===========================================================================
void i2c_init(uint8_t I2C_No,uint8_t Mode,uint8_t address,uint8_t BaudRate )
{
    //��ȡI2Cģ��Ļ�ַ
    uint8_t index;
    I2C_MemMapPtr num = i2c_get_base_address(I2C_No);
    if(I2C_No<0||I2C_No>1)//���ģ��Ŵ�����ǿ����Ϊ0
    {
        I2C_No=0;
    }
    if(num==I2C0)
    {
        //I2C0 Clock Gate Control --enable
        SIM_SCGC |= SIM_SCGC_I2C0_MASK;
        I2C0_C1=0X00;
        BSET(I2C_S_IICIF_SHIFT,I2C0_S1);
       #if(IIC_0_GROUP==1)
       //PTA2��PTA3����ΪI2C0_SDA,I2C0_SCL
       SIM_PINSEL0 &= ~SIM_PINSEL_I2C0PS_MASK;
       PORT_PUE0 |= 0xc;
       #endif
       #if(IIC_0_GROUP==2)
       //PTB6,PTB7����ΪI2C0_SDA,I2C0_SCL
       SIM_PINSEL0 |= SIM_PINSEL_I2C0PS_MASK;
       PORT_PUE0 |= 0xc000;
       #endif
        //���� MULT �� ICR,kL25��MCU����Ƶ��Ϊ24M���������Ϸ�Ƶ��75K������  
        I2C0_A1=address;                    //������Ϊ�ӻ�ʱ��Ĭ�ϵ�ַ
        for(index=0;index<10;index+=2)
        {
            if(iic_data[index]==BaudRate)
            {
                index++;
                I2C0_F=iic_data[index];        //������Ĳ�������I2C1_F
                break;
            }
        }
        if(1 == Mode)   //����ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C0_C1);//��i2c0ģ��ʹ��
            BSET(I2C_C1_TXAK_SHIFT,I2C0_C1); //��λi2c0 TXAK
        }
        else            //�ӻ�ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C0_C1); //ʹ��I2Cģ��
            BSET(I2C_C1_IICIE_SHIFT,I2C0_C1); //��I2C�ж�
            BSET(I2C_C1_MST_SHIFT,I2C0_C1);   //���ó�����ģʽ
            BCLR(I2C_C1_TX_SHIFT,I2C0_C1);    //TX = 0,MCU����Ϊ����ģʽ
            //i=I2C0_D;                       //����IIC1D,׼����������
            BCLR(I2C_C1_MST_SHIFT,I2C0_C1);   //MSTλ��1���0������Ϊ�ӻ�ģʽ
        }

    }
    else
    {
        //I2C1 Clock Gate Control --enable
        SIM_SCGC |= SIM_SCGC_I2C1_MASK;
        I2C1_C1=0X00;
        BSET(I2C_S_IICIF_SHIFT,I2C1_S1);
        #if(IIC_1_GROUP==1)
        //�ֱ�PTE0,PTE1����ΪI2C1_SDA,I2C1_SCL
        SIM_PINSEL1 &= ~SIM_PINSEL1_I2C1PS_MASK;
        PORT_PUE1 |= 0x3;
        #endif
        #if(IIC_1_GROUP==2)
        //PTH3,PTH4����ΪI2C1_SDA,I2C1_SCL
        SIM_PINSEL1 |= SIM_PINSEL1_I2C1PS_MASK;
        PORT_PUE1 |= 0x18000000;
         #endif
        I2C1_A1=address;                    //������Ϊ�ӻ�ʱ��Ĭ�ϵ�ַ
        for(index=0;index<10;index+=2)
        {
            if(iic_data[index]==BaudRate)
            {
               index++;
               I2C1_F=iic_data[index];          //������Ĳ�������I2C1_F
               break;
            }
        }
        if(1 == Mode)   //����ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C1_C1);//��i2c0ģ��ʹ��
            BSET(I2C_C1_TXAK_SHIFT,I2C1_C1); //��λi2c0 TXAK
        }
        else            //�ӻ�ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C1_C1);//ʹ��I2Cģ��
            BSET(I2C_C1_IICIE_SHIFT,I2C1_C1);//��I2C�ж�
            //BSET(I2C_C1_MST_SHIFT,I2C1_C1);//���ó�����ģʽ
            //BCLR(I2C_C1_TX_SHIFT,I2C1_C1); //TX = 0,MCU����Ϊ����ģʽ
            //i=I2C0_D;                      //����IIC1D,׼����������
            //BCLR(I2C_C1_MST_SHIFT,I2C1_C1);//MSTλ��1���0������Ϊ�ӻ�ģʽ
        }
    }
}

//===========================================================================
//�������ƣ�i2c_read1                                                        
//���ܸ�Ҫ���Ӵӻ���1���ֽ�����                                            
//����˵����I2C_No:ģ��ţ���ȡֵΪ0��1
//        DeviceAddr:�豸��ַ    ��Χ(1~255)
//        AccessAddr:���ʵ�ַ    ��Χ(0~255)
//        Data:�����յ���һ���ֽ�����
//�������أ�Ϊ0,�ɹ���һ���ֽ�;Ϊ1,��һ���ֽ�ʧ��  
//����˵��: �ڲ����� send_signal,wait  
//===========================================================================
uint8_t i2c_read1(uint8_t I2C_No,uint8_t DeviceAddr, uint8_t AccessAddr, uint8_t *Data)
{      
     //��ȡi2cģ���ַ
     I2C_MemMapPtr num = i2c_get_base_address(I2C_No);            
     BSET(I2C_C1_TX_SHIFT,I2C_C1_REG(num)); //TX = 1,MCU����Ϊ����ģʽ
     send_signal('S',I2C_No);               //���Ϳ�ʼ�ź� 
     I2C_D_REG(num)  = DeviceAddr & 0xfe;   //�����豸��ַ,��֪ͨ�ӻ���������
     if (wait('T',I2C_No))                  //�ȴ�һ���ֽ����ݴ������
     {      
          return 1;                         //û�д��ͳɹ�,��һ���ֽ�ʧ��
     }
     if (wait('A',I2C_No))                  //�ȴ��ӻ�Ӧ���ź�
     {
          return 1;                         //û�еȵ�Ӧ���ź�,��һ���ֽ�ʧ��
     }
     I2C_D_REG(num)  = AccessAddr;          //���ͷ��ʵ�ַ    
     if (wait('T',I2C_No))                  //�ȴ�һ���ֽ����ݴ������
     {     
          return 1;                         //û�д��ͳɹ�,��һ���ֽ�ʧ��
     }
     if (wait('A',I2C_No))                  //�ȴ��ӻ�Ӧ���ź�
     {  
          return 1;                         //û�еȵ�Ӧ���ź�,��һ���ֽ�ʧ��
     }
     // ��MCU������ģ ʽ�£����λд1������һ�����¿�ʼ�ź�  
     BSET(I2C_C1_RSTA_SHIFT,I2C_C1_REG(num));
     I2C_D_REG(num) = DeviceAddr | 0x01;    //֪ͨ�ӻ���Ϊ��������    
     if (wait('T',I2C_No))                  //�ȴ�һ���ֽ����ݴ������
     { 
          return 1;                         //û�д��ͳɹ�,��һ���ֽ�ʧ��
     }
     if (wait('A',I2C_No))                  //�ȴ��ӻ�Ӧ���ź�
     {
          return 1;                         //û�еȵ�Ӧ���ź�,��һ���ֽ�ʧ��
     }
     BCLR(I2C_C1_RSTA_SHIFT,I2C_C1_REG(num));           //TX = 0,MCU����Ϊ����ģʽ    
     *Data = I2C_D_REG(num);                //����IIC1D,׼����������
     if (wait('T',I2C_No))                  //�ȴ�һ���ֽ����ݴ������
     {       
          return 1;                         //û�д��ͳɹ�,��һ���ֽ�ʧ��
     }
     send_signal('O',I2C_No);               //����ֹͣ�ź�
     *Data = I2C_D_REG(num);                //�������յ���һ������
           return 0;                        //��ȷ���յ�һ���ֽ�����
}

//===========================================================================
//�������ƣ�i2c_write1                                                        
//���ܸ�Ҫ����ӻ�д1���ֽ�����                                           
//����˵����I2C_No:ģ��ţ���ȡֵΪ0��1
//        DeviceAddr:�豸��ַ    ��Χ(1~255)
//        AccessAddr:���ʵ�ַ    ��Χ(0~255)
//        Data:Ҫ�����ӻ���1���ֽ�����
//�������أ�Ϊ0,�ɹ�дһ���ֽ�;Ϊ1,дһ���ֽ�ʧ�� 
//����˵�����ڲ����� send_signal,wait
//===========================================================================
uint8_t i2c_write1(uint8_t I2C_No,uint8_t DeviceAddr, uint8_t AccessAddr, uint8_t Data)
{
     //��ȡi2cģ���ַ
     I2C_MemMapPtr num = i2c_get_base_address(I2C_No);    
     BSET(I2C_C1_TX_SHIFT,I2C_C1_REG(num)); //TX = 1,MCU����Ϊ����ģʽ
     send_signal('S',I2C_No);               //���Ϳ�ʼ�ź�
     I2C_D_REG(num) = DeviceAddr & 0xfe;    //�����豸��ַ,��֪ͨ�ӻ���������
     if (wait('T',I2C_No))                  //�ȴ�һ���ֽ����ݴ������
          return 1;                         //û�д��ͳɹ�,дһ���ֽ�ʧ��
     if (wait('A',I2C_No))                  //�ȴ��ӻ�Ӧ���ź�
          return 1;                         //û�еȵ�Ӧ���ź�,дһ���ֽ�ʧ��
     I2C_D_REG(num) = AccessAddr;           //���ͷ��ʵ�ַ
     if (wait('T',I2C_No))                  //�ȴ�һ���ֽ����ݴ������
          return 1;                         //û�д��ͳɹ�,дһ���ֽ�ʧ��
     if (wait('A',I2C_No))                  //�ȴ��ӻ�Ӧ���ź�
          return 1;                         //û�еȵ�Ӧ���ź�,дһ���ֽ�ʧ��
     I2C_D_REG(num) = Data;                 //д����
     if (wait('T',I2C_No))                  //�ȴ�һ���ֽ����ݴ������
          return 1;                         //û�д��ͳɹ�,дһ���ֽ�ʧ��
     if (wait('A',I2C_No))                  //�ȴ��ӻ�Ӧ���ź�
          return 1;                         //û�еȵ�Ӧ���ź�,дһ���ֽ�ʧ��
     send_signal('O',I2C_No);               //����ֹͣ�ź�
          return 0;
}
//===========================================================================
//�������ƣ�i2c_readn
//���ܸ�Ҫ���Ӵӻ���N���ֽ�����
//����˵����I2C_No:ģ��ţ���ȡֵΪ0��1
//        DeviceAddr:�豸��ַ    ��Χ(1~255)
//        AccessAddr:���ʵ�ַ    ��Χ(0~255)
//        Data:�������ݵĻ�����
//        N:�Ӵӻ������ֽڸ���
//�������أ� Ϊ0,�ɹ���N���ֽ�;Ϊ1,��N���ֽ�ʧ��  
//����˵��: �ڲ�����i2c_read1  
//===========================================================================
uint8_t i2c_readn(uint8_t I2C_No,uint8_t DeviceAddr, uint8_t AccessAddr, uint8_t Data[], uint8_t N)
{
    uint16_t i, j;
    for (i = 0;i < N;i++)
    {
        for(j = 0;j <15*40 ;j++);  //��С��ʱ(���͵�ÿ���ֽ�֮��Ҫ��ʱ����)
        if (i2c_read1(I2C_No,DeviceAddr, AccessAddr + i, &Data[i]))  
             return 1;             //����һ���ֽ�û�н��յ�,����ʧ�ܱ�־:1
    }
    if (i >= N)
        return 0;                  //�ɹ�����N������,���سɹ���־:0
}


//===========================================================================
//�������ƣ�i2c_writen
//���ܸ�Ҫ����ӻ�дN���ֽ�����
//����˵����I2C_No:ģ��ţ���ȡֵΪ0��1
//        DeviceAddr:�豸��ַ    ��Χ(1~255)
//        AccessAddr:���ʵ�ַ    ��Χ(0~255)
//        Data:Ҫд������� ���׵�ַ
//        N:�Ӵӻ������ֽڸ���
//�������أ� Ϊ0,�ɹ�дN���ֽ�;Ϊ1,дN���ֽ�ʧ��
//����˵��: �ڲ�����i2c_write1   
//===========================================================================
uint8_t i2c_writen(uint8_t I2C_No,uint8_t DeviceAddr, uint8_t AccessAddr,uint8_t Data[], uint8_t N)
{
    uint16_t i, j;
    for (i = 0;i < N;i++)
    {
        for(j = 0;j < 15*40;j++);  //��С��ʱ(���͵�ÿ���ֽ�֮��Ҫ��ʱ����)
        if (i2c_write1(I2C_No,DeviceAddr, AccessAddr + i, Data[i]))
            return 1;              //����һ���ֽ�û�з��ͳ�ȥ,����ʧ�ܱ�־:1
    }
    if (i >= N)
        return 0;                  //�ɹ�����N������,���سɹ���־:0
}
//===========================================================================
//�������ƣ�i2c_re_enable_int.
//����˵������i2c��IRQ�жϡ�
//����������i2cNO:i2cģ��ţ���ȡֵΪ0��1
//�������أ��ޡ�
//===========================================================================
void i2c_enable_re_int(uint8_t I2C_No)
{
     NVIC_EnableIRQ(I2C_No+8);
}

//===========================================================================
//�������ƣ�i2c_re_disable_int.
//����˵�����ر�i2c��IRQ�жϡ�
//����������i2cNO:i2cģ��ţ���ȡֵΪ0,1
//�������أ��ޡ�
//===========================================================================
void i2c_disable_re_int(uint8_t I2C_No)
{
     NVIC_DisableIRQ(I2C_No+8);
}

//===========================================================================
//�������ƣ�i2c_get_base_address                                                        
//���ܸ�Ҫ����ȡi2cģ��Ļ�ַ                                                
//����˵����i2cNO:i2cģ��ţ���ȡֵΪ0��1
//�������أ�i2cģ��Ļ�ֵַ                                                                  
//===========================================================================
I2C_MemMapPtr i2c_get_base_address(uint8_t I2C_No)
{
        switch(I2C_No)
        {
            case 0:
                    return I2C0_BASE_PTR;
                      break;
            case 1:
                    return I2C1_BASE_PTR;
                       break;
    }
}

//===========================================================================
//�������ƣ�send_signal
//���ܸ�Ҫ��������Ҫ������ʼ��ֹͣ�ź�
//����˵����I2C_No:ģ��� ����ȡֵΪ0��1
//        Signal: 'S'(Start),������ʼ�ź�   'O'(Over),  ����ֹͣ�ź�
//�������أ���
//===========================================================================
void send_signal(uint8_t Signal,uint8_t I2C_No)
{
    //��ȡi2cģ���ַ
    I2C_MemMapPtr num = i2c_get_base_address(I2C_No);
    if(num==I2C0)
    {
        if (Signal  == 'S')
        {
              //i2c0_c����ģʽѡ��λMST��0��Ϊ1,���Բ�����ʼ�ź�
              BSET(I2C_C1_MST_SHIFT,I2C0_C1);
         }
         else if (Signal == 'O')
        {
              //����ģʽѡ��λMST��1��Ϊ0,���Բ���ֹͣ�ź�
             BCLR(I2C_C1_MST_SHIFT,I2C0_C1);
        }
    }
    else if(num==I2C1)
    {
         if (Signal == 'S')
         {
              //i2c0_c����ģʽѡ��λMST��0��Ϊ1,���Բ�����ʼ�ź�
             BSET(I2C_C1_MST_SHIFT,I2C1_C1);
          }
          else if (Signal == 'O')
         {
              //����ģʽѡ��λMST��1��Ϊ0,���Բ���ֹͣ�ź�
              BCLR(I2C_C1_MST_SHIFT,I2C1_C1);
          }
    }
}
//===========================================================================
//�������ƣ� wait
//���ܸ�Ҫ����ʱ����,ѭ��������Ӧ���־λ,������ɱ�־λ,�ж�MCU
//        �Ƿ���յ�Ӧ���źŻ�һ���ֽ��Ƿ����������ϴ������
//����˵����I2C_No:ģ���  ����ȡֵΪ0��1
//        x:x = 'A'(Ack),�ȴ�Ӧ��;x = 'T'(Transmission),�ȴ�һ���ֽ����ݴ������
//�������أ�0:�յ�Ӧ���źŻ�һ���ֽڴ������;
//        1:δ�յ�Ӧ���źŻ�һ�� �ֽ�û������
//===========================================================================
uint8_t wait(uint8_t x,uint8_t I2C_No)
{
    uint16_t ErrTime, i;
    //��ȡi2cģ�����ַ
    I2C_MemMapPtr num = i2c_get_base_address(I2C_No);
    ErrTime = 255*10;              //�����ѯ��ʱʱ��
    for (i = 0;i < ErrTime;i++)
    {
         if (x == 'A')             //�ȴ�Ӧ���ź�
         {
              if(( I2C_S_REG(num)  & I2C_S_RXAK_MASK)==0)
                   return 0;       //������һ���ֽں�,�յ��˴ӻ���Ӧ���ź�
          }
         else if (x == 'T')        //�ȴ��������һ���ֽ��ź�
         {
             if ((I2C_S_REG(num) & I2C_S_IICIF_MASK) != 0)
             {
                  (I2C_S_REG(num) |=(0 | I2C_S_IICIF_MASK));  //��IICIF��־λ
                       return 0;   //�ɹ�������һ���ֽ�
              }
          }
     }
    if (i >= ErrTime)
         return 1;                 //��ʱ,û���յ�Ӧ���źŻ�����һ���ֽ�
}

//===========================================================================
