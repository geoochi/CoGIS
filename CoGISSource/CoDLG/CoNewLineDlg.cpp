// CoNewLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoNewLineDlg.h"
#include "afxdialogex.h"


// CoNewLineDlg �Ի���

IMPLEMENT_DYNAMIC(CoNewLineDlg, CDialog)

CoNewLineDlg::CoNewLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoNewLineDlg::IDD, pParent)
{
	m_NewLine = _T("");
}

CoNewLineDlg::~CoNewLineDlg()
{
}

void CoNewLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_NewLine);
}


BEGIN_MESSAGE_MAP(CoNewLineDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoNewLineDlg ��Ϣ�������


BOOL CoNewLineDlg::OnInitDialog()
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


HBRUSH CoNewLineDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
