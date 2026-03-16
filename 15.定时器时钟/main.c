#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"

unsigned char Sec,Min,Hour;
static unsigned int T0Count = 0;

//定时器中断跳转函数
void Timer0_Routine()interrupt 1
{
    TH0 = 64615 / 256;
    TL0 = 64615 % 256;
    TF0 = 0;
    T0Count ++;   
    if(T0Count >= 1000)//规定1000ms
    {
        T0Count = 0;//就是这个B地方我调了一天了才发现时间飞转的原因原来是我没有清零😡
        Sec++;
        if(Sec >= 60) {Sec = 0;Min ++;}
        if(Min >= 60) {Min = 0;Hour ++;}
        if(Hour >= 24){Hour = 0;}
        
    }
}




void main()
{
    LCD_Init();
    Timer0_Init();
    
    
    LCD_ShowString(1,1,"Clock:");//起始行//起始列//显示字符串//
    LCD_ShowString(2,3,":");//起始行//起始列//显示字符串//
    LCD_ShowString(2,6,":");//起始行//起始列//显示字符串//
 
    while(1)
    {
        LCD_ShowNum(2,1,Hour,2);//起始行//起始列//显示数字//
        LCD_ShowNum(2,4,Min,2);//起始行//起始列//显示数字//
        LCD_ShowNum(2,7,Sec,2);//起始行//起始列//显示数字//
        
        
    }
    
    
    
}