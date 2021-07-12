#include "StdAfx.h"
#include "GameBase.h"


GameBase::GameBase(void)
{
}


GameBase::~GameBase(void)
{
}
UINT64 GameBase::GetExeBase()
{
	static UINT64 nBase =(UINT64)LoadLibraryA("Wow.exe");
	return nBase;
}
UINT64 GameBase::GetRoleObj()//返回角色对象地址
{
	return R8(GetExeBase()+0x20);
}