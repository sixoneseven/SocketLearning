// TCP-IPTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string.h>
#include<stdio.h>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) printf("func WSAStartup Error!\n");


	/*inet_address*/
	{
		char * addr = "127.212.124.78";
		unsigned long conv_addr = inet_addr(addr);
		if (INADDR_NONE == conv_addr) printf("func inet_addr Error!\n");
		else printf("Network ordered integer addr: %#lx \n", conv_addr);
	}
	
	
	/*inet_aton*/
	{
		struct sockaddr_in addr;
		char *strPtr;
		char strArr[20];

		addr.sin_addr.S_un.S_addr = htonl(0x1020304);
		strPtr = inet_ntoa(addr.sin_addr);
		strcpy(strArr, strPtr);
		printf("Dotted-Decimal notation3 %s \n", strArr);
	}


	WSACleanup();
	getchar();
	return 0;
}

