
#ifndef __CoLineOper_H
#define __CoLineOper_H

#ifndef _CoLine_EXPORT_
#define LineOper  __declspec(dllimport)
#else
#define LineOper  __declspec(dllexport)
#endif

#include <_MouseOper.h>
#include <CoStructClass.h>
#include <_CoLogic.h>

//---------------------------------------------//
//������
class LineOper CoInputLine: public CoBaseTool
{
public:
	CoInputLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	~CoInputLine();
	void LButtonDown (UINT nFlags, CoPnt point);
	void RButtonDown(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void GetLinePro();
private:
	bool m_bDraw;
	CoPnt m_PtOrigin;
	CoPnt m_PerPoint;
	CoLinePro m_LinePro;
    vector<CoPnt>m_Line;
	CoDB m_DB;
	CString m_ActiveTable;
	CoScreen m_Screen;
};
//---------------------------------------------//
//ѡ����
class LineOper CoSelectLine:public CoBaseTool
{
public:
	CoSelectLine();
	CoSelectLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen,bool ISDrawPnt);
	virtual ~CoSelectLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp (UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void DelSelect();
public:
	CoRect m_rect;
	CoPnt m_orignpnt;
	CoPnt m_perpoint;
	static vector<CoPnt>m_Line;//��ŵ�ǰ�༭����
	static CoLinePro m_LinePro;//��ŵ�ǰ�༭��������
	CoDB m_DB;
	CString m_ActiveTB;
	bool m_bDraw;
	bool m_IsDrawPnt;
public:
	static bool m_Selected;//ѡ��ɹ�
	static CView* m_StaticView;
	static CoScreen m_Screen;
	
	inline static void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
	{
		CoCDC dc(m_StaticView,m_Screen);
		dc.XDrawLine(m_Line,m_LinePro);
	}
};

//---------------------------------------------//
//�ƶ���
class LineOper CoMoveLine:public CoBaseTool
{
public:
	CoMoveLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoMoveLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
 	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
 	CoLinePro m_linepro;
 	CoSelectLine m_SelectLine;

	CoDB m_DB;
	CString m_ActiveTB;

	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	bool m_bDraw;

	CoScreen m_Screen;
};

//---------------------------------------------//
//������
class LineOper CoCopyLine:public CoBaseTool
{
public:
	CoCopyLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoCopyLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	bool m_bDraw;

	int index;
	CoScreen m_Screen;
};

//---------------------------------------------//
//������
class LineOper CoCutLine:public CoBaseTool
{
public:
	CoCutLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoCutLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};

//---------------------------------------------//
//�޸�������
class LineOper CoAlterLinePro:public CoBaseTool
{
public:
	CoAlterLinePro(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoAlterLinePro();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};
//---------------------------------------------//
//���ϼӵ�
class LineOper CoAddPntLine:public CoBaseTool
{
public:
	CoAddPntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoAddPntLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};

//---------------------------------------------//
//�����Ƶ�
class LineOper CoMovePntLine:public CoBaseTool
{
public:
	CoMovePntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoMovePntLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	vector<CoPnt>m_perLine;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;

	bool m_bDraw;
	bool m_Double;
	int m_Pos;
	CoPnt m_perPoint1;
	CoPnt m_perPoint2;
	CoScreen m_Screen;
};

//---------------------------------------------//
//����ɾ��
class LineOper CoDelPntLine:public CoBaseTool
{
public:
	CoDelPntLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoDelPntLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};

//---------------------------------------------//
//ɾ����

class LineOper CoDeleteLine:public CoBaseTool
{
public:
	CoDeleteLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	virtual ~CoDeleteLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	bool m_Selected;
	vector<CoPnt>m_line;
	CoLinePro m_linepro;
	CoSelectLine m_SelectLine;
	
	CoDB m_DB;
	CString m_ActiveTB;
	CoScreen m_Screen;
};
//ɾ��������
class LineOper CoDleAllLine
{
public:
	CoDleAllLine(CView* ptView,CoDB DB,CString ActiveTable);
	virtual ~CoDleAllLine();
	void DeleteAllLine();
private:
	CView* m_ptView;
	CoDB m_DB;
	CString m_ActiveTB;
};

class LineOper CoDistance:public CoBaseTool
{
public:
	CoDistance(CView* ptView,CoScreen Screen);
	~CoDistance();
	void LButtonDown(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
	void RButtonDown(UINT nFlags, CoPnt point);
private:
	bool m_bDraw;
	CoPnt m_PtOrigin;
	CoPnt m_PerPoint;
	CoLinePro m_LinePro;
	vector<CoPnt>m_Line;
	CoDB m_DB;
	CString m_ActiveTable;
	CoScreen m_Screen;
};

class LineOper CoDistanceLine:public CoBaseTool
{
public:
	CoDistanceLine(CView* ptView,CoDB DB,CString ActiveTable,CoScreen Screen);
	~CoDistanceLine();
	void LButtonDown(UINT nFlags, CoPnt point);
	void LButtonUp(UINT nFlags, CoPnt point);
	void MouseMove(UINT nFlags, CoPnt point);
private:
	CoLinePro m_linepro;
	vector<CoPnt>m_line;
	CoSelectLine m_SelectLine;
	bool m_Selected;
	bool m_bDraw;
	CoLinePro m_LinePro;
	CoPnt m_ptOrigin;
	CoPnt m_perPoint;
	CoScreen m_Screen;
};

#ifndef _CoLine_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoLine.lib")
#else
#pragma comment(lib,"CoLine.lib")
#endif
#endif
#endif

