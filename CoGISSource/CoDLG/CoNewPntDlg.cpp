// CoNewPntDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoNewPntDlg.h"
#include "afxdialogex.h"


// CoNewPntDlg �Ի���

IMPLEMENT_DYNAMIC(CoNewPntDlg, CDialog)

CoNewPntDlg::CoNewPntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoNewPntDlg::IDD, pParent)
{
	m_PntName = _T("");
}

CoNewPntDlg::~CoNewPntDlg()
{
}

void CoNewPntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_PntName);
}


BEGIN_MESSAGE_MAP(CoNewPntDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoNewPntDlg ��Ϣ�������


BOOL CoNewPntDlg::OnInitDialog()
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


HBRUSH CoNewPntDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
