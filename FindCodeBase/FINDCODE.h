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
	SIZE_T CFINDCODE::GetExeSize();		//��ȡEXEģ���С
	UINT_PTR CFINDCODE::GetExeBegin();	//��ȡEXEģ����ʼ��ַ--��
	UINT_PTR CFINDCODE::GetExeEnd();	//��ȡEXE������ַ

	//��Ŀ����̴�������ݶ�ȡ���ؽ���
	static BYTE CFINDCODE::ExeBuf[0x1FA0000*2];//new malloc
	SIZE_T CFINDCODE::ReadExeToBuf();

	SIZE_T CFINDCODE::VirtualQueryExe();
	//��λ�ֽڼ� ������
	UINT_PTR CFINDCODE::FindCode(BYTE*ByFindData,BYTE nSize);
	
};