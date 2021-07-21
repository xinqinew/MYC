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
	SIZE_T CFINDCODE::GetExeSize();		//获取EXE模块大小
	UINT_PTR CFINDCODE::GetExeBegin();	//获取EXE模块起始地址--旧
	UINT_PTR CFINDCODE::GetExeEnd();	//获取EXE结束地址

	//把目标进程代码段数据读取本地进程
	static BYTE CFINDCODE::ExeBuf[0x1FA0000*2];//new malloc
	SIZE_T CFINDCODE::ReadExeToBuf();

	SIZE_T CFINDCODE::VirtualQueryExe();
	//定位字节集 特征码
	UINT_PTR CFINDCODE::FindCode(BYTE*ByFindData,BYTE nSize);
	
};