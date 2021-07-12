#include "stdafx.h"
void 遍历怪物列表()
{
	UINT64 exeBase = (UINT64)LoadLibraryA("Wow.exe");
	for (UINT i=0;i<=0x7F;i++)//7F可能不是 对象数量 对象的分类编号
	{
		UINT64 vrax=0;
		UINT64 vrdx = R8(R8(R8(exeBase+0x2387C88)+0x30)+0x10+i*3*8);
		if (vrdx == 0 )
		{
			break;
		}
		else//vrdx !=0
		{
			vrax = vrdx;
		}
		while((vrax&1)==0)
		{
			//遍历同类链表
			//rcx = dword([[wow.exe+0x2387C88]+0x30]+i*3*8) //0x28
			UINT64 vrcx = (UINT64)R4(R8(R8(exeBase+0x2387C88)+0x30)+i*3*8);//+28
			vrax = R8(vrcx+vrax+8);	//链表
			//+198]+20 //float x,y,z
			float x = R4F(R8(vrax+0x198)+0x20);
			float y = R4F(R8(vrax+0x198)+0x24);
			float z = R4F(R8(vrax+0x198)+0x28); 
			TRACE("[%d] 对象=%p (%f,%f,%f) \r\n",i,vrax,x,y,z);
		}
	}
}
