#pragma once

#include "resource.h"
// CoNewPolyDlg �Ի���

class CoNewPolyDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewPolyDlg)

public:
	CoNewPolyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoNewPolyDlg();

// �Ի�������
	enum { IDD = IDD_NEWPOLYITEM };
	CBrush m_brBk;//����һ��������ˢ
	CString	m_NewPolyItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
