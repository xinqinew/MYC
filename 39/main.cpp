#include "遍历模块.h"
#include "FINDCODE.h"
#include "RMEM.h"

CFINDCODE find;

BYTE 特征码20FA0[]=
{
	0xA0,0x0F,0x02 //
}

void 定位偏移例子()
{
	UINT_PTR 主模块地址 = find.GetExeBase();
	UINT32 主模块大小=find.GetExeSize();
	UINT_PTR 主模块开始地址 = find.GetExeBegin();
	UINT_PTR 主模块结束地址 = find.GetExeEnd();
	printf("主模块地址=%llX \r\n开始地址=%llX \r\n结束地址=%llX \r\n主模块大小=%llX",
		主模块地址,主模块开始地址,主模块结束地址,主模块大小);

	UINT64 max64=0x0007ffffffffffff;
	printf("%lld 倍\r\n",max64/0x1FA0000);
	// find.VirtualQueryExe();
	//查找特征码 定位偏移
	UINT_PTR 找到的地址=find.FindCode(特征码20FA0,sizeof(特征码20FA0));

	printf("偏移所在地址=%p 偏移=%X \r\n",找到的地址,R4(找到的地址));


}

void 定位CALL地址偏移例子()
{
	static BYTE 特征码0C[]={0x81,0xC3,0x88};
	UINT_PTR 主模块地址 = find.GetExeBase();
	UINT32 主模块大小=find.GetExeSize();
	UINT_PTR 主模块开始地址 = find.GetExeBegin();
	UINT_PTR 主模块结束地址 = find.GetExeEnd();
	//查找特征码 定位偏移
	UINT_PTR 找到的地址=find.FindCode(特征码0C,sizeof(特征码0C));

	UINT_PTR 指令地址=找到的地址+0x0C;//0x0c为相对位移
	UINT32 偏移=R4(指令地址+1);
	UINT_PTR CALL地址=指令地址+5+偏移;

	printf("偏移=%08X \r\n",偏移);//8字节对齐
	printf("主模块地址=%llX CALL地址=%llX CALL基址+偏移=Wow.exe+%llX \r\n",
		主模块地址,CALL地址,CALL地址-主模块地址);
}

int main(int argn, char  *argv[])
{
	定位偏移例子();
	定位CALL地址偏移例子();	

	getchar();//控制台内暂停用的
	return 1;
}

 