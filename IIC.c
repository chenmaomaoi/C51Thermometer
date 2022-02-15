#include "STC89C5xRC.h"
#include "IIC.h"

sbit SCL = P2 ^ 0;
sbit SDA = P2 ^ 1;

void IIC_dalay();
void IIC_start();
void IIC_stop();
void IIC_Init();
void IIC_send_ack(bit _ack);
bit IIC_get_ack();
bit IIC_Write_byte(unsigned char _data);
bit IIC_Switch_Device(unsigned char _type_id, unsigned char _device_id);
unsigned char IIC_read_byte();
unsigned char IIC_Read_Addr_byte(unsigned char _device_type_id, unsigned char _device_id);

/// <summary>
/// IIC专用延迟
/// </summary>
void IIC_dalay()
{
    _nop_();
    _nop_();
}

/// <summary>
/// 起始信号，时钟高，数据高变低
/// </summary>
void IIC_start()
{
    SDA = 1;
    IIC_dalay();
    SCL = 1;
    IIC_dalay();
    SDA = 0;
    IIC_dalay();
    SCL = 0;    //钳住I2C总线，准备发送或接收数据
}

/// <summary>
/// 停止信号
/// </summary>
void IIC_stop()
{
    SDA = 0;
    IIC_dalay();
    SCL = 0;
    IIC_dalay();
    SCL = 1;
    IIC_dalay();
    SDA = 1;
    IIC_dalay();
}

/// <summary>
/// IIC初始化
/// </summary>
void IIC_Init()
{
    SCL = 1;
    IIC_dalay();
    SDA = 1;
    IIC_dalay();
}

/// <summary>
/// 读取数据完成后，发送应答位
/// </summary>
/// <param name="_ack">
/// <para>　</para>
/// <para>　　0->不应答，告诉从机我不再继续接受数据，从机停止发送数据</para>
/// <para>　　1->应答，告诉从机我要继续读取下一个字节，从机收到这个信号后继续发送数据</para>
/// </param>
void IIC_send_ack(bit _ack)
{
    SDA = !_ack;
    SCL = 1;
    IIC_dalay();
    SCL = 0;    //拉低，完成应答位
    IIC_dalay();
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
bit IIC_get_ack()
{
    bit ack = 0;
    unsigned char i = 0;

    SCL = 1;
    IIC_dalay();

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
/// 发送一个字节，从高位往低位发送
/// <para>主机向从机发送数据，从机在时钟的下降沿采集SDA的数据</para>
/// </summary>
/// <param name="_data"></param>
/// <returns>
/// <para>0:不应答</para>
/// <para>1:应答</para>
/// </returns>
bit IIC_Write_byte(unsigned char _data)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        SDA = (bit)(_data & 0x80);   //先写高位
        IIC_dalay();
        SCL = 1;
        IIC_dalay();
        SCL = 0;          //下降沿采集数据
        IIC_dalay();
        _data = _data << 1;
    }

    SDA = 1;//发送完毕后，释放数据线，检测从机应答
    return IIC_get_ack();//等待应答
}

/// <summary>
/// 切换设备
/// </summary>
/// <param name="_type_id">从设备物料id，由供应商决定；一般相同的设备其ID是相同的</param>
/// <param name="_device_id">从设备id，可在从设备上修改；多个相同设备连接到同一总线时需要在设备上修改</param>
/// <returns>
/// <para>0:设备没有应答，可能切换失败</para>
/// <para>1:设备成功应答</para>
/// </returns>
bit IIC_Switch_Device(unsigned char _type_id, unsigned char _device_id)
{
    bit result = 0;
    IIC_stop();
    IIC_start();

    result = IIC_Write_byte(_type_id) && IIC_Write_byte(_device_id);

    return result;
}

//todo:读取数据未验证

/// <summary>
/// 读取数据
/// </summary>
/// <returns>data</returns>
unsigned char IIC_read_byte()
{
    unsigned char i = 0;
    unsigned char result = 0;

    SDA = 1;      //先确保主机释放SDA
    IIC_dalay();

    for (i = 0; i < 8; i++)
    {
        SCL = 1;
        result = (result << 1) | SDA;
        IIC_dalay();
        SCL = 0;    //拉低，采集数据
        IIC_dalay();
    }

    return result;
}

/// <summary>
/// 读取从设备一个字节数据
/// </summary>
/// <param name="_device_type_id">从设备物料id，由供应商决定；一般相同的设备其ID是相同的</param>
/// <param name="_device_id">从设备id，可在从设备上修改；多个相同设备连接到同一总线时需要在设备上修改</param>
/// <returns>data</returns>
unsigned char IIC_Read_Addr_byte(unsigned char _device_type_id, unsigned char _device_id)
{
    unsigned char result;

    IIC_start();
    IIC_Write_byte(_device_type_id);//发送设备地址+写信号
    IIC_Write_byte(_device_id);    //发送存储器单元
    IIC_start();            //必须从新启动IIC

    IIC_Write_byte(_device_type_id + 1);//发送设备地址+读信号
    result = IIC_read_byte();//读出数据
    IIC_send_ack(0);//发送非应答信号，停止读取数据
    IIC_stop();

    return result;
}