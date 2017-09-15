#ifndef __TEMP_H
#define __TEMP_H
#include "sys.h"

#define DS18B20  PAout(15)



u8 DS18B20_Init(void );   
u8 DS18B20_ReadByte(void );
void DS18B20_ReadTemp(void);
void DS18B20_WriteByte(u8 data);
void DS18B20_GPIOInit(void);

#endif

/*************************************************************
对于STM32F4  把引脚配置成双向IO时，只需要把引脚配置成开漏输出，然后外接上拉，就实现了双向IO


注：读取IO数据时需要使用GPIO_ReadInputDataBit() 函数。

*************************************************************/
