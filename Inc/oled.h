#ifndef OLED_H
#define OLED_H	

#include "SKEAZ1284.h" 
#include "common.h"

/*官方板*/
//#define OLED_D0_Port     PTI
//#define OLED_D0_Pin      PTI3

//#define OLED_D1_Port     PTI
//#define OLED_D1_Pin      PTI2

//#define OLED_RST_Port    PTF
//#define OLED_RST_Pin     PTF3

//#define OLED_DC_Port     PTF
//#define OLED_DC_Pin      PTF2

/*自己板*/
#define OLED_D0_Port     PTB
#define OLED_D0_Pin      PTB0

#define OLED_D1_Port     PTB
#define OLED_D1_Pin      PTB1

#define OLED_RST_Port    PTF
#define OLED_RST_Pin     PTF2

#define OLED_DC_Port     PTF
#define OLED_DC_Pin      PTF3

#define  OLED_X_MAX		128		//定义液晶x轴的像素数
#define  OLED_Y_MAX		64 		//定义液晶y轴的像素数
//---------------------------OLED端口定义--------------------------

#define OLED_SCL_HIGH()		Pin_Output_Set(OLED_D0_Port,  OLED_D0_Pin,  SET)  //D0
#define OLED_SCL_LOW()		Pin_Output_Set(OLED_D0_Port,  OLED_D0_Pin,  RESET)

#define OLED_SDA_HIGH()		Pin_Output_Set(OLED_D1_Port,  OLED_D1_Pin,  SET)  //D1
#define OLED_SDA_LOW()		Pin_Output_Set(OLED_D1_Port,  OLED_D1_Pin,  RESET)

#define OLED_RST_HIGH()		Pin_Output_Set(OLED_RST_Port, OLED_RST_Pin, SET)  //RST
#define OLED_RST_LOW()		Pin_Output_Set(OLED_RST_Port, OLED_RST_Pin, RESET)

#define OLED_DC_HIGH()		Pin_Output_Set(OLED_DC_Port,  OLED_DC_Pin,  SET)  //DC
#define OLED_DC_LOW()		Pin_Output_Set(OLED_DC_Port,  OLED_DC_Pin,  RESET)


#define Wirte_CMD  0	//写命令
#define Wirte_DATA 1	//写数据

extern volatile uint8_t OLED_GRAM[OLED_X_MAX][8];


void OLED_Refresh_Gram(void);
void OLED_Init(void);
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);

void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_Fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
void OLED_Show_Char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
void OLED_Show_Num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode);
void OLED_Show_Str(uint8_t x, uint8_t y, const uint8_t *ch, uint8_t size, uint8_t mode);
void OLED_Show_Char24_32(uint8_t x, uint8_t y, uint8_t ch, uint8_t mode);
void OLED_Show_Char48_64(uint8_t x, uint8_t y, uint8_t ch, uint8_t mode);
void OLED_Show_ZH14_16(uint8_t x, uint8_t y, uint8_t ch, uint8_t mode);

void  OLED_Show_PicLine(uint8_t x, uint8_t y, uint8_t *data, uint32_t x_num, uint8_t mode);
void  OLED_Show_Pic(uint8_t x, uint8_t y, uint8_t *data, uint8_t x_num, uint8_t y_num, uint8_t mode);
void  OLED_Show_StrAll(uint8_t x, uint8_t y, uint8_t *str, uint8_t mode);



#endif
