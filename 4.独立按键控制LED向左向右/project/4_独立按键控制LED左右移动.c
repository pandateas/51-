/*
小芝士:单片机的移位操作是固定死的,位移操作时是所有的位同时移动
多出去的位丢掉,空了的位补零.因此,常见的好用的位移操作是对0x01这种
进行位移操作,最后再对结果取反
*/

#include <REGX52.H>

void Delay(int x)	
{
	unsigned char data i, j;
	int t = 0;
	for(t = 0;t < x;t ++)
	{
			i = 11;
			j = 190;
			do
			{
				while (--j);
			}while (--i);
  }
}


	static unsigned char LEDNUM = 0;
void main()
{
		P2 = ~0X01;
	while(1)
	{
		
		if(P3_1 == 0)
		{
				
				Delay(20);
			  while(P3_1 == 0);
				
				Delay(20);
				LEDNUM ++;
				if(LEDNUM >= 8)
				{
						LEDNUM = 0;
				}
				P2 = ~(0x01 << LEDNUM );//P2 = 1111 1110
		}
			if(P3_0 == 0)
			{
					
					Delay(20);
					while(P3_0 == 0);
					Delay(20);
					if(LEDNUM == 0)
					{
							LEDNUM = 7;
					}
					else LEDNUM --;
					P2 = ~(0x01 << LEDNUM);
			}
		
		
		
		
		
		
	}
	
	
}
