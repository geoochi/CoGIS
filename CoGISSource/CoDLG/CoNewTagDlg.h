#pragma once

#include "resource.h"
// CoNewTagDlg �Ի���

class CoNewTagDlg : public CDialog
{
	DECLARE_DYNAMIC(CoNewTagDlg)

public:
	CoNewTagDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoNewTagDlg();

// �Ի�������
	enum { IDD = IDD_NEWFONTITEM };
	CBrush m_brBk;//����һ��������ˢ
	CString	m_TagName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
