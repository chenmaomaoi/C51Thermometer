#include "main.h"

char temp_ch[24];
sbit BLEState = P3 ^ 2;

void Timer_0_OnElapsed()
{
	//·¢ËÍÊý¾Ý
	if (BLEState)
	{
		if (SHT_30_DataProcess())
		{
			sprintf(temp_ch, "T:%.2f\r\nRH:%.2f\r\n\r\n", SHT_30_T, SHT_30_RH);
			UART_SendString(temp_ch);
		}
	}
}

void main()
{
	IIC_Init();
	SHT_30_Init();

	Timer_0_Init();
	Timer_0_SetInterval(10000);
	Timer_0_Event_Elapsed = &Timer_0_OnElapsed;
	Timer_0_Start();

	UART_Init();
	
	EA = 1;

	while (1)
	{
	}
}
