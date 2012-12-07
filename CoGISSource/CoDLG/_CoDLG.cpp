#include "StdAfx.h"
#include "_CoDLG.H"
#include "CoNewPntDlg.h"
#include "CoNewLineDlg.h"
#include "CoNewPolyDlg.h"
#include "CoInputPntDlg.h"
#include "CoInputLineDlg.h"
#include "CoInPutPolyDlg.h"
#include "CoPntPorDlg.h"
#include "CoLineProDlg.h"
#include "CoPolyProDlg.h"

#include "CoInputTagDlg.h"
#include "CoInPutTagStrDlg.h"
#include "CoNewTagDlg.h"
#include "CoAlterTagPro.h"
#include "CoAlterTagStr.h"
//=================================================

//================================================
//�����Ի���
bool DIALOG InputPointDLG(CoPntPro& PointPor)
{
	
	CoInputPntDlg PntDlg;
	if (PntDlg.DoModal()==IDOK)
	{
		PointPor.PntStyle = PntDlg.m_PntStyle;
		PointPor.PntRadio = PntDlg.m_Radio;
		PointPor.PntLayer = PntDlg.m_Layer;
		PointPor.PntColor = PntDlg.m_PntCor;
		return TRUE;
	}
	return FALSE;
}

//================================================
//�����߶Ի���
bool DIALOG InputLineDLG(CoLinePro& LinePor)
{
	CoInputLineDlg LineDlg;
	if (LineDlg.DoModal()==IDOK)
	{
		LinePor.LineColor = LineDlg.m_LineCor;
		LinePor.LineStyle = LineDlg.m_LineStyle;
		LinePor.LineWidth = LineDlg.m_LineWide;
		LinePor.LineLayer = LineDlg.m_LayerNum;
		return TRUE;
	}
	return FALSE;
}

//================================================
//�������Ի���
bool DIALOG InputPolyDLG(CoPolyPro& PolyPor)
{
	
	CoInPutPolyDlg PolyDlg;
	if (PolyDlg.DoModal()==IDOK)
	{
		PolyPor.PolyFillStyle = PolyDlg.m_FillStyle;
		PolyPor.PolyColor = PolyDlg.m_PolyFillCor;
		PolyPor.PolyStyle = PolyDlg.m_PolyStyle;
		PolyPor.PolyLayer = PolyDlg.m_PolyLayer;
		return TRUE;
	}
	return FALSE;
}
//����ע�ǶԻ���
bool DIALOG InputTagPro(CoTagPro& TagPro)
{
	
	CoInputTagDlg TagDlg;
	if (TagDlg.DoModal()==IDOK)
	{
		TagPro.TagHeight=TagDlg.m_tagheight;    //����߶�
		TagPro.TagWidth=TagDlg.m_tagwidth;     //������
		TagPro.TagAngle=360-TagDlg.m_tagangle;  //����Ƕ�
		TagPro.TextAngle=TagDlg.m_textangle; //�ı��Ƕ�
		TagPro.TagColor=TagDlg.m_tagcolor;//������ɫ
		TagPro.TagOffsite=TagDlg.m_tagoffsite;  //������
		TagPro.TagFont=TagDlg.m_tagfont;  //��������
		TagPro.TagLayer=TagDlg.m_taglayer; //ע��ͼ��
		return TRUE;
	}
	return FALSE;
}
//================================================
//����ע���ַ����Ի���
bool DIALOG InputTagStr(CoTagPro& TagPro)
{
	
	CoInPutTagStrDlg StrDlg;
	if (StrDlg.DoModal()==IDOK)
	{
		TagPro.TagStr=StrDlg.m_tagstr;
		return TRUE;
	}
	return FALSE;
}
//===============================================
//�������Ѱ�޸�
bool DIALOG PointPro(CoPntPro& PointPro)
{
	
	CString style;
	switch(PointPro.PntStyle)
	{
	case 0:
		style = "Բ��";
		break;
	case 1:
		style = "���ǵ�";
		break;
	case 2:
		style = "�ŵ�";
		break;
	default:
		break;
	}
	CoPntPorDlg dlg(PointPro.PntStyle,style,PointPro.PntRadio,
		PointPro.PntColor,PointPro.PntLayer,AfxGetMainWnd());
	if (dlg.DoModal()==IDOK)
	{
		PointPro.PntStyle = dlg.m_PntStyle;
		PointPro.PntRadio = dlg.m_Radio;
		PointPro.PntColor = dlg.m_PntCor;
		PointPro.PntLayer = dlg.m_Layler;
		return TRUE;
	}
	return FALSE;
}

//===============================================
//�����Բ�ѯ���޸�
bool DIALOG LinePro(CoLinePro& LinePro)
{
	
	CString style;
	switch(LinePro.LineStyle)
	{
	case 0:
		style = "ʵ��";
			break;
	case 1:
		style = "����";
			break;
	case 2:
		style = "����";
			break;
	case 3:
		style = "�㻮��";
			break;
	case 4:
		style = "˫�㻮��";
			break;
	case 5:
		style = "�ջ���";
			break;
	default:
		break;
	}

	CoLineProDlg dlg(LinePro.LineStyle,style,
		LinePro.LineWidth,LinePro.LineColor,LinePro.LineLayer,AfxGetMainWnd());
	if (dlg.DoModal()==IDOK)
	{
		LinePro.LineStyle = dlg.m_LineStyle;
		LinePro.LineWidth = dlg.m_EditWide;
		LinePro.LineColor = dlg.m_LineCor;
		LinePro.LineLayer = dlg.m_EditLayer;
		return TRUE;
	}
	return FALSE;
}

//================================================
//��������ѯ���޸�
bool DIALOG PolyGonPro(CoPolyPro& PolygonPro)
{
	
	CString style;
	CString FillStyle;
	switch(PolygonPro.PolyStyle)
	{
	case 0:
		style = "������";
		break;
	case 1:
		style = "�������";
		break;
	case 2:
		style = "��Բ��";
		break;
	case 3:
		style = "�������ڽ�Բ";
		break;
	case 4:
		style = "������";
		break;
	default:
		break;
	}
	switch(PolygonPro.PolyFillStyle)
	{
	case 0:
		FillStyle = "ˮƽ��";
		break;
	case 1:
		FillStyle = "��ֱ��";
		break;
	case 2:
		FillStyle = "��б��";
		break;
	case 3:
		FillStyle = "��б��";
		break;
	case 4:
		FillStyle = "ʮ����";
		break;
	case 5:
		FillStyle = "������";
		break;
	case 6:
		FillStyle = "��ͼ��";
		break;
	default:
		break;
	}

	CoPolyPro MyPolyPro= PolygonPro;
	CoPolyProDLG dlg(MyPolyPro,style,FillStyle,AfxGetMainWnd());

	if (dlg.DoModal()==IDOK)
	{
		PolygonPro.PolyStyle = dlg.m_PolyStyle;
		PolygonPro.PolyFillStyle = dlg.m_FillStyle;
		PolygonPro.PolyColor = dlg.m_FillCor;
		PolygonPro.PolyLayer = dlg.m_Layer;
		PolygonPro.PolyArea = dlg.m_Area;
		return TRUE;
	}
	return FALSE;
}

//================================================
//�½����ļ�
bool DIALOG NewPointDoc(CString* PntName)
{
	
	CoNewPntDlg newPoint;
	if (newPoint.DoModal()==IDOK)
	{
		*PntName = newPoint.m_PntName;
		return TRUE;
	}
	return FALSE;
}

//=================================================
//�½����ļ�
bool DIALOG NewLineDoc(CString* LineName)
{
	
	CoNewLineDlg NewLine;
	if (NewLine.DoModal()==IDOK)
	{
		*LineName= NewLine.m_NewLine;
		return TRUE;
	}
	return FALSE;
}

//==================================================
//�½����ļ�
bool DIALOG NewPolyDoc(CString* PolyName)
{
	
	CoNewPolyDlg NewPoly;
	if (NewPoly.DoModal()==IDOK)
	{
		*PolyName = NewPoly.m_NewPolyItem;
		return TRUE;
	}
	return FALSE;
}

//�½������ļ�
bool DIALOG NewTagDoc(CString* TagName)
{
	
	CoNewTagDlg NewTag;
	if (NewTag.DoModal()==IDOK)
	{
		*TagName = NewTag.m_TagName;
		return TRUE;
	}
	return FALSE;	
}


bool DIALOG AlterTagProDLG(CoTagPro& TagPro)
{
	
	CoAlterTagPro dlg(TagPro,AfxGetMainWnd());
	if (dlg.DoModal()==IDOK)
	{
		TagPro.TagAngle = dlg.m_lTagAngle;
		TagPro.TagColor = dlg.m_lFontCor;
		TagPro.TagFont = dlg.m_lTagFont;
		TagPro.TagHeight = dlg.m_lTagHeight;
		TagPro.TagWidth = dlg.m_lTagWidth;
		TagPro.TagLayer = dlg.m_lTagLayer;
		TagPro.TagOffsite = dlg.m_lTagOffsite;
		TagPro.TextAngle = dlg.m_lTextAngle;
		return TRUE;
	}
	return FALSE;
}

bool DIALOG AlterTagStr(CString& TagStr)
{
	
	CoAlterTagStr dlg;
	if (dlg.DoModal()==IDOK)
	{
		TagStr = dlg.m_TagStr;
		return TRUE;
	}
	return FALSE;
}
