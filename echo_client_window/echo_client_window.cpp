// echo_client_window.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>
#include<stdio.h>
#include<stdlib.h>

#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 1024



int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET	socket_clnt;
	SOCKADDR_IN sockaddr_svr;
	WSADATA wsaData;
	char message[BUF_SIZE] = { 0 };
	int strLen;

	if (-1 == WSAStartup(MAKEWORD(2, 2), &wsaData))
		printf("func WSAStartup Error");

	socket_clnt = socket(PF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == socket_clnt) printf("func socket Error!\n");

	memset(&sockaddr_svr, 0, sizeof(SOCKADDR));
	sockaddr_svr.sin_family = AF_INET;
	sockaddr_svr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //该IP地址送的是本机的IP地址
	sockaddr_svr.sin_port = 9190;

	if(SOCKET_ERROR==connect(socket_clnt, (SOCKADDR *)&sockaddr_svr, sizeof(sockaddr_svr)))
		printf("func connetc Error\n");
	else 
		printf("connet------\n");

	while (1){
		fputs("input Q to quit\n", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "Q\n") || !strcmp(message, "q\n"))
			break;

		send(socket_clnt, message, strlen(message), 0);
		
		strLen = recv(socket_clnt, message, BUF_SIZE - 1, 0);
		message[strLen] = 0;
		printf("Message froom svr: %s\n", message);
	}

	closesocket(socket_clnt);

	WSACleanup();
	return 0;
}

