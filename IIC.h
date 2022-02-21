#ifndef __IIC_H
#define __IIC_H

void IIC_Init();
void IIC_Start();
void IIC_Stop();
bit IIC_Write_byte(unsigned char _data);
unsigned char IIC_Read_byte(bit _ack);

#endif
