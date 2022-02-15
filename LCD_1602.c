#include "STC89C5xRC.h"
#include "IIC.h"
#include "LCD_1602.h"

#define _LCD_1602_type_id 0x4e
#define _LCD_1602_device_id 0x27

void LCD_1602_Init();
void LCD_1602_Clear();
void LCD_1602_write_command(char comm);
void LCD_1602_write_data(char ch);
void LCD_1602_ShowString(unsigned char x, unsigned char y, unsigned char* str);

/// <summary>
/// 初始化 LCD 1602
/// </summary>
void LCD_1602_Init()
{
    IIC_Switch_Device(_LCD_1602_type_id, _LCD_1602_device_id);
    LCD_1602_write_command(0x33); //将8位总线转为4位总线
    LCD_1602_write_command(0x32); //
    LCD_1602_write_command(0x28); // 4位数据线，显示2行，5*7点阵字符  ！如果是0x38  则为8位数据线，显示2行，5*7点阵字符
    LCD_1602_write_command(0x0C); // 开显示，关闭光标，不闪烁
    LCD_1602_write_command(0x06); // 设定输入方式，增量不位移
    LCD_1602_write_command(0x01); // 清屏
}

/// <summary>
/// 清屏
/// </summary>
void LCD_1602_Clear()
{
    IIC_Switch_Device(_LCD_1602_type_id, _LCD_1602_device_id);
    LCD_1602_write_command(0x01); // 清屏
}

/// <summary>
/// LCD 1602 写指令
/// </summary>
/// <param name="comm">指令</param>
void LCD_1602_write_command(char comm)
{
    char tmp;
    tmp = comm & 0xF0;  //仅保留最高位为原始状态，计算结果：0x80,0x00，最高位保持1，最终0x80
    tmp |= 0x0C;        //保留高4位为指令的高四位，低四位为 (null)1, EN = 1, RS = 0, RW = 0
    
    //tmp 最终结果：0x8c
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);

    tmp = (comm & 0x0F) << 4; //将指令的低四位 送到高位置保存
    tmp |= 0x0C;              // (null)1, EN = 1, RS = 0, RW = 0
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);
}

/// <summary>
/// LCD 写字符
/// </summary>
/// <param name="ch"></param>
void LCD_1602_write_data(char ch)
{
    char tmp;
    tmp = ch & 0xF0;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);

    tmp = (ch & 0x0F) << 4;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_byte(tmp);
}

/// <summary>
/// 显示字符串
/// </summary>
/// <param name="x">行</param>
/// <param name="y">列</param>
/// <param name="str"></param>
void LCD_1602_ShowString(unsigned char x, unsigned char y, unsigned char* str)
{
    IIC_Switch_Device(_LCD_1602_type_id, _LCD_1602_device_id);

    if (x == 0)
    {
        LCD_1602_write_command(0x80 | y);
    }
    if (x == 1)
    {
        LCD_1602_write_command(0xc0 | y);
    }
    //输出字符串
    while (*str != '\0')
    {
        LCD_1602_write_data(*str);
        str++;
    }
}