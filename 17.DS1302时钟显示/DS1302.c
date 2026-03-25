/*
DS1302是单片机外部时钟芯片,拥有计时器的基本功能
在使用的时候只需要给他设置好时分秒年月日啥的
以及十进制到BCD的转译啥的就能够用了
千万不要在引入单片机内部时钟,不然会屏闪
(别问我怎么知道的qwq)
*/






#include <REGX52.H>

sbit DS1302_SCLK = P3^6;// DS1302时钟引脚,通信的节拍器
sbit DS1302_IO   = P3^4;// 双向通信引脚,用来传输数据,与计时器通信的引脚
sbit DS1302_CE   = P3^5;// DS1302的使能开关,置1开启,置0关闭
 
#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR   0x84
#define DS1302_DATE   0x86
#define DS1302_MONTH  0x88
#define DS1302_DAY    0x8A
#define DS1302_YEAR   0x8C
#define DS1302_WP     0x8E

unsigned char i;
unsigned char DS1302_Time[] = {26,3,25,19,10,55,2};
//这里以十进制显示的日期时间信息,要存进单片机里必须
//以BCD码的形式写给单片机,为什么用BCD码?因为DS1302的
//设计可以理解它都是四个寄存器为一组表示0~9的十个数字
//使用BCD码正好能够用高四位、低四位,来存储0~9的信息



//初始化DS1302,打开开关使能DS1302
void DS1302_Init(void)
{
    DS1302_CE = 0;     //总开关关闭
    DS1302_SCLK = 0;   //时钟脉冲关闭
}



//单片机的读写操作都要通过下面的WriteByte,ReadByte函数来进行读写
//都需要先根据顺序,先来的是寻址,后来的是数据来进行读写操作
//读写需要有上升沿,都是从八位寄存器的最低位开始往高位进行寻址,即从0~7

//在Data里进行的|=操作你有没有觉得很奇怪?如果或等于是开关的话,从最低位
//打开到最高位的开关,但是或等于的特性是只改变选中的位置,而不改变其他的位置
//那么前面打开的开关怎么办?
//答:在Data里进行的操作实际上不是打开开关,而是写入数据
//单片机只能够逐位读取信息,所以在Data里要把二进制的信息拆分成8个部分逐一写入
//而或等于正是保证从低位到高位写入的数据不会被修改,能够正常的向后写入
//同理Command进行的&=操作也是逐一写入八位二进制数据,来规定我要往哪个寄存器写入数据

//电脑向单片机写入,先对目标寄存器,后写入数据
void DS1302_WriteByte(unsigned char Command,unsigned char Data)
{
    DS1302_CE = 1;//使用前启动,表示开始和芯片通信
    
    for(i = 0;i < 8;i ++)
    {
      DS1302_IO = Command&(0x01<<i);//保留第i位,其余强制置0
                                    //通过&符号表示只操作这一位
      DS1302_SCLK = 1;//脉冲时钟打开,上升沿寻址
      DS1302_SCLK = 0;//脉冲时钟关闭,下降沿完成寻址
    }   
    
     for(i = 0;i < 8;i ++)
    {
      DS1302_IO = Data&(0x01<<i);//保留第i位,其余置0
      DS1302_SCLK = 1;//脉冲打开,上升沿写入
      DS1302_SCLK = 0;//脉冲关闭,完成数据输入
    }   
    
     DS1302_CE = 0;//使用后关闭,通信结束
}





//单片机读取已经被写入进来的数据
unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i,Data = 0x00;
	Command |= 0x01;//将读位置1,进入读模式
    DS1302_CE = 1;  //打开DS1302开关
    
    //根据DS1302数据手册可知,在读模式下的寻址是用下降沿来激活的
    for(i = 0;i < 8;i ++)
    {
      DS1302_IO = Command&(0x01<<i);
      DS1302_SCLK = 0;//下降沿选定寄存器
      DS1302_SCLK = 1;//上升沿关闭寻址
    }   
    
    for(i = 0;i < 8;i ++)
    {
        DS1302_SCLK = 1;//上升沿读取寄存器中的数据
        DS1302_SCLK = 0;//下降沿完成读取操作  
        if(DS1302_IO){Data |= (0x01<<i);}
    }
   
	DS1302_CE = 0;//关闭DS1302开关
    DS1302_IO = 0;
	return Data;//返回真正需要表示的十进制日期、时间数字
}







//DS1302设置时间,写入单片机
void DS1302_SetTime(void)
{
    //十进制转换为BCD码
	DS1302_WriteByte(DS1302_WP,0x00);//关闭写入保护
    
    //下面是要存入的信息,先指定要存入的是什么位,然后再写入数据
	DS1302_WriteByte(DS1302_YEAR,  DS1302_Time[0]/10*16 + DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH, DS1302_Time[1]/10*16 + DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,  DS1302_Time[2]/10*16 + DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,  DS1302_Time[3]/10*16 + DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16 + DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16 + DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,   DS1302_Time[6]/10*16 + DS1302_Time[6]%10);
    
	DS1302_WriteByte(DS1302_WP,0x80);//打开写入保护
}



//单片机自身读取已经写入的时间
void DS1302_ReadTime(void)
{
	unsigned char temp;
	
    //将原本转换成单片机能够读取的BCD码的十进制数,转换成真正需要显示的正确十进制数
	temp = DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0] = temp/16*10 + temp%16;
	temp = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = temp/16*10 + temp%16;
	temp = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = temp/16*10 + temp%16;
	temp = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = temp/16*10 + temp%16;
	temp = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = temp/16*10 + temp%16;
	temp = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = temp/16*10 + temp%16;
	temp = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = temp/16*10 + temp%16;
}


/*
DS1302写入数据小原理
上升沿下降沿,把上升沿想象成开门,下降沿想象成关门
有人敲门那么寄存器就会开门接客,关门了那么就会准备迎接下一个客人

关于DS1302怎么区分Command和Data两种数据:
Command:表示我现在指定某一位,准备往这一位写入数据
Data:表示我要往这一位写入的数据
这两个都是人起的名字,实际上单片机并不认识Command和Data
单片机是靠进来的数据的先后顺序来判断哪一个是寻址指令,哪一个是数据
单片机强制规定:先进来的一定是寻址指令,后进来的一定是数据

Command操作的实际上是《DS1302中文手册》第八页表三的寄存器
操作的是年月日时分秒星期这些东西,来通过寻址指定我要往哪个位写入数据
*/