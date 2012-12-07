
#pragma once

#include "ViewTreeD.h"

class CDBViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CDBView : public CDockablePane
{
// ����
public:

	CDBView();

	void AdjustLayout();
	void OnChangeVisualStyle();

// ����
protected:

	CViewTreeD m_wndFileView;
	CImageList m_FileViewImages;
	CDBViewToolBar m_wndToolBar;
	HTREEITEM tempItem;

protected:
	void FillDBTCView();

// ʵ��
public:
	virtual ~CDBView();
public:
	CString m_ProjectItem;
	HTREEITEM hRoot;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);//�Ҽ��˵���Ӧ����
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNewPnt();//�½����ļ�
	afx_msg void OnNewLine();//�½����ļ�
	afx_msg void OnNewArea();//�½����ļ�
	afx_msg void OnNewNote();//�½�ע���ļ�
	afx_msg void OnOpenItem();//���ļ�
	afx_msg void OnCloseItem();//�ر��ļ�
	afx_msg void OnActiveItem();//�����ļ�
	afx_msg void OnDelItem();//ɾ���ļ�
	afx_msg void OnLoadDB();//�����ݿ��������ļ�
	DECLARE_MESSAGE_MAP()

public:
	HTREEITEM FindTreeItem(HTREEITEM item,CString& strText)   ;
	void DelViewState();
};

