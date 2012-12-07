#pragma once
#include "resource.h"
#include "CoStructClass.h"
// CoPolyProDLG �Ի���

class CoPolyProDLG : public CDialog
{
	DECLARE_DYNAMIC(CoPolyProDLG)

public:
	CoPolyProDLG(CWnd* pParent = NULL);   // ��׼���캯��
	CoPolyProDLG(CoPolyPro& PolyPro,CString PolyStyle,CString FillStyle,CWnd* pParent = NULL);
	virtual ~CoPolyProDLG();

// �Ի�������
	enum { IDD = IDD_POLYPRO };
	CBrush m_brBk;//����һ��������ˢ
	int		m_PolyStyle;
	int		m_FillStyle;
	CString	m_OrStyle;
	CString	m_OrFillStyle;
	int		m_OrFillCor;
	int		m_OrLayer;
	int		m_Layer;
	double	m_OrArea;
	double	m_Area;
public:
	COLORREF m_FillCor;
private:
	bool Tug1;
	bool Tug2;
	bool Tug3;
	bool Tug4;
	bool Tug5;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck4();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
