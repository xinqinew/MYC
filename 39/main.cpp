#include "����ģ��.h"
#include "FINDCODE.h"
#include "RMEM.h"

CFINDCODE find;

BYTE ������20FA0[]=
{
	0xA0,0x0F,0x02 //
};

void ��λƫ������()
{
	UINT_PTR ��ģ���ַ = find.GetExeBase();
	UINT64 ��ģ���С=find.GetExeSize();
	UINT_PTR ��ģ�鿪ʼ��ַ = find.GetExeBegin();
	UINT_PTR ��ģ�������ַ = find.GetExeEnd();
	printf("��ģ���ַ=%llX \r\n��ʼ��ַ=%llX \r\n������ַ=%llX \r\n��ģ���С=%llX",
		��ģ���ַ,��ģ�鿪ʼ��ַ,��ģ�������ַ,��ģ���С);

	UINT64 max64=0x0007ffffffffffff;
	printf("%lld ��\r\n",max64/0x1FA0000);
	// find.VirtualQueryExe();
	//���������� ��λƫ��
	UINT_PTR �ҵ��ĵ�ַ=find.FindCode(������20FA0,sizeof(������20FA0));

	printf("ƫ�����ڵ�ַ=%p ƫ��=%X \r\n",�ҵ��ĵ�ַ,R4(�ҵ��ĵ�ַ));


}

void ��λCALL��ַƫ������()
{
	static BYTE ������0C[]={0x81,0xC3,0x88};
	UINT_PTR ��ģ���ַ = find.GetExeBase();
	UINT64 ��ģ���С=find.GetExeSize();
	UINT_PTR ��ģ�鿪ʼ��ַ = find.GetExeBegin();
	UINT_PTR ��ģ�������ַ = find.GetExeEnd();
	//���������� ��λƫ��
	UINT_PTR �ҵ��ĵ�ַ=find.FindCode(������0C,sizeof(������0C));

	UINT_PTR ָ���ַ=�ҵ��ĵ�ַ+0x0C;//0x0cΪ���λ��
	UINT32 ƫ��=R4(ָ���ַ+1);
	UINT_PTR CALL��ַ=ָ���ַ+5+ƫ��;

	printf("ƫ��=%08X \r\n",ƫ��);//8�ֽڶ���
	printf("��ģ���ַ=%llX CALL��ַ=%llX CALL��ַ+ƫ��=Wow.exe+%llX \r\n",
		��ģ���ַ,CALL��ַ,CALL��ַ-��ģ���ַ);
}

int main(int argn, char  *argv[])
{
	��λƫ������();
	��λCALL��ַƫ������();	

	getchar();//����̨����ͣ�õ�
	return 1;
}

 