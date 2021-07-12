#include "stdafx.h"

typedef UINT64 (*TPCALL5)(UINT64,UINT64,UINT64,UINT64,char*);

char* GetObjName(UINT64 vrcx)
{
	char *putf8Name=NULL;
	__try
	{
		UINT64 pBase64 = (UINT_PTR)LoadLibraryA("Wow.exe");
		UINT64 pRoleObj = R8(R8(pBase64+0x2387C88)+0x200);
		TPCALL5 pcall5 = (TPCALL5)(pBase64+0x8AE040);
		char szpAscii[256]={0};

		putf8Name = (char*)pcall5(vrcx,0,1,0,0);
	}__except(1)
	{

	}
	return putf8Name;
}

void bian_li_guai_wu()
{
	UINT64 exeBase = (UINT64)LoadLibraryA("Wow.exe");
	for (UINT i=0;i<=0x7F;i++)//7F可能不是 对象数量 对象的分类编号
	{
		// UINT64 vrax=0;
		UINT64 vrax = R8(R8(R8(exeBase+0x2387C88)+0x30)+0x10+i*3*8);
		if (vrax == 0 )
		{
			break;
		}
		// else//vrdx !=0
		// {
		// 	vrax = vrdx;
		// }
		UINT64 vrcx = (UINT64)R4(R8(R8(exeBase+0x2387C88)+0x30)+i*3*8);//+28

		while((vrax&1)==0)
		{
			//遍历同类链表
			//rcx = dword([[wow.exe+0x2387C88]+0x30]+i*3*8) //0x28
			
			//+198]+20 //float x,y,z
			UINT64 pNode198 = R8(vrax+0x198);
			float x = R4F(pNode198+0x20);
			float y = R4F(pNode198+0x24);
			float z = R4F(pNode198+0x28); 

			char buf[2048];
			char asciiObjName[2048]={0};
			char *pObjName=GetObjName(vrax);
			if (pObjName&&pNode198)
			{
				utf8ToAscii(pObjName,asciiObjName);
			}
			sprintf_s(buf,"yjx:[%d] vrax=%p (%f,%f,%f) vrcx=%llx name=%p %s\r\n",i,vrax,x,y,z,vrcx,pObjName,asciiObjName);
			MessageBoxA(0,buf,"while",0);
			vrax = R8(vrcx+vrax+8);	//链表
		}
	}
}

