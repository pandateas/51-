/*
|=0x01 : 把第零位强制变成1,其他的不变
&=0x01 : 只保留第零位,其他的强制变成0
!=0x01 : 只会比较这一位的真假,返回0/1,不改变值
*/

#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Timer0.h"
#include "Key.h"
#include "Delay.h"

unsigned char KeyNum,MODE = 0,TimeSetSelect,TimeSetFlashFlag;

void TimeShow(void)
{
    DS1302_ReadTime();
        
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);  
}


//按键1:切换时钟模式还是设置模式
//按键2:选择要编辑的位,00-05分别是年月日时分秒
//按键3:对选择的位进行+1操作
//按键4:对选择的位进行-1操作

void TimeSet(void)
{
    
   if(KeyNum == 2)
       {
            TimeSetSelect ++;
           //if(TimeSetSelect > 5) TimeSetSelect = 0;
            TimeSetSelect %= 6;
           //LCD_ShowNum(2,10,TimeSetSelect,2);//测试当前位置是哪一个显示在屏幕上
       }       
       
       //在对所选位进行加减操作的时候还需要进行参数的合法性检查
       //到了某个值需要清零的得清零
       
   if(KeyNum == 3)
       {
           DS1302_Time[TimeSetSelect]++;
           
           if(DS1302_Time[0] > 99){DS1302_Time[0] = 0;}//年
           
           
           if(DS1302_Time[1] > 12){DS1302_Time[1] = 1;}//月
           if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
           {
                if(DS1302_Time[2] > 31){DS1302_Time[2] = 1;}//31天月份 
           }
  
           else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11) //三十天月份                  
               {
                   if(DS1302_Time[2] > 30){DS1302_Time[2] = 1;}
               }                   

           else if(DS1302_Time[1] == 2)
           {
               if(DS1302_Time[0] % 4 == 0)
                   {
                        if(DS1302_Time[2] > 29){DS1302_Time[2] = 1;}
                   
                       
                   }
                   else{
                             if(DS1302_Time[2] > 28){DS1302_Time[2] = 1;}
                       }
           }
                              
           
           
           if(DS1302_Time[3] > 23){DS1302_Time[3] = 0;}//时
           if(DS1302_Time[4] > 59){DS1302_Time[4] = 0;}//分
           if(DS1302_Time[5] > 59){DS1302_Time[5] = 0;}//秒
              
       }         
       
       
       
   if(KeyNum == 4)
       {
           DS1302_Time[TimeSetSelect]--;
           if(DS1302_Time[0] == 255){DS1302_Time[0] = 99;}//年
           if(DS1302_Time[1] < 1){DS1302_Time[1] = 12;}//月
           if(DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 || DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
           {
                if(DS1302_Time[2] < 1){DS1302_Time[2] = 31;}//31天月份           
           }
  
           else if(DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11) //三十天月份                  
               {
                   if(DS1302_Time[2] < 1){DS1302_Time[2] = 30;}
				   if(DS1302_Time[2] > 30){DS1302_Time[2] = 1;}//防止出现日期大于该月份的日期
               }                   

                      
           else if(DS1302_Time[1] == 2)
           {
               if(DS1302_Time[0] % 4 == 0)
                   {
                        if(DS1302_Time[2] < 1){DS1302_Time[2] = 29;}
						if(DS1302_Time[2] > 29){DS1302_Time[2] = 1;}//防止出现日期大于该月份的日期
                   
                       
                   }
                   else{
                             if(DS1302_Time[2] < 1){DS1302_Time[2] = 28;}
							 if(DS1302_Time[2] > 28){DS1302_Time[2] = 1;}//防止出现日期大于月份的总日期
                       }
           }
           
           
           if(DS1302_Time[3] == 255){DS1302_Time[3] = 23;}//时
           if(DS1302_Time[4] == 255){DS1302_Time[4] = 59;}//分
           if(DS1302_Time[5] == 255){DS1302_Time[5] = 59;}//秒
           
           
       }
	   
	   if(TimeSetSelect == 0 && TimeSetFlashFlag == 1){LCD_ShowString(1,1,"  ");}
	   else{LCD_ShowNum(1,1,DS1302_Time[0],2);}
	   if(TimeSetSelect == 1 && TimeSetFlashFlag == 1){LCD_ShowString(1,4,"  ");}
	   else{LCD_ShowNum(1,4,DS1302_Time[1],2);}
	   if(TimeSetSelect == 2 && TimeSetFlashFlag == 1){LCD_ShowString(1,7,"  ");}
	   else{LCD_ShowNum(1,7,DS1302_Time[2],2);}
	   if(TimeSetSelect == 3 && TimeSetFlashFlag == 1){LCD_ShowString(2,1,"  ");}
	   else{LCD_ShowNum(2,1,DS1302_Time[3],2);}
	   if(TimeSetSelect == 4 && TimeSetFlashFlag == 1){LCD_ShowString(2,4,"  ");}
	   else{LCD_ShowNum(2,4,DS1302_Time[4],2);}
	   if(TimeSetSelect == 5 && TimeSetFlashFlag == 1){LCD_ShowString(2,7,"  ");}
	   else{LCD_ShowNum(2,7,DS1302_Time[5],2);}
		
    
    //设置完成之后要进行显示的更新
//    LCD_ShowNum(1,1,DS1302_Time[0],2);
//	LCD_ShowNum(1,4,DS1302_Time[1],2);
//	LCD_ShowNum(1,7,DS1302_Time[2],2);
//	LCD_ShowNum(2,1,DS1302_Time[3],2);
//	LCD_ShowNum(2,4,DS1302_Time[4],2);
//	LCD_ShowNum(2,7,DS1302_Time[5],2);  
	//LCD_ShowNum(2,10,TimeSetSelect,2);//测试选择位置是否功能正确
	//LCD_ShowNum(2,13,TimeSetFlashFlag,2);//测试位置闪烁功能是否正确
    
}


void main()
{
    LCD_Init();//初始化LCD1602
	DS1302_Init();//初始化DS1302
    DS1302_SetTime();//设置时间
	Timer0_Init();
	//固定显示格式,一直显示不变
    LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
	
    
    while(1)
    {
        KeyNum = Key();
        if(KeyNum==1)//交替切换模式
        {       
            if(MODE==0){MODE = 1;}
            else if(MODE==1){MODE = 0;DS1302_SetTime();}
        }
        
        switch(MODE)
        {
            case 0:TimeShow();break;//时钟显示模式
            case 1:TimeSet();break;//时钟设置模式
            
            
        }
        
        
        
        
		
      
    }
}



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
        TimeSetFlashFlag =! TimeSetFlashFlag;
    }
}




/*
BCD码转十进制:DEC = BCD/16*10 + BCD % 16;
十进制转BCD码:BCD = DEC/10*16 + DEC % 10;
*/