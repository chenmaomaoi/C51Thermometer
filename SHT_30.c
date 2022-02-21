#include "REG52.H"
#include "IIC.h"
#include "SHT_30.h"
#include "CRC_8.h"

unsigned int raw_data[4];

void SHT_30_Init()
{
	IIC_Start();
	IIC_Write_byte(0x88);
	IIC_Write_byte(0x21);
	IIC_Write_byte(0x30);
	IIC_Stop();
}

unsigned char* read_raw_data()
{
	IIC_Start();
	IIC_Write_byte(0x88);
	IIC_Write_byte(0xe0);
	IIC_Write_byte(0x00);
	IIC_Stop();
	IIC_Start();
	IIC_Write_byte(0x89);

	raw_data[0] = IIC_Read_byte(1);
	raw_data[0] <<= 8;
	raw_data[0] |= IIC_Read_byte(1);
	raw_data[1] = IIC_Read_byte(1);

	raw_data[2] = IIC_Read_byte(1);
	raw_data[2] <<= 8;
	raw_data[2] |= IIC_Read_byte(1);
	raw_data[3] = IIC_Read_byte(0);

	IIC_Stop();
	return raw_data;
}

float SHT_30_ReadT()
{
	float T;
	read_raw_data();
	T = -45 + 175 * (1.0 * raw_data[0] / 65535);
	return T;
}

float SHT_30_ReadRH()
{
	float RH;
	//read_raw_data();
	RH = 100 * (1.0 * raw_data[2] / 65535);
	return RH;
}