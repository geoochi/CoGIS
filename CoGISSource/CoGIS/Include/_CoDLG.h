#ifndef _CoDLG_H_
#define _CoDLG_H_

#include "CoStructClass.h"

#ifndef _CoDLG_EXPORT_
#define DIALOG  __declspec(dllimport)
#else
#define DIALOG  __declspec(dllexport)
#endif
//================================================

//================================================
//�����Ի���
bool DIALOG InputPointDLG(CoPntPro& PointPor);

//================================================
//�����߶Ի���
bool DIALOG InputLineDLG(CoLinePro& LinePor);

//================================================
//�������Ի���
bool DIALOG InputPolyDLG(CoPolyPro& PolyPor);
//================================================
//����ע�ǶԻ���
bool DIALOG InputTagPro(CoTagPro& TagPro);
//================================================
//����ע���ı��Ի���
bool DIALOG InputTagStr(CoTagPro& TagPro);

//===============================================
//�������Ѱ�޸�
bool DIALOG PointPro(CoPntPro& PointPro);

//===============================================
//�����Բ�ѯ���޸�
bool DIALOG LinePro(CoLinePro& LinePro);

//================================================
//��������ѯ���޸�
bool DIALOG PolyGonPro(CoPolyPro& PolygonPro);

//================================================
//�½����ļ�
bool DIALOG NewPointDoc(CString* PntName);

//=================================================
//�½����ļ�
bool DIALOG NewLineDoc(CString* LineName);

//==================================================
//�½����ļ�
bool DIALOG NewPolyDoc(CString* PolyName);
//==================================================
//�½����ļ�
bool DIALOG NewTagDoc(CString* TagName);


bool DIALOG AlterTagProDLG(CoTagPro& TagPro);

bool DIALOG AlterTagStr(CString& TagStr);

 #ifndef _CoDLG_EXPORT_
   #ifdef _DEBUG
  #pragma comment(lib,"CoDLG.lib")
#else
  #pragma comment(lib,"CoDLG.lib")
  #endif
 #endif
#endif
