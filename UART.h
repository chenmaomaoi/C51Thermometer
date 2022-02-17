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
/// <param name="_data"></param>
void UART_SendData(unsigned char _data);

/// <summary>
/// 发送字符串
/// </summary>
/// <param name="_str"></param>
void UART_SendString(char* _str);

extern void (*Event_UART_RecvdStr)(unsigned char* str);

#endif
