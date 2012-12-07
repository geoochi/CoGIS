#ifndef _CoLogic_H
#define _CoLogic_H

#ifndef _CoLogic_EXPORT_
#define Logic  __declspec(dllimport)
#else
#define Logic  __declspec(dllexport)
#endif

#include "CoStructClass.h"

typedef float Matrix3x3 [3][3];
class _CoLogic  
{
public:
	_CoLogic();
	virtual ~_CoLogic();
};

//=================================================
//�߼�����
//=================================================
class Logic CoLog
{
public:
	CoLog();
	CoLog(double operx,double opery);
	CoLog(double rotejd);
	~CoLog();

public:
	//�����еĵ����ҵ�����x
	double GetMax_X(vector<CoPnt>& Point);
	//�����еĵ����ҵ�����y
	double GetMax_Y(vector<CoPnt>& Point);
	//�����еĵ����ҵ���С��x
	double GetMin_X(vector<CoPnt>& Point);
	//�����еĵ����ҵ���С��y
	double GetMin_Y(vector<CoPnt>& Point);


	CoRect GetMaxRect(CoRect rc1,CoRect rc2);

public:
	//����һ��ͼԪ����Ӿ���
	CoRect GetRect(vector<CoPnt>& Point);
    bool IsPointInLine(CoPnt point,vector<CoPnt>&Line);//���Ƿ�������
	bool IsPonEqlPon(CoPnt point1,CoPnt point2);//�ж��������Ƿ��غ�

	//���������ε�����Բ�뾶��Բ��
	bool InnerCircle_Radius(CoPnt A,CoPnt B,CoPnt C,int& radius,CoPnt& Center);
    //���Ƿ�������
	bool IsPointInLine(CoPnt point,CoPnt startPoint,CoPnt endPoint);
	//�����������
	double DistancePonToPon(CoPnt point1,CoPnt point2);
	//�ж������Ƿ��غ�
	bool IsTwoPntEqule(CoPnt point1,CoPnt point2);
	//����㵽�ߵľ���
	double DistancePointToLine(CoPnt point,CoPnt startPoint,CoPnt endPoint);
	//���Ƿ��ڶ�����ڲ�
	bool IsPointInPolygon(CoPnt point,vector<CoPnt>& Poly);
    //�жϵ��ϸ����������
	bool PointInLine(CoPnt point,CoPnt startPoint,CoPnt endPoint);
	//�ж�2���߶��Ƿ��ཻ
	bool IsTwoLineIntersect(CoPnt startPointA,CoPnt endPointA,CoPnt startPointB,CoPnt endPointB);

	//========================================================
	bool CutLine(CoPnt point,vector<CoPnt>& Line1,vector<CoPnt>& Line2);
	bool AddPntInLine(CoPnt point,vector<CoPnt>& Line);
	int GetPos(CoPnt point,vector<CoPnt>& Line);
	bool DeletePntLine(CoPnt point,vector<CoPnt>& Line);

	bool AddPntPoly(CoPnt point,vector<CoPnt>& Poly);
	bool DelPntPoly(CoPnt point,vector<CoPnt>& Poly);

	//========================================================
	//�������
	bool IsPntInRect(CoPnt& Point,CoRect& rc);
	//�ж�һ��ֻ������������Ƿ��һ�������ཻ
	bool IsTwoLineIntersect(CoPnt startPointA,CoPnt endPointA,vector<CoPnt>& Line);
	//��������
	bool ISLineInRect(CoRect& rc,vector<CoPnt>& Line);
	//����������,���뷵��FALSE�����򷵻�TURE
	bool RectAndPoly(CoRect& rc,vector<CoPnt>&Poly);
	//======================================================
	//��ȷ���1���ཻ����2���ں�����3,���뷵��4
 	int PolygonAndPolygon(vector<CoPnt>&Polygon1,vector<CoPnt>&Polygon2);
 	//���뷵��1���ཻ����2�������ڷ���3
 	int LineAndPolygon(vector<CoPnt>&Line,vector<CoPnt>&Polygon);
 	//���뷵��1���ཻ����2�������ڷ���3
    int LineAndPolygon(CoPnt pntStart,CoPnt pntEnd,vector<CoPnt>&Polygon);
	//========================================================
	//��ȷ���1;�ཻ����2;���뷵��3
	int LineAndLine(vector<CoPnt>& Line1,vector<CoPnt>& Line2);

	//////////////////////////////////////////////////////////////////////////
	bool TwoRectDeviat(CoRect& rc1,CoRect& rc2);

	Matrix3x3 matComposite;
	void translate2D(double tx,double ty);//��άͼ��ƽ�ƾ���
	void rote2D(CoPnt pivotPt,double theta);//��άͼ����ת�任
	void scale2D(float sx,float sy,CoPnt fixedPt);//��άͼ�εı����任
	void Matrix3x3SetIdentity(Matrix3x3 matrix3x3);//���þ���Խ���Ԫ��Ϊ1
	void matrix3x3PerMulitiplay(Matrix3x3 m1,Matrix3x3 m2);//��������˽������m2��
	void displayFcn(vector<CoPnt>&verts,int Oper);//operΪ1��ʾƽ�ƣ�Ϊ2��ʾ��ת��Ϊ3��ʾ���
	double m_tranx;
	double m_trany;
	double m_rotejd;
	double m_scax;
	double m_scay;
private:
	void transformVerts2D(vector<CoPnt>& verts);//����任��������

public:
	void CopyPnt(vector<CoPnt>&Point1,vector<CoPnt>&Point2);

	double GetArea(vector<CoPnt>&Poly);
};

//=========================================================
//��ͼ�߼�
//=========================================================
class Logic CoCDC
{
public:
    CoCDC(CView* ptView,CoScreen Screen);
	~CoCDC();

	void DrawLine(CoPnt PointStart,CoPnt PointEnd,CoLinePro LinePro);
	void DrawPolygon(vector<CoPnt>& Poly,CoPolyPro PolyPro);
    void XDrawPolygon(vector<CoPnt>& Poly,CoPolyPro PolyPro);
	void DrawRect(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);
    void DrawEillpse(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);

	void DrawLine(vector<CoPnt>& Line,CoLinePro LinePro);
	void XDrawLine(vector<CoPnt>&Line,CoLinePro LinePro);
	
	void XDrawLine(CoPnt PointStart,CoPnt PointEnd,CoLinePro LinePro);
	void XDrawRect(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);
    void XDrawEillpse(CoPnt Point1,CoPnt point2,CoPolyPro PolyPro);
	void XDrawRectNULLFill(CoPnt Point1,CoPnt point2);
	void XDrawEillpseNullFill(CoPnt Point1,CoPnt point2,CoLinePro LinePro);

	void DrawAllPoly(vector<CoPnt>& Poly,CoPolyPro PolyPro);
	void XDrawAllPoly(vector<CoPnt>& Poly,CoPolyPro PolyPro);
	//====================================================================
	//����
	void DrawAllPnt(CoPnt& point,CoPntPro& pntpro);
	void XDrawAllPnt(CoPnt& point,CoPntPro& pntpro);

	void CoInvalidateRect(bool Tug,vector<CoPnt>&Point);
	void CoInvalidateRect(bool Tug,CoRect& rc);

	void DrawPoint(vector<CoPnt>& Point);
	void DrawPoint(CoPnt Point);

public:
	void DrawCirclePnt(CoPnt Point,CoPntPro PntPro);
	void XDrawCirclePnt(CoPnt Point,CoPntPro PntPro);
	
	void DrawSquarePnt(CoPnt Point,CoPntPro PntPro);
	void XDrawSquarePnt(CoPnt Point,CoPntPro PntPro);

	void DrawTrianglePnt(CoPnt Point,CoPntPro PntPro);
    void XDrawTrianglePnt(CoPnt Point,CoPntPro PntPro);

	//��������
	void XDrawText(CoPnt Point,CoTagPro &TagPro,int Tug);
	void DrawText(CoPnt Point,CoTagPro &TagPro);
private:
	CView* m_ptView;
	CoScreen m_Screen;

private:
	void DPtoVP(double x,double y,long *X,long *Y);
	void VPtoDP(long x,long y,double *X,double *Y);
	long DLtoVL(double l);
	double VLtoDL(long l);
};

//========================================================
//�ַ�������
//========================================================

class Logic CoString
{
public:
	CoString();
	~CoString();
	CString dtostr(double a);//��double��������ת��Ϊstring����
	CString itostr(int b);//��int��������ת��Ϊstring����
	void DepTwoPart(CString &str,CString &str1,const CString tug);//��һ���ַ�����ĳһ����־��Ϊ����
	CString GetString(CoPnt Point);
	CoPnt GetCoPnt(CString str);
};
//=========================================================
//��д�ļ��߼�
//=========================================================
class Logic CoRWFile
{
public:
	CoRWFile();
	~CoRWFile();
	void WriteToFile(vector<CoPnt>& Point);
	void ReadFromFile(vector<CoPnt>& Point);
};
#ifndef _CoLogic_EXPORT_
#ifdef _DEBUG
#pragma comment(lib,"CoLogic.lib")
#else
#pragma comment(lib,"CoLogic.lib")
#endif
#endif
#endif