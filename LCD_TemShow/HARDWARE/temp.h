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
����STM32F4  ���������ó�˫��IOʱ��ֻ��Ҫ���������óɿ�©�����Ȼ�������������ʵ����˫��IO


ע����ȡIO����ʱ��Ҫʹ��GPIO_ReadInputDataBit() ������

*************************************************************/
