#pragma once

#include "resource.h"
// CoInputTagDlg �Ի���

class CoInputTagDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInputTagDlg)

public:
	CoInputTagDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoInputTagDlg();

// �Ի�������
	enum { IDD = IDD_INPUTTAG };
public:
	CBrush m_brBk;//����һ��������ˢ
	CComboBox	m_font;
	long	m_tagheight;
	long	m_taglayer;
	long	m_tagoffsite;
	long	m_tagangle;
	long	m_textangle;
	CString	m_tagfont;
	long	m_tagwidth;
	long	m_tagcolor;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedColor();
	virtual void OnOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
