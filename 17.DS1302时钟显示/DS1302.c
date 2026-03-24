#include <REGX52.H>

sbit DS1302_SCLK = P3^6;//串行时钟引脚,通信的节拍器
sbit DS1302_IO = P3^4;//双向通信引脚,用来传输数据
sbit DS1302_CE = P3^5;//DS1302的开关,置1打开,置0关闭

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
//这里存下以十进制显示的日期时间信息,要存在单片机里必须要
//以BCD码的形式写给单片机,为什么用BCD码,因为看DS1302的
//构造可以发现它都是四个寄存器为一组表示0~9的十个数字
//使用BCD码正好能够用上四个寄存器,来存储0~9的信息



//初始化DS1302,打开开关启用DS1302
void DS1302_Init(void)
{
    DS1302_CE = 0;     //总开关
    DS1302_SCLK = 0;   //时钟脉冲开关
}
   


//单片机的读写操作都要通过下面的WriteByte,ReadByte函数来进行读写
//都需要先根据顺序,先来的时选位,后来的是数据来进行读写操作
//读写需要有上升沿,都是从八位寄存器的最低位开始往高位进行选位,即从0~7

//问:在Data上进行的|=操作你有没有感觉很奇怪,如果或等于是开关的话,从最低位
//打开到最高位的开关,但是或等于的特性是只改变选中的位置,而不改变其他的位置
//那么前面打开的开关怎么办呢?
//答:在Data上进行的操作实际上不是打开开关,而是写入数据
//单片机只能够逐字的读取信息,所以在Data上要将二进制的信息拆分成8个部分逐一录入
//而或等于正式保证从低位到高位写入的数据不会被更改,能够正常的向后写入
//同理Command进行的|=操作也是逐一写入八位二进制数据,来规定我要往那个寄存器写入数据

//电脑向单片机写入,先对准寄存器,后写入数据
void DS1302_WriteByte(unsigned char Command,Data)
{
    
    DS1302_CE = 1;//使用前启动,表示开始和芯片通信
    
    for(i = 0;i < 8;i ++)
    {
      DS1302_IO = Command&(0x01<<i);//保留第0位,其余强制置位0
                                    //通过&符号表示只操作这一位
      DS1302_SCLK = 1;//脉冲时钟打开,上升沿选位
      DS1302_SCLK = 0;//脉冲时钟关闭,下降沿完成选位
        
    }   
    
     for(i = 0;i < 8;i ++)
    {
      DS1302_IO = Data&(0x01<<i);//保留第0位,其余其余置为0
                                //向上一个确定了的寄存器发送数据
      DS1302_SCLK = 1;//脉冲打开,上升沿写入
      DS1302_SCLK = 0;//脉冲关闭,完成数据输入
    }   
    
     DS1302_CE = 0;//使用后关闭,通信结束
    
}





//单片机读取已经被写入进来的数据
unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i,Data = 0x00;
	Command |= 0x01;//把二进制在1的这一位寄存器启用
    DS1302_CE = 1;  //打开DS1302开关
    
    
    //根据DS1302数据手册可以知道,在读模式下的选位是用下降沿来激活的
    for(i = 0;i < 8;i ++)
    {
      DS1302_IO = Command&(0x01<<i);
      DS1302_SCLK = 0;//下降沿选定寄存器
      DS1302_SCLK = 1;//上升沿关闭选位
      
    }   
    
    
    for(i = 0;i < 8;i ++)
    {
        DS1302_SCLK = 1;//上升沿读取寄存器中的数据
        DS1302_SCLK = 0;//下降沿完成读取操作   
        if(DS1302_IO){Data = Data |= (0x01<<i);}
    }
   
	DS1302_CE = 0;//关闭DS1302开关
	return Data;//返回真正需要表达的十进制日期/时间数
    
    
    
}










//DS1302设置时间,写给单片机
void DS1302_SetTime(void)
{
    //十进制转换为
	DS1302_WriteByte(DS1302_WP,0x00);//关闭写入保护
    
    //下面是要存入的信息,先锁定要存入的是什么位,然后在写入数据
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0] / 10 * 16 + DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1] / 10 * 16 + DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2] / 10 * 16 + DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3] / 10 * 16 + DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4] / 10 * 16 + DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5] / 10 * 16 + DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6] / 10 * 16 + DS1302_Time[6]%10);
    /*
    十进制转换成BCD码原理:
    我们拿一个具体数字举例，比如年份是 25（十进制）：
    25 / 10 = 2 → 取出十位
    2 * 16 = 32 → 把十位放到高 4 位（十六进制的 0x20）
    25 % 10 = 5 → 取出个位
    32 + 5 = 37 → 合并成 BCD 码 0x25
    这里可以注意到我们算出来的结果是37,所以你是不是疑惑为什么不是BCD码?
    其实单片机的眼中只有二进制的数据,只不过我们看到的是10进制
    我们将十进制的年份转换成十进制的37,但是本质上从2进制的角度来说已经发生了变化
    这里的37在单片机的眼中是2进制的数字,但是单片机会以BCD码的编码方式来读取里面的数据
    所以外表上我们从十进制转换成了十进制,看起来我们在瞎搞,实际上转换成了单片机能够
    以BCD码方式读取的2进制代码
    这破地方绕死我了(豆包神力😭👍)
    */
    
	DS1302_WriteByte(DS1302_WP,0x80);//打开写入保护
}
  


//单片机自身读取已经写入的时间
void DS1302_ReadTime(void)
{
	unsigned char temp;
	
    //将原先转换成了单片机能够读取的BCD码的十进制数转换成真正需要显示的正确的十进制数    
	temp = DS1302_ReadByte(DS1302_YEAR);
	temp = DS1302_Time[0]=temp / 16 * 10 + temp % 16;
	temp = DS1302_ReadByte(DS1302_MONTH);
	temp = DS1302_Time[1]=temp / 16 * 10 + temp % 16;
	temp = DS1302_ReadByte(DS1302_DATE);
	temp = DS1302_Time[2]=temp / 16 * 10 + temp % 16;
	temp = DS1302_ReadByte(DS1302_HOUR);
	temp = DS1302_Time[3]=temp / 16 * 10 + temp % 16;
	temp = DS1302_ReadByte(DS1302_MINUTE);
	temp = DS1302_Time[4]=temp / 16 * 10 + temp % 16;
	temp = DS1302_ReadByte(DS1302_SECOND);
	temp = DS1302_Time[5]=temp / 16 * 10 + temp % 16;
	temp = DS1302_ReadByte(DS1302_DAY);
	temp = DS1302_Time[6]=temp / 16 * 10 + temp % 16;
	
	
}


/*
DS1302写入数据小芝士:
上升沿河下降沿:将上升沿想象成敲门,下降沿想象成关门
有人敲门那么寄存器就会开门接客,关门了那就会准备迎接下一个客人

关于DS1302怎么分辨Command和Data两种数据:
Command:表示我现在指定某一位,准备往这一位写入数据
Data:表示我要往这一位写入的数据
这两个都是人为起的名字,实际上单片机并不认识Command和Data
单片机是靠进来的数据的先后顺序来判断哪一个是选位指令,哪一个是数据
单片机强制规定,先进来的一定是选位指令,后进来的一定是数据

Command操作的实际上是<<DS1302中文手册>>第八页表三的寄存器,操作的是
年月日时分秒星期这些东西,来通过选位指定我要往那个位写入数据

*/

























