#pragma once


// CPAGE1 �Ի���

class CPAGE1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPAGE1)

public:
	CPAGE1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPAGE1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_edt_strA;
};