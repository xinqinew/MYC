// 13-InJectDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

HWND GetGameHwnd()
{
	HWND 窗口句柄 = FindWindowA("WTWindow","Wow");
	return 窗口句柄;
}
UINT64 注入DLL(char* dllFullPathName)
{
	UINT64 nRet64 =0;
	DWORD lpExitCode=0;
	HWND 窗口句柄 =GetGameHwnd();

	if (窗口句柄)
	{

		DWORD 进程PID =0;
		GetWindowThreadProcessId(窗口句柄,&进程PID);
		HANDLE 进程句柄 = OpenProcess(PROCESS_ALL_ACCESS,  FALSE,进程PID);
		if (进程句柄)
		{

			DWORD tid =0;
			//读内存

			//创建远线程 调用GetModuleHandleA
			//__in      HANDLE hProcess,
			//__in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
			//__in      SIZE_T dwStackSize,
			//__in      LPTHREAD_START_ROUTINE lpStartAddress,
			//__in_opt  LPVOID lpParameter,
			//__in      DWORD dwCreationFlags,
			//__out_opt LPDWORD lpThreadId
			//在目标进程分配内存
			LPVOID 目标进程内存地址=VirtualAllocEx(进程句柄,NULL,1024,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
			SIZE_T nWriten =0;//用于返回实际写入字节数
			//DWORD nWriten =0;//用于返回实际写入字节数
			//写入要注入的DLL的路径
			BOOL br = WriteProcessMemory(进程句柄,目标进程内存地址,dllFullPathName,strlen(dllFullPathName)+1, &nWriten);
			HANDLE ht= CreateRemoteThread( 
				进程句柄, 
				NULL,
				0,//0x400000
				(LPTHREAD_START_ROUTINE)LoadLibraryA,//LoadLibraryA("c:\\123.dll")
				目标进程内存地址,//LoadLibraryA(目标进程内存地址)
				0,
				&tid
				);
			printf("窗口句柄=%p tid=%X \r\n",窗口句柄,tid);
			//printf("错误代码=%d \r\n", GetLastError());
			WaitForSingleObject( ht,0xFFFFFFFF);//1秒

			GetExitCodeThread( ht, &lpExitCode);
			printf("窗口句柄=%p lpExitCode=%X \r\n",窗口句柄,lpExitCode);//0x666888
		}
	}  
	//nRet64 = 0x100000000+lpExitCode;
	nRet64 = lpExitCode;
	return nRet64;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//获取当前目录
	//当前目录路径+DLL名字
	char 当前目录[256] ={0};
	GetCurrentDirectoryA(256,当前目录);
	//拼接DLL全路径名
	strcat_s( 当前目录,"\\MFCDLL.dll");
	printf("要注入的DLL全路径名为：%s \r\n",当前目录);
	//注入DLL
	注入DLL(当前目录);
	Sleep(100);
	// getchar();//等待

	return 0;
}

