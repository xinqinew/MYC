#include "遍历模块.h"
#include "FINDCODE.h"


CFINDCODE find;

int main(int argn, char  *argv[])
{

	UINT_PTR 主模块地址 = find.GetExeBase();
	UINT32 主模块大小=find.GetExeSize();
	UINT_PTR 主模块开始地址 = find.GetExeBegin();
	UINT_PTR 主模块结束地址 = find.GetExeEnd();
	printf("主模块地址=%llX \r\n开始地址=%llX \r\n结束地址=%llX \r\n主模块大小=%llX",
		主模块地址,主模块开始地址,主模块结束地址,主模块大小);
	getchar();//控制台内暂停用的
	return 1;
}