#ifndef _DATAEXCHANGE_H_
#define _DATAEXCHANGE_H_
#include "_CoDB.h"
#include "_MouseOper.h"

extern vector<AllTalble> theTables;//��ŵ�ǰ�����е����б�
extern CString m_CurrentOper;//��ʾ����״̬����
extern CoBaseTool* m_BaseOper;
extern int m_OverAllOper;
extern CoDB m_DB;
void setIniState();//���ó�ʼ״̬
bool isPntActive();//����м���ĵ��ļ�
CString getPntAct();//�õ�����ĵ��ļ�
bool isLineActive();//����м�������ļ�
CString getLineAct();//�õ���������ļ�
bool isAreaActive();//����м�������ļ�
CString getAreaAct();//�õ���������ļ�
bool isNoteActive();//����м����ע���ļ�
CString getNoteAct();//�õ������ע���ļ�
void GetConnect(CoConnect& conn);//�������ݿ�
void AddTables(CString temItem,bool isopen,bool isactive,CString filetype);//���ӵ�ǰ���̵ı�
void setOpenMark(CString temItem);//���ô򿪱��
void setCloseMark(CString temItem);//���ùرձ��
bool setActiveMark(CString temItem,CString&reItem);//���ü�����
void remItemMark(CString temItem);//ɾ��һ����¼
#endif