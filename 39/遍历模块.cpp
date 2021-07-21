#include "����ģ��.h"
#include <locale.h>

#pragma comment(lib,"psapi.lib")

int ��������ģ��(DWORD ����PID)
{
	HMODULE hMods[1024];	//20*sizeof(HMODULE)
	HANDLE ���̾��;
	DWORD cbNeeded;
	unsigned int i;
	//Print the proess identifier.
	printf("\nprocess ID: %u\n",����PID);
	//Get a handle to the process.
	���̾��=OpenProcess(PROCESS_ALL_ACCESS,FALSE,����PID);

	if (NULL == ���̾��)
		return 1;

	//Get a list of all the modules in this process.
	BOOL br = EnumProcessModules(���̾��,hMods,sizeof(hMods),&cbNeeded);
	if (br)
	{
		UINT32 ģ������=cbNeeded/sizeof(HMODULE);
		for ( i = 0; i < ģ������; i++)
		{
			TCHAR szModName[MAX_PATH];

			//Get the full path to the module file.
			if(GetModuleFileNameEx(���̾��,hMods[i],szModName,
									sizeof(szModName)/sizeof(TCHAR)))
			{
				//Print the module name and handle value.
				
				//_tprintf(TEXT("ģ����[%d]=%s ��ַ=%08X\n"),i,szModName,hModes[i]);
				printf("ģ����[%d]=%s ��ַ=%p\n",i,szModName,hMods[i]);
			}
		}
	}
	//Release the handle to the process.
	//
	CloseHandle(���̾��);
	return 0;
}

