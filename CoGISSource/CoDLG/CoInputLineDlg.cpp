// CoInputLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoInputLineDlg.h"
#include "afxdialogex.h"


// CoInputLineDlg �Ի���

IMPLEMENT_DYNAMIC(CoInputLineDlg, CDialog)

CoInputLineDlg::CoInputLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CoInputLineDlg::IDD, pParent)
{
	m_LineWide = 1;
	m_LayerNum = 0;
	m_LineCor = RGB(0,0,0);
	m_LineStyle = -1;
}

CoInputLineDlg::~CoInputLineDlg()
{
}

void CoInputLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ConLineStyle);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Text(pDX, IDC_EDIT1, m_LineWide);
	DDX_Text(pDX, IDC_EDIT2, m_LayerNum);
	DDX_CBIndex(pDX, IDC_COMBO1, m_LineStyle);
}


BEGIN_MESSAGE_MAP(CoInputLineDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COR, &CoInputLineDlg::OnBnClickedButtonCor)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CoInputLineDlg ��Ϣ�������


void CoInputLineDlg::OnBnClickedButtonCor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog cor;
	if (cor.DoModal()==IDOK)
		m_LineCor = cor.GetColor();	
}


BOOL CoInputLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ConLineStyle.SetCurSel(0);

	//��ӱ���
	CBitmap bmp; 
	bmp.LoadBitmap(IDB_BITMAP_Background); 
	m_brBk.CreatePatternBrush(&bmp); 
	bmp.DeleteObject();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CoInputLineDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
