// PAGE1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "012-MFCDLL.h"
#include "PAGE1.h"
#include "afxdialogex.h"
#include "��������.h"


// CPAGE1 �Ի���

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
	ON_BN_CLICKED(IDC_BUTTON_FIRE, &CPAGE1::OnBnClickedButtonFire)
	ON_BN_CLICKED(IDC_BUTTON_ICE, &CPAGE1::OnBnClickedButtonIce)
	ON_BN_CLICKED(IDC_BUTTON_ENUM_BACKPACK, &CPAGE1::OnBnClickedButtonEnumBackpack)
	ON_BN_CLICKED(IDC_BUTTON_SEACHGOODS, &CPAGE1::OnBnClickedButtonSeachgoods)
	ON_BN_CLICKED(IDC_BUTTON_PICK, &CPAGE1::OnBnClickedButtonPick)
END_MESSAGE_MAP()


// CPAGE1 ��Ϣ�������

// ����һ������ָ��
//typedef UINT64 (*TPCALL5)(UINT64,UINT64,UINT64,UINT64,char*);

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
	pcall5(1,7,0,0,(UINT64)szpUtf8Buf);
}

// pcall5(�����ַ,0,1,0,0);//�������ֵ�ַ
void CPAGE1::OnBnClickedButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT64 pBase64 = (UINT_PTR) LoadLibraryA("Wow.exe");
	UINT64 pRoleObj = R8(R8(pBase64+0x2387c88)+0x200);//��ɫ����
	TPCALL5 pcall5 =(TPCALL5)(pBase64+0xA7640);
	// TPCALL5 pcall5 = (TPCALL5)((UINT_PTR) LoadLibraryA("Wow.exe")+0xA7640);
	char szpAscii[256]={0};
	// char* utf8ToAscii(IN char*szpUtf8,OUT char*szpAscii);

	char *putf8Name =(char*) pcall5(pRoleObj,0,1,0,0);
	utf8ToAscii(putf8Name,szpAscii);
	m_edt_strA=szpAscii;
	UpdateData(FALSE);//�ѱ��������ݸ��µ�����
}


void CPAGE1::OnBnClickedButtonEnumMonster()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���������б�();
	
	bian_li_guai_wu();
}

void �ƶ�(float x,float y)
{
	float xyz[3]={x,y,0};

}


void CPAGE1::OnBnClickedButtonMove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GameBase::MoveRole(m_x,M_Y);
}


void CPAGE1::OnBnClickedButtonGetPos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_x = GameBase::GetRolePos()[0];
	M_Y = GameBase::GetRolePos()[1];
	UpdateData(FALSE);
	return;
}


void CPAGE1::OnBnClickedButtonMove2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GameBase::MoveRole2(m_x,M_Y);

}

//������
void CPAGE1::OnBnClickedButtonFire()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UINT64 arg2buf[50]={0};//���� ���� ���� 
	UINT64 ID16[50]={0,0};// 0x006FCC00007B4493 /*ID1*/,0x204D880000001140 /*ID2*/};//Ŀ������ID
	TGCALL::UseActionCall(0x00000085,arg2buf,ID16);
}

//˪����
void CPAGE1::OnBnClickedButtonIce()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT64 arg2buf[50]={0};//���� ���� ���� 
	UINT64 ID16[50]={0,0};//Ŀ������ID
	TGCALL::UseActionCall(0x000000A8,arg2buf,ID16);
}


void CPAGE1::OnBnClickedButtonEnumBackpack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TGCALL::EnumBackpack();//��������
}
void FindMonsterGoods(UINT64 ID1,UINT64 ID2)
{
	UINT64 buf[100]={0};
	UINT64 rsp30 = (UINT64)buf;
	TPCALL4 pcall1 = (TPCALL4)(GameBase::GetExeBase()+0x4240A0);
	TPCALL4 pcall2 = (TPCALL4)(GameBase::GetExeBase()+0x1050EA0);
	TPCALL4 pcall3 = (TPCALL4)(GameBase::GetExeBase()+0x131EEB0);
	UINT64 vrax =pcall1(rsp30,0,0,0);
	vrax =pcall2(rsp30+0x20,0,0,0);
	// W8(vrax+0,ID1);
	// W8(vrax+8,ID2);
	vrax=pcall3(rsp30,0,0,0);
}


//����ѡ�й����ϵ���Ʒ
void CPAGE1::OnBnClickedButtonSeachgoods()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UINT64 pBase = R8(GameBase::GetExeBase()+0x21E2858);

	UINT64 ID1 = R8(pBase+0x30);
	UINT64 ID2 = R8(pBase+0x38);
	UINT64 arg1[40] = {ID1,ID2,0,0};
	//ͨ��ѡ�ж���ID ���Ҷ���
	TPCALL4 pcallGetObj1=(TPCALL4)(GameBase::GetExeBase()+0xB66AB0);
	UINT64 vrax = pcallGetObj1((UINT64)arg1,0,0,0);//һ������
	char buf[1024];
	sprintf_s(buf,"vrax=%llx \r\n",vrax);

	TPCALL4 pcall =(TPCALL4)(R8(R8(vrax)+0x2C0));//2C0 �Ҽ����� ��������Ʒ�Ĵ���
	pcall(vrax,0,0,0);
 
}

//����
void CPAGE1::OnBnClickedButtonPick()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TPCALL4 pcall4 = (TPCALL4)(GameBase::GetExeBase()+0xF2A620);
	pcall4(0,0,0,0);
	pcall4(1,0,0,0);
	pcall4(2,0,0,0);
}
