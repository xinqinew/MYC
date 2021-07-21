#include "FINDCODE.h"


//过滤出代码段地址范围
CFINDCODE::CFINDCODE(void)
{

}
CFINDCODE::~CFINDCODE(void)
{

}

#define szGameSubCaption "魔兽世界"	//define宏定义,将标识符定义为一个字符串,不加分号
#define szClassName "GxWindowClass"

//获取窗口句柄
HWND CFINDCODE::GetGameHwnd(void)
{
	HWND hNext = FindWindowExA(HWND_DESKTOP,0,0,0);
	HWND h2 = FindWindowExA(HWND_DESKTOP,hNext,0,0);
	int i =0;
	while(h2)
	{
		char buf[256]={0};
		GetWindowTextA(h2,buf,256);
		if (strstr(buf,szGameSubCaption))
		{
			break;
		}
		h2 = FindWindowExA(HWND_DESKTOP,h2,0,0);
	}
	return h2;
}

//获取进程ID
DWORD CFINDCODE::GetPID()
{
	HWND h=GetGameHwnd();
	DWORD dwpid=0;
	GetWindowThreadProcessId(h,&dwpid);
	return dwpid;
}

//获取进程句柄
HANDLE CFINDCODE::GetGameHp()
{
	DWORD dwPid = GetPID();
	HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS,0,dwPid);
	// printf("hp=%hp, pid=%d\r\n",hp,dwPid);
	return hp;
}


//获取EXE模块起始地址
UINT_PTR CFINDCODE::GetExeBase()
{
	UINT_PTR exeBase64=NULL;
	HMODULE hMods[1024];	//20*sizeof(HMODULE)
	
	DWORD cbNeeded;
	unsigned int i;
	HANDLE 进程句柄=GetGameHp();

	//Get a list of all the modules in this process.
	BOOL br = EnumProcessModules(进程句柄,hMods,sizeof(hMods),&cbNeeded);
	if (br)
	{
		UINT32 模块数量=cbNeeded/sizeof(HMODULE);
		for ( i = 0; i < 模块数量; i++)
		{
			TCHAR szModName[MAX_PATH];

			//Get the full path to the module file.
			if(GetModuleFileNameEx(进程句柄,hMods[i],szModName,
									sizeof(szModName)/sizeof(TCHAR)))
			{
				//如果是“*.exe”的模块,直接返回基址
				if (strstr(szModName,".exe"))
				{
					exeBase64 = (UINT_PTR)hMods[i];
				}
				//Print the module name and handle value.
				
				//_tprintf(TEXT("模块名[%d]=%s 地址=%08X\n"),i,szModName,hModes[i]);
				// printf("模块名[%d]=%s 地址=%p\n",i,szModName,hMods[i]);
			}
		}
	}
	//Release the handle to the process.
	//
	CloseHandle(进程句柄);
	return exeBase64;
}


 // 获取EXE模块起始地址--旧
UINT_PTR CFINDCODE::GetExeBegin()
{
// 	static UINT_PTR nRet64=0;
// 	if (nRet64)
// 	{
// 		return nRet64;
// 	}
// 	DWORD64 lpExitCode=0;
// 	HWND 窗口句柄 = GetGameHwnd();
// 	if (窗口句柄)
// 	{
// 		DWORD 进程PID = 0;
// 		GetWindowThreadProcessId(窗口句柄,&进程PID);
// 		HANDLE 进程句柄=OpenProcess(PROCESS_ALL_ACCESS,FALSE,进程PID);
// 		if (进程句柄)
// 		{
// 			/* 读内存 */
// 			//创建远线程,调用GetModuleHandleA
// 			DWORD tid=0;

// 			HANDLE ht=CreateRemoteThread(
// 				进程句柄,
// 				NULL,
// 				0,//堆栈大小
// 				(LPTHREAD_START_ROUTINE)GetModuleHandleA,
// 				NULL,
// 				0,
// 				&tid);
// 			WaitForSingleObject(ht,1000);

// 			GetExitCodeThread(ht,(LPDWORD)&lpExitCode);
// 			printf("窗口句柄=%p, lpExitCode=%X \r\n",窗口句柄,lpExitCode);
// 			CloseHandle(进程句柄);
// 		}		
// 	}
// 	nRet64 = 0x100000000|lpExitCode;//合成模块基址
// 	printf("目标进程基址=%llx lpExitCode=%llx\r\n",nRet64,lpExitCode);
	return GetExeBase();
}


//获取EXE结束地址
UINT_PTR CFINDCODE::GetExeEnd()
{
	// HANDLE 进程句柄=GetGameHp();
	// UINT_PTR 模块基址 = GetExeBegin();
	// MEMORY_BASIC_INFORMATION meminfo;

	// //nSize函数写入lpBuffer的字节数,如果不等于sizeof(MEMORY_BASIC_INFORMATION)表示失败
	// SIZE_T nSize /*返回buf大小 */ = VirtualQueryEx(进程句柄,(LPCVOID)模块基址,&meminfo,sizeof(meminfo));
	// UINT_PTR 结束地址=(UINT_PTR)meminfo.AllocationBase+meminfo.RegionSize;
	// printf("GetExeEnd: AllocationBase=%llx,RegionSize=%X 结束地址=%llx \r\n",meminfo.AllocationBase,meminfo.RegionSize,结束地址);
	// return 结束地址;
	return GetExeBase()+GetExeSize();

}

//获取EXE模块大小
SIZE_T CFINDCODE::GetExeSize();		
{
	static SIZE_T nSize=0;
	if (nSize)
	{
		/* code */
		return nSize;
	}
	HANDLE 进程句柄=GetGameHp();
	UINT_PTR 模块基址 = GetExeBase();
	MEMORY_BASIC_INFORMATION meminfo;

	//nSize函数写入lpBuffer的字节数,如果不等于sizeof(MEMORY_BASIC_INFORMATION)表示失败
	SIZE_T nSize /*返回buf大小 */ = VirtualQueryEx(进程句柄,(LPCVOID)模块基址,&meminfo,sizeof(meminfo));
	nSize = meminfo.RegionSize;
	CloseHandle(进程句柄);
	return nSize;
}

