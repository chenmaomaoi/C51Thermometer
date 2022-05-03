#include "main.h"

char temp_ch[24];	//临时存储要发送的数据
sbit BLEState = P3 ^ 2;	//BLE连接状态

void Timer_0_OnElapsed()
{
	sprintf(temp_ch, "T:%.2f\r\n RH:%.2f\r\n\r\n", SHT_30_T, SHT_30_RH);
	//发送数据
	if (BLEState)
	{
		if (SHT_30_DataProcess())
		{
			UART_SendString(temp_ch);
		}
	}
	LCD_1602_ShowString(0, 0, temp_ch);
}

void main()
{
	IIC_Init();
	SHT_30_Init();
	LCD_1602_Init();

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
