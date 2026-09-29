// DLLinjection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <winternl.h>

int main()
{
	const char* ProcessPath = "E:\\tool\\code\\lastdance.exe";
	//const char* DLL_Path = "E:\\tool\\code\\hello-world-x86.dll";
	const char* DLL_Path = "C:\\Users\\Acer-PC\\source\\repos\\check_check_check\\x64\\Debug\\check_check_check.dll";
	LPSTARTUPINFOA Start_Up_Info = new STARTUPINFOA();
	PROCESS_BASIC_INFORMATION Basic_info = {0};
	PPROCESS_INFORMATION Process_info = new PROCESS_INFORMATION();
	DWORD dwReturnLength = 0; 
	DWORD size = strlen(ProcessPath);
	DWORD imagebase_offset = 0;
	DWORD Image_Base;
	LPVOID DLL_Mem_Location;
	PVOID lmaolmao = new PVOID();
	DWORD test;

	CreateProcessA(ProcessPath,0,0,0,TRUE, CREATE_SUSPENDED,0,0,Start_Up_Info,Process_info);
	//LoadLibraryA("C:\\Users\\Acer-PC\\Desktop\\ntdll.lib");
	
	
	ResumeThread(Process_info->hThread);

	DLL_Mem_Location = VirtualAllocEx(Process_info->hProcess, 0, strlen(DLL_Path), MEM_COMMIT , PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(Process_info->hProcess, DLL_Mem_Location, DLL_Path, strlen(DLL_Path), 0);
	//PVOID DLL_HDL = LoadLibraryA(DLL_Path);
	//DWORD a = strlen(DLL_Path);
	PTHREAD_START_ROUTINE threatStartRoutineAddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
	CreateRemoteThread(Process_info->hProcess, NULL, 0, threatStartRoutineAddress, DLL_Mem_Location, 0, NULL);


	CloseHandle(Process_info->hProcess);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
