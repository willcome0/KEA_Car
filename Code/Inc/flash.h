#ifndef __FLASH_H
#define __FLASH_H

#include "common.h"


//各部分参数在flash中的偏移量
#define PLAN1_FLASH_OFFSET		0
#define PLAN2_FLASH_OFFSET		80
#define PLAN3_FLASH_OFFSET		160
#define PLAN4_FLASH_OFFSET		240
#define PLAN5_FLASH_OFFSET		320
#define COM_FLASH_OFFSET		400

extern uint16_t ALL_DATA[256];	// 储存所有参数
extern uint16_t ALL_DATA_Change;

#define FLASH_Erase_All_Data()	FLASH_EraseSector(DATA_FLASH)
#define FLASH_Write_All_Data()	FLASH_WriteSector(DATA_FLASH, (const uint8_t *)ALL_DATA, 512, 0)




#define FTF									FTMRE

#define SECTOR_SIZE					(512)
#define FLASH_SECTOR_NUM		(256)                   //扇区数
#define FLASH_ALIGN_ADDR		2                       //地址对齐整数倍
#define DATA_FLASH				FLASH_SECTOR_NUM - 1    //储存数据的扇区号（最后一个）
typedef uint32_t						FLASH_WRITE_TYPE;       //flash_write 函数写入 的数据类型

//-------------------------------------------------------------------------------------------------------------------
//  @brief      使用宏定义对flash进行数据读取
//  @param      SectorNum 		需要写入的扇区编号
//  @param      offset	 		地址偏移
//  @param      type		 	读取的数据类型
//  @return     				返回给定地址的数据
//  @since      v1.0
//  Sample usage:               flash_read(20,0,uint32);//读取20号扇区偏移0数据类型为uint32
//-------------------------------------------------------------------------------------------------------------------
#define     FLASH_Read(SectorNum,offset,type)        (*(type *)((uint32_t)(((SectorNum)*SECTOR_SIZE) + (offset))))


void FLASH_Init(void);
uint32_t FLASH_GetSectorSize(void);
uint8_t FLASH_EraseSector(uint32_t SectorNum);
uint8_t FLASH_WriteSector(uint32_t SectorNum, const uint8_t *buf, uint32_t len, uint32_t offset);


#endif