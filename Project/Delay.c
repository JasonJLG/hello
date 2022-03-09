/*
void Delay(unsigned int xms)		//@11.0592MHz（自测），单位为毫秒
{
	unsigned int i,j;
	for(i=xms;i>0;i--)
		for(j=114;j>0;j--);
}
*/

#include <intrins.h>

void Delay(unsigned int xms)//@11.0592MHz,xms的类型最好用uint,因为uint范围0~65535，而char范围0~255.
{							
	unsigned char i, j;
	while(xms)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);	
		xms--;
	}
	
}

