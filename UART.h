#ifndef __UART_H
#define __UART_H

/// <summary>
/// 串口通信初始化
/// <para>使用了定时器1</para>
/// </summary>
void UART_Init();

/// <summary>
/// 发送一个字节
/// </summary>
/// <param name="dat"></param>
void UART_SendByte(unsigned char dat);

/// <summary>
/// 发送字符串
/// </summary>
/// <param name="str"></param>
void UART_SendString(const char* str);

extern void (*Event_UART_RecvdStr)(const unsigned char* str);

#endif
