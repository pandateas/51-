/*
驱动电机要给高电平,点亮LED要给低电平,两者极性相反
*/


#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"
#include "Key.h"
#include "nixie.h"

sbit LED = P2^0;
sbit Motor = P1^0;

//Compare表示100刻度的阈值,Compare以下低电平
//以上高电平,LED低电平亮,程序不断发出0 -> 100脉冲
unsigned char Counter,Compare,KeyNum;
unsigned char Speed;
void main()
{
    
    
    
    Timer0_Init();
    
    //设置通电时,电机不会转
    Speed = 0;
    if(Speed == 0){Compare = 100;}
    if(Speed == 1){Compare = 50;}
    if(Speed == 2){Compare = 25;}
    if(Speed == 3){Compare = 0;}
    
    while(1)
    {
        KeyNum = Key();
        
        if(KeyNum == 1)
        {
            Speed ++;
            Speed %= 4;
            
            if(Speed == 0){Compare = 100;}
            if(Speed == 1){Compare = 50;}
            if(Speed == 2){Compare = 25;}
            if(Speed == 3){Compare = 0;}
         }
        nixie(1,Speed);         //调速后显示速度档位
    } 
    
}

void Timer0_Routine() interrupt 1
{
    TL0 = 0xA4;          //重置定时器
    TH0 = 0xFF;
    Counter++;
    Counter%=100;       //脉冲计数器,从0 -> 100
    
    if(Counter < Compare)
    {
        Motor = 0;      //低电平不转
     }
    else
    {
        Motor = 1;      //高电平转
    }
}