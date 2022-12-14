#ifndef _HTTPHELPER_H
#define _HTTPHELPER_H

#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

#endif // !_HTTPHELPER_H

void httpHelper_Init(const unsigned char* host);

unsigned char* httpHelper_POST(const unsigned char* route, const unsigned char* content);

unsigned char* httpHelper_GET(const unsigned char* route);
