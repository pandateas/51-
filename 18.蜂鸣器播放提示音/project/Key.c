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


//返回值类型:unsigned char
unsigned char Key()
{
    unsigned char KeyNumber = 0;
    
    
	//P3_0 ~ 3是独立按键,和LED一样,0的时候是上电/按下
    if(P3_1 == 0){Delay(20);while(P3_1==0);Delay(20);KeyNumber=1;} 
    if(P3_0 == 0){Delay(20);while(P3_0==0);Delay(20);KeyNumber=2;}
    if(P3_2 == 0){Delay(20);while(P3_2==0);Delay(20);KeyNumber=3;}
    if(P3_3 == 0){Delay(20);while(P3_3==0);Delay(20);KeyNumber=4;}
    
    return KeyNumber;
    
    
}