// CoPolyProDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoPolyProDLG.h"
#include "afxdialogex.h"


// CoPolyProDLG �Ի���

IMPLEMENT_DYNAMIC(CoPolyProDLG, CDialog)

CoPolyProDLG::CoPolyProDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CoPolyProDLG::IDD, pParent)
{

}

CoPolyProDLG::CoPolyProDLG(CoPolyPro& PolyPro,CString PolyStyle,CString FillStyle,CWnd* pParent /* = NULL */)
	: CDialog(CoPolyProDLG::IDD, pParent)
{
	m_PolyStyle = PolyPro.PolyStyle;
	m_FillStyle = PolyPro.PolyFillStyle;
	m_OrStyle = PolyStyle;
	m_OrFillStyle = FillStyle;
	m_FillCor=m_OrFillCor = PolyPro.PolyColor;
	m_Layer = m_OrLayer = PolyPro.PolyLayer;
	m_Area =m_OrArea = PolyPro.PolyArea;
	Tug1 = Tug2 = Tug3 = Tug4 =	Tug5= FALSE;
}


CoPolyProDLG::~CoPolyProDLG()
{
}

void CoPolyProDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_PolyStyle);
	DDX_CBIndex(pDX, IDC_COMBO2, m_FillStyle);
	DDX_Text(pDX, IDC_EDIT1, m_OrStyle);
	DDX_Text(pDX, IDC_EDIT2, m_OrFillStyle);
	DDX_Text(pDX, IDC_EDIT3, m_OrFillCor);
	DDX_Text(pDX, IDC_EDIT4, m_OrLayer);
	DDX_Text(pDX, IDC_EDIT5, m_Layer);
	DDX_Text(pDX, IDC_EDIT6, m_OrArea);
	DDX_Text(pDX, IDC_EDIT7, m_Area);
}


BEGIN_MESSAGE_MAP(CoPolyProDLG, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoPolyProDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CoPolyProDLG::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CoPolyProDLG::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CoPolyProDLG::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK5, &CoPolyProDLG::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK4, &CoPolyProDLG::OnBnClickedCheck4)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoPolyProDLG ��Ϣ�������


BOOL CoPolyProDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);

	//��ӱ���
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CoPolyProDLG::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog CorDlg;
	if (CorDlg.DoModal())
	{
		m_FillCor = CorDlg.GetColor();
	}
}


void CoPolyProDLG::OnBnClickedCheck1()
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


void CoPolyProDLG::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(Tug2)
	{
		GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
		Tug1 = false;
	}
	else
	{
		GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);
		Tug2 = true;
	}
	UpdateData(FALSE);
}


void CoPolyProDLG::OnBnClickedCheck3()
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


void CoPolyProDLG::OnBnClickedCheck5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(Tug5)
	{
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		Tug5 = TRUE;
	}
	else
	{
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		Tug5 = TRUE;
	}
	UpdateData(FALSE);
}


void CoPolyProDLG::OnBnClickedCheck4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(Tug4)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		Tug4 = TRUE;
	}
	else
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		Tug4 = TRUE;
	}
	UpdateData(FALSE);
}


HBRUSH CoPolyProDLG::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
