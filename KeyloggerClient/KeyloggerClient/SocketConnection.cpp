#include "stdafx.h"
#include "SocketConnection.h"
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")
int retVal = 0;





SocketConnection::SocketConnection()
{
}


SocketConnection::~SocketConnection()
{
}

bool SocketConnection::Connect()
{
	//I DON'T KNOW
	WORD ver = MAKEWORD(2, 2);

	//init library for using
	WSADATA wsaData;


	//getting host information corresponding to a host name from a host database
	LPHOSTENT hostEnt;
	WSAStartup(ver, (LPWSADATA)&wsaData);

	hostEnt = gethostbyname("localhost");
	if (!hostEnt)
	{
		cout << "Unable to collect gethostbyname\n";
		WSACleanup();
		return false;
	}

	//create socket
	SOCKET ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "Unable to create socket\n";
		WSACleanup();
		return false;
	}

	//this structure specifies a transport address and port for the AF_INET address family
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET; //The address family for the transport address. This member should always be set to AF_INET.
	serverInfo.sin_port = htons(5898); //A transport protocol port number.
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list); //An IN_ADDR structure that contains an IPv4 transport address.

	int serverInfoSize = sizeof(serverInfo); // Длина структуры сервера

	//connect with server
	retVal = connect(ClientSocket, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));
	if (retVal == SOCKET_ERROR)
	{
		cout << "Unable to connect\n";
		WSACleanup();
		return false;
	}


	WIN32_FIND_DATA fd;

	HANDLE h = FindFirstFile(L"..\\logs\\*.klf", &fd);
	while (1)
	{
		std::locale loc("russian");
		//ifstream file;
		wchar_t sourceFile[100];
		wcscpy(sourceFile, L"..\\logs\\");
		wcscat(sourceFile, fd.cFileName);

		HANDLE Hyu = CreateFile(sourceFile,                // name of the write
			GENERIC_READ,          // open for writing
			0,                      // do not share
			NULL,                   // default security
			OPEN_EXISTING,             // create new file only
			FILE_ATTRIBUTE_NORMAL,  // normal file
			NULL);                  // no attr. template
		//HANDLE Hyu = CreateFile(sourceFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
		wchar_t buff[1000] = { 0 };
		DWORD haveRead = 0;
		ReadFile(Hyu, buff, 1000-1,&haveRead, NULL);
		CloseHandle(Hyu);
		buff[haveRead] = '\0';
		
		//file.open(sourceFile);
		//wstring lineToSend, tempLine; 
		//stringstream ss;
		//ss << file.rdbuf();
		//wstring ws = wstring((wchar_t *)ss.str().c_str());
		////file.close();

		//
		//int ssize = WideCharToMultiByte(CP_UTF8, NULL, buff, (int)haveRead, NULL, NULL, NULL, NULL);
		//char * t = new char[ssize];
		//WideCharToMultiByte(CP_UTF8, NULL, buff, (int)haveRead, t, ssize, NULL, NULL);
		//


		//retVal = sendto(ClientSocket, t,ssize, 0, (sockaddr *)&serverInfo, serverInfoSize); // В конец добавили структуру с инфой о сервере и длину этой структуры
		retVal = sendto(ClientSocket, (char*)((void*)buff), wcslen(buff)*sizeof(wchar_t), 0, (sockaddr *)&serverInfo, serverInfoSize);
		if (retVal == SOCKET_ERROR)
		{
			cout << "Unable to send\n";
			WSACleanup();
			return false;
		}
		
		if (FindNextFile(h, &fd) == FALSE)
			break;
	}
	




	//closing soket
	closesocket(ClientSocket);
	WSACleanup();
	return true;
}