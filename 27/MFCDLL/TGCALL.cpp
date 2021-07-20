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
		MessageBoxA(0,"ERROR 0x77DC40","错误",MB_OK);
	}
	return;
}

void TGCALL::EnumBackpack()
{
	OutputDebugStringA("yjx:遍历背包开始");
	char buf1000[1000]={0};
	//背包地址
	UINT64 nBaseForBackpack = R8(GameBase::GetRoleObj()+0x20FA0);
	for (UINT i=0;i<100;i++)
	{
		UINT64 ID1=R8(nBaseForBackpack+i*16+0);
		UINT64 ID2=R8(nBaseForBackpack+i*16+8);
		UINT64 obj1=0;
		UINT64 obj2=0;
		UINT32 nIDType =0;
		sprintf_s(buf1000,"yjx: ID1=%llx ID2=%llx \r\n",ID1,ID2);
		OutputDebugStringA(buf1000);
		if (ID2)
			//if (ID2=0x0C490800000000000)
		{
			//rax+940	//对象1
			//rax+48	//背包对象名字//对象2
			TPCALL4 pcallGetObj1=(TPCALL4) (GameBase::GetExeBase()+0xB66AB0);
			UINT64 arg1[4]={ID1,ID2};
			UINT64 arg3=GameBase::GetExeBase()+0x1CF1B30;
			char *putf8Name =NULL;
			char buf[1024]={0};
			__try
			{
				MessageBeep(1);
				obj1=pcallGetObj1((UINT64 )arg1,0,0,0);
				MessageBeep(2);
				if (obj1)
				{
					//获取obj2
					nIDType=R4(obj1+0x940);
					UINT64 arg1[10]={nIDType};
					UINT64 arg2[10]={0};
					TPCALL4 pcallGetObj2=(TPCALL4) (GameBase::GetExeBase()+0x371860);
					obj2 = pcallGetObj2((UINT64)arg1,(UINT64)arg2,0,0);
					if (obj2)
					{
						 putf8Name =(char*)R8(obj2+0x48);
						 char bufObjName[1024]={0};
						 utf8ToAscii(putf8Name,bufObjName);
						//打印相应信息
						sprintf_s(buf, "yjx:[%d]: obj1=%llx,obj2=%llx,分类ID=%X,名字=%s",i,obj1,obj2,nIDType, bufObjName);
						MessageBoxA(0,buf,"OK",MB_OK);
					}
				}
			}__except(1)
			{
				sprintf_s(buf,"yjx:ERROR [%d]: obj1=%llx,obj2=%llx,分类ID=%X,名字=%p",i,obj1,obj2,nIDType,putf8Name);
				MessageBoxA(0,buf,"OK",MB_OK);
			}
		}
	}
}