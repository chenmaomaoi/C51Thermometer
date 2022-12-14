#ifndef _IIC_H
#define _IIC_H

#ifndef _REG52_H
#include "reg52.h"
#endif // !_REG52_H

#ifndef _INTRINS_H
#include "intrins.h"
#endif // !_INTRINS_H

//#ifndef _STDLIB_H
//#include "stdlib.h"
//#endif // !_STDLIB_H

sbit IIC_SCL = P2 ^ 0;	//IIC时钟引脚
sbit IIC_SDA = P2 ^ 1;	//IIC数据引脚

/// <summary>
/// IIC初始化；IIC_SCL为P2.0，IIC_SDA为P2.1
/// </summary>
void IIC_Init();

/// <summary>
/// IIC开始信号
/// </summary>
void IIC_Start();

/// <summary>
/// IIC停止信号
/// </summary>
void IIC_Stop();

/// <summary>
/// IIC写字节
/// </summary>
/// <param name="dat"></param>
/// <returns>从机应答状态</returns>
bit IIC_Write_Byte(unsigned char dat);

/// <summary>
/// IIC读字节
/// </summary>
/// <param name="ack">
/// <para>　</para>
/// <para>　　0->不再继续读取数据</para>
/// <para>　　1->继续读取下一个字节</para>
/// </param>
/// <returns></returns>
unsigned char IIC_Read_Byte(bit ack);

#endif
