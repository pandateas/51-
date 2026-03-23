#include <REGX52.H>
#include <INTRINS.H>

//定义引脚,51单片机蜂鸣器在引脚P2^5上,可以看板子上面标记了
sbit Buzzer = P2^5;




//设置延时函数,延时五百微秒
void Buzzer_Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;
	_nop_();
	i = 227;
	while (--i);
}



//外用接口函数,设置多少ms的报警时间
void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i = 0;i < ms;i ++)//2000hz
	{
		Buzzer_Delay500us();
		Buzzer = !Buzzer;
	}
}