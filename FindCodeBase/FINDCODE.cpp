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

//��ȡģ��������
SIZE_T CFINDCODE::ReadExeToBuf()
{
	SIZE_T ʵ�ʶ�ȡ��С=0;
	HANDLE ���̾��=GetGameHp();
	UINT_PTR ģ���ַ=GetExeBase();
	ReadProcessMemory(���̾��,(LPCVOID)ģ���ַ,ExeBuf,GetExeSize(),&ʵ�ʶ�ȡ��С);
	CloseHandle(���̾��);
	return ʵ�ʶ�ȡ��С;
}

//�ڴ�Ա� 
UINT_PTR myMemcmp(UINT_PTR str1,UINT_PTR str2,SIZE_T nsize)
{
	SIZE_T size8=nsize/8;	//��8�ֽڱȽ�
	SIZE_T size1=nsize%8; 	//��1�ֽڱȽ� 
	UINT64* p8a=(UINT64*)strl;
	UINT64* p8b=(UINT64*)str2;

	BYTE* p1a=(BYTE*)str1;
	BYTE* p1b=(BYTE*)str2;
	for (SIZE_T i=0;i<size8;i++) 
	{
		if (p8a[i]!=p8b[i]) 
		{
			return 1;
		}
	}
	//���8�ֽڵıȽ�ȫ����ȲŻ�ִ�е��±� 
	for (SIZE_T i=0;i<size1;i++)
	{
		if (p1a[i]!=p1b[i])
		{
			return 1;
		}
	}
	//ִ�е����� ��ʾȫ�����
	return 0;

}
//��λ�ֽڼ�������
UINT_PTR CFINDCODE::FindCode(BYTE*ByFindData,BYTE nSize)
{
	//�������Ȱ�Ŀ������ڴ�һ�ζ�ȡ�������Լ��Ļ�����
	SIZE_T ʵ�ʶ�ȡ��С=ReadExeToBuf();
	if (ʵ�ʶ�ȡ��С! =GetExeSize())
	(
		printf("��ͣ��ʾ:ʵ�ʶ�ȡ��С=%llx,GetExeSize()=%llx \r\n",ʵ�ʶ�ȡ��С,GetExeSize());
		getchar();
	)
	printf ("��ʼ���������� ʵ�ʶ����С=%11x GetExeSize()=%llx nSize=%X\r\n",ʵ�ʶ�ȡ��С,GetExeSize(),nSize);
	//memcmp
	SIZE_T ƫ��=0;
	//94E230
	for (UINT_PTR i=0;i<GetExeSize();i++)
	{
	
		//94E230
		UINT_PTR br=myMemcmp((UINT64)&ExeBuf[i],(UINT64)ByFindData,nSize);
		if (br==0)
		{
			ƫ��=i;
			printf("findCode OK i=%d \r\n",i);
			break;
		}
		//printf("i=%llX br=%d\r\n",i,br);

	return GetExeBase()+ƫ��;
}

//VirtualQueryEx:��ѯģ�� ����ִҳ�淶Χ
SIZE_T CFINDCODE::VirtualQueryExe()
{
	HANDLE ���̾��=GetGameHp();
}
















