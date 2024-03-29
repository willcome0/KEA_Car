#include "flash.h"

// flash commands 
#define ERASE_VERITF_ALL_BLOCKS             0x01  // 擦除检验所有区块
#define ERASE_VERITF_BLOCKS                 0x02  // 擦除检验数据块
#define ERASE_VERITF_FLASH_SECTION          0x03  // 擦除检验Flash 段
#define READ_ONCE                           0x04  // 读取一次
#define PROGRAM_FLASH                       0x06  // 编程Flash
#define PROGRAM_ONCE                        0x07  // 编程一次
#define ERASE_ALL_BLOCKS                    0x08  // 擦除所有区块
#define ERASE_FLASH_BLOCKS                  0x09  // 擦除Flash 区块
#define ERASE_FLASH_SECTOR                  0x0A  // 擦除Flash 扇区
#define UNSECURE_FLASH                      0x0B  // 解密的Flash
#define VERITF_BACKDOOR_ACCESS_KEY          0x0C  // 检验后门访问密钥
#define SET_USER_MARGIN_LEVEL               0x0D  // 设置用户裕量水平
#define SET_FACTORY_MARGIN_LEVEL            0x0E  // 设置出厂裕量水平
#define CONFIGURE_NVM                       0x0F  // 配置NVM


uint16_t ALL_DATA[256];
uint16_t ALL_DATA_Change = 999;	// 999代表没有更改
//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLASH初始化
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void FLASH_Init(void)
{
    uint16_t clk;
    
    SIM->SCGC |= SIM_SCGC_FLASH_MASK;                                   //开启flash时钟         
    
    while(!(FTF->FSTAT & FTMRE_FSTAT_CCIF_MASK));                       //等待之前命令完成
    
    clk = BUS_CLK_KHZ/1000-1;

    FTF->FCLKDIV = FTMRE_FCLKDIV_FDIV(clk) | FTMRE_FCLKDIV_FDIVLCK_MASK;//设置flash分频系数
    
    FTF->FSTAT = FTMRE_FSTAT_FPVIOL_MASK | FTMRE_FSTAT_ACCERR_MASK;     //清除状态标识
}



volatile uint8_t s_flash_command_run[] = {0x00, 0xB5, 0x80, 0x21, 0x01, 0x70, 0x01, 0x78, 0x09, 0x06, 0xFC, 0xD5,0x00, 0xBD};
typedef void (*flash_run_entry_t)(volatile uint8_t *reg);
flash_run_entry_t s_flash_run_entry;
//下面使用
uint8_t FlashCmdStart(void)
{
    __disable_irq();
    
    FTF->FSTAT = FTMRE_FSTAT_FPVIOL_MASK | FTMRE_FSTAT_ACCERR_MASK;
    
    s_flash_run_entry = (flash_run_entry_t)((uint32_t)s_flash_command_run + 1);
    s_flash_run_entry(&FTF->FSTAT);
    
    __enable_irq();
    
    if(FTF->FSTAT & (FTMRE_FSTAT_ACCERR_MASK | FTMRE_FSTAT_FPVIOL_MASK | FTMRE_FSTAT_MGSTAT_MASK)) return 1;	//出现错误
    return 0;												//成功
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLASH擦除扇区
//  @param      SectorNum 		需要擦除的扇区编号
//  @return     				返回1擦除失败，返回0擦除成功
//  @since      v1.0
//  Sample usage:               uint32 dat = FLASH_GetSectorSize(10);
//-------------------------------------------------------------------------------------------------------------------
uint8_t FLASH_EraseSector(uint32_t SectorNum)
{
    uint32_t addr;

		addr = (uint32_t)SectorNum*SECTOR_SIZE;

    FTF->FCCOBIX = 0;
    FTF->FCCOBHI = ERASE_FLASH_SECTOR;
    FTF->FCCOBLO = addr>>16;
    
    FTF->FCCOBIX = 1;
    FTF->FCCOBHI = (addr&0xffff)>>8;
    FTF->FCCOBLO = addr&0xff;
    
    FlashCmdStart();
    
    return 0;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLASH数据写入到扇区
//  @param      SectorNum 		需要写入的扇区编号
//  @param      *buf	 		数据首地址
//  @param      len		 		写入的字节数 特别提醒一个uint16变量是两个字节 一个uint32变量是四个字节 每次写入得长度必须为4得倍数
//  @param      offset		 	必须为4的整数倍
//  @return     				返回1写入失败，返回0写入成功
//  @since      v1.0
//  Sample usage:               FLASH_WriteSector(10,(const uint8 *)buf,4,0);//将buf数组里面的前四位数据写入到10号扇区(每一位是uint8类型)
//  @note                       使用flash时，最好从最后一个扇区开始使用，最后一个扇区号为255
//-------------------------------------------------------------------------------------------------------------------


uint8_t FLASH_WriteSector(uint32_t SectorNum, const uint8_t *buf, uint32_t len, uint32_t offset)
{
    uint16_t step, i;
    uint32_t addr;

	addr = (uint32_t)SectorNum*SECTOR_SIZE + offset;

    step = 4;

	for(i=0; i<len; i+=step)
	{
        FTF->FCCOBIX = 0;
        FTF->FCCOBHI = PROGRAM_FLASH;
        FTF->FCCOBLO = addr>>16;
        
        FTF->FCCOBIX = 1;
        FTF->FCCOBHI = (addr&0xFFFF)>>8;
        FTF->FCCOBLO = addr&0xFC;
        
        FTF->FCCOBIX = 2;
        FTF->FCCOBLO = buf[0];
        FTF->FCCOBHI = buf[1];
        
        FTF->FCCOBIX = 3;
        FTF->FCCOBLO = buf[2];
        FTF->FCCOBHI = buf[3];

        buf += step;
        addr += step;

        FlashCmdStart();
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLASH初始化
//  @return     				返回一个扇区的大小
//  @since      v1.0
//  Sample usage:               uint32 dat = FLASH_GetSectorSize();
//-------------------------------------------------------------------------------------------------------------------
uint32_t FLASH_GetSectorSize(void)
{
    return SECTOR_SIZE;
}


