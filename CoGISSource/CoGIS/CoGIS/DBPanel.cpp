
#include "stdafx.h"
#include "mainfrm.h"
#include "DBPanel.h"
#include "Resource.h"
#include "CoGIS.h"
#include "DataExchange.h"//����ͨѶ
#include "_CoDLG.h"//�Ի���ͷ�ļ�
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/////////////////////////////////////////////////////////////////////////////
// CFileView
CDBView::CDBView()
{
}
CDBView::~CDBView()
{
}

BEGIN_MESSAGE_MAP(CDBView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_NEW_PNTITEM, OnNewPnt)//�½����ļ�
	ON_COMMAND(ID_NEW_LINEITEM, OnNewLine)//�½����ļ�
	ON_COMMAND(ID_NEW_AREAITEM, OnNewArea)//�½����ļ�
	ON_COMMAND(ID_NEW_NOTEITEM, OnNewNote)//�½�ע���ļ�
	ON_COMMAND(ID_OPEN_ITEM, OnOpenItem)//���ļ�
	ON_COMMAND(ID_CLOSE_ITEM, OnCloseItem)//�ر��ļ�
	ON_COMMAND(ID_ITEM_ACITIVE, OnActiveItem)//�����ļ�
	ON_COMMAND(ID_DEL_ITEM, OnDelItem)//ɾ���ļ�
	ON_COMMAND(ID_Load_DB,OnLoadDB)//�����ݿ������ļ�
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar ��Ϣ�������

int CDBView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE |TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("δ�ܴ���ͼ�������ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ������ͼͼ��:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	//m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	FillDBTCView();
	AdjustLayout();

	return 0;
}

void CDBView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

//Ĭ�Ͼ�̬�ļ�
void CDBView::FillDBTCView()
{
    hRoot = m_wndFileView.InsertItem(_T("Ĭ�Ϲ���"), 0, 0);
	/*m_wndFileView.InsertItem(_T("Ĭ�ϵ��ļ�.cp"), 1, 1, hRoot);
	m_wndFileView.InsertItem(_T("Ĭ�����ļ�.cl"), 2, 2, hRoot);
	m_wndFileView.InsertItem(_T("Ĭ�����ļ�.ca"), 3, 3, hRoot);
	m_wndFileView.InsertItem(_T("Ĭ��ע���ļ�.cn"), 4, 4, hRoot);*/
	m_wndFileView.Expand(hRoot, TVE_EXPAND);
}

//�Ҽ���Ӧ�˵�
void CDBView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}
	HTREEITEM hTreeItem;
	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}
	tempItem=hTreeItem;
	pWndTree->SetFocus();
	CMenu menu;
	CString str=m_wndFileView.GetItemText(hTreeItem);

	if((str!="Ĭ�Ϲ���")&&(hTreeItem!=NULL))
	{
		menu.LoadMenu(IDR_AITER);
		//m_DelItem = hItem; 
	}
	else
		menu.LoadMenu(IDR_MENU_NEW);
	CMenu *pPopup=menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CDBView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDBView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CDBView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CDBView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ����*/);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

/*=========start���̲����˵�==========*/
//�½����ļ�
void CDBView::OnNewPnt()
{
	//AfxMessageBox(_T("�½����ļ�"));
	/*setTemp(2);
	CMainFrame*   pMainFrm   =   (CMainFrame*)AfxGetMainWnd(); 
	pMainFrm-> GetActiveView()->Invalidate(TRUE);*/
	//CCoGISView *p=(CCoGISView*)(this->GetActiveWindow());
	CoConnect conn;
	GetConnect(conn);
	CoFeatureset DBFeatureset;
	if (NewPointDoc(&m_ProjectItem))
	{
		m_ProjectItem = m_ProjectItem+_T(".COP");
		if (DBFeatureset.Open(&conn,m_ProjectItem))
		{
			if(DBFeatureset.NewTable(1))
			{
				HTREEITEM NewItem=m_wndFileView.InsertItem(m_ProjectItem, 1, 1, hRoot);
				AddTables(m_ProjectItem,false,false,_T("COP"));
				m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
			}
		}
	}
	DBFeatureset.Close();
}
//�½����ļ�
void CDBView::OnNewLine()
{
	CoConnect conn;
	GetConnect(conn);
	CoFeatureset DBFeatureset;
	if (NewLineDoc(&m_ProjectItem))
	{
		m_ProjectItem = m_ProjectItem+_T(".COL");
		if (DBFeatureset.Open(&conn,m_ProjectItem))
		{
			if(DBFeatureset.NewTable(2))
			{
				HTREEITEM NewItem=m_wndFileView.InsertItem(m_ProjectItem, 2, 2, hRoot);
				AddTables(m_ProjectItem,false,false,_T("COL"));
				m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
			}
		}
	}
	DBFeatureset.Close();
}
//�½����ļ�
void CDBView::OnNewArea()
{
	CoConnect conn;
	GetConnect(conn);
	CoFeatureset DBFeatureset;
	if (NewPolyDoc(&m_ProjectItem))
	{
		m_ProjectItem = m_ProjectItem+_T(".COA");
		if (DBFeatureset.Open(&conn,m_ProjectItem))
		{
			if(DBFeatureset.NewTable(3))
			{
				HTREEITEM NewItem=m_wndFileView.InsertItem(m_ProjectItem, 3, 3, hRoot);
				AddTables(m_ProjectItem,false,false,_T("COA"));
				m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
			}
		}
	}
	DBFeatureset.Close();
}
//�½�ע���ļ�
void CDBView::OnNewNote()
{
	CoConnect conn;
	GetConnect(conn);
	CoFeatureset DBFeatureset;
	if (NewTagDoc(&m_ProjectItem))
	{
		m_ProjectItem = m_ProjectItem+".CON";
		if (DBFeatureset.Open(&conn,m_ProjectItem))
		{
			if(DBFeatureset.NewTable(4))
			{
				HTREEITEM NewItem=m_wndFileView.InsertItem(m_ProjectItem, 4, 4, hRoot);
				AddTables(m_ProjectItem,false,false,_T("CON"));
				m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
			}
		}
	}
	DBFeatureset.Close();
}
//�����ݿ������ļ�
void CDBView::OnLoadDB()
{
	CString filename;

	CFileDialog fileDialog(TRUE,_T("���ļ�(*.COP)|*.COP|���ļ�(*.COL)|*.COL|���ļ�(*.COA)|*.COA|ע���ļ�(*.CON)|*.CON"),
		NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T( "���ļ�(*.COP)|*.COP|���ļ�(*.COL)|*.COL|���ļ�(*.COA)|*.COA|ע���ļ�(*.CON)|*.CON||"));
	if(fileDialog.DoModal()==IDOK)
	{
		filename=fileDialog.GetFileName();
		//����ǵ��ļ�
		if (fileDialog.GetFileExt()==_T("COP"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;
			if (DBFeatureset.Open(&conn,filename))
			{
				if(DBFeatureset.NewTable(1))
				{
					HTREEITEM NewItem=m_wndFileView.InsertItem(filename, 1, 1, hRoot);
					AddTables(filename,false,false,_T("COP"));
					m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
				}
			}
			DBFeatureset.Close();
		}
		//��������ļ�
		if (fileDialog.GetFileExt()==_T("COL"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;
			if (DBFeatureset.Open(&conn,filename))
			{
				if(DBFeatureset.NewTable(2))
				{
					HTREEITEM NewItem=m_wndFileView.InsertItem(filename, 2, 2, hRoot);
					AddTables(filename,false,false,_T("COL"));
					m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
				}
			}
			DBFeatureset.Close();
		}
		//��������ļ�
		if (fileDialog.GetFileExt()==_T("COA"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;
			if (DBFeatureset.Open(&conn,filename))
			{
				if(DBFeatureset.NewTable(3))
				{
					HTREEITEM NewItem=m_wndFileView.InsertItem(filename, 3, 3, hRoot);
					AddTables(filename,false,false,_T("COA"));
					m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
				}
			}
			DBFeatureset.Close();
		}
		//�����ע���ļ�
		if (fileDialog.GetFileExt()==_T("CON"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;
			if (DBFeatureset.Open(&conn,filename))
			{
				if(DBFeatureset.NewTable(4))
				{
					HTREEITEM NewItem=m_wndFileView.InsertItem(filename, 4, 4, hRoot);
					AddTables(filename,false,false,_T("CON"));
					m_wndFileView.SetItemColor(NewItem,RGB(128,128,128));
				}
			}
			DBFeatureset.Close();
		}
	}
}
/*=========end ���̲����˵�==========*/

/*=========start���ļ�����===========*/
//���ļ�
void CDBView::OnOpenItem()
{
	//m_wndFileView.SetItemColor(tempItem,RGB(255,255,0));
	//m_wndFileView.SetItemBold(tempItem,TRUE);
	setOpenMark(m_wndFileView.GetItemText(tempItem));
	m_wndFileView.SetItemColor(tempItem,RGB(255,0,0));
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame*   pMainFrm   =   (CMainFrame*)AfxGetMainWnd(); 
	pMainFrm-> GetActiveView()->Invalidate(TRUE);
}
//�ر��ļ�
void CDBView::OnCloseItem()
{
	setCloseMark(m_wndFileView.GetItemText(tempItem));
	m_wndFileView.SetItemColor(tempItem,RGB(128,128,128));
	m_wndFileView.SetItemBold(tempItem,FALSE);
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame*   pMainFrm   =   (CMainFrame*)AfxGetMainWnd(); 
	pMainFrm-> GetActiveView()->Invalidate(TRUE);
}
//�����ļ�
void CDBView::OnActiveItem()
{
	CString tem;//����һ����ʱ�ڵ�
	HTREEITEM orItem=hRoot;
	if(setActiveMark(m_wndFileView.GetItemText(tempItem),tem))
	{
		orItem=FindTreeItem(orItem,tem);
		m_wndFileView.SetItemColor(orItem,RGB(255,0,0));
		m_wndFileView.SetItemBold(orItem,FALSE);
	
		m_wndFileView.SetItemColor(tempItem,RGB(255,0,0));
		m_wndFileView.SetItemBold(tempItem,TRUE);
	}
	else
	{
		m_wndFileView.SetItemColor(tempItem,RGB(255,0,0));
		m_wndFileView.SetItemBold(tempItem,TRUE);
	}
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame*   pMainFrm   =   (CMainFrame*)AfxGetMainWnd(); 
	pMainFrm-> GetActiveView()->Invalidate(TRUE);
}
//ɾ���ļ�
void CDBView::OnDelItem()
{
	if (MessageBox("ȷ��ɾ�����ļ���?","��ʾ",MB_YESNO| MB_ICONEXCLAMATION)==IDYES)
	{
		//�ڴ����ӵ������ݿ����
		remItemMark(m_wndFileView.GetItemText(tempItem));
		CString Table;
		Table = "TableItem";
		CString TableName = m_wndFileView.GetItemText(tempItem);
		CoConnect conn;
		GetConnect(conn); 
		CoFeatureset DBFeatureset;
		if(DBFeatureset.Open(&conn,Table))
		{
			if(DBFeatureset.DelTable(TableName))
			{
				m_wndFileView.DeleteItem(tempItem);
			}
		}
		DBFeatureset.Close();
	}
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame*   pMainFrm   =   (CMainFrame*)AfxGetMainWnd(); 
	pMainFrm-> GetActiveView()->Invalidate(TRUE);
}
/*=========end ���ļ�����===========*/

//������ؽڵ�
HTREEITEM CDBView::FindTreeItem(HTREEITEM item,CString& strText)   
{
	HTREEITEM  hFind;   
	if(item == NULL)   
		return  NULL;  

	while(item!=NULL)   
	{   
		if(m_wndFileView.GetItemText(item) == strText)   
			return item;  

		if(m_wndFileView.ItemHasChildren(item))   
		{   
			item = m_wndFileView.GetChildItem(item);   
			hFind = FindTreeItem(item,strText);   
			if(hFind)   
			{   
				return hFind;   
			}   
			else   
				item= m_wndFileView.GetNextSiblingItem(m_wndFileView.GetParentItem(item));   
		}   
		else   
		{   
			item = m_wndFileView.GetNextSiblingItem(item);   
			if(item == NULL)   
				return NULL;   
		}   
	}  

	return   item;   
}

//ɾ��view��״̬
void CDBView::DelViewState()
{
	if (m_BaseOper != NULL)
	{
		delete m_BaseOper;
		m_BaseOper = NULL;
	}
	m_OverAllOper= 0;
	m_CurrentOper=_T("�޲���");
}
