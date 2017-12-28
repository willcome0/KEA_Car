#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
//#include "delay.h"

/***************************************/
/*
ֻ�и����Դ溯������ˢ����Ļ
��ʾ������������ģʽѡ�񣬼�������ʾ��׵׺���
������ͼ����ʾ��������ʾ
*/

uint8_t HtoL(uint8_t a)
{
    return (a & 0x01)<<7| ((a>>1)&0x01)<<6 |((a>>2)&0x01)<<5 |((a>>3)&0x01)<<4 |((a>>4)&0x01)<<3 |((a>>5)&0x01)<<2 |((a>>6)&0x01)<<1 |((a>>7)&0x01);
}
    
    
    





volatile uint8_t OLED_GRAM[OLED_X_MAX][8];
uint8_t  oled[OLED_X_MAX][8] = {0};

void PicChange(void)
{
    for(int i=0;i<OLED_X_MAX;i++)
    {
        for(int j=0;j<8;j++)
        {
           oled[i][j] = HtoL(OLED_GRAM[OLED_X_MAX - i -1][ 7 - j]);
           // oled[i][j]  = 
        }
    }
return ;
}




//�����Դ浽OLED
void OLED_Refresh_Gram(void)
{
    PicChange();
    
	for(uint8_t i=0; i<8; i++)
	{
		OLED_WR_Byte (0xb0+i,Wirte_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,Wirte_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,Wirte_CMD);      //������ʾλ�á��иߵ�ַ
		for(uint8_t n=0; n<OLED_X_MAX; n++)
			OLED_WR_Byte(oled[n][i], Wirte_DATA);
	}
}
//��ʼ��SSD1306
void OLED_Init(void)
{
    Pin_Output_Config(OLED_D0_Port,  OLED_D0_Pin,  SET);
    Pin_Output_Config(OLED_D1_Port,  OLED_D1_Pin,  SET);
    Pin_Output_Config(OLED_RST_Port, OLED_RST_Pin, SET);
    Pin_Output_Config(OLED_DC_Port,  OLED_DC_Pin,  SET);
    
	OLED_DC_HIGH();
	OLED_RST_LOW();

	for(uint16_t i = 4000; i > 0; i--)	//������ʱ100ms
		for(uint16_t j = 100; j > 0; j--);

	OLED_RST_HIGH();

	OLED_WR_Byte(0xAE, Wirte_CMD); //�ر���ʾ
	OLED_WR_Byte(0xD5, Wirte_CMD); //����ʱ�ӷ�Ƶ����,��Ƶ��
	OLED_WR_Byte(0x80, Wirte_CMD);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	OLED_WR_Byte(0xA8, Wirte_CMD); //��������·��
	OLED_WR_Byte(0X3F, Wirte_CMD); //Ĭ��0X3F(1/64)
	OLED_WR_Byte(0xD3, Wirte_CMD); //������ʾƫ��
	OLED_WR_Byte(0X00, Wirte_CMD); //Ĭ��Ϊ0

	OLED_WR_Byte(0x40, Wirte_CMD); //������ʾ��ʼ�� [5:0],����.

	OLED_WR_Byte(0x8D, Wirte_CMD); //��ɱ�����
	OLED_WR_Byte(0x14, Wirte_CMD); //bit2������/�ر�
	OLED_WR_Byte(0x20, Wirte_CMD); //�����ڴ��ַģʽ
	OLED_WR_Byte(0x02, Wirte_CMD); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WR_Byte(0xA1, Wirte_CMD); //���ض�������,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0, Wirte_CMD); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	OLED_WR_Byte(0xDA, Wirte_CMD); //����COMӲ����������
	OLED_WR_Byte(0x12, Wirte_CMD); //[5:4]����

	OLED_WR_Byte(0x81, Wirte_CMD); //�Աȶ�����
	OLED_WR_Byte(0xEF, Wirte_CMD); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	OLED_WR_Byte(0xD9, Wirte_CMD); //����Ԥ�������
	OLED_WR_Byte(0xf1, Wirte_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB, Wirte_CMD); //����VCOMH ��ѹ����
	OLED_WR_Byte(0x30, Wirte_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4, Wirte_CMD); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	OLED_WR_Byte(0xA6, Wirte_CMD); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ
	OLED_WR_Byte(0xAF, Wirte_CMD); //������ʾ
	OLED_Clear();
}
//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	switch(cmd)
	{
		case 0: OLED_DC_LOW();	break;
		case 1: OLED_DC_HIGH();	break;
	}
	for(uint8_t i=0; i<8; i++)
	{
		OLED_SCL_LOW();
		if(dat&0x80)
			OLED_SDA_HIGH();
		else
			OLED_SDA_LOW();
		OLED_SCL_HIGH();
		dat<<=1;
	}
	OLED_DC_HIGH();
}

//����OLED��ʾ
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,Wirte_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,Wirte_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,Wirte_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,Wirte_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,Wirte_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,Wirte_CMD);  //DISPLAY OFF
}
//��������������ʾ�Դ�ȫ�����
void OLED_Clear(void)
{
	for(uint8_t i=0; i<8; i++)
		for(uint8_t n=0; n<128; n++)
			OLED_GRAM[n][i]=0X00;
}
//���㺯��
//x:0~127
//y:0~63
//mode:0 ��գ�1 ���
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t mode)
{
	if(x>127 || y>63)
		return;
	uint8_t pos = 7 - y/8;
	uint8_t bx = y%8;
	uint8_t temp = 0x01<<(7-bx);
	if(mode)
		OLED_GRAM[x][pos] |= temp;
	else
		OLED_GRAM[x][pos] &= ~temp;
}
//x1,y1,x2,y2 �������ĶԽ�����
//ȷ����1����2���ڷ�Χ�У��ҵ�2���ڵ�1
//mode:0 ���; 1 ���
void OLED_Fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)
{
	for(uint8_t x=x1; x<=x2; x++)
	{
		for(uint8_t y=y1; y<=y2; y++)
			OLED_DrawPoint(x, y, mode);
	}
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//chr:һ���ַ�
//size:ѡ������ 12/16/24
//mode:0 �׵׺���; 1 �ڵװ��֣�������
void OLED_Show_Char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode)
{
	uint8_t temp;
	uint8_t y0 = y;
	uint8_t csize = (size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr = chr-' ';//�õ�ƫ�ƺ��ֵ	���ո���ASCII��ʮ����Ϊ32�������ֿ����ǵ�һλ
    for(uint8_t t=0; t<csize; t++)
    {
		switch(size)//ѡ����õ��ֿ�
		{
			case 12: temp = asc2_1206[chr][t];	break;
			case 16: temp = asc2_1608[chr][t];	break;
			case 24: temp = asc2_2412[chr][t];	break;
			default:	break;
		}
		for(uint8_t t1=0; t1<8; t1++)
		{
			if(temp&0x80)
				OLED_DrawPoint(x, y, mode);
			else
				OLED_DrawPoint(x, y, !mode);
			temp <<= 1;
			y++;
			if((y-y0) == size)
			{
				y = y0;
				x++;
				break;
			}
		}
    }
}
//m^n��������Ҫ�����������
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result = 1;
	while(n--)
		result *= m;
	return result;
}

//��ʾ2������
//x,y :�������
//num:��ֵ(0~4294967295);
//len :���ֵ�λ��
//size:�����С
//mode:0 �׵׺���; 1 �ڵװ���(����)
void OLED_Show_Num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode)
{
	uint8_t enshow = 0;
	for(uint8_t t=0; t<len; t++)
	{
		uint8_t temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_Show_Char(x+(size/2)*t, y, ' ', size, mode);
				continue;
			}
			else
				enshow=1;
		}
	 	OLED_Show_Char(x+(size/2)*t, y, temp+'0', size, mode); //temp+'0'������ת�ַ�
	}
}
//��ʾ�ַ���
//x,y:�������
//size:�����С
//*ch:�ַ�����ʼ��ַ
//mode:0 �׵׺���; 1 �ڵװ���(����)
void OLED_Show_Str(uint8_t x, uint8_t y, const uint8_t *ch, uint8_t size, uint8_t mode)
{
    while((*ch<='~')&&(*ch>=' '))//�ж��ǲ��ǷǷ��ַ�
    {
//        if(x > (128-(size/2)))
//				{
//					x = 0;
//					y += size;
//				}
//        if(y > (64-size))
//				{
//					y = x = 0;
//					OLED_Clear();
//				}
        OLED_Show_Char(x, y, *ch, size, mode);
        x+=size/2;
        ch++;
    }
}




/* ����ʮ����(0-7)==>ʮ������λת����������ʾ
�������������ң�����ʮ������λ˳���ǵ��� */
const uint8_t DCB2HEX_TAB[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

uint8_t OLED_JudgeOver(uint8_t x, uint8_t y)//�ж����������Ƿ񳬹�OLED���ر߽�
{
	if(x > (OLED_X_MAX-32))
		return 1;
	if(y > (OLED_Y_MAX-32))
		return 1;
    return 0;
}
void OLED_Show_Char24_32(uint8_t x, uint8_t y, uint8_t ch, uint8_t mode)
{
	uint8_t   font_date;
	uint8_t   i, j, k;

   //����Խ�����˳���ʾ

	for(i=0; i<14; i++)//һ���������ֿ�
	{
		if(FONT24x32_TAB[i]==ch)
			break;
	}
	ch = i;

	for(i=0; i<32; i++)      // ��ʾ��32��
	{
		for(j=0; j<3; j++)     // ÿ�й�3�ֽ�
		{
			font_date = FONT24x32[ch][i*3+j];

			for(k=0; k<8; k++)
			{
				if( font_date & DCB2HEX_TAB[k] )
					OLED_DrawPoint(x, y, mode);//��
				else
					OLED_DrawPoint(x, y, !mode);//�������˴��͵���"!"��������"~"��
				x++;
			}
		}
		y++;    // ָ����һ��
		x -= 24;    // �ָ�xֵ
   }
}
void OLED_Show_Char48_64(uint8_t x, uint8_t y, uint8_t ch, uint8_t mode)
{
	uint8_t   font_date;
	uint8_t   i, j, k;


	for(i=0; i<9; i++)//һ���������ֿ�,�Ҳ����Ļ���ʾ�ֿ������һ��
	{
		if(FONT48x64_TAB[i]==ch)
			break;
	}
	ch = i;

	for(i=0; i<64; i++)      // ��ʾ��32��
	{
		for(j=0; j<6; j++)     // ÿ�й�3�ֽ�
		{
			font_date = FONT48x64[ch][i*6+j];

			for(k=0; k<8; k++)
			{
				if( font_date & DCB2HEX_TAB[k] )
					OLED_DrawPoint(x, y, mode);//��
				else
					OLED_DrawPoint(x, y, !mode);//�������˴��͵���"!"��������"~"��
				x++;
			}
		}
		y++;    // ָ����һ��
		x -= 48;    // �ָ�xֵ
   }
}
/*ȡ��ģʱ�����Ϊ8�ı��������ȡ��ģ�൱����16x12*/
void OLED_Show_ZH12_12(uint8_t x, uint8_t y, uint8_t ch1, uint8_t ch2, uint8_t mode)
{
	uint8_t   font_dat;
	uint8_t   i, j, k;

   for(i=0; i<100; i+=2)//һ���������ֿ�
   {  //��ͬʱ�жϺ��ֵĵ��ֽں͸��ֽ�
      if(FONT12x12_TAB[i]==ch1 && FONT12x12_TAB[i+1]==ch2)
         break;
   }
   ch1 = i;

   for(i=0; i<12; i++)//��ʾ��12��
   {
      for(j=0; j<2; j++) //ÿ��2�ֽ�
      {
         font_dat = FONT12x12[ch1][i*2+j];
         for(k=0; k<8; k++)
         {  /* ������Ӧ�ĵ�Ϊcolor��Ϊback_color */
            if( font_dat & DCB2HEX_TAB[k] )
               OLED_DrawPoint(x, y, mode);
            else
               OLED_DrawPoint(x, y, !mode);
            x++;
         }
      }
      y++;									// ָ����һ��
      x -= 16;								// �ָ�xֵ
   }
}
void  OLED_Show_StrAll(uint8_t x, uint8_t y, uint8_t *str, uint8_t mode)
{  
    while(1)
    {  
        if( (*str)=='\0' )
            break;
        if((*str<='~')&&(*str>=' '))
        {
            OLED_Show_Char(x, y, *str, 12, mode);
            x+=6;
            str++;
        }
        else
        {
            OLED_Show_ZH12_12(x, y, *str, *(str+1), mode);
            x+=12;
            str+=2;
        }
    }
}
void OLED_Show_ZH14_16(uint8_t x, uint8_t y, uint8_t ch, uint8_t mode)
{
	uint8_t   font_dat;
	uint8_t   i, j, k;

   for(i=0; i<15; i++)//һ���������ֿ�
   {
      if(FONT24x32_TAB[i]==ch)
         break;
   }
   ch = i;

   for(i=0; i<16; i++)//��ʾ��16��
   {
      for(j=0; j<2; j++) //ÿ��2�ֽ�
      {
         font_dat = FONT24x32[ch][i*2+j];
         for(k=0; k<8; k++)
         {  /* ������Ӧ�ĵ�Ϊcolor��Ϊback_color */
            if( font_dat & DCB2HEX_TAB[k] )
               OLED_DrawPoint(x, y, mode);
            else
               OLED_DrawPoint(x, y, !mode);
            x++;
         }
      }
      y++;									// ָ����һ��
      x -= 16;								// �ָ�xֵ
   }
}

/****************************************************************************
* ���ƣ�GUI_LoadLine()
* ���ܣ������ɫͼ�ε�һ�����ݡ�
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           data		Ҫ�����ʾ�����ݡ�
*           x_num      Ҫ��ʾ���еĵ����
* ���ڲ���������ֵΪ1ʱ��ʾ�����ɹ���Ϊ0ʱ��ʾ����ʧ�ܡ�
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  OLED_Show_PicLine(uint8_t x, uint8_t y, uint8_t *data, uint32_t x_num, uint8_t mode)
{
	uint8_t bit_data=0;

	for(uint8_t i=0; i<x_num; i++)
	{
		if(0 == (i%8))	//�ж��Ƿ�Ҫ��ȡ��������
			bit_data = *data++;
		if( bit_data & DCB2HEX_TAB[i&0x07] )
			OLED_DrawPoint(x, y, mode);//��
		else
			OLED_DrawPoint(x, y, !mode);//�������˴��͵���"!"��������"~"��
		x++;
	}
}
/****************************************************************************
* ���ƣ�GUI_LoadPic()
* ���ܣ������ɫͼ�����ݡ�
* ��ڲ����� x		ָ����ʾλ�ã�x����
*           y		ָ����ʾλ�ã�y����
*           dat		Ҫ�����ʾ������
*           hno     Ҫ��ʾ���еĵ����
*           lno     Ҫ��ʾ���еĵ����
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  OLED_Show_Pic(uint8_t x, uint8_t y, uint8_t *data, uint8_t x_num, uint8_t y_num, uint8_t mode)
{
	for(uint8_t i=0; i<y_num; i++)
	{
		OLED_Show_PicLine(x, y, data, x_num, mode);// ���һ������
		y++;										// ��ʾ��һ��
		data = data + (x_num>>3);// ������һ�е�����
		data++;
	}
}



//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127


/*
    1��Ҫ���������
		{
			uint8_t ch[25] = "";
			sprintf(ch, "                     ", �������);	          "                     "
			OLED_ShowString(0, 0, ch, 12, 1);
		}
		2��ֱ����ʾ��
		OLED_ShowString(0, 0, "                     ", 12);

		OLED_Show_Str(0,  0, "MJMJMJMJMJMJMJMJMJMJM", 12, 1);
		OLED_Show_Str(0, 13, "MJMJMJMJMJMJMJMJMJMJM", 12, 1);
		OLED_Show_Str(0, 26, "MJMJMJMJMJMJMJMJMJMJM", 12, 1);
		OLED_Show_Str(0, 39, "MJMJMJMJMJMJMJMJMJMJM", 12, 1);
		OLED_Show_Str(0, 52, "MJMJMJMJMJMJMJMJMJMJM", 12, 1);
*/


