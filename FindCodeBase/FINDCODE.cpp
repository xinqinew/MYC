#include "FINDCODE.h"


//���˳�����ε�ַ��Χ
CFINDCODE::CFINDCODE(void)
{

}
CFINDCODE::~CFINDCODE(void)
{

}

#define szGameSubCaption "ħ������"	//define�궨��,����ʶ������Ϊһ���ַ���,���ӷֺ�
#define szClassName "GxWindowClass"

//��ȡ���ھ��
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

//��ȡ����ID
DWORD CFINDCODE::GetPID()
{
	HWND h=GetGameHwnd();
	DWORD dwpid=0;
	GetWindowThreadProcessId(h,&dwpid);
	return dwpid;
}

//��ȡ���̾��
HANDLE CFINDCODE::GetGameHp()
{
	DWORD dwPid = GetPID();
	HANDLE hp = OpenProcess(PROCESS_ALL_ACCESS,0,dwPid);
	// printf("hp=%hp, pid=%d\r\n",hp,dwPid);
	return hp;
}


//��ȡEXEģ����ʼ��ַ
UINT_PTR CFINDCODE::GetExeBase()
{
	UINT_PTR exeBase64=NULL;
	HMODULE hMods[1024];	//20*sizeof(HMODULE)
	
	DWORD cbNeeded;
	unsigned int i;
	HANDLE ���̾��=GetGameHp();

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
				//����ǡ�*.exe����ģ��,ֱ�ӷ��ػ�ַ
				if (strstr(szModName,".exe"))
				{
					exeBase64 = (UINT_PTR)hMods[i];
				}
				//Print the module name and handle value.
				
				//_tprintf(TEXT("ģ����[%d]=%s ��ַ=%08X\n"),i,szModName,hModes[i]);
				// printf("ģ����[%d]=%s ��ַ=%p\n",i,szModName,hMods[i]);
			}
		}
	}
	//Release the handle to the process.
	//
	CloseHandle(���̾��);
	return exeBase64;
}


 // ��ȡEXEģ����ʼ��ַ--��
UINT_PTR CFINDCODE::GetExeBegin()
{
// 	static UINT_PTR nRet64=0;
// 	if (nRet64)
// 	{
// 		return nRet64;
// 	}
// 	DWORD64 lpExitCode=0;
// 	HWND ���ھ�� = GetGameHwnd();
// 	if (���ھ��)
// 	{
// 		DWORD ����PID = 0;
// 		GetWindowThreadProcessId(���ھ��,&����PID);
// 		HANDLE ���̾��=OpenProcess(PROCESS_ALL_ACCESS,FALSE,����PID);
// 		if (���̾��)
// 		{
// 			/* ���ڴ� */
// 			//����Զ�߳�,����GetModuleHandleA
// 			DWORD tid=0;

// 			HANDLE ht=CreateRemoteThread(
// 				���̾��,
// 				NULL,
// 				0,//��ջ��С
// 				(LPTHREAD_START_ROUTINE)GetModuleHandleA,
// 				NULL,
// 				0,
// 				&tid);
// 			WaitForSingleObject(ht,1000);

// 			GetExitCodeThread(ht,(LPDWORD)&lpExitCode);
// 			printf("���ھ��=%p, lpExitCode=%X \r\n",���ھ��,lpExitCode);
// 			CloseHandle(���̾��);
// 		}		
// 	}
// 	nRet64 = 0x100000000|lpExitCode;//�ϳ�ģ���ַ
// 	printf("Ŀ����̻�ַ=%llx lpExitCode=%llx\r\n",nRet64,lpExitCode);
	return GetExeBase();
}


//��ȡEXE������ַ
UINT_PTR CFINDCODE::GetExeEnd()
{
	// HANDLE ���̾��=GetGameHp();
	// UINT_PTR ģ���ַ = GetExeBegin();
	// MEMORY_BASIC_INFORMATION meminfo;

	// //nSize����д��lpBuffer���ֽ���,���������sizeof(MEMORY_BASIC_INFORMATION)��ʾʧ��
	// SIZE_T nSize /*����buf��С */ = VirtualQueryEx(���̾��,(LPCVOID)ģ���ַ,&meminfo,sizeof(meminfo));
	// UINT_PTR ������ַ=(UINT_PTR)meminfo.AllocationBase+meminfo.RegionSize;
	// printf("GetExeEnd: AllocationBase=%llx,RegionSize=%X ������ַ=%llx \r\n",meminfo.AllocationBase,meminfo.RegionSize,������ַ);
	// return ������ַ;
	return GetExeBase()+GetExeSize();

}

//��ȡEXEģ���С
SIZE_T CFINDCODE::GetExeSize();		
{
	static SIZE_T nSize=0;
	if (nSize)
	{
		/* code */
		return nSize;
	}
	HANDLE ���̾��=GetGameHp();
	UINT_PTR ģ���ַ = GetExeBase();
	MEMORY_BASIC_INFORMATION meminfo;

	//nSize����д��lpBuffer���ֽ���,���������sizeof(MEMORY_BASIC_INFORMATION)��ʾʧ��
	SIZE_T nSize /*����buf��С */ = VirtualQueryEx(���̾��,(LPCVOID)ģ���ַ,&meminfo,sizeof(meminfo));
	nSize = meminfo.RegionSize;
	CloseHandle(���̾��);
	return nSize;
}

