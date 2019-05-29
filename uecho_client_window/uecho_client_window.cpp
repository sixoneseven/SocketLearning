// uecho_client_window.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>
#include<stdlib.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 30


int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET socket_clnt;
	SOCKADDR_IN addr_svr, addr_clnt;
	char message[BUF_SIZE] = { 0 };
	int addr_svr_size;
	int strLen;

	WSADATA wsaData;
	if (-1 == WSAStartup(MAKEWORD(2, 2), &wsaData))
		printf("func wsastartup Error");


	socket_clnt = socket(PF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == socket_clnt) printf("func socket Error");

	memset(&addr_svr, 0, sizeof(addr_svr));
	addr_svr.sin_family = AF_INET;
	addr_svr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr_svr.sin_port = 8000;

#if 0

	while (1){
		fputs("输入Q结束\n",stdout);
		fgets(message, sizeof(message), stdin);
		if (!strcmp(message, "Q\n") || !strcmp(message, "q\n"))
			break;
		sendto(socket_clnt, message, BUF_SIZE, 0, (SOCKADDR *)&addr_svr, sizeof(addr_svr));
		recvfrom(socket_clnt, message, BUF_SIZE, 0, (SOCKADDR *)&addr_svr, &addr_svr_size);
		printf("\nrecevFrom Svr: %s\n", message);
	}

#else
	connect(socket_clnt, (SOCKADDR *)&addr_svr, sizeof(addr_svr));
	while (1){
		fputs("输入Q结束\n", stdout);
		fgets(message, sizeof(message), stdin);
		if (!strcmp(message, "Q\n") || !strcmp(message, "q\n"))
			break;

		send(socket_clnt, message, strlen(message), 0);

		strLen=recv(socket_clnt, message,sizeof(message)-1, 0);
		message[strLen] = 0;
		printf("\nrecevFrom Svr: %s\n", message);
	}
#endif

	closesocket(socket_clnt);
	WSACleanup();
	return 0;
}

