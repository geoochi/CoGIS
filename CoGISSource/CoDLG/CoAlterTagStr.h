#pragma once

#include "resource.h"
// CoAlterTagStr �Ի���

class CoAlterTagStr : public CDialog
{
	DECLARE_DYNAMIC(CoAlterTagStr)

public:
	CoAlterTagStr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoAlterTagStr();

// �Ի�������
	enum { IDD = IDD_MICALTERTAGSTR };
public:
	CBrush m_brBk;//����һ��������ˢ
	CString	m_TagStr;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
