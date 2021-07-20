// 012-MFCDLL.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "012-MFCDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMy012MFCDLLApp

BEGIN_MESSAGE_MAP(CMy012MFCDLLApp, CWinApp)
END_MESSAGE_MAP()


// CMy012MFCDLLApp 构造

CMy012MFCDLLApp::CMy012MFCDLLApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMy012MFCDLLApp 对象

CMy012MFCDLLApp theApp;

#include "PAGE1.h"
// CMy012MFCDLLApp 初始化
CPAGE1 pg1;
DWORD WINAPI ShowDlg(LPVOID arg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	//显示窗口	
	pg1.DoModal();
	//如果要执行必须关闭窗口
	FreeLibraryAndExitThread(theApp.m_hInstance,0x666888);
	return 1;
}

BOOL CMy012MFCDLLApp::InitInstance()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CWinApp::InitInstance();
	//main入口点
	//显示窗口
	//pg1.DoModal();
		//__in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
		//__in      SIZE_T dwStackSize,
		//__in      LPTHREAD_START_ROUTINE lpStartAddress,
		//__in_opt __deref __drv_aliasesMem LPVOID lpParameter,
		//__in      DWORD dwCreationFlags,
		//__out_opt LPDWORD lpThreadId
	//把它放在单独线程里

	::CreateThread(0,0, ShowDlg,0,0,NULL);
	return TRUE;
}
