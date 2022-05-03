#include "main.h"

char temp_ch[24];	//临时存储要发送的数据
sbit BLEState = P3 ^ 2;	//BLE连接状态

void Timer_0_OnElapsed()
{
	//发送数据
	if (BLEState)
	{
		if (SHT_30_DataProcess())
		{
			sprintf(temp_ch, "T:%.2f\r\nRH:%.2f\r\n\r\n", SHT_30_T, SHT_30_RH);
		}
		UART_SendString(temp_ch);
	}
}

void main()
{
	IIC_Init();
	SHT_30_Init();

	Timer_0_Init();
	Timer_0_Event_Elapsed = &Timer_0_OnElapsed;
	Timer_0_Start();

	UART_Init();
	
	EA = 1;

	while (1)
	{
	}
}
