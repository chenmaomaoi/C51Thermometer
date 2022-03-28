#include "main.h"

bit UART_OnRecvdStrFlag = 0;
bit Timer_0_OnElapsedFlag = 1;	//此处置1，以便于上电之后立即显示信息

unsigned char* UART_RecvdStr;

/// <summary>
/// 100us
/// </summary>
void delay()
{
	unsigned char a, b;
	for (b = 3; b > 0; b--)
		for (a = 13; a > 0; a--);
}

void Timer_0_OnElapsed()
{
	Timer_0_OnElapsedFlag = 1;
}

void UART_OnRecvdStr(const unsigned char* str)
{
	UART_OnRecvdStrFlag = 1;
	UART_RecvdStr = str;
}

void main()
{
	/// <summary>
	/// 用于临时存储要显示的字符串
	/// </summary>
	char temp_ch[16];

	IIC_Init();
	SHT_30_Init();
	LCD_1602_Init();

	UART_Init();
	UART_Event_RecvdStr = &UART_OnRecvdStr;
	
	Timer_0_Init();
	Timer_0_Event_Elapsed = &Timer_0_OnElapsed;
	Timer_0_SetInterval(30000);	//30秒
	Timer_0_Start();
	EA = 1;

	while (1)
	{
		if (UART_OnRecvdStrFlag)
		{
			if (SHT_30_DataProcess())
			{
				sprintf(temp_ch, "T:%.2f RH:%.2f", SHT_30_T, SHT_30_RH);
				UART_SendString(SHT_30_RAW_Data);
				LCD_1602_Clear();
				LCD_1602_ShowString(0, 0, UART_RecvdStr);
				LCD_1602_ShowString(1, 0, temp_ch);
				UART_OnRecvdStrFlag = 0;
			}
			delay();
		}
		if (Timer_0_OnElapsedFlag)
		{
			if (SHT_30_DataProcess())
			{
				sprintf(temp_ch, "T:%.2f RH:%.2f", SHT_30_T, SHT_30_RH);
				LCD_1602_Clear();
				LCD_1602_ShowString(1, 0, temp_ch);
				Timer_0_OnElapsedFlag = 0;
			}
			delay();
		}
	}
}
