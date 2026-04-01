//初始化定时器,开始计时
//计时满后跳转到 main 中的 interrupt 1 函数
//随后执行完interrupt 1 的指令后返回继续计时
//执行完一次 Timer0_Init 大约是 1ms

#include <REGX52.H>

void Timer0_Init()//@1ms
{
    //TMOD = 0x01;//0000 0001//当要使用两个定时器时这样写不行
    
    TMOD &= 0xF0;//清零定时器0模式位，不影响定时器2
    TMOD |= 0x01;//设置定时器0为模式1（16位定时器/计数器）
    
    TF0 = 0;//清除定时器0溢出标志
            //Timer OverFlow//溢出标志位，需要手动清零
    
    TR0 = 1;//Timer_Run//定时器启动开关，开启才能使用
    
    // 1ms 定时初值 晶振11.0592MHz 正确值：65536-1000=64536
    TH0 = 64536 / 256;//取出高八位
    TL0 = 64536 % 256;//取出低八位
    //公式:初始时间 / 256
    //     初始时间 % 256
    //TH0和TL0两个相互配合完成计时的过程
    
    ET0 = 1;//Enable Timer0 Interrupt//定时器0中断使能
    //定时器0中断开关，开启后计数满会执行中断                               
    //当ET0 = 0时就算定时器溢出了也不会响应中断
    
    EA = 1;//Enable All Interrupts
    //总开关，允许所有的中断
    
    PT0 = 0;//Priority Timer0
    //设置定时器0的中断优先级默认位 低优先级
}

/*
//定时器0中断服务函数
void Timer0_Routine()interrupt 1
{
    static unsigned int T0Count;
    int Sec = 0,Min = 0,Hour = 0;
    // 重装1ms定时初值
    TH0 = 64536 / 256;
    TL0 = 64536 % 256;
    TF0 = 0;
    T0Count ++;   
    if(T0Count >= 1000)//设定1000ms=1秒
    {
        T0Count = 0;//清零计数器
        Sec++;
        if(Sec >= 60) {Sec = 0;Min ++;}
        if(Min >= 60) {Min = 0;Hour ++;}
        if(Hour >= 24){Hour = 0;}
    }
}
*/