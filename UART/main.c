#include <REGX52.H>
#include "Delay.h"

#define uchar unsigned char
#define uint unsigned int

uchar count;
uchar Byte = 0x55;

void Timer0_Isr(void) interrupt 1
{	
	TL0 = 0x87;				//设置定时初始值
	TH0 = 0xFE;				//设置定时初始值
////	P2 = 0;
	if(count == 0)					//起始位
	{
		TXD = 0;
		count++;
	}
	else if(count == 9)					//终止位及重置
	{
//		P2 = 0;
		TR0 = 0;
		TXD = 1;
		count = 0;
	}
	else							//1-8位对应count1-8
	{
		TXD = Byte & (0x01 << (count - 1));
		count++;
	}
//	P2_1=~P2_1;
}

void Timer0_Init(void)		//	微秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x87;				//设置定时初始值
	TH0 = 0xFE;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 0;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断

	EA = 1;
}




//void Uart_Init(void)	//9600bps@11.0592MHz
//{
//	PCON &= 0x7F;		//??????
//	SCON = 0x50;		//8???,?????
//	TMOD &= 0x0F;		//???????
//	TMOD |= 0x20;		//???????
//	TL1 = 0xFD;			//???????
//	TH1 = 0xFD;			//???????
//	ET1 = 0;			//???????
//	TR1 = 0;			//???1????
//}

//void SendByte(uchar Byte)
//{
//	TXD = 0;
//	for(i = 0; i < 8; i++)
//	{
//		TXD = Byte & (0x80 >> i);
//	}
//	TXD = 1;
//}

void main()
{
//	Uart_Init();
	Timer0_Init();
	TXD = 1;
	while(1)
	{
		if(P3_3 == 0)
		{
			Delay(20);		
			while(P3_3 == 0);	
			Delay(20);	
			
			TR0 = 1;
		}
		
	}
}