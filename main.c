#include "REG52.H"
#include "intrins.h"
#include "UART.h"
#include "IIC.h"
#include "LCD_1602.h"
#include "SHT_30.h"
#include "stdio.h"
#include "ASCII.h"

char ch[16];

void EventHandler_UART_RecvByte(const unsigned char dat)
{
	unsigned char recvdStr[2] = { NUL,NUL };
	recvdStr[0] = dat;
	LCD_1602_ShowString(0, 0, recvdStr);
}

void delay1s(void)   //Îó²î -0.000000001137us
{
	unsigned char a, b, c;
	for (c = 13; c > 0; c--)
		for (b = 247; b > 0; b--)
			for (a = 142; a > 0; a--);
	_nop_();  //if Keil,require use intrins.h
}

void main()
{
	char mych[32] = "Hello World!";
	Event_UART_RecvdByte = &EventHandler_UART_RecvByte;

	UART_Init();
	EA = 1;

	IIC_Init();
	LCD_1602_Init();

	LCD_1602_ShowString(0, 0, mych);
	SHT_30_Init();

	UART_SendString(mych);

	while (1)
	{
		if (SHT_30_DataProcess())
		{
			sprintf(ch, "T:%.2f", SHT_30_T);
			LCD_1602_ShowString(1, 0, ch);

			sprintf(ch, "RH:%.2f", SHT_30_RH);
			LCD_1602_ShowString(1, 8, ch);
		}
		else
		{
			LCD_1602_ShowString(1, 0, mych);
		}

		delay1s();
	}
}
