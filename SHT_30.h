#ifndef __SHT_30
#define __SHT_30

/// <summary>
/// SHT 30 初始化
/// </summary>
void SHT_30_Init();

/// <summary>
/// SHT 30 数据读取与处理
/// </summary>
/// <returns></returns>
bit SHT_30_DataProcess();

/// <summary>
/// SHT 30 原始数据
/// </summary>
extern unsigned char SHT_30_RAW_Data[6];

/// <summary>
/// SHT 30 温度
/// </summary>
extern float SHT_30_T;

/// <summary>
/// SHT 30 湿度
/// </summary>
extern float SHT_30_RH;

#endif // !__SHT_30
