#include "����ģ��.h"
#include "FINDCODE.h"


CFINDCODE find;

int main(int argn, char  *argv[])
{

	UINT_PTR ��ģ���ַ = find.GetExeBase();
	UINT32 ��ģ���С=find.GetExeSize();
	UINT_PTR ��ģ�鿪ʼ��ַ = find.GetExeBegin();
	UINT_PTR ��ģ�������ַ = find.GetExeEnd();
	printf("��ģ���ַ=%llX \r\n��ʼ��ַ=%llX \r\n������ַ=%llX \r\n��ģ���С=%llX",
		��ģ���ַ,��ģ�鿪ʼ��ַ,��ģ�������ַ,��ģ���С);
	getchar();//����̨����ͣ�õ�
	return 1;
}