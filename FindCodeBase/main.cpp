#include "����ģ��.h"
#include "FINDCODE.h"


CFINDCODE find;

int main(int argn, char  *argv[])
{

	UINT_PTR ��ģ���ַ = find.GetExeBegin();
	printf("��ģ���ַ=%llX",��ģ���ַ);
	getchar();//����̨����ͣ�õ�
	return 1;
}