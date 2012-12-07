// CoInPutPolyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoInPutPolyDlg.h"
#include "afxdialogex.h"


// CoInPutPolyDlg �Ի���

IMPLEMENT_DYNAMIC(CoInPutPolyDlg, CDialog)

CoInPutPolyDlg::CoInPutPolyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInPutPolyDlg::IDD, pParent)
{
	m_FillStyle = -1;
	m_PolyStyle = -1;
	m_PolyLayer = 0;
	m_PolyFillCor = RGB(0,0,0);
}

CoInPutPolyDlg::~CoInPutPolyDlg()
{
}

void CoInPutPolyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_ConPolyStle);
	DDX_Control(pDX, IDC_COMBO1, m_ConFillStyle);
	DDX_CBIndex(pDX, IDC_COMBO1, m_FillStyle);
	DDX_CBIndex(pDX, IDC_COMBO2, m_PolyStyle);
	DDX_Text(pDX, IDC_EDIT1, m_PolyLayer);
}


BEGIN_MESSAGE_MAP(CoInPutPolyDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CoInPutPolyDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInPutPolyDlg ��Ϣ�������


void CoInPutPolyDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog FillCorDlg;
	if (FillCorDlg.DoModal()==IDOK)
	{
		m_PolyFillCor = FillCorDlg.GetColor();
	}
}


BOOL CoInPutPolyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ConFillStyle.SetCurSel(0);
	m_ConPolyStle.SetCurSel(1);

	//��ӱ���
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CoInPutPolyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
