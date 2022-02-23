#ifndef _ESP01_H
#define _ESP01_H

void ESP01_Init();

extern void (*ESP01_Event_WiFiConnected)();
extern void (*ESP01_Event_WiFiGotIP)();
extern void (*ESP01_Event_TCPServerConnected)();
extern void (*ESP01_Event_TCPClosed)();
extern void (*ESP01_Event_MsgRecvd)(const unsigned char* msg);
extern void (*ESP01_Event_Error)(const unsigned char* msg);

#endif // !_ESP01S_H
