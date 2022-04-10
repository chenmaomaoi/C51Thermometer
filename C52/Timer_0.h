#ifndef _TIMER_0_H
#define _TIMER_0_H
#endif // !_TIMER_0_H

#ifndef _REG52_H
#include "reg52.h"
#endif // !_REG52_H

extern void (*Timer_0_Event_Elapsed)(void);

/// <summary>
/// Timer0初始化，默认不启动定时器，间隔时间为1000ms
/// </summary>
void Timer_0_Init();

/// <summary>
/// 设置间隔时间(ms)
/// </summary>
/// <param name="interval">间隔时间</param>
void Timer_0_SetInterval(unsigned long interval);

/// <summary>
/// 启动
/// </summary>
void Timer_0_Start();

/// <summary>
/// 停止
/// </summary>
void Timer_0_Stop();
