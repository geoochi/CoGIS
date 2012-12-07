// CoInputPntDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoInputPntDlg.h"
#include "afxdialogex.h"


// CoInputPntDlg �Ի���

IMPLEMENT_DYNAMIC(CoInputPntDlg, CDialog)

CoInputPntDlg::CoInputPntDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInputPntDlg::IDD, pParent)
{
	m_PntStyle = -1;
	m_Radio = 1;
	m_Layer = 0;
	m_PntCor = RGB(0,0,0);
}

CoInputPntDlg::~CoInputPntDlg()
{
}

void CoInputPntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ConPntStyle);
	DDX_CBIndex(pDX, IDC_COMBO1, m_PntStyle);
	DDX_Text(pDX, IDC_EDIT1, m_Radio);
	DDV_MinMaxInt(pDX, m_Radio, 1, 20);
	DDX_Text(pDX, IDC_EDIT2, m_Layer);
}


BEGIN_MESSAGE_MAP(CoInputPntDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoInputPntDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInputPntDlg ��Ϣ�������


void CoInputPntDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog MyCorDlg;
	if (MyCorDlg.DoModal()==IDOK)
	{
		m_PntCor = MyCorDlg.GetColor();
	}
}


BOOL CoInputPntDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ConPntStyle.SetCurSel(0);

	//��ӱ���
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CoInputPntDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
