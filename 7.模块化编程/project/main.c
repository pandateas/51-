#include <REGX52.H>
#include "Delay.h"
#include "nixie.h"
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