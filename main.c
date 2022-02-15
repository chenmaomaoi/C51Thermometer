#include "STC89C5xRC.h"
#include "intrins.h"
#include "IIC.h"
#include "LCD_1602.h"

void main()
{
    char mych[16] = "Hello World!";

    IIC_Init();
    LCD_1602_Init();
    LCD_1602_ShowString(0, 0, mych);
    while (1)
    {
    }
}
