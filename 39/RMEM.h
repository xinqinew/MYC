#pragma once


HWND GetGameHwnd();
UINT64 R8(UINT64 地址);
DWORD R4(UINT64 地址);	//R8(UINT_PTR 地址) R8(UINT64 地址)
float R4F(UINT64 地址);	//R8(UINT_PTR 地址) R8(UINT64 地址)

UINT64 W4(UINT64 地址,UINT64 v32);//dword()
UINT64 W8(UINT64 地址,UINT64 v64);//dword()

UINT64 GetGameExeBase();
UINT64 获取对象地址();
void 打印角色对象属性();