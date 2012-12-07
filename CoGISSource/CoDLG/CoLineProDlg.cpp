// CoLineProDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoLineProDlg.h"
#include "afxdialogex.h"


// CoLineProDlg �Ի���

IMPLEMENT_DYNAMIC(CoLineProDlg, CDialog)

CoLineProDlg::CoLineProDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoLineProDlg::IDD, pParent)
{

}

CoLineProDlg::CoLineProDlg(int MyStyle,CString LineStyle,int LineWide,int LineCor,int LineLayle,CWnd* pParent /*=NULL*/)
	: CDialog(CoLineProDlg::IDD, pParent)
{
	m_LineStyle=MyStyle;
	m_EditLineStyle = LineStyle;

	m_EditWide = m_EditLineWide = LineWide;

	m_LineCor = m_EditLineCor = LineCor;

	m_EditLayer = m_EditLineLayer = LineLayle;

	Tug1 = Tug2 = Tug3 = Tug4 = FALSE;
}


CoLineProDlg::~CoLineProDlg()
{
}

void CoLineProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT6, m_Edit6);
	DDX_Control(pDX, IDC_EDIT5, m_Edit5);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_BUTTON1, m_SetCor);
	DDX_CBIndex(pDX, IDC_COMBO1, m_LineStyle);
	DDX_Text(pDX, IDC_EDIT1, m_EditLineStyle);
	DDX_Text(pDX, IDC_EDIT2, m_EditLineWide);
	DDX_Text(pDX, IDC_EDIT3, m_EditLineCor);
	DDX_Text(pDX, IDC_EDIT4, m_EditLineLayer);
	DDX_Text(pDX, IDC_EDIT5, m_EditWide);
	DDX_Text(pDX, IDC_EDIT6, m_EditLayer);
}


BEGIN_MESSAGE_MAP(CoLineProDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoLineProDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CoLineProDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CoLineProDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CoLineProDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CoLineProDlg::OnBnClickedCheck4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoLineProDlg ��Ϣ�������


BOOL CoLineProDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);

	//��ӱ���
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CoLineProDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog corDlg;
	if (corDlg.DoModal()==IDOK)
	{
		m_LineCor = corDlg.GetColor();
	}
}


void CoLineProDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(Tug1)
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		Tug1 = false;
	}
	else
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		Tug1 = true;
	}
	UpdateData(FALSE);
}



void CoLineProDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(Tug2)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		Tug2 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		Tug2 = true;
	}
	UpdateData(FALSE);
}


void CoLineProDlg::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(Tug3)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		Tug3 = false;
	}
	else
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		Tug3 = true;
	}
	UpdateData(FALSE);
}


void CoLineProDlg::OnBnClickedCheck4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(Tug4)
	{
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
		Tug4 = false;
	}
	else
	{
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		Tug4 = true;
	}
	UpdateData(FALSE);
}


HBRUSH CoLineProDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
