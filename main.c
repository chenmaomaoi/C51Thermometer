#include "REG52.H"
#include "intrins.h"
#include "UART.h"
#include "IIC.h"
#include "LCD_1602.h"
#include "SHT_30.h"
#include <stdio.h>

bit flag = 0;
char* ch;

void EventHandler_UART_RecvdStr(unsigned char* str)
{
	ch = str;
	flag = 1;
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

	Event_UART_RecvdStr = &EventHandler_UART_RecvdStr;

	UART_Init();
	EA = 1;

	IIC_Init();
	LCD_1602_Init();

	LCD_1602_ShowString(0, 0, mych);
	SHT_30_Init();

	UART_SendString(mych);

	while (1)
	{
		if (flag)
		{
			LCD_1602_ShowString(0, 0, ch);
			flag = 0;
		}

		sprintf(ch, "%.2f", SHT_30_ReadT());
		LCD_1602_ShowString(1, 0, ch);

		sprintf(ch, "%.2f", SHT_30_ReadRH());
		LCD_1602_ShowString(1, 11, ch);

		delay1s();
	}
}
