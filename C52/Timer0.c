#include "Timer0.h"

void (*Timer0_Event_Elapsed)(void);

unsigned long _Timer0_Counter;
unsigned long _Timer0_Interval;

/// <summary>
/// Timer0初始化，默认不启动定时器，间隔时间为1000ms
/// </summary>
void Timer0_Init()
{
	//1ms
	TMOD |= 0x01;
	TH0 = 0xF1;
	TL0 = 0x9A;
	_Timer0_Counter = 0;
	_Timer0_Interval = 1000;
}

/// <summary>
/// 设置间隔时间
/// </summary>
/// <param name="interval">间隔时间(ms)</param>
void Timer0_SetInterval(unsigned long interval)
{
	_Timer0_Interval = interval;
}

/// <summary>
/// 启动
/// </summary>
void Timer0_Start()
{
	ET0 = 1;
	TR0 = 1;
}

/// <summary>
/// 停止
/// </summary>
void Timer0_Stop()
{
	ET0 = 0;
	TR0 = 0;
}

void Timer0_Interrupt() interrupt 1
{
	TH0 = 0xF1;
	TL0 = 0x9A;
	//add your code here!
	_Timer0_Counter++;
	if (_Timer0_Counter >= _Timer0_Interval)
	{
		_Timer0_Counter = 0;
		(*Timer0_Event_Elapsed)();
	}
}
