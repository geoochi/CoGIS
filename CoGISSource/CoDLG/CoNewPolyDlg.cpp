// CoNewPolyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoNewPolyDlg.h"
#include "afxdialogex.h"


// CoNewPolyDlg �Ի���

IMPLEMENT_DYNAMIC(CoNewPolyDlg, CDialog)

CoNewPolyDlg::CoNewPolyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoNewPolyDlg::IDD, pParent)
{
	m_NewPolyItem = _T("");
}

CoNewPolyDlg::~CoNewPolyDlg()
{
}

void CoNewPolyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_NewPolyItem);
}


BEGIN_MESSAGE_MAP(CoNewPolyDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoNewPolyDlg ��Ϣ�������


BOOL CoNewPolyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ӱ���
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CoNewPolyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd == this) 
	{ 
		return m_brBk; 
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
