#include "CRC8.h"

/// <summary>
/// CRC-8 计算
/// </summary>
/// <param name="check_data"></param>
/// <param name="num_of_data"></param>
/// <returns></returns>
unsigned char CRC8_Compute(const unsigned char* check_data, unsigned char num_of_data)
{
	unsigned char bit_mask;        // bit mask
	unsigned char crc = 0xFF; // calculated checksum
	unsigned char byteCtr;    // byte counter

	// calculates 8-Bit checksum with given polynomial
	for (byteCtr = 0; byteCtr < num_of_data; byteCtr++)
	{
		crc ^= (check_data[byteCtr]);
		//crc校验，最高位是1就^0x31
		for (bit_mask = 8; bit_mask > 0; --bit_mask)
		{
			if (crc & 0x80)
			{
				crc = (crc << 1) ^ 0x31;
			}
			else
			{
				crc = (crc << 1);
			}
		}
	}
	return crc;
}

/// <summary>
/// CRC-8校验
/// </summary>
/// <param name="p"></param>
/// <param name="num_of_data"></param>
/// <param name="crc_data"></param>
/// <returns></returns>
bit CRC8_Check(const unsigned char* p, unsigned char num_of_data, unsigned char crc_data)
{
	return (CRC8_Compute(p, num_of_data) == crc_data) ? 1 : 0;
}
