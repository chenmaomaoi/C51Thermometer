#ifndef _SHT30_H
#define _SHT30_H

#include "CRC8.h"
#include "string.h"

/// <summary>
/// SHT30 初始化
/// </summary>
void SHT30_Init(void (*iic_start)(), void (*iic_stop)(), unsigned char (*iic_read_byte)(unsigned char), unsigned char (*iic_write_byte)(unsigned char));

/// <summary>
/// SHT30 数据读取与处理
/// </summary>
/// <returns></returns>
unsigned char SHT30_DataProcess();

/// <summary>
/// SHT30 原始数据(实际为SHT_30_RAW_Data[6])
/// </summary>
extern unsigned char SHT30_RAW_Data[7];

/// <summary>
/// SHT30 温度
/// </summary>
extern float SHT30_T;

extern unsigned int SHT30_T_uint16;

/// <summary>
/// SHT30 湿度
/// </summary>
extern float SHT30_RH;

extern unsigned int SHT30_RH_uint16;

#endif
