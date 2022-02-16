#ifndef __IIC_H
#define __IIC_H

/// <summary>
/// IIC初始化
/// </summary>
void IIC_Init();

/// <summary>
/// 发送一个字节，从高位往低位发送
/// <para>主机向从机发送数据，从机在时钟的下降沿采集SDA的数据</para>
/// </summary>
/// <param name="_data"></param>
/// <returns>
/// <para>0:不应答</para>
/// <para>1:应答</para>
/// </returns>
bit IIC_Write_byte(unsigned char _data);

/// <summary>
/// 切换设备
/// </summary>
/// <param name="_device_type_id">从设备物料id，由供应商决定；一般相同的设备其ID是相同的</param>
/// <param name="_device_id">从设备id，可在从设备上修改；多个相同设备连接到同一总线时需要在设备上修改</param>
/// <returns>
/// <para>0:设备没有应答，可能切换失败</para>
/// <para>1:设备成功应答</para>
/// </returns>
bit IIC_Switch_Device(unsigned char _device_type_id, unsigned char _device_id);

/// <summary>
/// 读取从设备一个字节数据
/// </summary>
/// <param name="_device_type_id">从设备物料id，由供应商决定；一般相同的设备其ID是相同的</param>
/// <param name="_device_id">从设备id，可在从设备上修改；多个相同设备连接到同一总线时需要在设备上修改</param>
/// <returns>data</returns>
unsigned char IIC_Read_Addr_byte(unsigned char _device_type_id, unsigned char _device_id);

#endif
