#include "stdafx.h"
#include "SocketConnection.h"
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MD5.h"
using namespace std;

#pragma comment(lib, "ws2_32.lib")
int retVal = 0;


WORD ver = MAKEWORD(2, 2);
WSADATA wsaData;
LPHOSTENT hostEnt;
SOCKADDR_IN serverInfo;
SOCKET ClientSocket;
static int trnID;
int serverInfoSize;
SocketConnection::SocketConnection()
{
	WSAStartup(ver, (LPWSADATA)&wsaData);
	hostEnt = gethostbyname("localhost");
	if (!hostEnt)
	{
		cout << "Unable to collect gethostbyname\n";
		WSACleanup();
		throw 1;
	}


	serverInfo.sin_family = AF_INET; //The address family for the transport address. This member should always be set to AF_INET.
	serverInfo.sin_port = htons(5898); //A transport protocol port number.
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list); //An IN_ADDR structure that contains an IPv4 transport address.

	trnID = 0;

	ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "Unable to create socket\n";
		WSACleanup();
		throw 1;
	}

	serverInfoSize = sizeof(serverInfo); // Длина структуры сервера

	//connect with server
	retVal = connect(ClientSocket, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));
	if (retVal == SOCKET_ERROR)
	{
		cout << "Unable to connect\n";
		WSACleanup();
		throw 1;
	}
}


SocketConnection::~SocketConnection()
{
	closesocket(ClientSocket);
	WSACleanup();
}

void SendToServer(char* bufferToSend)
{

	retVal = sendto(ClientSocket, bufferToSend, strlen(bufferToSend), 0, (sockaddr *)&serverInfo, serverInfoSize);
	if (retVal == SOCKET_ERROR)
	{
		cout << "Unable to send\n";
		WSACleanup();
		throw 1;
	}



}

void RecvFromServer(char* bufferToRecv)
{

	retVal = recvfrom(ClientSocket, bufferToRecv, strlen(bufferToRecv), 0, (sockaddr *)&serverInfo, &serverInfoSize);
	if (retVal == SOCKET_ERROR)
	{
		cout << "Unable to send\n";
		WSACleanup();
		throw 1;
	}

}

bool SocketConnection::Connect()
{





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
		char buff[1000] = { 0 };
		DWORD haveRead = 0;
		ReadFile(Hyu, buff, 1000-1,&haveRead, NULL);
		CloseHandle(Hyu);
		buff[haveRead] = '\0';
		
		char* idBuf = new char[3];
		char* message = new char[150];
		_itoa(trnID,idBuf,9);
		strcpy(message, "TRNINF ");
		strcat(message, idBuf);
		strcat(message, " 1 ");
		strcat(message, (md5(buff)).c_str());
		SendToServer(message);

		char* recvFromBuf = new char[20];
		RecvFromServer(recvFromBuf);
		SendToServer(buff);
		
		if (FindNextFile(h, &fd) == FALSE)
			break;
	}

	return true;
}