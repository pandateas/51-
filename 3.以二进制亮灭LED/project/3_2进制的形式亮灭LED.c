#include <REGX52.H>

void Delay(unsigned int x)
{
	int t = 0;
	for(t = 0;t < x;t ++)
			{
			unsigned char data i, j;
			i = 2;
			j = 199;
			do
		  {
			  while (--j);
		  }while (--i);
		}
}


void main()
{
		unsigned char LEDNUM = 0;//8bit
	
	
	while(1)
	{
			if(P3_0 == 0)
			{
					Delay(20);
					while(P3_0 == 0);//stop here
					Delay(20);
				LEDNUM++;
				P2 = ~LEDNUM;//2bit = 8bit
			}
		
	}
	
	
	
}
