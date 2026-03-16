//在lED矩阵里面0是低电平，1是高电平
#include <regx52.h>
#include "Delay.h"

//这三位io口是可以给led矩阵的，一下是使用sbit将这三位io口重命名的操作

sbit SER = P3^4;//输入 SER //将二进制的八位代码每一次赋一个值给SER
sbit SCK = P3^6;//位移 SCK //当SCK有了一个上升沿=1 -> =0后将SER中的数送到八位寄存器中
sbit RCK = P3^5;//打包 RCK //当RCK存满了八位，给RCK一个上升沿，就可以将八位一次性输出

void _595_writeByte(unsigned int Byte)//输出二进制数据到LED矩阵引脚(形参为十六进制)
{
	int i = 0;
	for(i = 0;i < 8;i ++)
	{
		SER = Byte & (0x80>>i);//这个移位的操作是十六进制的移位一个十进制的数
		                       //这里i=0时0x80是第一位，当i=1时，变成了0x40即第二位
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;//给一个上升沿，将八位数据一次性输出到引脚
	
}

void LED_show(unsigned char col,unsigned char DATA)//形参为（十进制，十六进制）
{
	_595_writeByte(DATA);
	P0 = ~(0x80 >> col);//P0可以理解成是只用来管理LED矩阵的I/O口
	Delay(1);
	P0 = 0xFF;//清零
	
	
}

void main()
{
	SCK = 0;
	RCK = 0;//初始化变成低电平
	
}


/*
0000 0 0001 1 0010 2 0011 3

0100 4 0101 5 0110 6 0111 7

1000 8 1001 9 1010 a 1011 b

1100 c 1101 d 1110 e 1111 f
*/


