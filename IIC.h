#ifndef __IIC_H
#define __IIC_H

/// <summary>
/// IIC初始化
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
