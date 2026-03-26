//初始化定时器,开始计时
//计时满后跳转到 main 中的 interrupt 1 函数
//随后执行完interrupt 1 的指令后在返回接着执行计时
//执行完一次 Timer0_Init 大约是 1ms



#include <REGX52.H>

void Timer0_Init()//@1ms
{
	//TMOD = 0x01;//0000 0001//当要是用两个定时器时这样写不行
    
    TMOD &= 0xF0;//单片机定时器启动模式,默认启动定时器1
                //但是这种写法不是很好,容易影响到定时器2
    TMOD |= 0x01;
     
    
    TF0 = 0;//当计数满了后归1中断计时
            //Timer OverFlow//溢出标志位,需要手动清零
    
    
	TR0 = 1;//Timer_Run//定时器启动开关,开启了才能用
    
    
    TH0 = 64615 / 256;//拿出高八位 //相当于拿出,十百位
    TL0 = 64615  % 256 + 1;//拿出低八位 //相当于拿出个位
	//通式:起始时间 / 256(2的16位)
    //     起始时间 % 256
    //TH0和TL0两个互相打配合,来完成计时的过程
    
    
    ET0 = 1;//Enable Timer0 Interrupt//定时器使能中断器
    //定时器中断开关,开启后计数满会执行中断                               
    //当ET0 = 0时就算定时器溢出了也不会触发中断
    
    
    EA = 1;//Enable All Interrupts
    //总开关,允许所有的中断
    
    PT0 = 0;//Priority Timer0
    //设置定时器0的中断优先级默认为0//低优先级
    
    
    
    
}




/*
//定时器中断跳转函数模板
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

*/