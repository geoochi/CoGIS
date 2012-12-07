#pragma once

#include "resource.h"
// CoInPutPolyDlg �Ի���

class CoInPutPolyDlg : public CDialog
{
	DECLARE_DYNAMIC(CoInPutPolyDlg)

public:
	CoInPutPolyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CoInPutPolyDlg();

// �Ի�������
	enum { IDD = IDD_INPUTPOLY };
public:
	CBrush m_brBk;//����һ��������ˢ
	CComboBox	m_ConPolyStle;
	CComboBox	m_ConFillStyle;
	int		m_FillStyle;
	int		m_PolyStyle;
	int		m_PolyLayer;
	COLORREF m_PolyFillCor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
