#include "StdAfx.h"
#include "GameBase.h"

typedef UINT64 (*TPCALL2)(UINT64 arg1,UINT64);
typedef UINT64 (*TPCALL6)(UINT64 arg1,UINT64,UINT64,UINT64,UINT64,UINT64 arg6);
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
	return R8(R8(GetExeBase()+0x2387C88)+0x200);
}
// 移动
UINT64 GameBase::MoveRole(float x,float y)
{
	UINT64 nRax=0;
	UINT64 nrcx = GetRoleObj();
	float xyz[6]={x,y};
	TPCALL2 movCall =(TPCALL2)(GetExeBase()+0x8CAE30);
	__try
	{
		nRax = movCall(nrcx,(UINT64)&xyz);
	}__except(1)
	{
		MessageBoxA(0,"可能基址需要更新","ERROR",0);
	}
	return nRax;
}
float* GameBase::GetRolePos()
{
	static float xyz[6]={0};
	xyz[0]=R4F(R8(GetRoleObj()+0x198)+0x20);
	xyz[1]=R4F(R8(GetRoleObj()+0x198)+0x24);
	xyz[2]=R4F(R8(GetRoleObj()+0x198)+0x28);
	xyz[3]=R4F(R8(GetRoleObj()+0x198)+0x30);//转向好像是30
	return xyz;
}

void GameBase::MoveRole2(float x,float y)
{
	UINT64 nRax=0;
	UINT64 nrcx = GetRoleObj();
	float r9xyz[6]={x,y};
	TPCALL6 movCall =(TPCALL6)(GetExeBase()+0x8B2C40);
	UINT64 vr8[20] = {0};
	UINT64 arg1 = GameBase::GetRoleObj();
	__try
	{
		nRax = movCall(arg1,5,(UINT64)&vr8,(UINT64)r9xyz,0,0);
	}__except(1)
	{
		MessageBoxA(0,"可能基址需要更新","ERROR",0);
	}
}
