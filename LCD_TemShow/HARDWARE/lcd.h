#ifndef __LCD_H
#define __LCD_H
#include "sys.h"

//定义LCD操作结构体
typedef struct 
{
  vu16 LCD_REG;//写命令
  vu16 LCD_RAM;//写数据
} LCD_TypeDef;
#define LCD_BASE ((u32)(0x6C000000|0x00001FFE))
#define LCD      ((LCD_TypeDef *)LCD_BASE)

//定义LCD相关参数
typedef struct 
{
	u16 LCD_High; 
	u16 LCD_Wide;
	u16 id;
	u8 dir; //1为横屏，0为竖屏
	u16 wramcmd; //开始写显存gram指令
	u16 setxcmd;
	u16 setycmd;
	
} _lcd_dev;
extern _lcd_dev lcddev;

#define	LCD_LED PFout(10)  		//LCD背光    		 PF10


void LCD_WR_REG(vu16 cmd);  //写命令
void LCD_WR_DATA(vu16 data);//写数据
u16 LCD_RD_DATA(void ); //读数据
void LED_Init(void );  //LED初始化
void FSMC_Init(void);  //FSMC初始化
u16 Read_ID(void );  //读ID
void LCD_Order(void ); //初始化序列
void LCD_DisplayDir(u8 dir);
void LCD_Init(void);  //初始化LCD
void LCD_Color(u16 color);
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);

void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
#endif
