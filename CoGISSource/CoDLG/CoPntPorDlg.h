#pragma once
#include "resource.h"
#include "CoStructClass.h"
// CoPntPorDlg �Ի���

class CoPntPorDlg : public CDialog
{
	DECLARE_DYNAMIC(CoPntPorDlg)

public:
	CoPntPorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CoPntPorDlg(int Style,CString PntStyle,int Raido,int PntCor,int PntLayer,CWnd* pParent = NULL);
	virtual ~CoPntPorDlg();

// �Ի�������
	enum { IDD = IDD_POINTPRO };
	CBrush m_brBk;//����һ��������ˢ
	CComboBox	m_CorPntStyle;
	CString	m_OrPntStyle;
	int		m_OrRadio;
	int		m_OrPntCor;
	int		m_OrPntLayler;
	int		m_Radio;
	int		m_Layler;
	int		m_PntStyle;
public:
	COLORREF m_PntCor;
	CoPntPro m_PntPro;
	bool Tug1;
	bool Tug2;
	bool Tug3;
	bool Tug4;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
