#include <REGX52.H>
#include "LCD1602.h"

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"I Love China!");
	LCD_ShowString(2,1,"I Love NanHua!");
	while(1);
}