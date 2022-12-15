#ifndef _HTTPHELPER_H
#define _HTTPHELPER_H

#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

#ifndef _STDIO_H
#include "stdio.h"
#endif // !_STDIO_H

#endif // !_HTTPHELPER_H

void httpHelper_SetHost(const unsigned char* host);

extern void httpHelper_POST(const char* route, void (*UART_SendStr)(const unsigned char* str));

//void httpHelper_SetRoute(const unsigned char* route);

//void httpHelper_POST(void (*UART_SendStr)(const unsigned char* str));
