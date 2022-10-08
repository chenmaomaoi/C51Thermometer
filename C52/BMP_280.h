#pragma once
#include "IIC.h"

/// <summary>
/// BMP 280 初始化，前置条件：IIC初始化
/// </summary>
void BMP_280_Init();

/// <summary>
/// BMP 280 数据读取与处理
/// </summary>
/// <returns></returns>
bit BMP_280_DataProcess();