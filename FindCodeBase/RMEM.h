#pragma once


HWND GetGameHwnd();
UINT64 R8(UINT64 ��ַ);
DWORD R4(UINT64 ��ַ);	//R8(UINT_PTR ��ַ) R8(UINT64 ��ַ)
float R4F(UINT64 ��ַ);	//R8(UINT_PTR ��ַ) R8(UINT64 ��ַ)

UINT64 W4(UINT64 ��ַ,UINT64 v32);//dword()
UINT64 W8(UINT64 ��ַ,UINT64 v64);//dword()

UINT64 GetGameExeBase();
UINT64 ��ȡ�����ַ();
void ��ӡ��ɫ��������();