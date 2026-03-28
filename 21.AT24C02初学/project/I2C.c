/*
从机地址 Slave Address 在I2C总线通信的唯一地址,相当于小区 AT24C02的小区名字叫做 0xA0
寄存器地址 0~255
AT24C02ROM一共拥有256个字节的存储单元,相当于256个门牌号,每个门牌号下能够存下8个人(1111 1111)

I2C总线通信顺序:
起始位Start(圣旨来了)--->发送从机地址(前七位为从机地址)(某某奴才听命)--->设置读写模式(后一位为读写模式)(&0x01/0x00,读1写0)--->
从机应答(返回应答位Ack给主机)(奴才在)--->发送寄存器地址(告诉从机我要在哪里写数据)--->从机应答(返回应答Ack)(奴才听令)--->
发送数据(主机控制高低电平) ---> 从机回复成功接收(Ack应答位) --->终止位Stop(上拉电平结束通信)


在I2C中,SDA传输数据的顺序是从高位到低位传输
读写都是这样,从八位数据的最高位往最低位传

I2C中的数据传输永远都是主机接收/发送数据,从机
永远都是被动的等待主机的呼叫.在主机发送从机的地址
并且从机返回了一个应答位说明主机从机之间建立了通信连接

当SDA=1时,说明现在没有设备调用SDA需要发送数据,
那么就可以由其他的设备来控制SDA传输数据,同一时间
只能有一个设备控制SDA传输数据

发送数据时（主机→从机）
主机控制 SDA，主机负责拉低 / 拉高 
→ 程序猿要主动产生下降沿 / 上升沿,主动让SDA = 1/0
以Byte的二进制方式拉高或降低SDA电平

接收数据时（从机→主机）
从机控制 SDA，主机只负责读 SDA 的电平,并写入到Byte中
→ 所以程序猿不需要、也不能给 SDA 下降沿,无需手动让SDA = 1/0
只需要读取SDA上面的电平,转化成二进制0/1变成数据即可

Ack表示应答,英文单词为: Acknowledgement
NAck表示无应答,英文单词为: No Acknowledgement

*/




#include <REGX52.H>


sbit I2C_SCL = P2^1;        //时钟位
sbit I2C_SDA = P2^0;        //数据位




/*
* @brief  给一个上升沿,让在这一条线上的所有设备知道皇帝(单片机)要呼唤奴才(从机设备)了
* @param  无
* @retval 无
*/
void I2C_Start(void)
{
    I2C_SCL = 1;       //先保证SCL是1
    I2C_SDA = 1;       //SDA从1变成0
    I2C_SDA = 0;       //给一个下降沿
    I2C_SCL = 0;       //最后结束这一个数据帧,SCL变0
}





/*
* @brief  提供一个上升沿,表明停止传输数据信息
* @param  无
* @retval 无
*/
void I2C_Stop(void)
{
    I2C_SDA = 0;                //保证SDA初始情况是0
    I2C_SCL = 1;                //再拉高SCL
    I2C_SDA = 1;                //再拉高SDA,给一个上升沿
}




/*
* @brief  控制SDA线上的高低电平,将传进来的数据变化成二进制的电平信号并且传输出去
* @param  Byte要发送的字节
* @retval 无
*/
void I2C_SendByte(unsigned char Byte)
{
                                    //不能够先SCL = 1再传输数据后SCL = 0;
                                    //I2C协议规定,在SCL为高电平的时候SDA
                                    //必须要保持稳定,否则会错误识别为其他操作
                                    //因此必须先给SDA传数据后再给SCL上拉电平
    
    unsigned char i;
    for(i = 0;i < 8;i ++)
    {
        I2C_SDA =Byte&(0x80>>i);        //从高位到低位传数据,&操作符相当于只取这一位
        I2C_SCL = 1;                    //下降沿,表明完成这一位的数据传输
        I2C_SCL = 0;
    }
}




/*
* @brief  I2C接受一个字节
* @param  无
* @retval 接收到的一个字节数据
*/
unsigned char I2C_ReceiveByte(void)
{
    unsigned char i,Byte = 0x00;      //初始化接受数据为0,因为后面要赋值,避免没有清空
    
    I2C_SDA = 1;                      //重置SDA电平,将 SDA 引脚置为高电平输入状态（释放总线，让从机可以驱动 SDA 发送数据）
    
    for(i = 0;i < 8;i ++)
    {
         I2C_SCL = 1;
         if(I2C_SDA){Byte|=(0x80>>i);}//从高位到低位被动接收数据
                                      //这里根据SDA线上的电平来接收
                                      //二进制转化成数据,绝对不能控制
                                      //SDA高低电平,只能够被动接收
         I2C_SCL = 0;   
    }
   return Byte;                       //(外部接口)返回接收到的数据,供外部调用
}
    \


  /*
  * @brief I2C发送应答
  * @param AckBit应答位,0为应答,1为非应答
  * @retval 无
  */void I2C_SendAck(unsigned char AckBit)
{
    I2C_SDA = AckBit;                       //发送应答位
    I2C_SCL = 1;
    I2C_SCL = 0;
    
}



/*
* @brief  I2C接收应答位
* @param  无
* @retval 接收到的应答位
*/
unsigned char I2C_ReceiveAck(void)
{
    unsigned char AckBit;           //判断是否应答位
    I2C_SDA = 1;                    //释放数据线
    I2C_SCL = 1; 
    AckBit = I2C_SDA;               //接收应答位
    I2C_SCL = 0;
    return AckBit;                  //(外部接口)返回是否应答的数据,供外部调用
    
    
    
}
    
