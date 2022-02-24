#include "main.h"

unsigned char Timer0Counter;
void (*Timer0_Event_Invok)(void);

void showRecvStr(const unsigned char* str)
{
	LCD_1602_Clear();
	LCD_1602_ShowString(0, 0, str);
}

void showAndSendData()
{
	char ch[16];
	if (SHT_30_DataProcess())
	{
		sprintf(ch, "T:%.2f RH:%.2f", SHT_30_T, SHT_30_RH);
		LCD_1602_ShowString(1, 0, ch);
		UART_SendString(SHT_30_RAW_Data);
	}
	return;
}

void InitTimer0()
{
	//10ms
	TMOD |= 0x01;
	TH0 = 0xDC;
	TL0 = 0x00;
	ET0 = 1;
	TR0 = 1;
	Timer0Counter = 0;
}

void main()
{
	IIC_Init();
	LCD_1602_Init();
	SHT_30_Init();

	UART_Init();
	EA = 1;

	InitTimer0();

	UART_Event_RecvdStr = &showRecvStr;
	Timer0_Event_Invok = &showAndSendData;

	while (1)
	{
		;
	}
}

void Timer0Interrupt() interrupt 1
{
	TH0 = 0xDC;
	TL0 = 0x00;
	//add your code here!
	Timer0Counter++;
	if (Timer0Counter > 200)
	{
		Timer0Counter = 0;
		(*Timer0_Event_Invok)();
	}
}
