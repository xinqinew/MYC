#pragma once


// CPAGE1 对话框

class CPAGE1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPAGE1)

public:
	CPAGE1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPAGE1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_edt_strA;
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedButtonEnumMonster();
	float m_x;
	float M_Y;
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButtonGetPos();
	afx_msg void OnBnClickedButtonMove2();
};
