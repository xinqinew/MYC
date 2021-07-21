#include "遍历模块.h"
#include "FINDCODE.h"
#include "RMEM.h"

CFINDCODE find;

BYTE 特征码20FA0[]=
{
	0xA0,0x0F,0x02 //
}

int main(int argn, char  *argv[])
{

	UINT_PTR 主模块地址 = find.GetExeBase();
	UINT32 主模块大小=find.GetExeSize();
	UINT_PTR 主模块开始地址 = find.GetExeBegin();
	UINT_PTR 主模块结束地址 = find.GetExeEnd();
	printf("主模块地址=%llX \r\n开始地址=%llX \r\n结束地址=%llX \r\n主模块大小=%llX",
		主模块地址,主模块开始地址,主模块结束地址,主模块大小);

	UINT64 max64=0x0007ffffffffffff;
	printf("%lld 倍\r\n",max64/0x1FA0000);
	find.VirtualQueryExe();
	//查找特征码 定位偏移
	UINT_PTR 找到的地址=find.FindCode(特征码20FA0,sizeof(特征码20FA0));

	printf("偏移所在地址=%p 偏移=%X \r\n",找到的地址,R4(找到的地址));

	getchar();//控制台内暂停用的
	return 1;
}

 