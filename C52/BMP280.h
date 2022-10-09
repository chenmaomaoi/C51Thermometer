#ifndef _BMP280_H
#define _BMP280_H

#ifndef _IIC_H
#include "IIC.h"
#endif // !_IIC_H

/// <summary>
/// BMP 280 初始化，前置条件：IIC初始化
/// </summary>
void BMP280_Init();

/// <summary>
/// BMP 280 数据读取与处理
/// </summary>
/// <returns></returns>
bit BMP280_DataProcess();

#endif // !_BMP280_H