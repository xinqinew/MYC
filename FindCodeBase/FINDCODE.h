#pragma once
#include <stdio.h>
#include <Windows.h>
#include <Psapi.h>

class CFINDCODE
{
public:
	CFINDCODE(void);
	~CFINDCODE(void);

	HWND CFINDCODE::GetGameHwnd(void);	//获取窗口句柄
	DWORD CFINDCODE::GetPID();			//获取进程ID
	HANDLE CFINDCODE::GetGameHp();		//获取进程句柄
	UINT_PTR CFINDCODE::GetExeBase();	//获取EXE模块起始地址
	UINT_PTR CFINDCODE::GetExeBegin();	//获取EXE模块起始地址--旧
	UINT_PTR CFINDCODE::GetExeEnd();	//获取EXE结束地址
	
};