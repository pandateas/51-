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
    
    
    TH0 = 0xFF;//拿出高八位 //相当于拿出,十百位
    TL0 = 0xA4;//拿出低八位 //相当于拿出个位
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
//定时器中断跳转函数
void Timer0_Routine()interrupt 1
{
    static unsigned int T0Count;
    int Sec = 0,Min = 0,Hour = 0;
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

*/