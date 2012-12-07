#pragma once
#include "afxwin.h"

#include "resource.h"
// CoInputLineDlg �Ի���

class CoInputLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInputLineDlg)

public:
	CoInputLineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoInputLineDlg();

// �Ի�������
	enum { IDD = IDD_INPUTLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brBk;//����һ��������ˢ
	CComboBox m_ConLineStyle;
	CEdit m_Edit1;
	CEdit m_Edit2;
	int		m_LineWide;
	int		m_LayerNum;
	COLORREF m_LineCor;
	int		m_LineStyle;
	afx_msg void OnBnClickedButtonCor();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
