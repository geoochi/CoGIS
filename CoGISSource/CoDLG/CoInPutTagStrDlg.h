#pragma once

#include "resource.h"
// CoInPutTagStrDlg �Ի���

class CoInPutTagStrDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInPutTagStrDlg)

public:
	CoInPutTagStrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoInPutTagStrDlg();

// �Ի�������
	enum { IDD = IDD_INPUTTAGSTRDLG };
public:
	CBrush m_brBk;//����һ��������ˢ
	CString	m_tagstr;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
