#include "����ģ��.h"
#include "FINDCODE.h"
#include "RMEM.h"

CFINDCODE find;

BYTE ������20FA0[]=
{
	0xA0,0x0F,0x02 //
}

int main(int argn, char  *argv[])
{

	UINT_PTR ��ģ���ַ = find.GetExeBase();
	UINT32 ��ģ���С=find.GetExeSize();
	UINT_PTR ��ģ�鿪ʼ��ַ = find.GetExeBegin();
	UINT_PTR ��ģ�������ַ = find.GetExeEnd();
	printf("��ģ���ַ=%llX \r\n��ʼ��ַ=%llX \r\n������ַ=%llX \r\n��ģ���С=%llX",
		��ģ���ַ,��ģ�鿪ʼ��ַ,��ģ�������ַ,��ģ���С);

	UINT64 max64=0x0007ffffffffffff;
	printf("%lld ��\r\n",max64/0x1FA0000);
	find.VirtualQueryExe();
	//���������� ��λƫ��
	UINT_PTR �ҵ��ĵ�ַ=find.FindCode(������20FA0,sizeof(������20FA0));

	printf("ƫ�����ڵ�ַ=%p ƫ��=%X \r\n",�ҵ��ĵ�ַ,R4(�ҵ��ĵ�ַ));

	getchar();//����̨����ͣ�õ�
	return 1;
}

 