
// CoGISView.cpp : CCoGISView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CoGIS.h"
#endif
#include "MainFrm.h"
#include "CoGISDoc.h"
#include "CoGISView.h"
#include "CoStructClass.h"
#include "DataExchange.h"
//�����Զ���ͷ�ļ�
#include "_CoToolPoint.h"
#include "_CoLine.h"
#include "_CoArea.h"
#include "_CoLogic.h"
#include "_CoDLG.H"
#include "_CoDB.h"
#include "_CoOverall.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoGISView

IMPLEMENT_DYNCREATE(CCoGISView, CView)

BEGIN_MESSAGE_MAP(CCoGISView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCoGISView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CESHI, &CCoGISView::OnCeshi)
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_INPUT_POINT, &CCoGISView::OnInputPoint)
	ON_COMMAND(ID_SELECT_POINT, &CCoGISView::OnSelectPoint)
	ON_COMMAND(ID_MOVE_POINT, &CCoGISView::OnMovePoint)
	ON_COMMAND(ID_COPY_POINT, &CCoGISView::OnCopyPoint)
	ON_COMMAND(ID_RE_POINTPRO, &CCoGISView::OnRePointpro)
	ON_COMMAND(ID_DEL_POINT, &CCoGISView::OnDelPoint)
	ON_COMMAND(ID_DELALL_POINT, &CCoGISView::OnDelallPoint)
	ON_COMMAND(ID_INPUT_LINE, &CCoGISView::OnInputLine)
	ON_COMMAND(ID_SELECT_LINE, &CCoGISView::OnSelectLine)
	ON_COMMAND(ID_MOVE_LINE, &CCoGISView::OnMoveLine)
	ON_COMMAND(ID_COPY_LINE, &CCoGISView::OnCopyLine)
	ON_COMMAND(ID_EDIT_LINEPRO, &CCoGISView::OnEditLinepro)
	ON_COMMAND(ID_CUT_LINE, &CCoGISView::OnCutLine)
	ON_COMMAND(ID_ADDPNT_LINE, &CCoGISView::OnAddpntLine)
	ON_COMMAND(ID_MOVEPNT_ONLINE, &CCoGISView::OnMovepntOnline)
	ON_COMMAND(ID_DELPNT_ONLINE, &CCoGISView::OnDelpntOnline)
	ON_COMMAND(ID_DEL_LINE, &CCoGISView::OnDelLine)
	ON_COMMAND(ID_DELALL_LINE, &CCoGISView::OnDelallLine)
	ON_COMMAND(ID_INPUT_POLYGON, &CCoGISView::OnInputPolygon)
	ON_COMMAND(ID_SELECT_POLY, &CCoGISView::OnSelectPoly)
	ON_COMMAND(ID_COPY_POLY, &CCoGISView::OnCopyPoly)
	ON_COMMAND(ID_MOVE_POLY, &CCoGISView::OnMovePoly)
	ON_COMMAND(ID_REPOLY_PRO, &CCoGISView::OnRepolyPro)
	ON_COMMAND(ID_DEL_POLY, &CCoGISView::OnDelPoly)
	ON_COMMAND(ID_DELALL_POLY, &CCoGISView::OnDelallPoly)
	ON_COMMAND(ID_INPUT_TAG, &CCoGISView::OnInputTag)
	ON_COMMAND(ID_SELECT_TAG, &CCoGISView::OnSelectTag)
	ON_COMMAND(ID_MOVE_TAG, &CCoGISView::OnMoveTag)
	ON_COMMAND(ID_COPY_TAG, &CCoGISView::OnCopyTag)
	ON_COMMAND(ID_ALTER_TAGTEXT, &CCoGISView::OnAlterTagtext)
	ON_COMMAND(ID_RE_TAGGPRO, &CCoGISView::OnReTaggpro)
	ON_COMMAND(ID_DEL_TAG, &CCoGISView::OnDelTag)
	ON_COMMAND(ID_DELALL_TAG, &CCoGISView::OnDelallTag)
	ON_COMMAND(ID_TOPO_SELPNT, &CCoGISView::OnTopoSelpnt)
	ON_COMMAND(ID_TOPO_SELLINE, &CCoGISView::OnTopoSelline)
	ON_COMMAND(ID_TOPO_SELPOLY, &CCoGISView::OnTopoSelpoly)
	ON_COMMAND(ID_GET_DISTANCE, &CCoGISView::OnGetDistance)
	ON_COMMAND(ID_ZOON_IN, &CCoGISView::OnZoonIn)
	ON_COMMAND(ID_ZOON_OUT, &CCoGISView::OnZoonOut)
	ON_COMMAND(ID_PAN, &CCoGISView::OnPan)
	ON_COMMAND(ID_MICFW, &CCoGISView::OnMicfw)
	ON_COMMAND(ID_FRASH, &CCoGISView::OnFrash)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_CLEAR_LINE_STATE, &CCoGISView::OnClearLineState)
	ON_COMMAND(ID_CLEAR_AREA_STATE, &CCoGISView::OnClearAreaState)
	ON_COMMAND(ID_ADD_PNT_AREA, &CCoGISView::OnAddPntArea)
	ON_COMMAND(ID_MOVE_PNT_AREA, &CCoGISView::OnMovePntArea)
	ON_COMMAND(ID_DEL_PNT_AREA, &CCoGISView::OnDelPntArea)
	ON_COMMAND(ID_DIS_LINE, &CCoGISView::OnDisLine)
END_MESSAGE_MAP()

// CCoGISView ����/����

CCoGISView::CCoGISView()
{
	// TODO: �ڴ˴���ӹ������
	m_BaseOper = NULL;
	m_CoScreen.sx=0;
	m_CoScreen.sy=0;
	m_CoScreen.blc=1;
	m_MapMode = 1;
	m_OverAllOper = 0;//�������
	ShStatae=0;//����״̬��ʾ
	m_CurrentOper=_T("�޲���");
	//��ʼ��ʾ������
	setIniState();//���ü�����״̬
}

CCoGISView::~CCoGISView()
{
}

BOOL CCoGISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCoGISView ����
void CCoGISView::OnDraw(CDC* pDC)
{
	CCoGISDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (ShStatae)
	{
		ShowState();
	}
	ShStatae=1;
	DisPaly();
}


// CCoGISView ��ӡ


void CCoGISView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCoGISView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCoGISView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCoGISView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}
// CCoGISView ���

#ifdef _DEBUG
void CCoGISView::AssertValid() const
{
	CView::AssertValid();
}

void CCoGISView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCoGISDoc* CCoGISView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCoGISDoc)));
	return (CCoGISDoc*)m_pDocument;
}
#endif //_DEBUG


// CCoGISView ��Ϣ�������
//�����Ӧ����
void CCoGISView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	/*ClientToScreen(&point);
	OnContextMenu(this, point);*/
}

void CCoGISView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CCoGISView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ʵʱ��ʾ����λ��
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	//==========================================================
	//��ʾ��Ļ����
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CMFCStatusBar&pStatus = pFrame->GetStatusBar();
	CString str;
	str.Format(_T("x=%3f,y=%3f"),MyPoint.x,MyPoint.y);
	pStatus.SetPaneText(pStatus.CommandToIndex(IDS_MOUSE_POINT), str,TRUE);
	CView::OnMouseMove(nFlags, point);
	//�����ʾ
	if(m_OverAllOper==1)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_FD); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==2)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_SX); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==3)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_YD); 
		SetCursor(hCursor);
	}
	//=======�����µĲ���========
	if (m_BaseOper)
		m_BaseOper->MouseMove(nFlags,MyPoint);
}

void CCoGISView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_OverAllOper==1)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_FD); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==2)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_SX); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==3)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_YD); 
		SetCursor(hCursor);
	}
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	if(m_BaseOper)
		m_BaseOper->LButtonDown(nFlags,MyPoint);
	CView::OnLButtonDown(nFlags, point);
}

void CCoGISView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_OverAllOper==1)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_FD); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==2)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_SX); 
		SetCursor(hCursor);
	}
	if(m_OverAllOper==3)
	{
		HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR_YD); 
		SetCursor(hCursor);
	}
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	if(m_BaseOper)
		m_BaseOper->LButtonUp(nFlags,MyPoint);
	CView::OnLButtonUp(nFlags, point);
}

void CCoGISView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CoPnt MyPoint;
	VPtoDP(point.x,point.y,&MyPoint.x,&MyPoint.y);
	if (m_BaseOper)
		m_BaseOper->RButtonDown(nFlags,MyPoint);
	CView::OnRButtonDown(nFlags, point);
}
//��Ӧ�����ַŴ���С
BOOL CCoGISView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DelectMouseOper();
	m_CurrentOper =_T("���ַŴ���С");
	ShowState();
	CoPnt MyPnt;
	VPtoDP(pt.x,pt.y,&MyPnt.x,&MyPnt.y);
	CoZoom Zoom(this,m_CoScreen);
	Zoom.MouseWheel(nFlags,zDelta,MyPnt);
	m_CoScreen=Zoom.m_Screen;

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CCoGISView::OnCeshi()
{
}



//===========��˵�����ز���============//
//�����
void CCoGISView::OnInputPoint()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("�����");
		ShowState();
		m_BaseOper = new CoInPutPnt(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ѡ���
void CCoGISView::OnSelectPoint()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("ѡ���");
		ShowState();
		m_BaseOper = new SelectPoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�ƶ���
void CCoGISView::OnMovePoint()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("�ƶ���");
		ShowState();
		m_BaseOper = new MovePoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//���Ƶ�
void CCoGISView::OnCopyPoint()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("���Ƶ�");
		ShowState();
		m_BaseOper = new CopyPoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//�޸ĵ����
void CCoGISView::OnRePointpro()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("�޸ĵ����");
		ShowState();
		m_BaseOper = new ModifyPntPro(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//ɾ����
void CCoGISView::OnDelPoint()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper=_T("ɾ����");
		ShowState();
		m_BaseOper = new DeletePoint(this,m_DB,getPntAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//ɾ�����е�
void CCoGISView::OnDelallPoint()
{
	// TODO: �ڴ���������������
	if(isPntActive())
	{
		m_CurrentOper=_T("ɾ�����е�");
		ShowState();
		DelAllPoint del(this,m_DB,getPntAct());
		del.CoDellAllPnt();
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//==============�߲˵���ز���===========//

//������
void CCoGISView::OnInputLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("������");
		ShowState();
		m_BaseOper = new CoInputLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//ѡ����
void CCoGISView::OnSelectLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("ѡ����");
		ShowState();
		m_BaseOper = new CoSelectLine(this,m_DB,getLineAct(),m_CoScreen,TRUE);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//���ѡ����״̬
void CCoGISView::OnClearLineState()
{
	// TODO: �ڴ���������������
	m_CurrentOper ="���ѡ��";
	ShowState();
	CoSelectLine DelSelect;
	DelSelect.DelSelect();
	Invalidate(TRUE);
}

//�ƶ���
void CCoGISView::OnMoveLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("�ƶ���");
		ShowState();
		m_BaseOper = new CoMoveLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//������
void CCoGISView::OnCopyLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("������");
		ShowState();
		m_BaseOper = new CoCopyLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�༭�߲���
void CCoGISView::OnEditLinepro()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("�༭�߲���");
		ShowState();
		m_BaseOper = new CoAlterLinePro(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//������
void CCoGISView::OnCutLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("������");
		ShowState();
		m_BaseOper = new CoCutLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//���ϼӵ�
void CCoGISView::OnAddpntLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("���ϼӵ�");
		ShowState();
		m_BaseOper = new CoAddPntLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�����Ƶ�
void CCoGISView::OnMovepntOnline()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
		{
			m_CurrentOper=_T("�����Ƶ�");
			ShowState();
			m_BaseOper = new CoMovePntLine(this,m_DB,getLineAct(),m_CoScreen);
		}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//����ɾ��
void CCoGISView::OnDelpntOnline()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("����ɾ��");
		ShowState();
		m_BaseOper = new CoDelPntLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ɾ����
void CCoGISView::OnDelLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper=_T("ɾ����");
		ShowState();
		m_BaseOper = new CoDeleteLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ɾ��������
void CCoGISView::OnDelallLine()
{
	// TODO: �ڴ���������������
	if(isLineActive())
	{
		m_CurrentOper=_T("ɾ��������");
		ShowState();
		CoDleAllLine del(this,m_DB,getLineAct());
		del.DeleteAllLine();
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//==============���˵���ز���==============//

//������
void CCoGISView::OnInputPolygon()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("������");
		ShowState();
		m_BaseOper = new CoInputPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ѡ����
void CCoGISView::OnSelectPoly()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("ѡ����");
		ShowState();
		m_BaseOper = new CoSelectPoly(this,m_DB,getAreaAct(),m_CoScreen,TRUE);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//������
void CCoGISView::OnCopyPoly()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("������");
		ShowState();
		m_BaseOper = new CoCopyPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//�ƶ���
void CCoGISView::OnMovePoly()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("�ƶ���");
		ShowState();
		m_BaseOper = new CoMovePoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//�޸�������
void CCoGISView::OnRepolyPro()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("�޸�������");
		ShowState();
		m_BaseOper = new CoModifyPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//���ѡ��״̬
void CCoGISView::OnClearAreaState()
{
	// TODO: �ڴ���������������
	m_CurrentOper =_T("���ѡ��");
	ShowState();
	CoSelectPoly DelSelect;
	DelSelect.DelSelect();
	Invalidate(TRUE);
}

//�߽�ӵ�
void CCoGISView::OnAddPntArea()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if (isAreaActive())
	{
		m_CurrentOper =_T("�߽�ӵ�");
		ShowState();
		m_BaseOper=new CoAddPntPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�߽��Ƶ�
void CCoGISView::OnMovePntArea()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if (isAreaActive())
	{
		m_CurrentOper =_T("�߽��Ƶ�");
		ShowState();
		m_BaseOper=new CoMovePntPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�߽�ɾ��
void CCoGISView::OnDelPntArea()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if (isAreaActive())
	{
		m_CurrentOper =_T("�߽�ɾ��");
		ShowState();
		m_BaseOper=new CoDelPntPoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}
//ɾ����
void CCoGISView::OnDelPoly()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper=_T("ɾ����");
		ShowState();
		m_BaseOper = new CoDeletePoly(this,m_DB,getAreaAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);

}

//ɾ��������
void CCoGISView::OnDelallPoly()
{
	// TODO: �ڴ���������������
	if(isAreaActive())
	{
		m_CurrentOper=_T("ɾ��������");
		ShowState();
		CoDeleteAllPoly DelAll(this,m_DB,getAreaAct());
		DelAll.DelAllPoly();
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//==============ע�Ͳ˵���ز���============//

//����ע��
void CCoGISView::OnInputTag()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("����ע��");
		ShowState();
		m_BaseOper = new CoInputTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ѡ��ע��
void CCoGISView::OnSelectTag()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("ѡ��ע��");
		ShowState();
		m_BaseOper = new CoSelectTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�ƶ�ע��
void CCoGISView::OnMoveTag()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("�ƶ�ע��");
		ShowState();
		m_BaseOper = new CoMoveTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//����ע��
void CCoGISView::OnCopyTag()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("����ע��");
		ShowState();
		m_BaseOper = new CoCopyTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�޸�ע���ı�
void CCoGISView::OnAlterTagtext()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("�޸�ע���ı�");
		ShowState();
		m_BaseOper = new CoAlterTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�޸�ע�Ͳ���
void CCoGISView::OnReTaggpro()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("�޸�ע�Ͳ���");
		ShowState();
		m_BaseOper = new CoAlterTagPro(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ɾ��ע��
void CCoGISView::OnDelTag()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isNoteActive())
	{
		m_CurrentOper=_T("ɾ��ע��");
		ShowState();
		m_BaseOper = new CoDelTag(this,m_DB,getNoteAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ɾ������ע��
void CCoGISView::OnDelallTag()
{
	// TODO: �ڴ���������������
	if(isNoteActive())
	{
		m_CurrentOper=_T("ɾ������ע��");
		ShowState();
		CoDelAllTag DelAllTag(this,m_DB,getNoteAct());
		DelAllTag.DelAllTag();
	}
	else
		MessageBox("û���ҵ�ע���ļ�,���½��򼤻����е�ע���ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//============�ռ�����˵���ز���============//

//ѡ���
void CCoGISView::OnTopoSelpnt()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isPntActive())
	{
		m_CurrentOper =_T("����ѡ��");
		ShowState();
		m_BaseOper = new CoTopo(this,m_DB,getPntAct(),1,m_CoScreen);
	}

	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����еĵ��ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ѡ����
void CCoGISView::OnTopoSelline()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper =_T("����ѡ��");
		ShowState();
		m_BaseOper = new CoTopo(this,m_DB,getLineAct(),2,m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//ѡ����
void CCoGISView::OnTopoSelpoly()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isAreaActive())
	{
		m_CurrentOper =_T("����ѡ��");
		ShowState();
		m_BaseOper = new CoTopo(this,m_DB,getAreaAct(),3,m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}

//�Զ����������
void CCoGISView::OnGetDistance()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	m_CurrentOper=_T("��������");
	ShowState();
	m_BaseOper = new CoDistance(this,m_CoScreen);
}
//��֪�߶�����
void CCoGISView::OnDisLine()
{
	// TODO: �ڴ���������������
	DelectMouseOper();
	if(isLineActive())
	{
		m_CurrentOper =_T("��֪�߶�����");
		ShowState();
		m_BaseOper = new CoDistanceLine(this,m_DB,getLineAct(),m_CoScreen);
	}
	else
		MessageBox("û���ҵ����ļ�,���½��򼤻����е����ļ���","��ʾ",MB_OK |MB_ICONASTERISK);
}
//=============���������ز˵���Ӧ===========//

//�Ŵ�
void CCoGISView::OnZoonIn()
{
	// TODO: �ڴ���������������
	m_CurrentOper =_T("�Ŵ�");
	ShowState();
	DelectMouseOper();
	m_OverAllOper = 1;
	m_BaseOper = new CoZoonIn(this,m_CoScreen);

}

//��С
void CCoGISView::OnZoonOut()
{
	// TODO: �ڴ���������������
	m_CurrentOper =_T("��С");
	ShowState();
	DelectMouseOper();
	m_OverAllOper = 2;
	m_BaseOper = new CoZoonOut(this,m_CoScreen);
}

//�ƶ�
void CCoGISView::OnPan()
{
	// TODO: �ڴ���������������
	m_CurrentOper =_T("�ƶ�");
	ShowState();
	DelectMouseOper();
	m_OverAllOper = 3;
	m_BaseOper = new CoPan(this,m_CoScreen);
}

//��λ
void CCoGISView::OnMicfw()
{
	// TODO: �ڴ���������������
	m_CurrentOper =_T("��λ");
	ShowState();
	DelectMouseOper();
	m_OverAllOper=0;
	m_CoScreen.sx=0;
	m_CoScreen.sy=0;
	m_CoScreen.blc=1;
	DisPaly();
	Invalidate(TRUE);
}

//ˢ��
void CCoGISView::OnFrash()
{
	// TODO: �ڴ���������������
	Invalidate(TRUE);
}

/*===========Start���ò˵�==============*/

/*===========end���ò˵�==============*/


void CCoGISView::DelectMouseOper()
{
	if (m_BaseOper != NULL)
	{
		delete m_BaseOper;
		m_BaseOper = NULL;
	}
	m_OverAllOper= 0;
}

//��ʾ״̬����
void CCoGISView::ShowState()
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CMFCStatusBar&pStatus = pFrame->GetStatusBar();
	pStatus.SetPaneText(pStatus.CommandToIndex(ID_INDICATOR_NUM), m_CurrentOper,TRUE);
}

//��Ļ����ת������ int to double
void CCoGISView::VPtoDP(int x,int y,double* X,double* Y)
{
	*X=m_CoScreen.sx+x*m_CoScreen.blc;
	if(m_MapMode==1)
		*Y=m_CoScreen.sy+m_CoScreen.blc*(m_CoScreen.hScreen-y);
	else
		*Y=m_CoScreen.sy+m_CoScreen.blc*(y+m_CoScreen.hScreen);
}

void CCoGISView::DPtoVP(double x,double y,int* X,int* Y)
{
	*X=(int)((x-m_CoScreen.sx)/m_CoScreen.blc);
	if(m_MapMode==1)
		*Y=m_CoScreen.hScreen-(int)((y-m_CoScreen.sy)/m_CoScreen.blc);
	else
		*Y=(int)((y-m_CoScreen.sy)/m_CoScreen.blc)-m_CoScreen.hScreen;
}

double CCoGISView::VLtoDL(int l)
{
	return m_CoScreen.blc*l;
}

int CCoGISView::DLtoVL(double l)
{
	return (int)(l/m_CoScreen.blc);
}

//��Ļ���ڱ仯����
void CCoGISView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	m_CoScreen.wScreen = cx;//��ͼ��Ļ�Ŀ��
	m_CoScreen.hScreen = cy;//��ͼ��Ļ�ĸ߶�
}

//�����ػ�ĺ���
void CCoGISView::DisPaly()
{
	if(m_OverAllOper == 1)
	{
		CoZoonIn obj;
		m_CoScreen = obj.m_Screen;
	}

	if(m_OverAllOper==2)
	{
		CoZoonOut obj;
		m_CoScreen = obj.m_Screen;
	}

	if(m_OverAllOper==3)
	{
		CoPan obj;
		m_CoScreen = obj.m_Screen;
	}
	CString type;
	CoConnect conn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	CoFeatureset feature;
	CoRecorset MicReco;
	CString str;
	int lengh = theTables.size();
	CoCDC dc(this,m_CoScreen);
	for(int i=lengh-1;i>=0;i--)
	{
		if (theTables[i].isOpen==true)
		{
			feature.Open(&conn,theTables[i].itemnode);
			str.Format("SELECT ID FROM [%s]",theTables[i].itemnode);
			MicReco.Open(&feature,str);
			type=theTables[i].itemnode.Right(4);
			while (!MicReco.CoEOF())
			{
				if (type==".COP")
				{
					if (MicReco.GetPoint(m_Point,m_PntPro))
					{
						dc.DrawAllPnt(m_Point,m_PntPro);
						m_Point.x = m_Point.y = 0;
					}
				}
				if(type==".COL")
				{
					if (MicReco.GetLine(m_Line,m_LinePro))
					{
						dc.DrawLine(m_Line,m_LinePro);
						m_Line.clear();
					}
				}
				if (type==".COA")
				{
					if (MicReco.GetPolygon(m_Poly,m_PolyPro))
					{
						dc.DrawAllPoly(m_Poly,m_PolyPro);
						m_Poly.clear();
					}
				}
				if (type==".CON")
				{
					if (MicReco.GetTag(m_TagPnt,m_TagPro))
					{
						dc.DrawText(m_TagPnt,m_TagPro);
						m_TagPnt.x = m_TagPnt.y = 0;
					}
				}
				MicReco.MoveNext();
			}
		}
	}
}






