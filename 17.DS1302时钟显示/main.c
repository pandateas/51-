/*
|=0x01 : 把第零位强制变成1,其他的不变
&=0x01 : 只保留第零位,其他的强制变成0
!=0x01 : 只会比较这一位的真假,返回0/1,不改变值
*/

#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"


void main()
{
    LCD_Init();//初始化LCD1602
	DS1302_Init();//初始化DS1302
    DS1302_SetTime();//设置时间
	
	//固定显示格式,一直显示不变
    LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
	
    
    while(1)
    {
		DS1302_ReadTime();
       
        //在定时器中时间以BCD码的方式储存,所以
        //读写之前都需要人工转译
        
        
		LCD_ShowNum(1,1,DS1302_Time[0],2);
		LCD_ShowNum(1,4,DS1302_Time[1],2);
		LCD_ShowNum(1,7,DS1302_Time[2],2);
		LCD_ShowNum(2,1,DS1302_Time[3],2);
		LCD_ShowNum(2,4,DS1302_Time[4],2);
		LCD_ShowNum(2,7,DS1302_Time[5],2);  
       
      
    }
}



/*
BCD码转十进制:DEC = BCD/16*10 + BCD % 16;
十进制转BCD码:BCD = DEC/10*16 + DEC % 10;
*/