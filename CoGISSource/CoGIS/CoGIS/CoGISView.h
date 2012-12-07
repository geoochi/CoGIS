// CoGISView.h : CCoGISView ��Ľӿ�
//


#pragma once

#include <_MouseOper.h>
#include "CoStructClass.h"
class CCoGISView : public CView
{
protected: // �������л�����
	CCoGISView();
	DECLARE_DYNCREATE(CCoGISView)

// ����
public:
	CCoGISDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCoGISView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��	
public:
	CoScreen m_CoScreen;
	int m_MapMode;
	int ShStatae;
private:
	CoPnt m_Point;
	CoPntPro m_PntPro;
	//=======================
	vector<CoPnt>m_Line;
	CoLinePro m_LinePro;
	//=======================
	vector<CoPnt>m_Poly;
	CoPolyPro m_PolyPro;
	//=======================

	CoPnt m_TagPnt;
	CoTagPro m_TagPro;
public:
	void ShowState();//��ʾ״̬����
	void DPtoVP(double x,double y,int* X,int* Y);//ʵ������ת�����߼�����
	void VPtoDP(int x,int y,double* X,double* Y);//�߼�����ת����ʵ������
	int DLtoVL(double l);
	double VLtoDL(int l);
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCeshi();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInputPoint();
	afx_msg void OnSelectPoint();
	afx_msg void OnMovePoint();
	afx_msg void OnCopyPoint();
	afx_msg void OnRePointpro();
	afx_msg void OnDelPoint();
	afx_msg void OnDelallPoint();
	afx_msg void OnInputLine();
	afx_msg void OnSelectLine();
	afx_msg void OnMoveLine();
	afx_msg void OnCopyLine();
	afx_msg void OnEditLinepro();
	afx_msg void OnCutLine();
	afx_msg void OnAddpntLine();
	afx_msg void OnMovepntOnline();
	afx_msg void OnDelpntOnline();
	afx_msg void OnDelLine();
	afx_msg void OnDelallLine();
	afx_msg void OnInputPolygon();
	afx_msg void OnSelectPoly();
	afx_msg void OnCopyPoly();
	afx_msg void OnMovePoly();
	afx_msg void OnRepolyPro();
	afx_msg void OnDelPoly();
	afx_msg void OnDelallPoly();
	afx_msg void OnInputTag();
	afx_msg void OnSelectTag();
	afx_msg void OnMoveTag();
	afx_msg void OnCopyTag();
	afx_msg void OnAlterTagtext();
	afx_msg void OnReTaggpro();
	afx_msg void OnDelTag();
	afx_msg void OnDelallTag();
	afx_msg void OnTopoSelpnt();
	afx_msg void OnTopoSelline();
	afx_msg void OnTopoSelpoly();
	afx_msg void OnGetDistance();
	afx_msg void OnZoonIn();
	afx_msg void OnZoonOut();
	afx_msg void OnPan();
	afx_msg void OnMicfw();
	afx_msg void OnFrash();
	void DelectMouseOper();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void DisPaly();
	afx_msg void OnClearLineState();
	afx_msg void OnClearAreaState();
	afx_msg void OnAddPntArea();
	afx_msg void OnMovePntArea();
	afx_msg void OnDelPntArea();
	afx_msg void OnDisLine();
};

#ifndef _DEBUG  // CoGISView.cpp �еĵ��԰汾
inline CCoGISDoc* CCoGISView::GetDocument() const
   { return reinterpret_cast<CCoGISDoc*>(m_pDocument); }
#endif

