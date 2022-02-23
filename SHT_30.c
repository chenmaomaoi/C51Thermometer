#include "REG52.H"
#include "IIC.h"
#include "SHT_30.h"
#include "CRC_8.h"

/// <summary>
/// 温湿度原始数据
/// </summary>
unsigned char SHT_30_RAW_Data[6];

/// <summary>
/// 温度
/// </summary>
float SHT_30_T;

/// <summary>
/// 湿度
/// </summary>
float SHT_30_RH;

/// <summary>
/// 初始化
/// </summary>
void SHT_30_Init()
{
	IIC_Start();
	IIC_Write_Byte(0x88);
	IIC_Write_Byte(0x21);
	IIC_Write_Byte(0x30);
	IIC_Stop();
}

/// <summary>
/// 数据读取与处理
/// </summary>
/// <returns></returns>
bit SHT_30_DataProcess()
{
	unsigned int buffer[2];

	IIC_Start();
	IIC_Write_Byte(0x88);
	IIC_Write_Byte(0xe0);
	IIC_Write_Byte(0x00);
	IIC_Stop();
	IIC_Start();
	IIC_Write_Byte(0x89);

	SHT_30_RAW_Data[0] = IIC_Read_Byte(1);
	SHT_30_RAW_Data[1] = IIC_Read_Byte(1);
	SHT_30_RAW_Data[2] = IIC_Read_Byte(1);
	SHT_30_RAW_Data[3] = IIC_Read_Byte(1);
	SHT_30_RAW_Data[4] = IIC_Read_Byte(1);
	SHT_30_RAW_Data[5] = IIC_Read_Byte(0);
	IIC_Stop();

	if (CRC_8_Check(&SHT_30_RAW_Data[0], 2, SHT_30_RAW_Data[2]) && CRC_8_Check(&SHT_30_RAW_Data[3], 2, SHT_30_RAW_Data[5]))
	{
		buffer[0] = SHT_30_RAW_Data[0];
		buffer[0] <<= 8;
		buffer[0] |= SHT_30_RAW_Data[1];

		buffer[1] = SHT_30_RAW_Data[3];
		buffer[1] <<= 8;
		buffer[1] |= SHT_30_RAW_Data[4];

		SHT_30_T = -45 + 175 * (1.0 * buffer[0] / 65535);
		SHT_30_RH = 100 * (1.0 * buffer[1] / 65535);

		return 1;
	}
	else
	{
		return 0;
	}
}
