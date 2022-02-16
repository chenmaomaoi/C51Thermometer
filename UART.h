#ifndef __UART_H
#define __UART_H

/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity,奇校验
#define EVEN_PARITY     2   //Even parity,偶校验
#define MARK_PARITY     3   //Mark parity,1校验
#define SPACE_PARITY    4   //Space parity,0校验

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

#endif
