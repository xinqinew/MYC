// PAGE1.cpp : 实现文件
//

#include "stdafx.h"
#include "012-MFCDLL.h"
#include "PAGE1.h"
#include "afxdialogex.h"
#include "遍历怪物.h"


// CPAGE1 对话框

IMPLEMENT_DYNAMIC(CPAGE1, CDialogEx)

CPAGE1::CPAGE1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPAGE1::IDD, pParent)
	, m_edt_strA(_T(""))
	, m_x(0)
	, M_Y(0)
{

}

CPAGE1::~CPAGE1()
{
}

void CPAGE1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edt_strA);
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, M_Y);
}


BEGIN_MESSAGE_MAP(CPAGE1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPAGE1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON, &CPAGE1::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON_ENUM_MONSTER, &CPAGE1::OnBnClickedButtonEnumMonster)
	ON_BN_CLICKED(IDC_BUTTON_Move, &CPAGE1::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON_GET_POS, &CPAGE1::OnBnClickedButtonGetPos)
	ON_BN_CLICKED(IDC_BUTTON_Move2, &CPAGE1::OnBnClickedButtonMove2)
END_MESSAGE_MAP()


// CPAGE1 消息处理程序

// 定义一个函数指针
typedef UINT64 (*TPCALL5)(UINT64,UINT64,UINT64,UINT64,char*);

// DWORD AnsiToUtf8(LPCSTR Ansi,OUT LPSTR szpUtf8Buf)
void CPAGE1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//把窗口的数据更新到变量
	TPCALL5 pcall5 = (TPCALL5)((UINT_PTR) LoadLibraryA("Wow.exe")+0xA7640);
	//pcall5(1,7,0,0,"xinqinew");
	// m_edt_strA.GetBuffer() 多字节字符串
	char szpUtf8Buf[256]={0};//存放utf8的转码
	AnsiToUtf8(m_edt_strA.GetBuffer(),szpUtf8Buf);
	// pcall5(1,7,0,0,m_edt_strA.GetBuffer());
	pcall5(1,7,0,0,szpUtf8Buf);
}

// pcall5(对象地址,0,1,0,0);//返回名字地址
void CPAGE1::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT64 pBase64 = (UINT_PTR) LoadLibraryA("Wow.exe");
	UINT64 pRoleObj = R8(R8(pBase64+0x2387c88)+0x200);//角色对象
	TPCALL5 pcall5 =(TPCALL5)(pBase64+0xA7640);
	// TPCALL5 pcall5 = (TPCALL5)((UINT_PTR) LoadLibraryA("Wow.exe")+0xA7640);
	char szpAscii[256]={0};
	// char* utf8ToAscii(IN char*szpUtf8,OUT char*szpAscii);

	char *putf8Name =(char*) pcall5(pRoleObj,0,1,0,0);
	utf8ToAscii(putf8Name,szpAscii);
	m_edt_strA=szpAscii;
	UpdateData(FALSE);//把变量的数据更新到窗口
}


void CPAGE1::OnBnClickedButtonEnumMonster()
{
	// TODO: 在此添加控件通知处理程序代码
	//遍历怪物列表();
	
	bian_li_guai_wu();
}

void 移动(float x,float y)
{
	float xyz[3]={x,y,0};

}


void CPAGE1::OnBnClickedButtonMove()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GameBase::MoveRole(m_x,M_Y);
}


void CPAGE1::OnBnClickedButtonGetPos()
{
	// TODO: 在此添加控件通知处理程序代码
	m_x = GameBase::GetRolePos()[0];
	M_Y = GameBase::GetRolePos()[1];
	UpdateData(FALSE);
	return;
}


void CPAGE1::OnBnClickedButtonMove2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GameBase::MoveRole2(m_x,M_Y);

}
