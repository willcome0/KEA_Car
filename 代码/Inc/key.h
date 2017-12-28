#ifndef __KEY_H_
#define __KEY_H_

#include "common.h"

/***********************************************************
 * 
 * 引脚重命名
 * 
 **********************************************************/
#define KEY_Down_Port      PTE
#define KEY_Down_Pin       PTE4

#define KEY_Up_Port    PTD
#define KEY_Up_Pin     PTD3

#define KEY_Mid_Port     PTF
#define KEY_Mid_Pin      PTF1

#define KEY_Right_Port    PTF
#define KEY_Right_Pin     PTF0

#define KEY_Left_Port   PTD
#define KEY_Left_Pin    PTD4

/***********************************************************
 * 
 * 定义 按下值
 * 
 **********************************************************/
#define Press_NULL    0
#define Press_Up      1
#define Press_Down    2
#define Press_Mid     3
#define Press_Left    4
#define Press_Right   5


/***********************************************************
 * 
 * 函数声明
 * 
 **********************************************************/
void KEY_Init(void);
uint8_t Get_Key(void);


#endif
