// CoInputTagDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoInputTagDlg.h"
#include "afxdialogex.h"


// CoInputTagDlg �Ի���

IMPLEMENT_DYNAMIC(CoInputTagDlg, CDialog)

CoInputTagDlg::CoInputTagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInputTagDlg::IDD, pParent)
{
	m_tagheight = 20;
	m_taglayer = 0;
	m_tagoffsite = 1;
	m_tagangle = 0;
	m_textangle = 0;
	m_tagfont = _T("���Ŀ���");
	m_tagwidth = 10;
	m_tagcolor=RGB(0,0,0);
}

CoInputTagDlg::~CoInputTagDlg()
{
}

void CoInputTagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_font);
	DDX_Text(pDX, IDC_HEIGHT, m_tagheight);
	DDV_MinMaxLong(pDX, m_tagheight, 1, 40);
	DDX_Text(pDX, IDC_LAYER, m_taglayer);
	DDX_Text(pDX, IDC_OFFSITE, m_tagoffsite);
	DDX_Text(pDX, IDC_TAGANGLE, m_tagangle);
	DDV_MinMaxLong(pDX, m_tagangle, 0, 360);
	DDX_Text(pDX, IDC_TEXTANGLE, m_textangle);
	DDX_Text(pDX, IDC_TEXTFONT, m_tagfont);
	DDX_Text(pDX, IDC_WIDTH, m_tagwidth);
	DDV_MinMaxLong(pDX, m_tagwidth, 1, 40);
}


BEGIN_MESSAGE_MAP(CoInputTagDlg, CDialog)
	ON_BN_CLICKED(IDC_COLOR, &CoInputTagDlg::OnBnClickedColor)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInputTagDlg ��Ϣ�������


void CoInputTagDlg::OnBnClickedColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg;
	dlg.DoModal();
	m_tagcolor=dlg.GetColor();
}


void CoInputTagDlg::OnOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index;
	index=m_font.GetCurSel();
	m_font.GetLBText(index,m_tagfont);
	CDialog::OnOK();
}


BOOL CoInputTagDlg::OnInitDialog()
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


HBRUSH CoInputTagDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
