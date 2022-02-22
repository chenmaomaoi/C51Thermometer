#include "REG52.H"
#include "intrins.h"
#include "UART.h"
#include "IIC.h"
#include "LCD_1602.h"
#include "SHT_30.h"
#include "stdio.h"
#include "ASCII.h"

void EventHandler_UART_RecvByte(const unsigned char dat)
{
	static unsigned char buffer[64];
	static char index = 0;

	if (dat == '\r' || index > sizeof(buffer) - 1)
	{
		buffer[index] = NUL;
		LCD_1602_Clear();
		LCD_1602_ShowString(0, 0, buffer);
		index = 0;
		return;
	}
	buffer[index] = dat;
	index++;
}

void delay1s(void)   //��� -0.000000001137us
{
	unsigned char a, b, c;
	for (c = 13; c > 0; c--)
		for (b = 247; b > 0; b--)
			for (a = 142; a > 0; a--);
	_nop_();  //if Keil,require use intrins.h
}

void main()
{
	char ch[10];
	Event_UART_RecvdByte = &EventHandler_UART_RecvByte;

	UART_Init();
	EA = 1;

	IIC_Init();
	LCD_1602_Init();
	SHT_30_Init();

	//UART_SendString("AT\r\n" + EOT);

	while (1)
	{
		if (SHT_30_DataProcess())
		{
			sprintf(ch, "T:%.2f ", SHT_30_T);
			LCD_1602_ShowString(1, 0, ch);

			sprintf(ch, "RH:%.2f", SHT_30_RH);
			LCD_1602_ShowString(1, 8, ch);
		}

		delay1s();
	}
}
