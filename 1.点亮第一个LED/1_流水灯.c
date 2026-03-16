#include <REGX52.H>
#include <INTRINS.H>


void Delay300ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 4;
	j = 60;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
 
//0 1 2 3 4 5 6 7 -- 1~8
//8 9 a b c d e f -- 9~16
void main()
{
	int i = 4;
	int j = 60;
	int k = 119;
		P2 = 0xfe;//1111 1110
		Delay300ms();
		P2 = 0xfd;//1111 1101
		Delay300ms();
		P2 = 0xfb;//1111 1011
		Delay300ms();
		P2 = 0xf7;//1111 0111
		Delay300ms();
		P2 = 0xef;//1110 1111
		Delay300ms();
		P2 = 0xdf;//1101 1111
		Delay300ms();
		P2 = 0xbf;//1011 1111
		Delay300ms();
		P2 = 0x7f;//0111 1111
		Delay300ms();
	
}
