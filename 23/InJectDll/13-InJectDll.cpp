// 13-InJectDll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

HWND GetGameHwnd()
{
	HWND ���ھ�� = FindWindowA("WTWindow","Wow");
	return ���ھ��;
}
UINT64 ע��DLL(char* dllFullPathName)
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
			//��Ŀ����̷����ڴ�
			LPVOID Ŀ������ڴ��ַ=VirtualAllocEx(���̾��,NULL,1024,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
			SIZE_T nWriten =0;//���ڷ���ʵ��д���ֽ���
			//DWORD nWriten =0;//���ڷ���ʵ��д���ֽ���
			//д��Ҫע���DLL��·��
			BOOL br = WriteProcessMemory(���̾��,Ŀ������ڴ��ַ,dllFullPathName,strlen(dllFullPathName)+1, &nWriten);
			HANDLE ht= CreateRemoteThread( 
				���̾��, 
				NULL,
				0,//0x400000
				(LPTHREAD_START_ROUTINE)LoadLibraryA,//LoadLibraryA("c:\\123.dll")
				Ŀ������ڴ��ַ,//LoadLibraryA(Ŀ������ڴ��ַ)
				0,
				&tid
				);
			printf("���ھ��=%p tid=%X \r\n",���ھ��,tid);
			//printf("�������=%d \r\n", GetLastError());
			WaitForSingleObject( ht,0xFFFFFFFF);//1��

			GetExitCodeThread( ht, &lpExitCode);
			printf("���ھ��=%p lpExitCode=%X \r\n",���ھ��,lpExitCode);//0x666888
		}
	}  
	//nRet64 = 0x100000000+lpExitCode;
	nRet64 = lpExitCode;
	return nRet64;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//��ȡ��ǰĿ¼
	//��ǰĿ¼·��+DLL����
	char ��ǰĿ¼[256] ={0};
	GetCurrentDirectoryA(256,��ǰĿ¼);
	//ƴ��DLLȫ·����
	strcat_s( ��ǰĿ¼,"\\MFCDLL.dll");
	printf("Ҫע���DLLȫ·����Ϊ��%s \r\n",��ǰĿ¼);
	//ע��DLL
	ע��DLL(��ǰĿ¼);
	Sleep(100);
	// getchar();//�ȴ�

	return 0;
}

