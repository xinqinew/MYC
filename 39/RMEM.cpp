#include "stdafx.h"
#include <Windows.h>

HWND GetGameHwnd()
{
	HWND 窗口句柄 = FindWindowA("WTWindow","Wow");
	return 窗口句柄;
}

UINT64 W4(UINT64 地址,UINT64 v32)//dword()
{
	//1 FindWindow获取目标进程 窗口句柄
	//2 OpenProcess(打开权限,false,进程PID) 获取目标进程的句柄 而且这个句柄 需要有读内存的权限
	//3 ReadprocessMemory()
	//4 CloseHandle 释放掉进程句柄
	UINT64 返回值=0;
	HWND 窗口句柄=GetGameHwnd();
	if(窗口句柄) 
	{
		DWORD 进程PID = 0;
		GetWindowThreadProcessId(窗口句柄,&进程PID);
		HANDLE 进程句柄=OpenProcess(PROCESS_ALL_ACCESS,FALSE,进程PID);
		if(进程句柄)
		{
			返回值=WriteProcessMemory(进程句柄,(LPVOID)地址,&v32,4,NULL);
		}
	}
	return 返回值;
}
UINT64 W8(UINT64 地址,UINT64 v64)//dword()
{
	//1 FindWindow获取目标进程 窗口句柄
	//2 OpenProcess(打开权限,false,进程PID) 获取目标进程的句柄 而且这个句柄 需要有读内存的权限
	//3 ReadprocessMemory()
	//4 CloseHandle 释放掉进程句柄
	UINT64 返回值=0;
	HWND 窗口句柄=GetGameHwnd();
	if(窗口句柄) 
	{
		DWORD 进程PID = 0;
		GetWindowThreadProcessId(窗口句柄,&进程PID);
		HANDLE 进程句柄=OpenProcess(PROCESS_ALL_ACCESS,FALSE,进程PID);
		if(进程句柄)
		{
			返回值=WriteProcessMemory(进程句柄,(LPVOID)地址,&v64,8,NULL);
		}
	}
	return 返回值;
}


//dword(qword(14000000+8A85)+160)
//typedef UINT64 QWORD;
UINT64 R8(UINT64 地址)  //dword()
{
	//跨进程读写
	//1 FindWindow() 获取目标进程 窗口句柄
	//2 OpenProcess(打开权限，false，进程pid) 获取目标进程的句柄 而且这个句柄需要有读内存的权限
	//3 ReadProcessMemory()
	//4 CloseHandle() 释放掉进程句柄
	UINT64 返回值=0;
	HWND 窗口句柄 =GetGameHwnd();

	if (窗口句柄)
	{
		DWORD 进程PID =0;
		GetWindowThreadProcessId(窗口句柄,&进程PID);
		HANDLE 进程句柄 = OpenProcess(PROCESS_ALL_ACCESS,  FALSE,进程PID);
		if (进程句柄)
		{
			//读内存
			ReadProcessMemory(进程句柄,(LPVOID)地址,&返回值,8,NULL);
		}
	}

	return 返回值;
}
DWORD R4(UINT64 地址)  //R8(UINT_PTR 地址)  R8(UINT64 地址)
{
	return (DWORD)R8(地址);
}
float R4F(UINT64 地址)  //dword()
{
	float 返回值=0;
	HWND 窗口句柄 =GetGameHwnd();

	if (窗口句柄)
	{
		DWORD 进程PID =0;
		GetWindowThreadProcessId(窗口句柄,&进程PID);
		HANDLE 进程句柄 = OpenProcess(PROCESS_ALL_ACCESS,  FALSE,进程PID);
		if (进程句柄)
		{
			//读内存
			ReadProcessMemory(进程句柄,(LPVOID)地址,&返回值,sizeof(float),NULL);
		}
	}

	return 返回值;
}
UINT64 GetGameExeBase()
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
			HANDLE ht= CreateRemoteThread( 
				进程句柄, 
				NULL,
				0,//0x400000
				(LPTHREAD_START_ROUTINE)GetModuleHandleA,
				NULL,
				0,
				&tid
				);
			//printf("错误代码=%d \r\n", GetLastError());
			WaitForSingleObject( ht,1000);

			GetExitCodeThread( ht, &lpExitCode);
			printf("窗口句柄=%p,lpExitCode=%X \r\n",窗口句柄,lpExitCode);
		}
	}  
	nRet64 = 0x100000000+lpExitCode;//合成模块基址
	// nRet64 = lpExitCode;
	return nRet64;
}
UINT64 获取对象地址()
{
	//获取模块基址
	//HMODULE hdll1 = LoadLibraryA("Wow.exe");
	//HMODULE hdll2 = GetModuleHandleA(NULL);
	// return R4(GetGameExeBase()+0xA7640 );
	return R8(R8(GetGameExeBase()+0x2387C88)+0x200);
	//return GetGameExeBase();

}
