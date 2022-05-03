#include "UART.h"

void (*UART_Event_RecvdStr)(const unsigned char* str);

/// <summary>
/// 串口通信初始化 波特率：115200
/// <para>使用了定时器1</para>
/// </summary>
void UART_Init()
{
	TMOD = 0x20;
	SCON = 0x50;
	TH1 = 0xFF;
	TL1 = TH1;
	PCON = 0x80;
	//EA = 1;
	ES = 1;
	TR1 = 1;
}

/// <summary>
/// 发送一个字节
/// </summary>
/// <param name="dat"></param>
void UART_SendByte(unsigned char dat)
{
	SBUF = dat;             //Send data to UART buffer
	while (!TI);
	TI = 0;
}

/// <summary>
/// 发送字符串
/// </summary>
/// <param name="str"></param>
void UART_SendString(const unsigned char* str)
{
	unsigned char i;
	for (i = 0; i < strlen(str); i++)
	{
		UART_SendByte(str[i]);
	}
}

/// <summary>
/// 接收字符串
/// </summary>
/// <returns></returns>
const unsigned char* recvingStr()
{
	unsigned char recvdStr[64];
	unsigned char i = 0;
	unsigned char count = 0;
loop:
	recvdStr[i] = SBUF;
	count = 0;
	RI = 0;
	if (i < sizeof(recvdStr) - 1)
	{
		i++;
		while (!RI)
		{
			count++;
			//接收数据等待延迟，等待时间太久会导致CPU运算闲置，太短会出现"数据包被分割", 默认count = 130
			if (count > 130)
			{
				recvdStr[i] = '\0';
				return recvdStr;
			}
		}
		goto loop;
	}
	return recvdStr;
}

/// <summary>
/// 串口中断服务
/// </summary>
void UART_ISR() interrupt 4
{
	if (RI)
	{
		//触发字符串接收事件
		(*UART_Event_RecvdStr)(recvingStr());
	}
}
