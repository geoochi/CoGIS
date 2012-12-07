
#include "stdafx.h"
#include "ViewTreeD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTreeD

CViewTreeD::CViewTreeD()
{
}

CViewTreeD::~CViewTreeD()
{
}

BEGIN_MESSAGE_MAP(CViewTreeD, CTreeCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTreeD ��Ϣ�������

BOOL CViewTreeD::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

//������������
void CViewTreeD::SetItemFont(HTREEITEM hItem, LOGFONT& logfont)
{
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		cf.color = (COLORREF)-1;
	cf.logfont = logfont;
	m_mapColorFont[hItem] = cf;
}

void CViewTreeD::SetItemBold(HTREEITEM hItem, BOOL bBold)
{
	SetItemState( hItem, bBold ? TVIS_BOLD: 0, TVIS_BOLD );
}

void CViewTreeD::SetItemColor(HTREEITEM hItem, COLORREF color)
{
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		cf.logfont.lfFaceName[0] = '\0';
	cf.color = color;
	m_mapColorFont[hItem] = cf;
}

BOOL CViewTreeD::GetItemFont(HTREEITEM hItem, LOGFONT * plogfont)
{
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		return FALSE;
	if( cf.logfont.lfFaceName[0] == '\0' ) 
		return FALSE;
	*plogfont = cf.logfont;
	return TRUE;

}

BOOL CViewTreeD::GetItemBold(HTREEITEM hItem)
{
	return GetItemState( hItem, TVIS_BOLD ) & TVIS_BOLD;
}

COLORREF CViewTreeD::GetItemColor(HTREEITEM hItem)
{
	// Returns (COLORREF)-1 if color was not set
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		return (COLORREF)-1;
	return cf.color;

}

void CViewTreeD::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CTreeCtrl::OnPaint()
	// ʹ�ý�Ҫ���ƵĶ����DC����һ��memory DC
	//memory device context�ĸ�������ڴ��д���һ���ṹ����ӳһ����ʾ����Ļ���򡢴��ڡ�
	//��ӡ���ȣ��ı��档�������������ڴ���׼����Ҫ��ʾ��ͼ�񣬴Ӷ�ʵ��˫���棬���ˢ��
	//�ٶȼ���ˢ��ʱ��������˸��
	CDC memDC;
	//�ӵ�ǰDC�����ڴ����
	memDC.CreateCompatibleDC( &dc );

	//����CRect��������ȷ������
	CRect rcClip, rcClient;
	//��ȡ��ǰ����ı߽�����
	dc.GetClipBox( &rcClip );
	//��ȡ��ǰ������û�����
	GetClientRect(&rcClient);

	// Select a compatible bitmap into the memory DC
	//����һ��bmp�ļ�����ΪmemDC������
	//���ļ��Ĵ�С������������ͬ
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	memDC.SelectObject( &bitmap );

	// Set clip region to be same as that in paint DC
	//ͨ������ı߽����򴴽�CRgn����
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcClip );
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject();



	// First let the control do its default drawing.
	//�����ÿؼ��Լ�����Ĭ�ϵĻ��ƣ����Ƶ��ڴ���
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	//��ȡ��״�ؼ��ĵ�һ���ڵ�
	HTREEITEM hItem = GetFirstVisibleItem();

	//���������
	int n = GetVisibleCount()+1;
	while( hItem && n--)
	{
		CRect rect;

		// Do not meddle with selected items or drop highlighted items
		//����ѡ�еĽڵ��ʵ���ϷŹ��ܵĽڵ���в���
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;

		//�������塢��ɫ
		Color_Font cf;


		//��������
		if ( !(GetItemState( hItem, selflag ) & selflag )
			&& m_mapColorFont.Lookup( hItem, cf ))
		{
			CFont *pFontDC;
			CFont fontDC;
			LOGFONT logfont;

			if( cf.logfont.lfFaceName[0] != '\0' )
			{
				//�û�����������
				logfont = cf.logfont;
			}
			else
			{
				// �û�û�ж��壬ʹ��ϵͳ����
				CFont *pFont = GetFont();
				pFont->GetLogFont( &logfont );
			}

			//�û��Ƿ��趨�ڵ�Ϊ�Ӵ�
			if( GetItemBold( hItem ) )
				logfont.lfWeight = 700;
			//��������
			fontDC.CreateFontIndirect( &logfont );
			pFontDC = memDC.SelectObject( &fontDC );

			//����������ɫ
			if( cf.color != (COLORREF)-1 )
				memDC.SetTextColor( cf.color );

			//��ȡ�ڵ�����
			CString sItem = GetItemText( hItem );

			//��ȡ�ڵ�����
			GetItemRect( hItem, &rect, TRUE );
			//���ñ���ɫΪϵͳɫ
			memDC.SetBkColor( GetSysColor( COLOR_WINDOW ) );
			//���ڴ��е�ͼƬд������,Ϊ�ýڵ������
			memDC.TextOut( rect.left+2, rect.top+1, sItem );

			memDC.SelectObject( pFontDC );
		}
		hItem = GetNextVisibleItem( hItem );
	}


	dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC,
		rcClip.left, rcClip.top, SRCCOPY );
}

