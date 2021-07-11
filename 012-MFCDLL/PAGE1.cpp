// PAGE1.cpp : 实现文件
//

#include "stdafx.h"
#include "012-MFCDLL.h"
#include "PAGE1.h"
#include "afxdialogex.h"


// CPAGE1 对话框

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


// CPAGE1 消息处理程序

// 定义一个函数指针
typedef UINT64 (*TPCALL5)(UINT64,UINT64,UINT64,UINT64,char*);


void CPAGE1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//把窗口的数据更新到变量
	TPCALL5 pcall5 = (TPCALL5)((UINT_PTR) LoadLibraryA("Wow.exe")+0xA7640);
	//pcall5(1,7,0,0,"xinqinew");
	pcall5(1,7,0,0,m_edt_strA.GetBuffer());
}
