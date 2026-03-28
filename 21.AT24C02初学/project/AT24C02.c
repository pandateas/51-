/*
向AT24C02进行什么操作(读/写)
*/




#include <REGX52.H>
#include "I2C.h"
#define AT24C02_ADDRESS 0xA0//地址


/*
* @brief AT24C02写入一个字节
* @param WordAddress要写入字节的地址
* @param Data要写入的数据
* @retval 无
*/
 void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data)
{
   
    I2C_Start();                        //向整个I2C上的从机声明我要开始数据传输了
    I2C_SendByte(AT24C02_ADDRESS);      //点名要这个地址(AT24C02ROM 0xA0)上的从机
    I2C_ReceiveAck();                   //从机喊 "到!"
    I2C_SendByte(WordAddress);          //告诉从机我要在他的哪个寄存器(WordAddress)里面写东西
    I2C_ReceiveAck();                   //从机喊 "收到!"
    I2C_SendByte(Data);                 //主机传输数据Data
    I2C_ReceiveAck();                   //传输完成一个字节后,从机返回是否全部收到
    I2C_Stop();                         //数据传输完成,SCL和SDA全部置1,初始化成原本的状态
    
    
}



/*
* @brief  AT24C02读取一个字节
* @param  WordAddress要读出字节的地址
* @retval 要写入的数据
*/
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
    /*
    <<关于为什么要进行两次读写操作而不是多此一举这件事>>
    在I2C上,每一次通信的进行都是单向的,所以既然我想要读取
    在ROM中的数据,那么我单片机肯定要向外声明,而这一次向外声明
    不是读操作而是写操作.单片机不能够在一次通信中进行读写两种操作
    所以就必须有两次Start,第一次向外界声明我要操作这个ROM,但是不要
    Stop结束,否则相当于两次通信没有链接到一起,随后在进行第二次Start
    第二次Start就可以直接进行写操作,因为我在第一次已经声明了我要操作
    这个寄存器,中间没有Stop中断操作,那我就还是操作这一个寄存器
    
    
    */
    
    
    
    
    unsigned char Data;
    
    I2C_Start();                            //开始数据传输
    I2C_SendByte(AT24C02_ADDRESS);          //声明从机是谁
    I2C_ReceiveAck();                       //从机应答
    I2C_SendByte(WordAddress);              //声明我要操作的寄存器是哪一个
    I2C_ReceiveAck();                       //从机应答
    
    
    I2C_Start();                            //切换读模式     
    I2C_SendByte(AT24C02_ADDRESS|0x01);     //声明我要操作的从机地址,并通过"或"运算声明我是要读操作
    I2C_ReceiveAck();                       //从机返回应答
    Data = I2C_ReceiveByte();               //接收8位数据并返回给外部,此时我要访问的寄存器地址在第一次Start中已经声明是WordAddress了
    I2C_SendAck(1);                         //接收完成,从机应答
    I2C_Stop();                             //结束通信
    
    return Data;                            //返回读取出来的数据给外部调用的函数或变量
}
