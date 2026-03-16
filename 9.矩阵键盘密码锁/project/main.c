#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "MatrixKeys.h"

unsigned char KeyNum;
unsigned int Password;
unsigned int count = 1;
void main()
{
	again:
		LCD_Init();
	LCD_ShowString(1,1,"Pssword:");
	
	while(1)
	{
		
			KeyNum = MatrixKeys();
			
			if(KeyNum)
			{
					if(KeyNum <= 10)
					{
						if(count <= 4)
						{
							Password *= 10;
							Password += KeyNum % 10;
							count ++;
						}//................前四个正常输入
							LCD_ShowNum(2,1,Password,4);			
					}
				if(KeyNum == 11)
				{
						if(Password == 2345)
						{
								LCD_ShowString(1,14,"OK");
								Password = 0;
								count = 0;
						}
						else
						{
									LCD_ShowString(1,14,"EOR");
								Password = 0;
								count = 0;
						}
				}
			}
	
	}
	
}
