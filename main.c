#include "main.h"

bit sendRAWDataFlag = 0;

void delay(void)   //100us
{
	unsigned char a, b;
	for (b = 3; b > 0; b--)
		for (a = 13; a > 0; a--);
}

void recvdStr(const unsigned char* str)
{
	if (str[0] == 'C' && str[1] == ':')
	{
		//C: ÷∏¡ÓΩ‚Œˆ
		sendRAWDataFlag = 1;
	}
}

void main()
{
	IIC_Init();
	SHT_30_Init();

	UART_Init();
	EA = 1;

	UART_Event_RecvdStr = &recvdStr;

	while (1)
	{
		if (sendRAWDataFlag)
		{
			if (SHT_30_DataProcess())
			{
				UART_SendString(SHT_30_RAW_Data);
				sendRAWDataFlag = 0;
			}
			delay();
		}
	}
}
