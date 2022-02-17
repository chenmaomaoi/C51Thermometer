#include "REG52.H"
#include "intrins.h"
#include "UART.h"
#include "IIC.h"
#include "LCD_1602.h"

//void EventHandler_UART_RecvdStr(unsigned char* str);
//void Handel_UART_Event();
//bit UART_recvingStr();

//char UART_RecvdStr[32];	//串口接收的数据，数据超长时会引发覆盖

void EventHandler_UART_RecvdStr(unsigned char* str)
{
	LCD_1602_ShowString(1, 5, str);
}

void main()
{
	char mych[32] = "Hello World!";

	Event_UART_RecvdStr = &EventHandler_UART_RecvdStr;

	UART_Init();
	EA = 1;

	IIC_Init();
	LCD_1602_Init();

	LCD_1602_ShowString(0, 0, mych);

	UART_SendString(mych);

	while (1)
	{
	}
}

///// <summary>
///// 处理串行数据传入，参数是UART_RecvdStr
///// </summary>
//void Handel_UART_Event()
//{
//	LCD_1602_ShowString(0, 0, UART_RecvdStr);
//}
//
///// <summary>
///// 串口通信事件：有数据传入
///// </summary>
//void UART_Event_Recvd()
//{
//	//此处可抛弃过长数据
//	UART_recvingStr();
//	_UART_recvdFlag = 1;
//}
//
///// <summary>
///// 串口通信，接收字符串数据
///// </summary>
///// <returns>数据长度大于等于数组长度时，返回1</returns>
//bit UART_recvingStr()
//{
//	char* RecStr = UART_RecvdStr;
//	char num = 0;
//	unsigned char count = 0;
//loop:
//	//todo:奇偶校验
//	*RecStr = SBUF;
//	count = 0;
//	RI = 0;
//	if (num < sizeof(UART_RecvdStr) - 1)
//	{
//		num++;
//		RecStr++;
//		while (!RI)
//		{
//			count++;
//
//			//接收数据等待延迟，等待时间太久会导致CPU运算闲置，太短会出现"数据包被分割",默认count=130
//			if (count > 130)
//			{
//				return 0;
//			}
//		}
//		goto loop;
//	}
//	return 1;
//}
