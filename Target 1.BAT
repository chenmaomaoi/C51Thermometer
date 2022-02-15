SET C51INC=C:\Keil\C51\Inc;C:\Keil\C51\Inc\STC
SET C51LIB=C:\Keil\C51\Lib
SET CPU_TYPE=STC89C52RC Series
SET CPU_VENDOR=STC
SET UV2_TARGET=Target 1
SET CPU_XTAL=0x00A8C000
"C:\Keil\C51\BIN\A51.EXE" @".\Objects\STARTUP._ia"
"C:\Keil\C51\BIN\C51.EXE" @".\Objects\main.__i"
"C:\Keil\C51\BIN\C51.EXE" @".\Objects\LCD_1602.__i"
"C:\Keil\C51\BIN\C51.EXE" @".\Objects\IIC.__i"
"C:\Keil\C51\BIN\BL51.EXE" @".\Objects\mainProj.lnp"
"C:\Keil\C51\BIN\OH51.EXE" ".\Objects\mainProj" 
