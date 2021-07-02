
#include "stdafx.h"
#include "mainfrm.h"
#include "DBPanel.h"
#include "Resource.h"
#include "CoGIS.h"
#include "DataExchange.h"//����ͨѶ
#include "_CoDLG.h"//�Ի���ͷ�ļ�

#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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
	ON_COMMAND(ID_SAVEGEOJSON_ITEM, OnSaveGeojsonItem)//����Geojson�ļ�
	ON_COMMAND(ID_Load_DB, OnLoadDB)//�����ݿ������ļ�
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
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

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
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndFileView;
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
	tempItem = hTreeItem;
	pWndTree->SetFocus();
	CMenu menu;
	CString str = m_wndFileView.GetItemText(hTreeItem);

	if ((str != "Ĭ�Ϲ���") && (hTreeItem != NULL))
	{
		menu.LoadMenu(IDR_AITER);
		//m_DelItem = hItem; 
	}
	else
		menu.LoadMenu(IDR_MENU_NEW);
	CMenu* pPopup = menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
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
	CString filename;

	CFileDialog fileDialog(TRUE, _T("���ļ�(*.COP)|*.COP"),
		NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("���ļ�(*.COP)|*.COP||"));
	if (fileDialog.DoModal() == IDOK)
	{
		//filename = fileDialog.GetFileName();
		filename = fileDialog.GetPathName();// ��Ϊ����λ��

		//����ǵ��ļ�
		if (fileDialog.GetFileExt() == _T("COP"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;

			m_ProjectItem = filename;
			if (DBFeatureset.Open(&conn, m_ProjectItem))
			{
				if (DBFeatureset.NewTable(1))
				{
					HTREEITEM NewItem = m_wndFileView.InsertItem(m_ProjectItem, 1, 1, hRoot);
					AddTables(m_ProjectItem, false, false, _T("COP"));
					m_wndFileView.SetItemColor(NewItem, RGB(128, 128, 128));
				}
			}
			DBFeatureset.Close();

			// չ����Ŀ¼
			m_wndFileView.Expand(hRoot, TVE_EXPAND);
		}
	}


}
//�½����ļ�
void CDBView::OnNewLine()
{
	CString filename;

	CFileDialog fileDialog(TRUE, _T("���ļ�(*.COL)|*.COL|"),
		NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("���ļ�(*.COL)|*.COL||"));
	if (fileDialog.DoModal() == IDOK)
	{
		//filename = fileDialog.GetFileName();
		filename = fileDialog.GetPathName();// ��Ϊ����λ��

		//��������ļ�
		if (fileDialog.GetFileExt() == _T("COL"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;
			m_ProjectItem = filename;
			if (DBFeatureset.Open(&conn, m_ProjectItem))
			{
				if (DBFeatureset.NewTable(2))
				{
					HTREEITEM NewItem = m_wndFileView.InsertItem(m_ProjectItem, 2, 2, hRoot);
					AddTables(m_ProjectItem, false, false, _T("COL"));
					m_wndFileView.SetItemColor(NewItem, RGB(128, 128, 128));
				}
			}
			DBFeatureset.Close();

			// չ����Ŀ¼
			m_wndFileView.Expand(hRoot, TVE_EXPAND);

		}
	}

}
//�½����ļ�
void CDBView::OnNewArea()
{
	CString filename;

	CFileDialog fileDialog(TRUE, _T("���ļ�(*.COA)|*.COA"),
		NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("���ļ�(*.COA)|*.COA||"));
	if (fileDialog.DoModal() == IDOK)
	{
		//filename = fileDialog.GetFileName();
		filename = fileDialog.GetPathName();// ��Ϊ����λ��

		//��������ļ�
		if (fileDialog.GetFileExt() == _T("COA"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;
			m_ProjectItem = filename;
			if (DBFeatureset.Open(&conn, m_ProjectItem))
			{
				if (DBFeatureset.NewTable(3))
				{
					HTREEITEM NewItem = m_wndFileView.InsertItem(m_ProjectItem, 3, 3, hRoot);
					AddTables(m_ProjectItem, false, false, _T("COA"));
					m_wndFileView.SetItemColor(NewItem, RGB(128, 128, 128));
				}
			}
			DBFeatureset.Close();

			// չ����Ŀ¼
			m_wndFileView.Expand(hRoot, TVE_EXPAND);

		}
	}

}
//�½�ע���ļ�
void CDBView::OnNewNote()
{
	CString filename;

	CFileDialog fileDialog(TRUE, _T("ע���ļ�(*.CON)|*.CON"),
		NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("ע���ļ�(*.CON)|*.CON||"));
	if (fileDialog.DoModal() == IDOK)
	{
		//filename = fileDialog.GetFileName();
		filename = fileDialog.GetPathName();// ��Ϊ����λ��

		//�����ע���ļ�
		if (fileDialog.GetFileExt() == _T("CON"))
		{
			CoConnect conn;
			GetConnect(conn);
			CoFeatureset DBFeatureset;
			m_ProjectItem = filename;
			if (DBFeatureset.Open(&conn, m_ProjectItem))
			{
				if (DBFeatureset.NewTable(4))
				{
					HTREEITEM NewItem = m_wndFileView.InsertItem(m_ProjectItem, 4, 4, hRoot);
					AddTables(m_ProjectItem, false, false, _T("CON"));
					m_wndFileView.SetItemColor(NewItem, RGB(128, 128, 128));
				}
			}
			DBFeatureset.Close();

			// չ����Ŀ¼
			m_wndFileView.Expand(hRoot, TVE_EXPAND);
		}
	}

}

void CDBView::OnLoadFile(CString filename, CString fileExt)
{
	int nImage, nSelectedImage;
	if (fileExt == _T("COP"))
		nImage = nSelectedImage = 1;
	else if (fileExt == _T("COL"))
		nImage = nSelectedImage = 2;
	else if (fileExt == _T("COA"))
		nImage = nSelectedImage = 3;
	else if (fileExt == _T("CON"))
		nImage = nSelectedImage = 4;

	CoConnect conn;
	GetConnect(conn);
	CoFeatureset DBFeatureset;
	if (DBFeatureset.Open(&conn, filename))
	{
		HTREEITEM NewItem = m_wndFileView.InsertItem(filename, nImage, nSelectedImage, hRoot);
		AddTables(filename, false, false, fileExt);
		m_wndFileView.SetItemColor(NewItem, RGB(128, 128, 128));
	}
	DBFeatureset.Close();

	// չ����Ŀ¼
	m_wndFileView.Expand(hRoot, TVE_EXPAND);
}

string replace(string src, const string old_value, const string new_value) {
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		if ((pos = src.find(old_value, pos)) != string::npos) {
			src.replace(pos, old_value.length(), new_value);
		}
		else break;
	}
	return src;
}

string ClearGeojson(string src)
{
	src = replace(src, string(" "), string(""));
	src = replace(src, string("\t"), string(""));
	src = replace(src, string("\n"), string(""));
	return src;
}

string ReadGeojson(ifstream& ifs)
{
	stringstream buffer;
	buffer << ifs.rdbuf();
	string contents(buffer.str());
	contents = ClearGeojson(contents);

	return contents;
}

void WriteCOPFile(CString filename, string geojsonString)
{
	regex reg(R"(\{\"type\":\"Feature\",\"properties\":\{\"PntID\":([0-9]{1,4}),\"PntRadio\":([0-9]{1,4}),\"PntStyle\":([0-9]{1,4}),\"PntColor\":([0-9]{1,4}),\"PntLayer\":([0-9]{1,4})\},\"geometry\":\{\"type\":\"Point\",\"coordinates\":\[\[([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*)\]\]\}\})");
	sregex_iterator start(geojsonString.begin(), geojsonString.end(), reg);
	sregex_iterator end;

	CFile file;
	file.Open(LPCTSTR(filename), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	int ID, PntRadio, PntStyle, PntColor, PntLayer;
	double x, y;
	for (sregex_iterator it = start; it != end; ++it)
	{
		ID       = atoi((*it)[1].str().c_str());
		PntRadio = atoi((*it)[2].str().c_str());
		PntStyle = atoi((*it)[3].str().c_str());
		PntColor = atoi((*it)[4].str().c_str());
		PntLayer = atoi((*it)[5].str().c_str());
		x        = atof((*it)[6].str().c_str());
		y        = atof((*it)[7].str().c_str());
		ar << ID << PntRadio << PntStyle << PntColor << PntLayer;
		ar << x << y;
	}
	ar.Close();
	file.Close();
}

void WriteCOLFile(CString filename, string geojsonString)
{
	vector<vector<string>>lineProList{};
	vector<string>lineXYList{};
	int lineCount = 0;

	regex reg(R"(\{\"type\":\"Feature\",\"properties\":\{\"LineID\":([0-9]{1,4}),\"LineStyle\":([0-9]{1,4}),\"LineWidth\":([0-9]{1,4}),\"LineColor\":([0-9]{1,10}),\"LineLayer\":([0-9]{1,4}),\"size\":([0-9]{1,4})\},\"geometry\":\{\"type\":\"LineString\",\"coordinates\":\[((\[([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*)\])*,*)*\]\}\})");
	sregex_iterator start(geojsonString.begin(), geojsonString.end(), reg);
	sregex_iterator end;
	for (sregex_iterator it = start; it != end; ++it)
	{
		++lineCount;
		vector<string>linePro{};
		for (int i = 1; i <= 6; i++)
			linePro.push_back((*it)[i].str());
		lineProList.push_back(linePro);
	}
	regex reg2(R"(\[((\[([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*)\])*,*)*\])");
	sregex_iterator start2(geojsonString.begin(), geojsonString.end(), reg2);
	sregex_iterator end2;
	for (sregex_iterator it2 = start2; it2 != end2; ++it2)
		lineXYList.push_back((*it2)[0].str());

	CFile file;
	file.Open(LPCTSTR(filename), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	int ID, LineStyle, LineWidth, LineColor, LineLayer, linenum;
	double x, y;

	bool flag;
	for (int num = 0; num < lineCount; num++)
	{
		ID        = atoi(lineProList[num][0].c_str());
		LineStyle = atoi(lineProList[num][1].c_str());
		LineWidth = atoi(lineProList[num][2].c_str());
		LineColor = atoi(lineProList[num][3].c_str());
		LineLayer = atoi(lineProList[num][4].c_str());
		linenum   = atoi(lineProList[num][5].c_str());
		ar << ID << LineStyle << LineWidth << LineColor << LineLayer << linenum;

		regex reg3(R"(([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*))");
		sregex_iterator start3(lineXYList[num].begin(), lineXYList[num].end(), reg3);
		sregex_iterator end3;

		flag = true;
		for (sregex_iterator it3 = start3; it3 != end3; ++it3)
			if (flag)
			{
				flag = false;
				x = atof((*it3)[1].str().c_str());
				y = atof((*it3)[2].str().c_str());
				ar << x << y;
			}
			else
				flag = true;
	}
	ar.Close();
	file.Close();
}

void WriteCOAFile(CString filename, string geojsonString)
{
	vector<vector<string>>polyProList{};
	vector<string>polyXYList{};
	int polyCount = 0;

	regex reg(R"(\{\"type\":\"Feature\",\"properties\":\{\"PolyID\":([0-9]{1,4}),\"PolyArea\":([0-9]{1,4}),\"PolyColor\":([0-9]{1,10}),\"PolyFillStyle\":([0-9]{1,4}),\"PolyStyle\":([0-9]{1,4}),\"PolyLayer\":([0-9]{1,4}),\"size\":([0-9]{1,4})\},\"geometry\":\{\"type\":\"Polygon\",\"coordinates\":\[((\[([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*)\])*,*)*\]\}\})");
	sregex_iterator start(geojsonString.begin(), geojsonString.end(), reg);
	sregex_iterator end;
	for (sregex_iterator it = start; it != end; ++it)
	{
		++polyCount;
		vector<string>polyPro{};
		for (int i = 1; i <= 7; i++)
			polyPro.push_back((*it)[i].str());
		polyProList.push_back(polyPro);
	}
	regex reg2(R"(\[((\[([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*)\])*,*)*\])");
	sregex_iterator start2(geojsonString.begin(), geojsonString.end(), reg2);
	sregex_iterator end2;
	for (sregex_iterator it2 = start2; it2 != end2; ++it2)
		polyXYList.push_back((*it2)[0].str());

	CFile file;
	file.Open(LPCTSTR(filename), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	int ID, PolyColor, PolyFillStyle, PolyStyle, PolyLayer, polynum;
	double PolyArea, x, y;

	bool flag;
	for (int num = 0; num < polyCount; num++)
	{
		ID            = atoi(polyProList[num][0].c_str());
		PolyArea      = atof(polyProList[num][1].c_str());
		PolyColor     = atoi(polyProList[num][2].c_str());
		PolyFillStyle = atoi(polyProList[num][3].c_str());
		PolyStyle     = atoi(polyProList[num][4].c_str());
		PolyLayer     = atoi(polyProList[num][5].c_str());
		polynum       = atoi(polyProList[num][6].c_str());
		ar << ID << PolyArea << PolyColor << PolyFillStyle << PolyStyle << PolyLayer << polynum;

		regex reg3(R"(([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*))");
		sregex_iterator start3(polyXYList[num].begin(), polyXYList[num].end(), reg3);
		sregex_iterator end3;

		flag = true;
		for (sregex_iterator it3 = start3; it3 != end3; ++it3)
			if (flag)
			{
				flag = false;
				x = atof((*it3)[1].str().c_str());
				y = atof((*it3)[2].str().c_str());
				ar << x << y;
			}
			else
				flag = true;
	}
	ar.Close();
	file.Close();
}

void WriteCONFile(CString filename, string geojsonString)
{
	regex reg(R"(\{\"type\":\"Feature\",\"properties\":\{\"ID\":([0-9]{1,4}),\"TagAngle\":([0-9]{1,4}),\"TagColor\":([0-9]{1,10}),\"TagFont\":\"(\S{1,20})\",\"TagHeight\":([0-9]{1,4}),\"TagLayer\":([0-9]{1,4}),\"TagOffsite\":([0-9]{1,4}),\"TagStr\":\"(\S{1,20})\",\"TagWidth\":([0-9]{1,4}),\"TextAngle\":([0-9]{1,4})\},\"geometry\":\{\"type\":\"Tag\",\"coordinates\":\[\[([0-9]*\.*[0-9]*),([0-9]*\.*[0-9]*)\]\]\}\})");
	sregex_iterator start(geojsonString.begin(), geojsonString.end(), reg);
	sregex_iterator end;

	CFile file;
	file.Open(LPCTSTR(filename), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	int ID, TagColor, TagHeight, TagLayer, TagOffsite, TagWidth;
	float TagAngle, TextAngle;
	CString TagFont, TagStr;
	double x, y;
	for (sregex_iterator it = start; it != end; ++it)
	{
		ID         =    atoi((*it)[1].str().c_str());
		TagAngle   =    atof((*it)[2].str().c_str());
		TagColor   =    atoi((*it)[3].str().c_str());
		TagFont    = CString((*it)[4].str().c_str());
		TagHeight  =    atoi((*it)[5].str().c_str());
		TagLayer   =    atoi((*it)[6].str().c_str());
		TagOffsite =    atoi((*it)[7].str().c_str());
		TagStr     = CString((*it)[8].str().c_str());
		TagWidth   =    atoi((*it)[9].str().c_str());
		TextAngle  =    atof((*it)[10].str().c_str());
		x          =    atof((*it)[11].str().c_str());
		y          =    atof((*it)[12].str().c_str());
		ar << ID << TagAngle << TagColor << TagFont << TagHeight << TagLayer << TagOffsite << TagStr << TagWidth << TextAngle;
		ar << x << y;
	}
	ar.Close();
	file.Close();
}


//�����ݿ������ļ�
void CDBView::OnLoadDB()
{
	CFileDialog fileDialog(TRUE, _T("�����ļ�(*.*)|*.*|geojson�ļ�(*.geojson)|*.geojson|���ļ�(*.COP)|*.COP|���ļ�(*.COL)|*.COL|���ļ�(*.COA)|*.COA|ע���ļ�(*.CON)|*.CON"),
		NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("�����ļ�(*.*)|*.*|geojson�ļ�(*.geojson)|*.geojson|���ļ�(*.COP)|*.COP|���ļ�(*.COL)|*.COL|���ļ�(*.COA)|*.COA|ע���ļ�(*.CON)|*.CON||"));
	if (fileDialog.DoModal() == IDOK)
	{
		//CString filename = fileDialog.GetFileName();
		CString filename = fileDialog.GetPathName();// ��Ϊ����λ��
		CString fileExt = fileDialog.GetFileExt();

		//�����Geojson�ļ�
		if (fileExt == _T("geojson"))
		{
			ifstream ifs(filename);
			string geojsonString = ReadGeojson(ifs);
			ifs.close();
			regex  reg(R"(\"geometry\":\{\"type\":\"(.*?)\")");
			sregex_iterator start(geojsonString.begin(), geojsonString.end(), reg);
			string geoType;
			geoType = (*start)[1];
			if (geoType == "Point")
			{
				fileExt = CString("COP");
				filename = filename.Left(filename.GetLength() - 8) + "_COP." + fileExt;
				WriteCOPFile(filename, geojsonString);
			}
			else if (geoType == "LineString")
			{
				fileExt = CString("COL");
				filename = filename.Left(filename.GetLength() - 8) + "_COL." + fileExt;
				WriteCOLFile(filename, geojsonString);
			}
			else if (geoType == "Polygon")
			{
				fileExt = CString("COA");
				filename = filename.Left(filename.GetLength() - 8) + "_COA." + fileExt;
				WriteCOAFile(filename, geojsonString);
			}
			else if (geoType == "Tag")
			{
				fileExt = CString("CON");
				filename = filename.Left(filename.GetLength() - 8) + "_CON." + fileExt;
				WriteCONFile(filename, geojsonString);
			}
		}

		if (fileExt == _T("COP") | fileExt == _T("COL") | fileExt == _T("COA") | fileExt == _T("CON"))
			OnLoadFile(filename, fileExt);
		else
			AfxMessageBox("�ļ���ʽ����ȷ��");
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
	m_wndFileView.SetItemColor(tempItem, RGB(255, 0, 0));
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->GetActiveView()->Invalidate(TRUE);
}
//�ر��ļ�
void CDBView::OnCloseItem()
{
	setCloseMark(m_wndFileView.GetItemText(tempItem));
	m_wndFileView.SetItemColor(tempItem, RGB(128, 128, 128));
	m_wndFileView.SetItemBold(tempItem, FALSE);
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->GetActiveView()->Invalidate(TRUE);
}
//�����ļ�
void CDBView::OnActiveItem()
{
	CString tem;//����һ����ʱ�ڵ�
	HTREEITEM orItem = hRoot;
	if (setActiveMark(m_wndFileView.GetItemText(tempItem), tem))
	{
		orItem = FindTreeItem(orItem, tem);
		m_wndFileView.SetItemColor(orItem, RGB(255, 0, 0));
		m_wndFileView.SetItemBold(orItem, FALSE);

		m_wndFileView.SetItemColor(tempItem, RGB(255, 0, 0));
		m_wndFileView.SetItemBold(tempItem, TRUE);
	}
	else
	{
		m_wndFileView.SetItemColor(tempItem, RGB(255, 0, 0));
		m_wndFileView.SetItemBold(tempItem, TRUE);
	}
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->GetActiveView()->Invalidate(TRUE);
}
//ɾ���ļ�
void CDBView::OnDelItem()
{
	if (MessageBox("ȷ��ɾ�����ļ���?", "��ʾ", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
	{
		//�ڴ����ӵ������ݿ����
		remItemMark(m_wndFileView.GetItemText(tempItem));
		CString Table;
		Table = "TableItem";
		CString TableName = m_wndFileView.GetItemText(tempItem);
		CoConnect conn;
		GetConnect(conn);
		CoFeatureset DBFeatureset;
		if (DBFeatureset.Open(&conn, Table))
		{
			if (DBFeatureset.DelTable(TableName))
			{
				m_wndFileView.DeleteItem(tempItem);
			}
		}
		DBFeatureset.Close();
	}
	//view״̬���
	DelViewState();
	//ˢ����ʾ
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->GetActiveView()->Invalidate(TRUE);
}
//����Geojson�ļ�
void CDBView::OnSaveGeojsonItem()
{
	CString TableName = m_wndFileView.GetItemText(tempItem);
	CoConnect conn;
	GetConnect(conn);
	CoFeatureset DBFeatureset;
	DBFeatureset.Open(&conn, TableName);
	DBFeatureset.ReadFileMy();
	DBFeatureset.SaveGeojsonMy();
}
/*=========end ���ļ�����===========*/

//������ؽڵ�
HTREEITEM CDBView::FindTreeItem(HTREEITEM item, CString& strText)
{
	HTREEITEM  hFind;
	if (item == NULL)
		return  NULL;

	while (item != NULL)
	{
		if (m_wndFileView.GetItemText(item) == strText)
			return item;

		if (m_wndFileView.ItemHasChildren(item))
		{
			item = m_wndFileView.GetChildItem(item);
			hFind = FindTreeItem(item, strText);
			if (hFind)
			{
				return hFind;
			}
			else
				item = m_wndFileView.GetNextSiblingItem(m_wndFileView.GetParentItem(item));
		}
		else
		{
			item = m_wndFileView.GetNextSiblingItem(item);
			if (item == NULL)
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
	m_OverAllOper = 0;
	m_CurrentOper = _T("�޲���");
}
