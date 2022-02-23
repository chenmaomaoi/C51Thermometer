#include "LCD_1602.h"
#include "UART.h"
#include "ESP01.h"

void (*ESP01_Event_WiFiConnected)();
void (*ESP01_Event_WiFiGotIP)();
void (*ESP01_Event_TCPServerConnected)();
void (*ESP01_Event_TCPClosed)();
void (*ESP01_Event_MsgRecvd)(const unsigned char* msg);
void (*ESP01_Event_Error)(const unsigned char* msg);

enum ESP01State
{
	Started,
	WiFiConnected,
	WiFiGotIP,
	TCPConnected
} state = Started;

//const char* CONNECT_SERVER_STR = "AT+CIPSTART=\"TCP\",\"cn-zz-bgp-4.natfrp.cloud\",16967\r\n";

void parseCMD(const unsigned char* str)
{
	if (str[0] == 'W' && str[5] == 'C')
	{
		//WIFI CONNECTED
		(*ESP01_Event_WiFiConnected)();
		state = WiFiConnected;
	}
	else if (str[0] == 'W' && str[5] == 'G')
	{
		//WIFI GOT IP
		(*ESP01_Event_WiFiGotIP)();
		//UART_SendString(CONNECT_SERVER_STR);
		state = WiFiGotIP;
	}
	else if (str[0] == 'C' && str[3] == 'N' && str[6] == 'T')
	{
		//CONNECT
		(*ESP01_Event_TCPServerConnected)();
		state = TCPConnected;
	}
	//接收消息&检测TCP关闭事件CLOSED
	//消息头 +IPD,(num_of_data):dat\r\n
	else if (str[0] == 'C' && str[1] == 'L')
	{
		//TCP连接关闭
		(*ESP01_Event_TCPClosed)();
		state = WiFiGotIP;
	}
	else if (str[0] == 0x0D && str[6] == 0x2C)
	{
		str += 6;
		while (*str != 0x3A)
		{
			str++;
		}
		str++;
		(*ESP01_Event_MsgRecvd)(str);
	}
	else
	{
		(*ESP01_Event_Error)(str);
	}
}

void ESP01_Init()
{
	UART_Event_RecvdStr = &parseCMD;
}