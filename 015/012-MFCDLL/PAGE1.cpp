// PAGE1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "012-MFCDLL.h"
#include "PAGE1.h"
#include "afxdialogex.h"


// CPAGE1 �Ի���

IMPLEMENT_DYNAMIC(CPAGE1, CDialogEx)

CPAGE1::CPAGE1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPAGE1::IDD, pParent)
	, m_edt_strA(_T(""))
{

}

CPAGE1::~CPAGE1()
{
}

void CPAGE1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edt_strA);
}


BEGIN_MESSAGE_MAP(CPAGE1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPAGE1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPAGE1 ��Ϣ�������

// ����һ������ָ��
typedef UINT64 (*TPCALL5)(UINT64,UINT64,UINT64,UINT64,char*);

// DWORD AnsiToUtf8(LPCSTR Ansi,OUT LPSTR szpUtf8Buf)
void CPAGE1::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//�Ѵ��ڵ����ݸ��µ�����
	TPCALL5 pcall5 = (TPCALL5)((UINT_PTR) LoadLibraryA("Wow.exe")+0xA7640);
	//pcall5(1,7,0,0,"xinqinew");
	// m_edt_strA.GetBuffer() ���ֽ��ַ���
	char szpUtf8Buf[256]={0};//���utf8��ת��
	AnsiToUtf8(m_edt_strA.GetBuffer(),szpUtf8Buf);
	// pcall5(1,7,0,0,m_edt_strA.GetBuffer());
	pcall5(1,7,0,0,szpUtf8Buf);
}
