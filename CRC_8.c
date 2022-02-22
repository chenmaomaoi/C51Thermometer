
unsigned char CRC_8_Compute(unsigned char* check_data, unsigned char num_of_data)
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

bit CRC_8_Check(unsigned char* p, unsigned char num_of_data, unsigned char crc_data)
{
	return (CRC_8_Compute(p, num_of_data) == crc_data) ? 1 : 0;
}
