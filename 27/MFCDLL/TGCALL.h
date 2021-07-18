#pragma once
typedef UINT64 (*TPCALL2)(UINT64 arg1,UINT64);
typedef UINT64 (*TPCALL4)(UINT64 arg1,UINT64,UINT64,UINT64);
typedef UINT64 (*TPCALL5)(UINT64 arg1,UINT64,UINT64,UINT64,UINT64);
typedef UINT64 (*TPCALL6)(UINT64 arg1,UINT64,UINT64,UINT64,UINT64,UINT64 arg6);
class TGCALL
{
public:
	TGCALL(void);
	~TGCALL(void);
	static void TGCALL::UseActionCall(UINT32 SkillID,UINT64* argBuf40,UINT64 *TargetID16);
	static void TGCALL::EnumBackpack();
};

