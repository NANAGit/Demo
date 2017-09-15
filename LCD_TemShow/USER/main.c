#include "stm32f4xx.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"
#include "Imgine.h"
#include "temp.h"
//ALIENTEK 探索者STM32F407开发板 实验0
//STM32F4工程模板-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
  
extern float Tem;

int main(void)
{ float T;
	u32 i,k,n,TemL;	
	u16 PointColor;
	k=0;n=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
  delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	DS18B20_GPIOInit();
 	LCD_Init();  //初始化LCD FSMC接口
	LCD->LCD_REG=0x36;
	LCD->LCD_RAM=0x0C;
	LCD->LCD_REG =0x2C;
	for(i=0;i<76800;i++)
		{  
			PointColor=gImage_Imgine[k]<<8;
			PointColor|=gImage_Imgine[n];
			LCD->LCD_RAM=PointColor;
			k+=2; n+=2;
		}	k=0;n=1;
	
  
	while(1)
	{ 
		
   
   
    DS18B20_ReadTemp();
		T=Tem*100;
		if((int)T%10>=0&&(int)T%10<5)
		{ TemL=(int)T/10%10;}
		if((int)T%10>=5&&(int)T%10<=9)
		{TemL=(int)T/10%10+1;}   //四舍五入
		
		printf("Tem:%05.2f", Tem);
		printf("℃\r\n");
		LCD_ShowString(82,50,150,24,24,"Tem:");   //第三个参数宽度不知怎样确定
		LCD_ShowxNum(130,50,Tem,2,24,0);
		
		LCD_ShowString(154,50,50,24,24,".");
   	LCD_ShowxNum(165,50,TemL,1,24,0);
    LCD_ShowString(176,50,50,24,24,"`C");
	}
	
}



	
