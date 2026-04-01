/*
Loop ---> 循环
Scan ---> 扫描

程序运行顺序
上电 → main ()
main () 初始化定时器
定时器自动跑 → Timer0_Routine ()
定时器驱动 → nixie_Loop ()
nixie_Loop () 驱动 → nixie_Scan ()
main () 循环 → Key_GateState ()
main () 计算时间 → nixie_SetBuf ()
nixie_Scan () 查段码表 → 数码管显示
*/



#include <REGX52.H>
#include "Key.h"
#include "nixie.h"
#include "Timer0.h"
#include "Delay.h"


unsigned char KeyNum;
unsigned char Min,Sec,MinSec;//分别代表分钟,秒钟,和一个在秒钟后面跑的玩意
unsigned char runflag;


void main()
{
    Timer0_Init();                 //初始化定时器
    
    while(1)
    {   
        KeyNum = Key();           //返回按下的独立按键位号
        
        if(KeyNum == 1)
        {
            runflag = !runflag;   //暂停时钟显示
        }
        if(KeyNum == 2)           //重置时钟显示
        {
            Sec = 0;
            Min = 0;
            MinSec = 0;
        }
        
        //下面是设定静态数码管显示的东西,哪一位显示什么数字
        nixie_SetBuf(1,Min/10);
        nixie_SetBuf(2,Min%10);
        nixie_SetBuf(3,11);
        
        nixie_SetBuf(4,Sec/10);
        nixie_SetBuf(5,Sec%10);
        nixie_SetBuf(6,11);
        
        nixie_SetBuf(7,MinSec/10);
        nixie_SetBuf(8,MinSec%10);
    }
}


void Sec_Loop(void)     //时间的循环
{
    if(runflag)         //判断当前是否是时钟模式,是就进入时间判断,否则跳出函数
    {   
        MinSec ++;
        if(MinSec>=100)
        {
            MinSec = 0;
            Sec++;            
            if(Sec>=60)
            {
                Sec = 0;
               Min++; 
            }            
            if(Min >= 60)
            {  
               Min = 0;                
            }             
        }
    }
    
}



void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count1,T0Count2,T0Count3;
    TL0 = 0x18;
    TH0 = 0xFC;
    
    
    //以下的if语句可以看作三个在同时进行,三个Timerx计数器也是同时进行
    
    T0Count1 ++;             //每过1ms加一
    if(T0Count1 >= 10)       //每隔10ms刷新一次,静态数码管的状态
    {
        T0Count1 = 0;
        Key_Loop();         //刷新按键状态,检测是否有按下并且松手的按键并返回
        
    }
    T0Count2 ++;
    if(T0Count2>=2)         //2ms刷新一次静态数码管显示状态
    {
        T0Count2 = 0;
        nixie_Loop();       //刷新数码管显示状态
    }
    T0Count3++;
    if(T0Count3 >= 10)      //每10ms判断当前的按键状态,计时还是暂停
    {
        T0Count3 = 0;
        Sec_Loop();         //判断时间是否溢出,溢出则清零
        
    }
    
    
    
}



