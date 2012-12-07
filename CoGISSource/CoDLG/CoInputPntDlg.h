#pragma once
#include "afxwin.h"

#include "resource.h"
// CoInputPntDlg �Ի���

class CoInputPntDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInputPntDlg)

public:
	CoInputPntDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoInputPntDlg();

// �Ի�������
	enum { IDD = IDD_INPUTPNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brBk;//����һ��������ˢ
	CComboBox m_ConPntStyle;
	int		m_PntStyle;
	int		m_Radio;
	int		m_Layer;
	COLORREF m_PntCor;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
