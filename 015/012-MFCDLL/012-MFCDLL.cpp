// 012-MFCDLL.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "012-MFCDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CMy012MFCDLLApp

BEGIN_MESSAGE_MAP(CMy012MFCDLLApp, CWinApp)
END_MESSAGE_MAP()


// CMy012MFCDLLApp ����

CMy012MFCDLLApp::CMy012MFCDLLApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMy012MFCDLLApp ����

CMy012MFCDLLApp theApp;

#include "PAGE1.h"
// CMy012MFCDLLApp ��ʼ��
CPAGE1 pg1;
DWORD WINAPI ShowDlg(LPVOID arg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	//��ʾ����	
	pg1.DoModal();
	//���Ҫִ�б���رմ���
	FreeLibraryAndExitThread(theApp.m_hInstance,0x666888);
	return 1;
}

BOOL CMy012MFCDLLApp::InitInstance()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CWinApp::InitInstance();
	//main��ڵ�
	//��ʾ����
	//pg1.DoModal();
		//__in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
		//__in      SIZE_T dwStackSize,
		//__in      LPTHREAD_START_ROUTINE lpStartAddress,
		//__in_opt __deref __drv_aliasesMem LPVOID lpParameter,
		//__in      DWORD dwCreationFlags,
		//__out_opt LPDWORD lpThreadId
	//�������ڵ����߳���

	::CreateThread(0,0, ShowDlg,0,0,NULL);
	return TRUE;
}
