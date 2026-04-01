//当按下独立按键后,能够实现记录当前按下的独立按键标号
//并将标号转递给KeyNumber并且返回标号
//方便在main函数中再次使用




#include <REGX52.H>
#include "Delay.h"


/*
* @brief    获取独立按键的密码
* @param    无
* @retval   按下按键的键码,范围0~4,无按键时返回0
*/
unsigned char Key_KeyNumber;



//按下按键返回独立按键标号,但是没有添加防抖和松开按键开始计时功能
unsigned char Key(void)
{
    unsigned char Temp = 0;
    Temp = Key_KeyNumber;
    Key_KeyNumber = 0;
    return Temp;
    
    
}


//返回当前按下的按键标号
unsigned char Key_GateState()
{
    unsigned char KeyNumber = 0;
    
    
    //P3_0 ~ 3是独立按键
    if(P3_1 == 0){KeyNumber=1;} 
    if(P3_0 == 0){KeyNumber=2;}
    if(P3_2 == 0){KeyNumber=3;}
    if(P3_3 == 0){KeyNumber=4;}
    
    return KeyNumber;
}


//这个函数的作用是在松开按键后保留按下按键的标号,以供其他函数使用
void Key_Loop(void)
{
    
    //LastState表示上一个状态,NowState表示现在的状态
    //当上一个状态非0且现在的状态为0则是松开按键,根据
    //这一个松开按键的变化返回操控的按键是什么
    
    static unsigned char NowState,LastState;
    LastState = NowState;
    NowState = Key_GateState();
    
    
    //捕获按下按键时的电平跳变,并在松手时发送按下的按键位号
    if(LastState==1 && NowState ==0)
       {
           Key_KeyNumber = 1;
       }
    if(LastState==2 && NowState ==0)
       {
           Key_KeyNumber = 2;
       }
    if(LastState==3 && NowState ==0)
       {
           Key_KeyNumber = 3;
       }
    if(LastState==4 && NowState ==0)
       {
           Key_KeyNumber = 4;
       }
    
 }













