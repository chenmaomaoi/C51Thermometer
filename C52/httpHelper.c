#include "httpHelper.h"

unsigned char* Host;

unsigned char* Route;

const unsigned char Line3_ContentType[] = "Content-Type:application/json";

/// <summary>
/// 第三行：载荷长度
/// </summary>
unsigned char Line3_ContentLength[];

/// <summary>
/// 设置Host
/// </summary>
/// <param name="host"></param>
void httpHelper_SetHost(const unsigned char* host)
{
	Host = host;

	//Line2_Host[0] = '\0';

	//strcat(Line2_Host, "Host:");
	//strcat(Line2_Host, host);
	//strcat(Line2_Host, "\r\n\0");
}

///// <summary>
///// 设置请求路由
///// </summary>
///// <param name="route"></param>
//void httpHelper_SetRoute(const unsigned char* route)
//{
//	Line1_requestMethod[0] = '\0';
//
//	strcat(Line1_requestMethod, "POST ");
//	strcat(Line1_requestMethod, route);
//	strcat(Line1_requestMethod, " HTTP/1.1");
//	strcat(Line1_requestMethod, "\r\n\0");
//}

void httpHelper_SetCountent(const unsigned char* content)
{
}

const unsigned char* getLine1()
{
	unsigned char temp[] = '\0';

	strcat(temp, "POST ");
	strcat(temp, Route);
	strcat(temp, " HTTP/1.1");
	strcat(temp, "\r\n\0");
	return temp;
}

const unsigned char* getLine2()
{
	unsigned char temp[] = '\0';

	strcat(temp, "Host:");
	strcat(temp, Host);
	strcat(temp, "\r\n\0");
	return temp;
}

void httpHelper_POST(const char* route, void (*UART_SendStr)(const unsigned char* str))
{
	(*UART_SendStr)(getLine1());
	(*UART_SendStr)(getLine2());
	//UART_SendStr(Line3_ContentType);
}

///// <summary>
///// 拼接一个 http POST
///// </summary>
///// <param name="route">路由</param>
///// <param name="content"></param>
///// <returns></returns>
//unsigned char* httpHelper_POST(const unsigned char* route, const unsigned char* content, const char* length)
//{
//	unsigned char method[] = "POST ";
//	unsigned char requestType[] = " HTTP/1.1";
//	unsigned char contentType[] = "Content-Type:application/json";
//
//	temp[0] = '\0';
//
//	strcat(temp, method);
//	strcat(temp, route);
//	strcat(temp, requestType);
//	strcat(temp, "\r\n");
//
//	strcat(temp, "Host:");
//	strcat(temp, Host);
//	strcat(temp, "\r\n");
//
//	strcat(temp, "Content-Length:");
//	strcat(temp, length);
//	strcat(temp, "\r\n");
//
//	strcat(temp, contentType);
//	strcat(temp, "\r\n");
//
//	strcat(temp, "\r\n");
//	strcat(temp, '\"');
//	strcat(temp, content);
//	strcat(temp, '\"');
//	strcat(temp, "\r\n");
//
//	return temp;
//}
//
///// <summary>
///// 拼接一个 http GET
///// </summary>
///// <param name="route">路由</param>
///// <param name="content"></param>
///// <returns></returns>
//unsigned char* httpHelper_GET(const unsigned char* route)
//{
//	unsigned char method[] = "GET ";
//	unsigned char requestType[] = " HTTP/1.1";
//
//	temp[0] = '\0';
//
//	strcat(temp, method);
//	strcat(temp, route);
//	strcat(temp, requestType);
//	strcat(temp, "\r\n");
//
//	strcat(temp, "Host:");
//	strcat(temp, Host);
//	strcat(temp, "\r\n");
//
//	return temp;
//}
