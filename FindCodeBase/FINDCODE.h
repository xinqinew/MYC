#pragma once
#include <stdio.h>
#include <Windows.h>
#include <Psapi.h>

class CFINDCODE
{
public:
	CFINDCODE(void);
	~CFINDCODE(void);

	HWND CFINDCODE::GetGameHwnd(void);	//��ȡ���ھ��
	DWORD CFINDCODE::GetPID();			//��ȡ����ID
	HANDLE CFINDCODE::GetGameHp();		//��ȡ���̾��
	UINT_PTR CFINDCODE::GetExeBase();	//��ȡEXEģ����ʼ��ַ
	UINT_PTR CFINDCODE::GetExeBegin();	//��ȡEXEģ����ʼ��ַ--��
	UINT_PTR CFINDCODE::GetExeEnd();	//��ȡEXE������ַ
	
};