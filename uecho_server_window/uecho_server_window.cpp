// uecho_server_window.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>
#include<stdlib.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 30


int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET socket_svr;
	SOCKADDR_IN addr_svr, addr_clnt;
	char message[BUF_SIZE] = { 0 };
	int recvLen;

	WSADATA wsaData;
	if (-1 == WSAStartup(MAKEWORD(2, 2), &wsaData))
		printf("func wsastartup Error");

	socket_svr = socket(PF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == socket_svr) printf("func socket Error");

	memset(&addr_svr, 0, sizeof(addr_svr));
	addr_svr.sin_family = AF_INET;
	addr_svr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr_svr.sin_port = 8000;

	if(INVALID_SOCKET==bind(socket_svr, (sockaddr *)&addr_svr, sizeof(addr_svr)))
		printf("func bind Error");

	while (1)
	{
#if 0
		recvfrom(socket_svr, message, BUF_SIZE, 0, (SOCKADDR *)&addr_clnt, &recvLen);
		if(0!=strlen(message))printf("recv: %s\n", message);
		sendto(socket_svr, message, BUFSIZ, 0, (SOCKADDR *)&addr_clnt, recvLen);
		memset(message,0,sizeof(message));
#else
		recvLen=recv(socket_svr, message, BUF_SIZE, 0);
		send(socket_svr, message, recvLen, 0);
#endif
	}
	closesocket(socket_svr);
	WSACleanup();

	return 0;
}

