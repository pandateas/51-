#include <REGX52.H>

void Delay(int x)	
{
	int t = 0;
	for(t = 0;t < x;t ++)
			{
				unsigned char data i, j;
				i = 2;
				j = 15;
					do
						{
							while (--j);
						} while (--i);
			}
}

unsigned int nixietable[] = 
{0x3f,0x06,0x5b,0x4f,
 0x66,0x6d,0x7d,0x07,
 0x7f,0x6f,0x77,0x7c,
 0x39,0x5e,0x79,0x71};

void nixie(int Location,int Number)
{
		switch(Location)
		{
			case 1:P2_4 = 1;P2_3 = 1;P2_2 = 1;break;
			case 2:P2_4 = 1;P2_3 = 1;P2_2 = 0;break;
			case 3:P2_4 = 1;P2_3 = 0;P2_2 = 1;break;
			case 4:P2_4 = 1;P2_3 = 0;P2_2 = 0;break;
			case 5:P2_4 = 0;P2_3 = 1;P2_2 = 1;break;
			case 6:P2_4 = 0;P2_3 = 1;P2_2 = 0;break;
			case 7:P2_4 = 0;P2_3 = 0;P2_2 = 1;break;
			case 8:P2_4 = 0;P2_3 = 0;P2_2 = 0;break;
		}
		P0 = nixietable[Number];
	
}
void main()
{
		while(1)
		{
			nixie(1,1); 
			Delay(1);
			nixie(2,2);
			Delay(1);
			nixie(3,3);
			Delay(1);
			nixie(4,4);
			Delay(1);
			nixie(5,5);
			Delay(1);
			nixie(6,6);
			Delay(1);
			nixie(7,7);
			Delay(1);
			nixie(8,8);
			Delay(1);
		}
		
}