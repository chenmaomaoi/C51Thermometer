#include "main.h"

unsigned int Timer0Counter;
void (*Timer0_Event_Invok)(void);
bit sendRAWDataFlag = 0;

void delay1ms(void)   //误差 -0.651041666667us
{
	unsigned char a, b;
	for (b = 102; b > 0; b--)
		for (a = 3; a > 0; a--);
}

void recvdStr(const unsigned char* str)
{
	if (str[0] == 'C' && str[1] == ':')
	{
		//C: 指令解析
		sendRAWDataFlag = 1;
	}
	else
	{
		//直接显示
		LCD_1602_Clear();
		LCD_1602_ShowString(0, 0, str);
	}
}

void showInfo()
{
	char ch[16];
	if (SHT_30_DataProcess())
	{
		sprintf(ch, "T:%.2f RH:%.2f", SHT_30_T, SHT_30_RH);
		LCD_1602_ShowString(1, 0, ch);
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

	UART_Event_RecvdStr = &recvdStr;
	Timer0_Event_Invok = &showInfo;

	while (1)
	{
		if (sendRAWDataFlag)
		{
			if (SHT_30_DataProcess())
			{
				UART_SendString(SHT_30_RAW_Data);
				sendRAWDataFlag = 0;
			}
			delay1ms();
		}
	}
}

void Timer0Interrupt() interrupt 1
{
	TH0 = 0xDC;
	TL0 = 0x00;
	//add your code here!
	Timer0Counter++;
	if (Timer0Counter > (10 * 100))
	{
		Timer0Counter = 0;
		(*Timer0_Event_Invok)();
	}
}
