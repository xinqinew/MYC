#include "stdafx.h"
#include <Windows.h>

HWND GetGameHwnd()
{
	HWND ���ھ�� = FindWindowA("WTWindow","Wow");
	return ���ھ��;
}

UINT64 W4(UINT64 ��ַ,UINT64 v32)//dword()
{
	//1 FindWindow��ȡĿ����� ���ھ��
	//2 OpenProcess(��Ȩ��,false,����PID) ��ȡĿ����̵ľ�� ���������� ��Ҫ�ж��ڴ��Ȩ��
	//3 ReadprocessMemory()
	//4 CloseHandle �ͷŵ����̾��
	UINT64 ����ֵ=0;
	HWND ���ھ��=GetGameHwnd();
	if(���ھ��) 
	{
		DWORD ����PID = 0;
		GetWindowThreadProcessId(���ھ��,&����PID);
		HANDLE ���̾��=OpenProcess(PROCESS_ALL_ACCESS,FALSE,����PID);
		if(���̾��)
		{
			����ֵ=WriteProcessMemory(���̾��,(LPVOID)��ַ,&v32,4,NULL);
		}
	}
	return ����ֵ;
}
UINT64 W8(UINT64 ��ַ,UINT64 v64)//dword()
{
	//1 FindWindow��ȡĿ����� ���ھ��
	//2 OpenProcess(��Ȩ��,false,����PID) ��ȡĿ����̵ľ�� ���������� ��Ҫ�ж��ڴ��Ȩ��
	//3 ReadprocessMemory()
	//4 CloseHandle �ͷŵ����̾��
	UINT64 ����ֵ=0;
	HWND ���ھ��=GetGameHwnd();
	if(���ھ��) 
	{
		DWORD ����PID = 0;
		GetWindowThreadProcessId(���ھ��,&����PID);
		HANDLE ���̾��=OpenProcess(PROCESS_ALL_ACCESS,FALSE,����PID);
		if(���̾��)
		{
			����ֵ=WriteProcessMemory(���̾��,(LPVOID)��ַ,&v64,8,NULL);
		}
	}
	return ����ֵ;
}


//dword(qword(14000000+8A85)+160)
//typedef UINT64 QWORD;
UINT64 R8(UINT64 ��ַ)  //dword()
{
	//����̶�д
	//1 FindWindow() ��ȡĿ����� ���ھ��
	//2 OpenProcess(��Ȩ�ޣ�false������pid) ��ȡĿ����̵ľ�� ������������Ҫ�ж��ڴ��Ȩ��
	//3 ReadProcessMemory()
	//4 CloseHandle() �ͷŵ����̾��
	UINT64 ����ֵ=0;
	HWND ���ھ�� =GetGameHwnd();

	if (���ھ��)
	{
		DWORD ����PID =0;
		GetWindowThreadProcessId(���ھ��,&����PID);
		HANDLE ���̾�� = OpenProcess(PROCESS_ALL_ACCESS,  FALSE,����PID);
		if (���̾��)
		{
			//���ڴ�
			ReadProcessMemory(���̾��,(LPVOID)��ַ,&����ֵ,8,NULL);
		}
	}

	return ����ֵ;
}
DWORD R4(UINT64 ��ַ)  //R8(UINT_PTR ��ַ)  R8(UINT64 ��ַ)
{
	return (DWORD)R8(��ַ);
}
float R4F(UINT64 ��ַ)  //dword()
{
	float ����ֵ=0;
	HWND ���ھ�� =GetGameHwnd();

	if (���ھ��)
	{
		DWORD ����PID =0;
		GetWindowThreadProcessId(���ھ��,&����PID);
		HANDLE ���̾�� = OpenProcess(PROCESS_ALL_ACCESS,  FALSE,����PID);
		if (���̾��)
		{
			//���ڴ�
			ReadProcessMemory(���̾��,(LPVOID)��ַ,&����ֵ,sizeof(float),NULL);
		}
	}

	return ����ֵ;
}
UINT64 GetGameExeBase()
{
	UINT64 nRet64 =0;
	DWORD lpExitCode=0;
	HWND ���ھ�� =GetGameHwnd();

	if (���ھ��)
	{

		DWORD ����PID =0;
		GetWindowThreadProcessId(���ھ��,&����PID);
		HANDLE ���̾�� = OpenProcess(PROCESS_ALL_ACCESS,  FALSE,����PID);
		if (���̾��)
		{

			DWORD tid =0;
			//���ڴ�

			//����Զ�߳� ����GetModuleHandleA
			//__in      HANDLE hProcess,
			//__in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
			//__in      SIZE_T dwStackSize,
			//__in      LPTHREAD_START_ROUTINE lpStartAddress,
			//__in_opt  LPVOID lpParameter,
			//__in      DWORD dwCreationFlags,
			//__out_opt LPDWORD lpThreadId
			HANDLE ht= CreateRemoteThread( 
				���̾��, 
				NULL,
				0,//0x400000
				(LPTHREAD_START_ROUTINE)GetModuleHandleA,
				NULL,
				0,
				&tid
				);
			//printf("�������=%d \r\n", GetLastError());
			WaitForSingleObject( ht,1000);

			GetExitCodeThread( ht, &lpExitCode);
			printf("���ھ��=%p,lpExitCode=%X \r\n",���ھ��,lpExitCode);
		}
	}  
	nRet64 = 0x100000000+lpExitCode;//�ϳ�ģ���ַ
	// nRet64 = lpExitCode;
	return nRet64;
}
UINT64 ��ȡ�����ַ()
{
	//��ȡģ���ַ
	//HMODULE hdll1 = LoadLibraryA("Wow.exe");
	//HMODULE hdll2 = GetModuleHandleA(NULL);
	// return R4(GetGameExeBase()+0xA7640 );
	return R8(R8(GetGameExeBase()+0x2387C88)+0x200);
	//return GetGameExeBase();

}
