#include <REGX52.H>

//静态数码管显示表格,代表着{0,1,2,3,4,5,6,7,8,9,熄灭所有灯,显示分割横线}
unsigned int nixietable[] = 
{0x3f,0x06,0x5b,0x4f,
 0x66,0x6d,0x7d,0x07,
 0x7f,0x6f,0x00,0x40};

 
 //
unsigned char nixie_Buf[9];
 

//传入要写入的东西并存放在数组中
void nixie_SetBuf(unsigned char Location,Number)
{
    nixie_Buf[Location] = Number;//Number是从主函数中传进来的数,表明要在第几位显示几
}    



void nixie_Scan(int Location,int Number)
{
        P0 = 0x00;//熄灭所有静态数码管,相当于初始化操作
    
    
		switch(Location)//根据传入的Location选择要显示的静态数码管位置
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
		P0 = nixietable[Number];//向
}


void nixie_Loop(void)
{
    static unsigned char i;
    
    //在主函数中每20ms刷新一次静态数码管其中一位的显示状态
    nixie_Scan(i,nixie_Buf[i]);
    i ++;
    if(i >= 9){i = 1;}
    
}