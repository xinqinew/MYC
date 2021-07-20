#include "遍历模块.h"
#include "FINDCODE.h"


CFINDCODE find;

int main(int argn, char  *argv[])
{

	UINT_PTR 主模块地址 = find.GetExeBegin();
	printf("主模块地址=%llX",主模块地址);
	getchar();//控制台内暂停用的
	return 1;
}