// echo_client_window.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>
#include<stdio.h>
#include<stdlib.h>

#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 1024
#define INTSIZE 4


int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET	socket_clnt;
	SOCKADDR_IN sockaddr_svr;
	WSADATA wsaData;
	char message[BUF_SIZE] = { 0 };
	int cnt = 0;
	int buff;
	int ret;

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
		printf("------connet------\n");
	/*
	while (1){
		fputs("input Q to quit\n", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "Q\n") || !strcmp(message, "q\n"))
			break;

		sendLen=send(socket_clnt, message, strlen(message), 0);
		recvLen = 0;
		while (recvLen < sendLen){
			recv_cnt = recv(socket_clnt, message, BUF_SIZE - 1, 0);
			if (-1 == recv_cnt) printf("func recv Error");
			recvLen += recv_cnt;
		}
		message[recvLen] = 0;
		printf("Message from svr: %s\n", message);
	}
	*/

	
	puts("数据个数:\n");
	scanf("%d", &cnt);
	message[0] = (char)cnt;

	puts("请输入数据:\n");
	for (int i = 0; i < cnt; i++)
	{
		scanf("%d", &buff);
		memcpy(&message[i*INTSIZE + 1], &buff, INTSIZE);
	}
	puts("输入符号:\n");
	getchar(); //不加这个会将FL（\10）输入到message中
	scanf("%c", &message[cnt*INTSIZE + 1]);

	send(socket_clnt, message, cnt * INTSIZE + 2, 0);
	recv(socket_clnt, (char*)&ret, INTSIZE, 0);
	printf("计算结果：%d\n", ret);

	closesocket(socket_clnt);
	WSACleanup();
	system("pause");
	return 0;
}

