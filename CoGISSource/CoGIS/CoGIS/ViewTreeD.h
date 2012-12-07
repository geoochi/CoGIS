
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTreeD ����

class CViewTreeD : public CTreeCtrl
{
// ����
public:
	CViewTreeD();

// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// ʵ��
public:
	virtual ~CViewTreeD();
//�Զ���ı�������ɫ
protected:
	struct Color_Font
	{
		COLORREF color;
		LOGFONT  logfont;
	};
//������ɫ��Ϣ�ı���
protected:
	CMap< void*, void*, Color_Font, Color_Font& > m_mapColorFont ;
protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetItemFont(HTREEITEM hItem, LOGFONT& logfont);
	void SetItemBold(HTREEITEM hItem, BOOL bBold);
	void SetItemColor(HTREEITEM hItem, COLORREF color);
	BOOL GetItemFont(HTREEITEM hItem, LOGFONT * plogfont);
	BOOL GetItemBold(HTREEITEM hItem);
	COLORREF GetItemColor(HTREEITEM hItem);
	afx_msg void OnPaint();
};
