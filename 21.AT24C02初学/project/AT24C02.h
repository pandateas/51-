#ifndef __AT24C02_H__
#define __AT24C02_H__

void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data);   //表示我要在那个寄存器中写入什么数据
unsigned char AT24C02_ReadByte(unsigned char WordAddress);              //0~255个寄存器


#endif