#ifndef __LCD1602_H__
#define __LCD1602_H__



//用户可调用函数：
void LCD_Init();//初始化LCD屏幕,进行清屏操作

void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);//显示字符

void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);//显示字符串

void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);//显示数字

void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);//显示有符号十进制字符串

void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);//展示16进制数字

void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);//展示2进制数字

#endif
