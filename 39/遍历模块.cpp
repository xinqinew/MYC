#include "遍历模块.h"
#include <locale.h>

#pragma comment(lib,"psapi.lib")

int 遍历进程模块(DWORD 进程PID)
{
	HMODULE hMods[1024];	//20*sizeof(HMODULE)
	HANDLE 进程句柄;
	DWORD cbNeeded;
	unsigned int i;
	//Print the proess identifier.
	printf("\nprocess ID: %u\n",进程PID);
	//Get a handle to the process.
	进程句柄=OpenProcess(PROCESS_ALL_ACCESS,FALSE,进程PID);

	if (NULL == 进程句柄)
		return 1;

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
				//Print the module name and handle value.
				
				//_tprintf(TEXT("模块名[%d]=%s 地址=%08X\n"),i,szModName,hModes[i]);
				printf("模块名[%d]=%s 地址=%p\n",i,szModName,hMods[i]);
			}
		}
	}
	//Release the handle to the process.
	//
	CloseHandle(进程句柄);
	return 0;
}

