#include "SHT30.h"

void (*SHT30_iic_Start)();
void (*SHT30_iic_Stop)();
unsigned char (*SHT30_iic_Read_Byte)(unsigned char);
unsigned char (*SHT30_iic_Write_Byte)(unsigned char);

/// <summary>
/// 温湿度原始数据
/// </summary>
unsigned char SHT30_RAW_Data[7];

/// <summary>
/// 温度
/// </summary>
float SHT30_T;
unsigned int SHT30_T_uint16;

/// <summary>
/// 湿度
/// </summary>
float SHT30_RH;
unsigned int SHT30_RH_uint16;

/// <summary>
/// 初始化
/// </summary>
void SHT30_Init(void (*iic_start)(), void (*iic_stop)(), unsigned char (*iic_read_byte)(unsigned char), unsigned char (*iic_write_byte)(unsigned char))
{
	SHT30_iic_Start = iic_start;
	SHT30_iic_Stop = iic_stop;
	SHT30_iic_Read_Byte = iic_read_byte;
	SHT30_iic_Write_Byte = iic_write_byte;

	SHT30_iic_Start();
	SHT30_iic_Write_Byte(0x88);
	SHT30_iic_Write_Byte(0x21);
	SHT30_iic_Write_Byte(0x30);
	SHT30_iic_Stop();
}

/// <summary>
/// 数据读取与处理
/// </summary>
/// <returns></returns>
unsigned char SHT30_DataProcess()
{
	unsigned int buffer[2];

	SHT30_iic_Start();
	SHT30_iic_Write_Byte(0x88);
	SHT30_iic_Write_Byte(0xe0);
	SHT30_iic_Write_Byte(0x00);
	SHT30_iic_Stop();
	SHT30_iic_Start();
	SHT30_iic_Write_Byte(0x89);

	SHT30_RAW_Data[0] = SHT30_iic_Read_Byte(1);
	SHT30_RAW_Data[1] = SHT30_iic_Read_Byte(1);
	SHT30_RAW_Data[2] = SHT30_iic_Read_Byte(1);
	SHT30_RAW_Data[3] = SHT30_iic_Read_Byte(1);
	SHT30_RAW_Data[4] = SHT30_iic_Read_Byte(1);
	SHT30_RAW_Data[5] = SHT30_iic_Read_Byte(0);
	SHT30_RAW_Data[6] = '\0';
	SHT30_iic_Stop();

	if (CRC8_Check(&SHT30_RAW_Data[0], 2, SHT30_RAW_Data[2]) && CRC8_Check(&SHT30_RAW_Data[3], 2, SHT30_RAW_Data[5]))
	{
		buffer[0] = SHT30_RAW_Data[0];
		buffer[0] <<= 8;
		buffer[0] |= SHT30_RAW_Data[1];
		SHT30_T_uint16 = buffer[0];

		buffer[1] = SHT30_RAW_Data[3];
		buffer[1] <<= 8;
		buffer[1] |= SHT30_RAW_Data[4];
		SHT30_RH_uint16 = buffer[1];

		SHT30_T = 175.0f * (float)buffer[0] / 65535.0f - 45.0f;
		SHT30_RH = 100.0f * buffer[1] / 65535.0f;

		return 1;
	}
	else
	{
		return 0;
	}
}
