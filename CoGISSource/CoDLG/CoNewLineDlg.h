#pragma once

#include "resource.h"
// CoNewLineDlg �Ի���

class CoNewLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewLineDlg)

public:
	CoNewLineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoNewLineDlg();

// �Ի�������
	enum { IDD = IDD_NEWLINEITEM };
	CBrush m_brBk;//����һ��������ˢ
	CString	m_NewLine;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
