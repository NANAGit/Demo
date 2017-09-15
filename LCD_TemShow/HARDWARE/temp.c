#include "temp.h"
#include "delay.h"

float  Tem=0;  //实际温度变量

void DS18B20_GPIOInit(void )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA,ENABLE );
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init (GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
}


u8 DS18B20_Init(void)
{   u16 i=0;
	  DS18B20=0;
	  delay_us (500);
	  DS18B20=1;
	  while(DS18B20)
		{
			delay_us (1);
			i++;
			if(i>5000)
			{return 0;}
		}
		return 1;
}

void DS18B20_WriteByte(u8 data)
{  u8 i;
	for(i=0;i<8;i++)
	{
	  DS18B20=0;
	  delay_us(1);
	  DS18B20=data&0x01;
	  delay_us(68);
		DS18B20=1;
		delay_us(1);
		data>>=1;
	}
}

u8 DS18B20_ReadByte(void )
{ 
	u8 i,byte,bi;
	for(i=0;i<8;i++)
	{
		DS18B20=0;
	  delay_us(1);
	  DS18B20=1;
	  delay_us(6);
		bi=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
		byte=(byte>>1)|(bi<<7);
		delay_us(48);
	}
	
	return byte;
}

void  DS18B20_ChangTemp()
{   
	  DS18B20_Init();
	  delay_ms(1);
		DS18B20_WriteByte(0xCC);  //跳过ROM操作命令
		DS18B20_WriteByte(0x44); //温度转换命令
		delay_ms(100);
}

void  DS18B20_ReadTemCmd()
{
	DS18B20_Init();
	delay_ms(1);
	DS18B20_WriteByte(0xCC);  //跳过ROM操作命令
	DS18B20_WriteByte(0xBE); //发送读取温度命令
}

void DS18B20_ReadTemp(void)
{  
   u8 Tu;
	 u16 Temp_B;
	 u8 Tm_H=0,Tm_L=0;
   DS18B20_ChangTemp();
	 DS18B20_ReadTemCmd();
	 Tm_L=DS18B20_ReadByte();
	 Tm_H=DS18B20_ReadByte();
	 Temp_B=Tm_H;
	 Temp_B<<=8;
	 Temp_B |=Tm_L;
	 Tu=Temp_B&0x8000;
   if(Tu==0)
	 {
	   Tem=Temp_B * 0.0625;
	 }
	 if(Tu==1)
	 {
		 Temp_B--;
		 Tem=-(~Temp_B)*0.0625;
	 }
}
	

	



