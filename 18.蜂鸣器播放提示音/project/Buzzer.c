#include <REGX52.H>
#include <INTRINS.H>

//蜂鸣器端口:
sbit Buzzer = P2^5;




//蜂鸣器发声
//ms发声时长
void Buzzer_Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}



void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i = 0;i < ms*2;i ++)//2000hz
	{
		Buzzer_Delay500us();
		Buzzer = !Buzzer;
	}
}