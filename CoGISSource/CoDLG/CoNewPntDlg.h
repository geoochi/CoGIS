#pragma once
#include "resource.h"

// CoNewPntDlg �Ի���

class CoNewPntDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewPntDlg)

public:
	CoNewPntDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoNewPntDlg();

// �Ի�������
	enum { IDD = IDD_NEWPNTITEM };
	CBrush m_brBk;//����һ��������ˢ
	CString	m_PntName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
