#ifndef __DS1302_H__
#define __DS1302_H__


//声明外部的数组,变量,函数,要加上extern
extern unsigned char DS1302_Time[] = {26,3,25,6,59,50};



void DS1302_Init(void);//初始化DS1302
void DS1302_SetTime(void);
void DS1302_WriteByte(unsigned char Command,Data);//写入数据
unsigned char DS1302_ReadByte(unsigned char Command);//读取数据
void DS1302_ReadTime(void);


#endif