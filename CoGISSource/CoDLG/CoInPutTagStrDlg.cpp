// CoInPutTagStrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoInPutTagStrDlg.h"
#include "afxdialogex.h"


// CoInPutTagStrDlg �Ի���

IMPLEMENT_DYNAMIC(CoInPutTagStrDlg, CDialog)

CoInPutTagStrDlg::CoInPutTagStrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInPutTagStrDlg::IDD, pParent)
{
	m_tagstr = _T("");
}

CoInPutTagStrDlg::~CoInPutTagStrDlg()
{
}

void CoInPutTagStrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tagstr);
}


BEGIN_MESSAGE_MAP(CoInPutTagStrDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInPutTagStrDlg ��Ϣ�������


BOOL CoInPutTagStrDlg::OnInitDialog()
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


HBRUSH CoInPutTagStrDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
