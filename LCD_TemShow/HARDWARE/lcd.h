#ifndef __LCD_H
#define __LCD_H
#include "sys.h"

//����LCD�����ṹ��
typedef struct 
{
  vu16 LCD_REG;//д����
  vu16 LCD_RAM;//д����
} LCD_TypeDef;
#define LCD_BASE ((u32)(0x6C000000|0x00001FFE))
#define LCD      ((LCD_TypeDef *)LCD_BASE)

//����LCD��ز���
typedef struct 
{
	u16 LCD_High; 
	u16 LCD_Wide;
	u16 id;
	u8 dir; //1Ϊ������0Ϊ����
	u16 wramcmd; //��ʼд�Դ�gramָ��
	u16 setxcmd;
	u16 setycmd;
	
} _lcd_dev;
extern _lcd_dev lcddev;

#define	LCD_LED PFout(10)  		//LCD����    		 PF10


void LCD_WR_REG(vu16 cmd);  //д����
void LCD_WR_DATA(vu16 data);//д����
u16 LCD_RD_DATA(void ); //������
void LED_Init(void );  //LED��ʼ��
void FSMC_Init(void);  //FSMC��ʼ��
u16 Read_ID(void );  //��ID
void LCD_Order(void ); //��ʼ������
void LCD_DisplayDir(u8 dir);
void LCD_Init(void);  //��ʼ��LCD
void LCD_Color(u16 color);
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);

void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
#endif
