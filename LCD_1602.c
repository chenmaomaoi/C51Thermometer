#include "REG52.H"
#include "IIC.h"
#include "LCD_1602.h"

/// <summary>
/// 切换到当前设备
/// </summary>
/// <returns></returns>
void switch_device()
{
    IIC_Start();
    IIC_Write_Byte(0x4e);
    IIC_Write_Byte(0x27);
}

/// <summary>
/// 写指令
/// </summary>
/// <param name="comm"></param>
void write_command(char comm)
{
    char tmp;
    tmp = comm & 0xF0;  //仅保留最高位为原始状态，计算结果：0x80,0x00，最高位保持1，最终0x80
    tmp |= 0x0C;        //保留高4位为指令的高四位，低四位为 (null)1, EN = 1, RS = 0, RW = 0

    //tmp 最终结果：0x8c
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);

    tmp = (comm & 0x0F) << 4; //将指令的低四位 送到高位置保存
    tmp |= 0x0C;              // (null)1, EN = 1, RS = 0, RW = 0
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);
}

/// <summary>
/// 写字符
/// </summary>
/// <param name="_ch"></param>
void write_char(char ch)
{
    char tmp;
    tmp = ch & 0xF0;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);

    tmp = (ch & 0x0F) << 4;
    tmp |= 0x0D; // RS = 0, RW = 0, EN = 1
    IIC_Write_Byte(tmp);

    tmp &= 0xFB; // Make EN = 0
    IIC_Write_Byte(tmp);
}

/// <summary>
/// 初始化
/// </summary>
void LCD_1602_Init()
{
    switch_device();
    write_command(0x33); //将8位总线转为4位总线
    write_command(0x32); //
    write_command(0x28); // 4位数据线，显示2行，5*7点阵字符  ！如果是0x38  则为8位数据线，显示2行，5*7点阵字符
    write_command(0x0C); // 开显示，关闭光标，不闪烁
    write_command(0x06); // 设定输入方式，增量不位移
    write_command(0x01); // 清屏
    IIC_Stop();
}

/// <summary>
/// 清屏
/// </summary>
void LCD_1602_Clear()
{
    switch_device();
    write_command(0x01); // 清屏
    IIC_Stop();
}

/// <summary>
/// 显示字符串
/// <para>带自动换行</para>
/// </summary>
/// <param name="row">行</param>
/// <param name="column">列</param>
/// <param name="_str"></param>
void LCD_1602_ShowString(unsigned char row, unsigned char column, const unsigned char* str)
{
    unsigned char count = 16;
    count -= column;

    switch_device();

    if (row == 0)
    {
        write_command(0x80 | column);
    }
    if (row == 1)
    {
        write_command(0xc0 | column);
    }
    //输出字符串
    while (*str)
    {
        //自动换行
        if (!row && !count)
        {
            write_command(0xc0 | 0);
        }
        count--;

        write_char(*str++);
    }

    IIC_Stop();
}
