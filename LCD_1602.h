#ifndef __LCD_1602_H
#define __LCD_1602_H

#include "STC89C5xRC.h"
#include "intrins.h"

/// <summary>
/// 初始化 LCD 1602
/// </summary>
void LCD_1602_Init();

/// <summary>
/// 清屏
/// </summary>
void LCD_1602_Clear();

/// <summary>
/// 显示字符串
/// </summary>
/// <param name="x">行</param>
/// <param name="y">列</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char x, unsigned char y, unsigned char* str);

#endif
