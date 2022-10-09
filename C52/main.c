#include "main.h"

char temp_ch[32];	//临时存储要显示的字符串
unsigned char *recvdStr;
bit Timer0_Elapsed_Flag = 1;	//T0事件
bit UART_RecvdStr_Flag = 0;		//串口接收到字符串

void Timer0_OnElapsed()
{
	Timer0_Elapsed_Flag = 1;
}

void UART_OnRecvdStr(const unsigned char* str)
{
	recvdStr = str;
	UART_RecvdStr_Flag = 1;
}

void main()
{
	IIC_Init();
	SHT30_Init();
	LCD1602_Init();

	Timer0_Init();
	Timer0_Event_Elapsed = &Timer0_OnElapsed;
	Timer0_SetInterval(5000);
	Timer0_Start();

	UART_Event_RecvdStr = &UART_OnRecvdStr;
	UART_Init();

	EA = 1;

	while (1)
	{
		if (Timer0_Elapsed_Flag)
		{
			if (SHT30_DataProcess())
			{
				//刷新LCD1602显示
				sprintf(temp_ch, "T:%.2f RH:%.2f\r\n", SHT30_T, SHT30_RH);
				LCD1602_ShowString(1, 0, temp_ch);

				//发送数据
				UART_SendString(temp_ch);
				Timer0_Elapsed_Flag = 0;
			}
		}

		if (UART_RecvdStr_Flag)
		{
			//未找到则直接显示发送来的数据
			LCD1602_Clear_Row(0);
			LCD1602_ShowString(0, 0, recvdStr);

			//refreshFlag = 0;
			UART_RecvdStr_Flag = 0;
		}
	}
}
