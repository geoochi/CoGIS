// CoNewTagDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoNewTagDlg.h"
#include "afxdialogex.h"


// CoNewTagDlg �Ի���

IMPLEMENT_DYNAMIC(CoNewTagDlg, CDialog)

CoNewTagDlg::CoNewTagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoNewTagDlg::IDD, pParent)
{
	m_TagName = _T("");
}

CoNewTagDlg::~CoNewTagDlg()
{
}

void CoNewTagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_TagName);
}


BEGIN_MESSAGE_MAP(CoNewTagDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoNewTagDlg ��Ϣ�������


BOOL CoNewTagDlg::OnInitDialog()
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


HBRUSH CoNewTagDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
