// echo_server_window.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<WinSock2.h>


#pragma comment(lib,"ws2_32.lib")


#define BUF_SIZE 1024

int _tmain(int argc, _TCHAR* argv[])
{
	SOCKET socket_svr,socket_clnt;
	WSADATA wsaData;
	SOCKADDR_IN svr_addr, clnt_addr; 
	char message[BUF_SIZE] = { 0 };
	int clnt_addrlen;
	int strLen;

	if(-1==WSAStartup(MAKEWORD(2, 2), &wsaData))
		printf("func: WSAStartup Error");
	
	socket_svr = socket(PF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == socket_svr)
		printf("func: socket Error");


	svr_addr.sin_family = AF_INET; //address family IPV4
	svr_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //IP地址跟主机一致
	svr_addr.sin_port = 9190;
	
	if(-1==bind(socket_svr, (SOCKADDR *)&svr_addr, sizeof(SOCKADDR)))
		printf("func bind Error");

	if(-1==listen(socket_svr, 5))
		printf("func listen Error");

	clnt_addrlen = sizeof(SOCKADDR);
	for (int  i = 0; i < 5; i++)
	{
		socket_clnt = accept(socket_svr, (SOCKADDR *)&clnt_addr, &clnt_addrlen);
		if (-1 == socket_clnt) printf("func accept Error");
		else printf("SVR: Connet Clinet: %d \n", i);
		
		while (0 != (strLen = recv(socket_clnt, message, BUF_SIZE, 0)))
			send(socket_clnt, message, strLen,0);
		
		closesocket(socket_clnt);
	}

	closesocket(socket_svr);
	
	WSACleanup();
	return 0;
}

