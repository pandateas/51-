#include <REGX52.H>
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"
#include "Delay.h"

unsigned char Data;
unsigned char KeyNum;
unsigned int Num;




void main()
{
    LCD_Init();                 //初始化LCD屏幕
    LCD_ShowString(1,1,"hello");//测试LCD屏幕是否正确显示
    
/*测试AT24C02功能是否正常
    AT24C02_WriteByte(1,128);
    Delay(5);
    Data = AT24C02_ReadByte(1);
    LCD_ShowNum(2,1,Data,3);
*/    
    
   
    while(1)                //通过按键来选择和存储数据
    {
        KeyNum = Key();
        if(KeyNum == 1) 
           {
               Num ++;
               LCD_ShowNum(1,1,Num,5);
           }
        if(KeyNum == 2) 
           {
               Num --;
               LCD_ShowNum(1,1,Num,5);
               Delay(5);
           }
         if(KeyNum == 3) 
           {
               AT24C02_WriteByte(0,Num%256);//取低八位
               Delay(5);
               AT24C02_WriteByte(1,Num/256);//取高八位
               Delay(5);
               LCD_ShowString(2,1,"Write OK");
               Delay(1000);
               LCD_ShowString(2,1,"        ");
           }
         if(KeyNum == 4) 
           {
               Num = AT24C02_ReadByte(0);
               Num |= AT24C02_ReadByte(1)<<8;//拼接在0寄存器取出来的数后面
               LCD_ShowNum(1,1,Num,5);
               LCD_ShowString(2,1,"Read OK");
               Delay(1000);
               LCD_ShowString(2,1,"       ");
           }
    }
    
}