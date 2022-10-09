#include "main.h"

char temp_ch[32];	//临时存储要显示的字符串
unsigned char *recvdStr;
bit Timer_0_Elapsed_Flag = 1;	//T0事件
bit UART_RecvdStr_Flag = 0;		//串口接收到字符串
//bit refreshFlag = 1;

void Timer_0_OnElapsed()
{
	Timer_0_Elapsed_Flag = 1;
}

void UART_OnRecvdStr(const unsigned char* str)
{
	recvdStr = str;
	UART_RecvdStr_Flag = 1;
}

void main()
{
	IIC_Init();
	SHT_30_Init();
	LCD_1602_Init();

	Timer_0_Init();
	Timer_0_Event_Elapsed = &Timer_0_OnElapsed;
	Timer_0_SetInterval(5000);
	Timer_0_Start();

	UART_Event_RecvdStr = &UART_OnRecvdStr;
	UART_Init();

	EA = 1;

	while (1)
	{
		if (Timer_0_Elapsed_Flag)
		{
			if (SHT_30_DataProcess())
			{
				//刷新LCD1602显示
				sprintf(temp_ch, "T:%.2f RH:%.2f\r\n", SHT_30_T, SHT_30_RH);
				LCD_1602_ShowString(1, 0, temp_ch);

				//发送数据
				UART_SendString(temp_ch);
				Timer_0_Elapsed_Flag = 0;
			}
		}

		if (UART_RecvdStr_Flag)
		{			
			//未找到则直接显示发送来的数据
			LCD_1602_Clear_Row(0);
			LCD_1602_ShowString(0, 0, recvdStr);

			//refreshFlag = 0;
			UART_RecvdStr_Flag = 0;
		}
	}
}
