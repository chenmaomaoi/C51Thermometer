#include "STC89C5xRC.h"
#include "intrins.h"
#include "UART.h"
#include "main.h"

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

#define PARITYBIT NONE_PARITY   //Testing even parity

bit busy;

void UART_SendData(unsigned char _data);
void UART_SendString(char* s);

/// <summary>
/// 串口通信初始化
/// <para>使用了定时器1</para>
/// </summary>
void UART_Init()
{
#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;            //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;            //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;            //9-bit variable UART, parity bit initial to 0
#endif

    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
    TH1 = TL1 = -(FOSC / 12 / 32 / BAUD); //Set auto-reload vaule
    TR1 = 1;                //Timer1 start run
    ES = 1;                 //Enable UART interrupt
}

/// <summary>
/// 发送一个字节
/// </summary>
/// <param name="_data"></param>
void UART_SendData(unsigned char _data)
{
    while (busy);           //Wait for the completion of the previous data is sent
    ACC = _data;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;            //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;            //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;            //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;            //Set parity bit to 0
#endif
    }
    busy = 1;
    SBUF = ACC;             //Send data to UART buffer
}

/// <summary>
/// 发送字符串
/// </summary>
/// <param name="_str"></param>
void UART_SendString(char* _str)
{
    while (*_str)              //Check the end of the string
    {
        UART_SendData(*_str++);     //Send current char and increment string ptr
    }
}

/// <summary>
/// 串口中断服务
/// </summary>
void UART_ISR() interrupt 4
{
    if (RI)
    {
        UART_Event_Recvd();
    }
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}
