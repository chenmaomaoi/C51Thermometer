#include "REG52.H"
#include "intrins.h"
#include "IIC.h"

sbit SCL = P2 ^ 0;
sbit SDA = P2 ^ 1;

/// <summary>
/// IIC专用延迟
/// </summary>
void dalay()
{
    _nop_();
    _nop_();
}

/// <summary>
/// 主机发送完成，等待应答
/// <para>主机发送完一个字节的数据之后会把SDA拉高，等待从机的信号，如果从机不应答，SDA将一直拉高，等待约250us后返回0，表示非应答</para>
/// <para>如果在SCL高电平期间，SDA被从设备拉低表示从设备应答，此时while跳过，应答位结束，返回1，表示应答</para>
/// </summary>
/// <returns>
/// <para>0:不应答</para>
/// <para>1:应答</para>
/// </returns>
bit wait_ack()
{
    bit ack = 0;
    unsigned char i = 0;

    SCL = 1;
    dalay();

    while (SDA == 1)
    {
        i++;
        if (i >= 250)
        {
            break;
        }
        ack = SDA;
    }

    SCL = 0;   //拉低，完成应答位

    return !ack;
}

/// <summary>
/// IIC开始信号
/// </summary>
void IIC_Start()
{
    SDA = 1;
    dalay();
    SCL = 1;
    dalay();
    SDA = 0;
    dalay();
    SCL = 0;    //钳住I2C总线，准备发送或接收数据
}

/// <summary>
/// IIC停止信号
/// </summary>
void IIC_Stop()
{
    SDA = 0;
    dalay();
    SCL = 0;
    dalay();
    SCL = 1;
    dalay();
    SDA = 1;
    dalay();
}

/// <summary>
/// IIC初始化
/// </summary>
void IIC_Init()
{
    SCL = 1;
    dalay();
    SDA = 1;
    dalay();
}

/// <summary>
/// 发送一个字节，从高位往低位发送
/// <para>主机向从机发送数据，从机在时钟的下降沿采集SDA的数据</para>
/// </summary>
/// <param name="dat"></param>
/// <returns>
/// <para>0:从机不应答，不要继续发送数据</para>
/// <para>1:从机应答，继续发送数据</para>
/// </returns>
bit IIC_Write_Byte(unsigned char dat)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        SDA = (bit)(dat & 0x80);   //先写高位
        dalay();
        SCL = 1;
        dalay();
        SCL = 0;          //下降沿采集数据
        dalay();
        dat = dat << 1;
    }

    SDA = 1;//发送完毕后，释放数据线，检测从机应答
    return wait_ack();//等待应答
}

/// <summary>
/// IIC读字节
/// </summary>
/// <param name="ack">
/// <para>　</para>
/// <para>　　0->不再继续读取数据</para>
/// <para>　　1->继续读取下一个字节</para>
/// </param>
/// <returns></returns>
unsigned char IIC_Read_Byte(bit ack)
{
    unsigned char i = 0;
    unsigned char result = 0;

    SDA = 1;      //先确保主机释放SDA
    dalay();

    for (i = 0; i < 8; i++)
    {
        SCL = 1;
        result = (result << 1) | SDA;
        dalay();
        SCL = 0;    //拉低，采集数据
        dalay();
    }

    //发送应答位
    SDA = !ack;
    SCL = 1;
    dalay();
    SCL = 0;    //拉低，完成应答位
    dalay();

    return result;
}
