#ifndef _LCD_1602_H
#define _LCD_1602_H

#ifndef _IIC_H
#include "IIC.h"
#endif // !_IIC_H

#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

/// <summary>
/// 初始化 LCD 1602，前置条件：IIC初始化
/// </summary>
void LCD_1602_Init();

/// <summary>
/// 清屏
/// </summary>
void LCD_1602_Clear();

/// <summary>
/// 清楚行
/// </summary>
void LCD_1602_Clear_Row(unsigned char row);

/// <summary>
/// 显示字符串
/// </summary>
/// <param name="row">行</param>
/// <param name="column">列</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char row, unsigned char column, const unsigned char* str);

#endif
