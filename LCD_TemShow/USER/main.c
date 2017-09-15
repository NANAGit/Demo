#include "stm32f4xx.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"
#include "Imgine.h"
#include "temp.h"
//ALIENTEK ̽����STM32F407������ ʵ��0
//STM32F4����ģ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK
  
extern float Tem;

int main(void)
{ float T;
	u32 i,k,n,TemL;	
	u16 PointColor;
	k=0;n=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
  delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	DS18B20_GPIOInit();
 	LCD_Init();  //��ʼ��LCD FSMC�ӿ�
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
		{TemL=(int)T/10%10+1;}   //��������
		
		printf("Tem:%05.2f", Tem);
		printf("��\r\n");
		LCD_ShowString(82,50,150,24,24,"Tem:");   //������������Ȳ�֪����ȷ��
		LCD_ShowxNum(130,50,Tem,2,24,0);
		
		LCD_ShowString(154,50,50,24,24,".");
   	LCD_ShowxNum(165,50,TemL,1,24,0);
    LCD_ShowString(176,50,50,24,24,"`C");
	}
	
}



	
