#include <REGX52.H>
#include <INTRINS.H>

void Delay(unsigned int x)	
{
		unsigned char data i, j,t;
		for(t = 0;t < x;t ++)
		{
				i = 36;
				j = 217;
				do
					{
						while (--j);
					} while (--i);
		}
}



void main()
{
		while(1)
		{
			if(P3_0 == 0)
			{
					Delay(20);
					while(P3_0==0);
					Delay(20);
					P2_0 = ~P2_0;
					
			}
	  }
}
