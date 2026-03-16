//用定时器实现流水灯

#include <REGX52.H>
int cnt = 0;
void time()//进行1s的计数
{
	TMOD = 0x01;
	for(cnt = 0;cnt < 20;cnt ++)
	{
			//初始化开始计时
			TH0 = (65536 - 46074) / 256;
			TL0 = (65536 - 46074) % 256;
			TR0 = 1;
		
			//溢出时重置所有数据
			while(1)
				{
						if(TF0 == 1)
						{
							TR0 = 0;
							TF0 = 0;
							break;
						}
				}
	}
	
}

void main()
{
	while(1)
	{
			P2 = 0xff;
			P2_0 = 0;time();
			P2_0 = 1;P2_1 = 0;time();
			P2_1 = 1;P2_2 = 0;time();
			P2_2 = 1;P2_3 = 0;time();
			P2_3 = 1;P2_4 = 0;time();
			P2_4 = 1;P2_5 = 0;time();
			P2_5 = 1;P2_6 = 0;time();
			P2_6 = 1;P2_7 = 0;time();
	}
}