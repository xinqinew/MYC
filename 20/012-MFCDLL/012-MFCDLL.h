// 012-MFCDLL.h : 012-MFCDLL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy012MFCDLLApp
// �йش���ʵ�ֵ���Ϣ������� 012-MFCDLL.cpp
//

class CMy012MFCDLLApp : public CWinApp
{
public:
	CMy012MFCDLLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
