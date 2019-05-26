// char_int_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#define BUFSIZE 1024
#define OPSIZE 4
#pragma warning(disable:4996)


int _tmain(int argc, _TCHAR* argv[])
{
	char opmsg[BUFSIZE] = { 0 };
	int opnd_cnt;
	int buff;
	double dbuff;

#if 0
	fputs("输入操作数:", stdout);
	scanf("%d", &opnd_cnt);
	opmsg[0] = (char)opnd_cnt;

	for (int  i = 0; i < opnd_cnt; i++)
	{
	//	scanf("%d", (int *)&opmsg[i*OPSIZE+1]);
		scanf("%lf", &dbuff);
	//	itoa(buff, &opmsg[i*OPSIZE + 1], 10);
	//	sprintf(&opmsg[i*OPSIZE + 1], "%d", buff);
		memcpy(&opmsg[i*OPSIZE + 1], &dbuff, sizeof(double));
		printf("%b");
	}
	
	/*输出*/
	
		memcpy(&dbuff, &opmsg[1], sizeof(double));
		printf("Return: %lf ", dbuff);
#endif
	char sig;
	scanf("%c", &sig);

	system("pause");
	return 0;
}

