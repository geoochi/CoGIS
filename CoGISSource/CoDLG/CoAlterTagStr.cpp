// CoAlterTagStr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoAlterTagStr.h"
#include "afxdialogex.h"


// CoAlterTagStr �Ի���

IMPLEMENT_DYNAMIC(CoAlterTagStr, CDialog)

CoAlterTagStr::CoAlterTagStr(CWnd* pParent /*=NULL*/)
	: CDialog(CoAlterTagStr::IDD, pParent)
{
	m_TagStr = _T("");
}

CoAlterTagStr::~CoAlterTagStr()
{
}

void CoAlterTagStr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_TagStr);
}


BEGIN_MESSAGE_MAP(CoAlterTagStr, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoAlterTagStr ��Ϣ�������


BOOL CoAlterTagStr::OnInitDialog()
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


HBRUSH CoAlterTagStr::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
