#include "StdAfx.h"
#include "_CoOverall.h"
#include <_CoLogic.h>

vector<MyTopo> CoTopo::m_TopoObject;

CoTopo::CoTopo(CView* ptView,CoDB DB,CString ActiveTB,int Style,CoScreen Screen)
{

	m_ptView = ptView;
	m_DB = DB;
	m_ActiveTB = ActiveTB;
	
	SelectPoint obj1(m_ptView,m_DB,m_ActiveTB,Screen);
	m_SelectPnt = obj1;


	CoSelectLine obj2(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectLine = obj2;


	CoSelectPoly obj3(m_ptView,m_DB,m_ActiveTB,Screen,FALSE);
	m_SelectePoly = obj3;

	m_Selected = FALSE;

	m_SelectStyle = Style;

}

CoTopo::~CoTopo()
{

}

void CoTopo::LButtonDown(UINT nFlags, CoPnt point)
{
	switch(m_SelectStyle)
	{
	case 1:
		if(!m_Selected)
			m_SelectPnt.LButtonDown(nFlags,point);
		break;
	case 2:
		if(!m_Selected)
			m_SelectLine.LButtonDown(nFlags,point);
		break;
	case 3:
		if (!m_Selected)
			m_SelectePoly.LButtonDown(nFlags,point);
		break;
	default:
		break;
	}
}

void CoTopo::LButtonUp(UINT nFlags, CoPnt point)
{
	vector<CoPnt>MyPoint;
	MyTopo topo;
	switch(m_SelectStyle)
	{
	case 1:
		if(!m_Selected)
			m_SelectPnt.LButtonUp(nFlags,point);
		m_Selected = m_SelectPnt.m_Selected;
		if(m_Selected)
		{
			MyPoint.push_back(m_SelectPnt.m_pnt);
			topo.index = 1;
			topo.Object = MyPoint;
			m_TopoObject.push_back(topo);
			if(m_TopoObject.size()==2)
			{
				MyAllTopo(m_TopoObject);
				m_TopoObject.clear();
			}

			m_Selected=FALSE;
			m_SelectPnt.m_Selected = FALSE;
		}
		break;
	case 2:
		if(!m_Selected)
			m_SelectLine.LButtonUp(nFlags,point);
		m_Selected=m_SelectLine.m_Selected;
		if (m_Selected)
		{
			topo.index = 2;
			topo.Object = m_SelectLine.m_Line;

			m_TopoObject.push_back(topo);
			if(m_TopoObject.size()==2)
			{
				MyAllTopo(m_TopoObject);
				m_TopoObject.clear();
			}
			
			m_Selected=FALSE;
			m_SelectLine.m_Selected = FALSE;
		}
		break;
	case 3:
		if (!m_Selected)
			m_SelectePoly.LButtonUp(nFlags,point);
		m_Selected = m_SelectePoly.m_Selected;
		if (m_Selected)
		{
			topo.index = 3;
			topo.Object = m_SelectePoly.m_Poly;
			
			m_TopoObject.push_back(topo);
			if(m_TopoObject.size()==2)
			{
				MyAllTopo(m_TopoObject);
				m_TopoObject.clear();
			}
			
			m_Selected=FALSE;
			m_SelectePoly.m_Selected = FALSE;
		}
		break;
	default:
		break;
	}
}

void CoTopo::MouseMove(UINT nFlags, CoPnt point)
{

	switch(m_SelectStyle)
	{
	case 1:
		if(!m_Selected)
			m_SelectPnt.MouseMove(nFlags,point);
		break;
	case 2:
		if(!m_Selected)
			m_SelectLine.MouseMove(nFlags,point);
		break;
	case 3:
		if (!m_Selected)
			m_SelectePoly.MouseMove(nFlags,point);
		break;
	default:
		break;
	}

}

void CoTopo::MyAllTopo(vector<MyTopo>TopoObject)
{
	CoLog math;
	vector<CoPnt> Topo1;
	vector<CoPnt> Topo2;
	int index1;//index=1��ʾ�㣻����2��ʾ�ߣ�����3��ʾ��
	int index2;
	Topo1 = TopoObject[0].Object;
	index1 = TopoObject[0].index;
	Topo2 = TopoObject[1].Object;
	index2 = TopoObject[1].index;
	//������ϵ
	if(index1==1&&index2==1)
	{
		if(math.IsPonEqlPon(Topo1[0],Topo2[0]))
			MessageBox(m_ptView->m_hWnd,"�����غ�","��������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		else
			MessageBox(m_ptView->m_hWnd,"���������","��������˹�ϵ",MB_OK|MB_ICONINFORMATION);
	}

	//������
	if (index1==1&&index2==2)
	{
		if(math.IsPointInLine(Topo1[0],Topo2))
			MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		else
			MessageBox(m_ptView->m_hWnd,"�㲻������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
	}

	if (index1==2&&index2==1)
	{
		if(math.IsPointInLine(Topo2[0],Topo1))
			MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		else
			MessageBox(m_ptView->m_hWnd,"�㲻������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
	}

	//������

	switch(index1)
	{
	case 1:
		if(index2==3)
		{
			if(math.IsPointInPolygon(Topo1[0],Topo2))
			  MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		    else
			  MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		}
		break;

	case 3:
		if (index2==1)
		{
			if(math.IsPointInPolygon(Topo2[0],Topo1))
				MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
			else
				MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		}
		break;
	default:
		;
	}

	//������
	if (index1==2&&index2==2)
	{
		//��ȷ���1;�ཻ����2;���뷵��3
		int index=math.LineAndLine(Topo1,Topo2);
		switch(index)
		{
		case 1:
			MessageBox(m_ptView->m_hWnd,"���������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
			break;
		case 2:
			MessageBox(m_ptView->m_hWnd,"�������ཻ","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
			break;
		case 3:
			MessageBox(m_ptView->m_hWnd,"����������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		default:
			;
		}
	}

	//������
	//���뷵��1���ཻ����2�������ڷ���3
	int LinePolygon;
	switch(index1)
	{
	case 2:
		if (index2==3)
		{
			LinePolygon = math.LineAndPolygon(Topo1,Topo2);
			if(LinePolygon==1)
				MessageBox(m_ptView->m_hWnd,"����������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
			else if(LinePolygon==2)
				MessageBox(m_ptView->m_hWnd,"�������ཻ","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
			else
			MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		}
		break;

	case 3:
		if (index2==2)
		{
			LinePolygon = math.LineAndPolygon(Topo2,Topo1);
			if(LinePolygon==1)
				MessageBox(m_ptView->m_hWnd,"����������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
			else if(LinePolygon==2)
				MessageBox(m_ptView->m_hWnd,"�������ཻ","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
			else
				MessageBox(m_ptView->m_hWnd,"��������","���������˹�ϵ",MB_OK|MB_ICONINFORMATION);
		}
		break;

	default:
		;
	}

	//������
	//��ȷ���1���ཻ����2���ں�����3,���뷵��4
	if(index1==3&&index2==3)
	{
		int PolygonPolygon = math.PolygonAndPolygon(Topo2,Topo1);
		if (PolygonPolygon==1)
			MessageBox(m_ptView->m_hWnd,"���������","������������",MB_OK|MB_ICONINFORMATION);
		if(PolygonPolygon==2)
			MessageBox(m_ptView->m_hWnd,"�������ཻ","������������",MB_OK|MB_ICONINFORMATION);
		if (PolygonPolygon==3)
			MessageBox(m_ptView->m_hWnd,"���ں�","������������",MB_OK|MB_ICONINFORMATION);
		if (PolygonPolygon==4)
		    MessageBox(m_ptView->m_hWnd,"����������","������������",MB_OK|MB_ICONINFORMATION);
		if (PolygonPolygon==5)
			MessageBox(m_ptView->m_hWnd,"��������","������������",MB_OK|MB_ICONINFORMATION);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CoScreen CoZoonIn::m_Screen;

CoZoonIn::CoZoonIn()
{

}
CoZoonIn::CoZoonIn(CView* ptView,CoScreen Screen)
{
	m_ptView = ptView;
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;

	m_bDraw = FALSE;
}

CoZoonIn::~CoZoonIn()
{

}

void CoZoonIn::LButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_PtOrigin.x = m_perPoint.x = point.x;
	m_PtOrigin.y = m_perPoint.y = point.y;
}

void CoZoonIn::MouseMove(UINT nFlags, CoPnt point)
{
	if(m_bDraw)
	{
		CoCDC dc(m_ptView,m_Screen);
		dc.XDrawRectNULLFill(m_PtOrigin,m_perPoint);
		dc.XDrawRectNULLFill(m_PtOrigin,point);
		m_perPoint.x = point.x;
		m_perPoint.y = point.y;
	}
}

void CoZoonIn::LButtonUp(UINT nFlags, CoPnt point)
{
	int x1,y1,x2,y2;
	m_bDraw = FALSE;
	if ((m_PtOrigin.x==point.x)&&(m_PtOrigin.y==point.y))
	{
		CRect rect;
		GetClientRect(m_ptView->m_hWnd,&rect);
		double b11,b12;
		int n=50;
		double x=rect.Width();
		double y=rect.Height();
		double xo=point.x;
		double yo=point.y;
		m_Screen.sx=xo-(m_Screen.blc*(x-n))/2;
		m_Screen.sy=yo-(m_Screen.blc*(y-n))/2;
		b11=(x-n)/x;
		b12=(y-n)/y;
		m_Screen.blc=m_Screen.blc*max(b11,b12);
	    m_ptView->Invalidate(TRUE);
		
	}
	else
	{
		x1=min(m_PtOrigin.x,point.x);
		y1=max(m_PtOrigin.y,point.y);
		x2=max(m_PtOrigin.x,point.x);
		y2=min(m_PtOrigin.y,point.y); 
		VPtoDP(x1,y1,&m_Screen.sx,&m_Screen.sy);
		float bl1=(float)m_Screen.wScreen/(float)(x2-x1); 
		float bl2=(float)m_Screen.hScreen/(float)(y1-y2);
		if(bl2<bl1)
			bl1=bl2;
		if(bl1>0)   
			m_Screen.blc=m_Screen.blc/bl1;
	}
	m_ptView->Invalidate(TRUE);
}

void CoZoonIn::VPtoDP(long x,long y,double *X,double *Y)
{
	*X=m_Screen.sx+x*(m_Screen.blc);
	*Y=m_Screen.sy+(m_Screen.blc)*(m_Screen.hScreen-y);
}

void CoZoonIn::DPtoVP(double x,double y,int* X,int* Y)
{
	*X=(int)((x-m_Screen.sx)/m_Screen.blc);
	*Y=m_Screen.hScreen-(int)((y-m_Screen.sy)/m_Screen.blc);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CoScreen CoZoonOut::m_Screen;
CoZoonOut::CoZoonOut()
{

}
CoZoonOut::CoZoonOut(CView* ptView,CoScreen Screen)
{
	m_ptView = ptView;
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoZoonOut::~CoZoonOut()
{

}

void CoZoonOut::LButtonDown(UINT nFlags, CoPnt point)
{
	double b11,b12;
	int n=50;
	double x=m_Screen.wScreen;
	double y=m_Screen.hScreen;
	double xo=point.x;
	double yo=point.y;
	m_Screen.sx=xo-(m_Screen.blc*(n+x))/2;
	m_Screen.sy=yo-(m_Screen.blc*(n+y))/2;
	b11=(x+n)/x;
	b12=(y+n)/y;
	m_Screen.blc=m_Screen.blc*min(b11,b12);
	m_ptView->Invalidate(TRUE);
}

void CoZoonOut::VPtoDP(long x,long y,double *X,double *Y)
{
	*X=m_Screen.sx+x*(m_Screen.blc);
	*Y=m_Screen.sy+(m_Screen.blc)*(m_Screen.hScreen-y);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CoScreen CoPan::m_Screen;
CoPan::CoPan()
{

}
CoPan::CoPan(CView* ptView,CoScreen Screen)
{
	m_ptView = ptView;
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;

	m_bDraw = FALSE;
}

CoPan::~CoPan()
{
	
}

void CoPan::LButtonDown(UINT nFlags, CoPnt point)
{
	m_bDraw = TRUE;
	m_PtOrigin.x = point.x;
	m_PtOrigin.y = point.y;
}

void CoPan::MouseMove(UINT nFlags, CoPnt point)
{
	if(m_bDraw)
	{
		m_Screen.sx=m_Screen.sx-m_Screen.blc*(point.x-m_PtOrigin.x);
		m_Screen.sy=m_Screen.sy-m_Screen.blc*(point.y-m_PtOrigin.y);
	    m_PtOrigin.x = point.x;
	    m_PtOrigin.y = point.y;
	}
}

void CoPan::LButtonUp(UINT nFlags, CoPnt point)
{
	m_bDraw = FALSE;
	m_ptView->Invalidate(TRUE);
}

void CoPan::VPtoDP(long x,long y,double *X,double *Y)
{
	
	*X=m_Screen.sx+x*(m_Screen.blc);
	*Y=m_Screen.sy+(m_Screen.blc)*(m_Screen.hScreen-y);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CoScreen CoZoom::m_Screen;
CoZoom::CoZoom(CView* ptView,CoScreen Screen)
{
	m_ptView = ptView;
	m_Screen.sx = Screen.sx;
	m_Screen.sy = Screen.sy;
	m_Screen.blc = Screen.blc;
	m_Screen.wScreen = Screen.wScreen;
	m_Screen.hScreen = Screen.hScreen;
}

CoZoom::~CoZoom()
{

}

void CoZoom::MouseWheel(UINT nFlags, short zDelta, CoPnt pt)
{
	double b11,b12;
	int n=50;
	double x=m_Screen.wScreen;
	double y=m_Screen.hScreen;
	double xo=m_Screen.sx+(x*m_Screen.blc)/2;
	double yo=m_Screen.sy+(y*m_Screen.blc)/2;
	if(zDelta<0)
	{
		m_Screen.sx=xo-(m_Screen.blc*(n+x))/2;
		m_Screen.sy=yo-(m_Screen.blc*(n+y))/2;
		b11=(x+n)/x;
		b12=(y+n)/y;
		m_Screen.blc=m_Screen.blc*max(b11,b12);
	}
	else
	{
		m_Screen.sx=xo-(m_Screen.blc*(x-n))/2;
		m_Screen.sy=yo-(m_Screen.blc*(y-n))/2;
		b11=(x-n)/x;
		b12=(y-n)/y;
		m_Screen.blc=m_Screen.blc*min(b11,b12);
	}
	m_ptView->Invalidate(TRUE);
}