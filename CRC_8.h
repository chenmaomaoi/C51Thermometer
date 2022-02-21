#ifndef _CRC_8_H
#define _CRC_8_H

unsigned char CRC_8_Compute(unsigned  char* check_data, unsigned char num_of_data);
bit CRC_8_Check(unsigned  char* p, unsigned char num_of_data, unsigned char crc_data);

#endif // !_CRC_8_H
