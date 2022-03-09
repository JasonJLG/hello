#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

#define SPEED 500	//四分音符的标准速度(持续500ms),修改可调整音乐整体速度
//音符与索引对应表，P：休止符，L：低音，M：中音，H：高音，下划线：升半音符号#
#define P	0
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36

sbit Buzzer=P2^3;

unsigned int FreqTable[]={0,
	63625,63732,63833,63929,64019,64104,64185,64260,64332,64400,64463,64524,
	64580,64634,64685,64732,64778,64820,64860,64898,64934,64968,65000,65030,
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283};//频率表

unsigned char code Music[]={
	//音符,时值,
	
	//1
	P,	4,
	P,	4,
	P,	4,
	M6,	2,
	M7,	2,
	
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	M7,	4+4+4,
	M3,	2,
	M3,	2,
	
	//2
	M6,	4+2,
	M5,	2,
	M6, 4,
	H1,	4,
	
	M5,	4+4+4,
	M3,	4,
	
	M4,	4+2,
	M3,	2,
	M4,	4,
	H1,	4,
	
	//3
	M3,	4+4,
	P,	2,
	H1,	2,
	H1,	2,
	H1,	2,
	
	M7,	4+2,
	M4_,2,
	M4_,4,
	M7,	4,
	
	M7,	8,
	P,	4,
	M6,	2,
	M7,	2,
	
	//4
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	M7,	4+4+4,
	M3,	2,
	M3,	2,
	
	M6,	4+2,
	M5,	2,
	M6, 4,
	H1,	4,
	
	//5
	M5,	4+4+4,
	M2,	2,
	M3,	2,
	
	M4,	4,
	H1,	2,
	M7,	2+2,
	H1,	2+4,
	
	H2,	2,
	H2,	2,
	H3,	2,
	H1,	2+4+4,
	
	//6
	H1,	2,
	M7,	2,
	M6,	2,
	M6,	2,
	M7,	4,
	M5_,4,
	
	
	M6,	4+4+4,
	H1,	2,
	H2,	2,
	
	H3,	4+2,
	H2,	2,
	H3,	4,
	H5,	4,
	
	//7
	H2,	4+4+4,
	M5,	2,
	M5,	2,
	
	H1,	4+2,
	M7,	2,
	H1,	4,
	H3,	4,
	
	H3,	4+4+4+4,
	
	//8
	M6,	2,
	M7,	2,
	H1,	4,
	M7,	4,
	H2,	2,
	H2,	2,
	
	H1,	4+2,
	M5,	2+4+4,
	
	H4,	4,
	H3,	4,
	H3,	4,
	H1,	4,
	
	//9
	H3,	4+4+4,
	H3,	4,
	
	H6,	4+4,
	H5,	4,
	H5,	4,
	
	H3,	2,
	H2,	2,
	H1,	4+4,
	P,	2,
	H1,	2,
	
	//10
	H2,	4,
	H1,	2,
	H2,	2,
	H2,	4,
	H5,	4,
	
	H3,	4+4+4,
	H3,	4,
	
	H6,	4+4,
	H5,	4+4,
	
	//11
	H3,	2,
	H2,	2,
	H1,	4+4,
	P,	2,
	H1,	2,
	
	H2,	4,
	H1,	2,
	H2,	2+4,
	M7,	4,
	
	M6,	4+4+4,
	P,	4,
	
	0xFF	//终止标志
};//乐谱的索引

unsigned char FreqSelect,MusicSelect;

void main()
{	
	Timer0_Init();
	while(1)
	{
  		if(Music[MusicSelect]!=0xff)//0xff是一个终止符(终止标志)，起到终止的作用
		{
			FreqSelect=Music[MusicSelect];
			MusicSelect++;//相当于一种转换，通过Music数组作为索引（下标），让FreqSelect顺序可以按自己的想法来.
			Delay(SPEED/4*Music[MusicSelect]);//可以决定每个音的时长,这里面我们定义一个16分音符的时长为125ms,通常以4分音符为基准，所以我们定义一个宏SPEED，可以通过宏修改歌曲的整体速度。
			MusicSelect++;
			TR0=0;//关
			Delay(5);//使每个音符有个停顿，相当于有个抬手的瞬间
			TR0=1;//开
		}
		else//如果读到终止符就关闭TR0，死循环（停）
		{
			TR0=0;
			while(1);
			//注：MusicSelect=0;可以清零后从头继续播放
		}
	}			
}

void Timer0_Routine() interrupt 1 //1ms进一次中断
{
	if(FreqTable[FreqSelect])//如果是0，就不执行不震荡（休止），就没有声音。
	{
		TL0 = (FreqTable[FreqSelect]+79)%256;		//设置定时初值
		TH0 = (FreqTable[FreqSelect]+79)/256;		//设置定时初值
		Buzzer=!Buzzer;  //1ms翻转一次，相当于1/(2*10^-3)=500Hz
	}
	
}