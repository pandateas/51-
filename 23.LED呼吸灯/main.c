/*
直流电机没有正负极,但是输入电流的方向不同会导致电机旋转的方向不同
*/

#include <REGX52.H>
sbit LED = P2^0;

void Delay(unsigned char i)
{
    while(i --);
    
    
}


   
    

void main()
{  
//    int p;
//    int flag;//p亮,共计100,放到Delay函数中
//    p = 100;
//    flag = 0;//1 表示递减,0表示递增
    
    
    
    
    unsigned char Time,i;
    
    
    
    
    
    
      
    while(1)
    {
        
        //缓慢变暗
        for(Time = 0;Time < 100;Time ++)
        {
            for(i = 0;i < 20;i ++)
            {
                LED = 0;
                Delay(Time);
                LED = 1;
                Delay(100 - Time);
            }
        }
        
        //缓慢变亮
        for(Time = 100;Time > 0;Time --)
        {
            for(i = 0;i < 20;i ++)
            {
                LED = 0;
                Delay(Time);
                LED = 1;
                Delay(100 - Time);
            }
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
//        if(flag == 0)
//        {
//            LED = 0;
//            Delay(p);
//            
//            LED = 1;
//            Delay(100 - p);
//            
//            p -= 1;
//            if(p == 45) {flag = 1;}
//         }
//        
//        if(flag == 1)
//        {
//            LED = 0;
//            Delay(p);
//            
//            LED = 1;
//            Delay(100 - p);
//            
//            p += 1;
//            if(p == 105) {flag = 0;}
//        }
        
    }
    
    
}