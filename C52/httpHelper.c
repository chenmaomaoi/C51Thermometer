#include "httpHelper.h"

const unsigned char* Host;
char temp[100];

/// <summary>
/// 初始化httpHelper
/// </summary>
/// <param name="host"></param>
void httpHelper_Init(const unsigned char* host)
{
	Host = host;
}

/// <summary>
/// 拼接一个 http POST
/// </summary>
/// <param name="route">路由</param>
/// <param name="content"></param>
/// <returns></returns>
unsigned char* httpHelper_POST(const unsigned char* route, const unsigned char* content)
{
	unsigned char method[] = "POST ";
	unsigned char requestType[] = " HTTP/1.1";
	unsigned char contentType[] = "Content-Type:application/json";
	unsigned char length[] = 2;

	length[0] += strlen(content);
	temp[0] = '\0';

	strcat(temp, method);
	strcat(temp, route);
	strcat(temp, requestType);
	strcat(temp, "\r\n");

	strcat(temp, "Host:");
	strcat(temp, Host);
	strcat(temp, "\r\n");

	strcat(temp, "Content-Length:");
	strcat(temp, length);
	strcat(temp, "\r\n");

	strcat(temp, contentType);
	strcat(temp, "\r\n");

	strcat(temp, "\r\n");
	strcat(temp, '\"');
	strcat(temp, content);
	strcat(temp, '\"');
	strcat(temp, "\r\n");

	return temp;
}

/// <summary>
/// 拼接一个 http GET
/// </summary>
/// <param name="route">路由</param>
/// <param name="content"></param>
/// <returns></returns>
unsigned char* httpHelper_GET(const unsigned char* route)
{
	unsigned char method[] = "GET ";
	unsigned char requestType[] = " HTTP/1.1";

	temp[0] = '\0';

	strcat(temp, method);
	strcat(temp, route);
	strcat(temp, requestType);
	strcat(temp, "\r\n");

	strcat(temp, "Host:");
	strcat(temp, Host);
	strcat(temp, "\r\n");

	return temp;
}
