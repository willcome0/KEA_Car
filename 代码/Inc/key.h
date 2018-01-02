#ifndef __KEY_H_
#define __KEY_H_

#include "common.h"

/***********************************************************
 * 
 * 引脚重命名
 * 
 **********************************************************/
#define KEY_Up_Port     PTA
#define KEY_Up_Pin      PTA7

#define KEY_Down_Port   PTA  
#define KEY_Down_Pin    PTA6

#define KEY_Mid_Port    PTE
#define KEY_Mid_Pin     PTE4

#define KEY_Left_Port   PTF
#define KEY_Left_Pin    PTF2

#define KEY_Right_Port  PTF
#define KEY_Right_Pin   PTF1

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
