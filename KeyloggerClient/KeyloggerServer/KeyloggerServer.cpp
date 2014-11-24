#include "stdafx.h"
#include <winsock2.h>
#include <iostream>
#include <fstream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, ".1251");
	int retVal = 0;

	//I DON'T KNOW
	WORD sockVer = MAKEWORD(2, 2);

	//init library for using
	WSADATA wsaData;
	WSAStartup(sockVer, &wsaData);

	//create soket
	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM = UDP
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Unable to create socket\n";
		WSACleanup();
		return SOCKET_ERROR;
	}

	//this structure specifies a transport address and port for the AF_INET address family
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET; //The address family for the transport address. This member should always be set to AF_INET.
	serverInfo.sin_port = htons(5898); //A transport protocol port number.
	serverInfo.sin_addr.s_addr = INADDR_ANY; //An IN_ADDR structure that contains an IPv4 transport address.

	retVal = bind(ServerSocket, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));
	if (retVal == SOCKET_ERROR)
	{
		cout << "Unable to bind\n";
		WSACleanup();
		return SOCKET_ERROR;
	}

	char Request[1000];

	while (true)
	{

		sockaddr_in client; // Структура, куда запишется инфа о клиенте (ip шник, все такое)
		int clientSize = sizeof(client); // Размер этой структуры
		retVal = recvfrom(ServerSocket, Request, sizeof(Request), 0, (sockaddr *)&client, &clientSize); // В конце функции добавили пустую структуру, куда запишется инфа от отправителя и длину структуры
		if (retVal == SOCKET_ERROR)
		{
			DWORD sex = GetLastError();
			cout << "Unable to recvfrom\n";
			return SOCKET_ERROR;
		}

		Request[retVal] = '\0';
		wchar_t * sex = (wchar_t*)((void*)(Request));
		int ssize=MultiByteToWideChar(CP_ACP, NULL, Request, sizeof(Request), NULL, NULL);
		wchar_t* test = new wchar_t[ssize];
		MultiByteToWideChar(CP_ACP, NULL, Request, sizeof(Request), test, ssize);
		test[retVal*sizeof(wchar_t)] = '\0';
		wofstream f;

		HANDLE logFile = CreateFile(L"log.txt", FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, 0, NULL);
		DWORD l = GetLastError();
		DWORD numb = { 0 };
		WriteFile(logFile, test, retVal*sizeof(wchar_t), &numb, NULL);
		CloseHandle(logFile);

	}

	closesocket(ServerSocket);

	WSACleanup();
	return 0;
}

