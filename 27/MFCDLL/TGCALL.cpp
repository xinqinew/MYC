#include "StdAfx.h"
#include "TGCALL.h"


TGCALL::TGCALL(void)
{
}


TGCALL::~TGCALL(void)
{
}
void TGCALL::UseActionCall(UINT32 SkillID,UINT64* argBuf40,UINT64 *TargetID16)
{
	typedef UINT64 (*TPCALL4)(UINT64 arg1,UINT64* arg2,UINT64 arg3,UINT64* arg4);
	TPCALL4 pcall=(TPCALL4)(GameBase::GetExeBase()+0x77DC40);
	__try
	{
		pcall(SkillID,argBuf40,0,TargetID16);
	}__except(1)
	{
		MessageBoxA(0,"ERROR 0x77DC40","´íÎó",MB_OK);
	}
	return;
}