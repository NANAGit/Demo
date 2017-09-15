#include "lcd.h"
#include "delay.h"
#include "font.h"

u16 POINT_COLOR=0xF800;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 
_lcd_dev lcddev;
void LCD_WR_REG(vu16 cmd)
{
	 cmd=cmd;
	 LCD->LCD_REG=cmd;
}

void LCD_WR_DATA(vu16 data)
{
	data=data;
	LCD->LCD_RAM=data;
}

u16 LCD_RD_DATA(void )
{
	vu16 Rdata;
	Rdata =LCD->LCD_RAM;
	return Rdata;
}


void LED_Init(void )
{
	GPIO_InitTypeDef  LED_GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	LED_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	LED_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	LED_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	LED_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	LED_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &LED_GPIO_InitStructure);
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
}

void FSMC_Init(void)
{
	GPIO_InitTypeDef  FSMC_GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//使能FSMC时钟  
	 
	FSMC_GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(7<<8)|(3<<14);//PD0,1,4,5,8,9,10,14,15 AF OUT
  FSMC_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  FSMC_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  FSMC_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  FSMC_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &FSMC_GPIO_InitStructure);//初始化  
	
  FSMC_GPIO_InitStructure.GPIO_Pin = (0X1FF<<7);//PE7~15,AF OUT
  FSMC_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  FSMC_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  FSMC_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  FSMC_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &FSMC_GPIO_InitStructure);//初始化  

	FSMC_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PF12,FSMC_A6
  FSMC_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  FSMC_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  FSMC_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  FSMC_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	
  GPIO_Init(GPIOG, &FSMC_GPIO_InitStructure);//初始化  

	FSMC_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PF12,FSMC_NE4
  FSMC_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  FSMC_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  FSMC_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  FSMC_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &FSMC_GPIO_InitStructure);//初始化 

  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);//PD0,AF12
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);//PD1,AF12
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);//PD15,AF12
 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);//PE7,AF12
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);//PE15,AF12
 
  GPIO_PinAFConfig(GPIOG,GPIO_PinSource2,GPIO_AF_FSMC);//PF12,AF12
  GPIO_PinAFConfig(GPIOG,GPIO_PinSource12,GPIO_AF_FSMC);
	
	readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
  readWriteTiming.FSMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
    

	writeTiming.FSMC_AddressSetupTime =9;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
  writeTiming.FSMC_DataSetupTime = 8;		 //数据保存时间为6ns*9个HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0x00;
  writeTiming.FSMC_DataLatency = 0x00;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 

 
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
}
u16 Read_ID(void )
{   
    LCD_WR_REG(0xD3);
	  lcddev .id=LCD_RD_DATA();  //读XX
	  lcddev .id=LCD_RD_DATA();  //读00H
	  lcddev .id=LCD_RD_DATA();  //读93H
	  lcddev .id<<=8;
	  lcddev .id |=LCD_RD_DATA();  //读到41H，然后与9300H相与，得9341H
	  return lcddev .id ;
}
void LCD_Order()
{
	LCD_WR_REG(0xCF);  
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0xC1); 
		LCD_WR_DATA(0X30); 
		LCD_WR_REG(0xED);  
		LCD_WR_DATA(0x64); 
		LCD_WR_DATA(0x03); 
		LCD_WR_DATA(0X12); 
		LCD_WR_DATA(0X81); 
		LCD_WR_REG(0xE8);  
		LCD_WR_DATA(0x85); 
		LCD_WR_DATA(0x10); 
		LCD_WR_DATA(0x7A); 
		LCD_WR_REG(0xCB);  
		LCD_WR_DATA(0x39); 
		LCD_WR_DATA(0x2C); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x34); 
		LCD_WR_DATA(0x02); 
		LCD_WR_REG(0xF7);  
		LCD_WR_DATA(0x20); 
		LCD_WR_REG(0xEA);  
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_REG(0xC0);    //Power control 
		LCD_WR_DATA(0x1B);   //VRH[5:0] 
		LCD_WR_REG(0xC1);    //Power control 
		LCD_WR_DATA(0x01);   //SAP[2:0];BT[3:0] 
		LCD_WR_REG(0xC5);    //VCM control 
		LCD_WR_DATA(0x30); 	 //3F
		LCD_WR_DATA(0x30); 	 //3C
		LCD_WR_REG(0xC7);    //VCM control2 
		LCD_WR_DATA(0XB7); 
		LCD_WR_REG(0x36);    // Memory Access Control 
		LCD_WR_DATA(0x48); 
		LCD_WR_REG(0x3A);   
		LCD_WR_DATA(0x55); 
		LCD_WR_REG(0xB1);   
		LCD_WR_DATA(0x00);   
		LCD_WR_DATA(0x1A); 
		LCD_WR_REG(0xB6);    // Display Function Control 
		LCD_WR_DATA(0x0A); 
		LCD_WR_DATA(0xA2); 
		LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
		LCD_WR_DATA(0x00); 
		LCD_WR_REG(0x26);    //Gamma curve selected 
		LCD_WR_DATA(0x01); 
		LCD_WR_REG(0xE0);    //Set Gamma 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x2A); 
		LCD_WR_DATA(0x28); 
		LCD_WR_DATA(0x08); 
		LCD_WR_DATA(0x0E); 
		LCD_WR_DATA(0x08); 
		LCD_WR_DATA(0x54); 
		LCD_WR_DATA(0XA9); 
		LCD_WR_DATA(0x43); 
		LCD_WR_DATA(0x0A); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x00); 		 
		LCD_WR_REG(0XE1);    //Set Gamma 
		LCD_WR_DATA(0x00); 
		LCD_WR_DATA(0x15); 
		LCD_WR_DATA(0x17); 
		LCD_WR_DATA(0x07); 
		LCD_WR_DATA(0x11); 
		LCD_WR_DATA(0x06); 
		LCD_WR_DATA(0x2B); 
		LCD_WR_DATA(0x56); 
		LCD_WR_DATA(0x3C); 
		LCD_WR_DATA(0x05); 
		LCD_WR_DATA(0x10); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_DATA(0x3F); 
		LCD_WR_DATA(0x3F); 
		LCD_WR_DATA(0x0F); 
		LCD_WR_REG(0x2B); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x3f);
		LCD_WR_REG(0x2A); 
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0x00);
		LCD_WR_DATA(0xef);	 
		LCD_WR_REG(0x11); //Exit Sleep
		delay_ms(120);
		LCD_WR_REG(0x29); //display on	
}
void LCD_DisplayDir(u8 dir)
{
	if(dir ==0)
	{
		dir =0;
		lcddev .LCD_Wide =240;
		lcddev .LCD_High=320;
		LCD_WR_REG(0x2A);//x坐标设置
		LCD_WR_DATA (0x00);
		LCD_WR_DATA (0x00);//SC坐标
		LCD_WR_DATA((lcddev .LCD_Wide-1)>>8);//EC坐标
		LCD_WR_DATA((lcddev .LCD_Wide-1)&0x00FF);
		
		LCD_WR_REG(0x2B);//y坐标设置
		LCD_WR_DATA (0x00);
		LCD_WR_DATA (0x00);//SP坐标
		LCD_WR_DATA((lcddev .LCD_High-1)>>8);//EP坐标
		LCD_WR_DATA((lcddev .LCD_High-1)&0x00FF);
		
		LCD_WR_REG(0x2C);
		LCD_WR_DATA (0x0000);//RGB颜色设置
	}
	else {
	  lcddev .LCD_Wide =320;
		lcddev .LCD_High=240;
		LCD_WR_REG(0x2A);//x坐标设置
		LCD_WR_DATA (0x00);
		LCD_WR_DATA (0x00);//SC坐标
		LCD_WR_DATA((lcddev .LCD_Wide-1)>>8);//EC坐标
		LCD_WR_DATA((lcddev .LCD_Wide-1)&0x00FF);
		
		LCD_WR_REG(0x2B);//y坐标设置
		LCD_WR_DATA (0x00);
		LCD_WR_DATA (0x00);//SP坐标
		LCD_WR_DATA((lcddev .LCD_High-1)>>8);//EP坐标
		LCD_WR_DATA((lcddev .LCD_High-1)&0x00FF);
		
		LCD_WR_REG(0x2C);
		LCD_WR_DATA (0x0000);//RGB颜色设置
	}
}

void LCD_Init(void)
{
	 LED_Init();
	 FSMC_Init ();
	
	 FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//地址建立时间(ADDSET)清零 	 
	 FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//数据保存时间清零
	 FSMC_Bank1E->BWTR[6]|=3<<0;		//地址建立时间(ADDSET)为3个HCLK =18ns  	 
	 FSMC_Bank1E->BWTR[6]|=2<<8; 	//数据保存时间(DATAST)为6ns*3个HCLK=18ns
	 LCD_Order();
	//LCD_SSD_BackLightSet(100);
	 LCD_DisplayDir(0);LCD_LED=1;
}

void LCD_Color(u16 color)
{ u16 n,k;
	LCD_DisplayDir(0);
	LCD->LCD_REG=0x36;
	LCD->LCD_RAM=0x08;
	LCD->LCD_REG =0x2C;
	for(n=0;n<=lcddev .LCD_High ;n++)
	{
		for(k=0;k<=lcddev .LCD_Wide;k++)
		LCD->LCD_RAM =color;
	}
}
/******************************************************************************/



//快速画点
//x,y:坐标
//color:颜色
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{
    LCD_WR_REG(0x2A); 
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF);  			 
		LCD_WR_REG(0x2B); 
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 	
    
	 LCD->LCD_REG=0x2C; 
	 LCD->LCD_RAM=color; 


}


//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
  u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
  lcddev .LCD_Wide =240;
	lcddev .LCD_High=320;	
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>= lcddev .LCD_Wide)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev .LCD_High)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 



//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);	 
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 

//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;    
	while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
  {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
  }  
}
