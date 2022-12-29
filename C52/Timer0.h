#ifndef _TIMER0_H
#define _TIMER0_H

#include "reg52.h"

extern void (*Timer0_Event_Elapsed)(void);

/// <summary>
/// Timer0初始化，默认不启动定时器，间隔时间为1000ms
/// </summary>
void Timer0_Init();

/// <summary>
/// 设置间隔时间(ms)
/// </summary>
/// <param name="interval">间隔时间</param>
void Timer0_SetInterval(unsigned long interval);

/// <summary>
/// 启动
/// </summary>
void Timer0_Start();

/// <summary>
/// 停止
/// </summary>
void Timer0_Stop();

#endif