#include <reg52.h>


/*************************************************************************
- Function    : 串口通讯实验
- Description : 测试
- Step        : 
								1.确定 定时器1 工作方式（配置工作方式寄存器TMOD）
								2.计算 T1 初值，装载TH1 TL1
								3.启动 T1 （配置控制寄存器TCON中的TR1）
								4.确定 串口 工作方式（配置串行口控制寄存器SCON）
								5.注意 TI RI 清0
- Author      : Y.
- Date        : 2017.12
 *************************************************************************/

void main()
{
		
    /* 配置定时器T1 */
	TMOD = 0x20;                  // 设置定时器T1工作方式2
	TH1 = 0xfd;                   // 波特率 9600
	TL1 = 0xfd;
	TR1 = 1;                      // 启动定时器   （ET1=1打开定时器1 工作方式2自动重装初值 进中断后无事可做 因此此处不用打开）

	/* 配置串行口 */
	SM0 = 0;                     // 设置为工作方式1
	SM1 = 1;  
	REN = 1;                     // 打开串口通信开关

	EA = 1;                      // 打开中断总开关
	ES = 1;                      // 打开串口中断

	while(1)
	{

		if(RI == 1)
		{
			RI = 0;              // 清0 才能产生下一次中断
			P1 = SBUF;           // 将SBUF中数据给P1
		}


	}
}


/* 串行口中断程序 序号4 */
void ser() interrupt 4           // 串行口中断 4  收到或者发送了数据，进入串口中断
{
	RI = 0;                      // 清0 才能产生下一次中断
	P1 = SBUF;                   // 将SBUF中数据给P1
}


