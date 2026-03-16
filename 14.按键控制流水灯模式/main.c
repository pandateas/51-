#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "Delay.h"
#include <INTRINS.H>//一个函数库,其中包含非常多的功能

unsigned int KeyNum,LEDMode;
//单片机的晶振频率是1s的脉冲次数
//16位计数是记2的16次方个记录,每12hz(脉冲)是一个机器周期-00-
//一个机器周期使得计数加1,记满2的16次方触发中断


//TMOD一般用的多的都是16位计时(主流,记录的时间长)
//TF0---中断溢出标志位







//函数尾部带有interrupt+数字的是定时器中断函数
//后面的数字代表着中断源是什么
//当中断源发生中断后,会无条件跳转到中断函数
//并执行完这里面的程序在返回原来跳转的位置
/*中断号 + 中断源标识符
*interrupt 0 → 外部中断 0
*interrupt 1 → 定时器 0 中断（当前选取的定时器）
*interrupt 2 → 外部中断 1
*interrupt 3 → 定时器 1 中断
*interrupt 4 → 串口中断
*/



//定时器中断跳转函数
void Timer0_Routine()interrupt 1
{
    //static可以要该值在结束后保留不会消失
    //将数据放在静态存储区
    static unsigned int T0Count = 0;
    
    TH0 = 64635 / 256;
    TL0 = 64535 % 256;
    TF0 = 0;
    T0Count ++;
    //当1ms的中断触发后执行中断函数内指令
    //要讲定时器高低8位重置,并且计数器 TCount + 1
    
    if(T0Count >= 500)//规定500ms
    {
        //P2_0 = ~P2_0;
        T0Count = 0;     
        if(LEDMode == 0)
            P2 = _crol_(P2,1);
        if(LEDMode == 1)
            P2 = _cror_(P2,1);
    }
}









void main()
{
    P2 = 0xFE;//1111 1110 //0是亮灯低电平
   
    Timer0_Init();
	while(1)
	{
        KeyNum = Key(); //Key返回按下的按键标号
        if(KeyNum)
        {
            if(KeyNum == 1)
            {
                LEDMode ++;
                
               if(LEDMode >= 2)
                   LEDMode = 0;  
           }           
        }
	}
	
	
	
	
	
}