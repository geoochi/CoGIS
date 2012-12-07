#include "stdafx.h"
#include "DataExchange.h"
#include "CoStructClass.h"

vector<AllTalble> theTables;//��ŵ�ǰ�����е����б�
CoDB m_DB;
//��ǰ���������ű�
AcTable m_PntTable;
AcTable m_LineTable;
AcTable m_AreaTable;
AcTable m_NoteTable;
//��ǰ�Ĺ���Ŀ¼
CString m_CurrentOper;//��ʾ����״̬����
CoBaseTool* m_BaseOper;
int m_OverAllOper;

//���ó�ʼ״̬����
void setIniState()
{
	m_PntTable.isAct=false;
	m_LineTable.isAct=false;
	m_AreaTable.isAct=false;
	m_NoteTable.isAct=false;
}

//����м���ĵ��ļ�
bool isPntActive()
{
	if(m_PntTable.isAct)
		return true;
	else
		return false;
}

//�õ�����ĵ��ļ�
CString getPntAct()
{
	return m_PntTable.item;
}
//����м�������ļ�
bool isLineActive()
{
	if (m_LineTable.isAct)
		return true;
	else
		return false;
	
}

//�õ���������ļ�
CString getLineAct()
{
	return m_LineTable.item;
}

//����м�������ļ�
bool isAreaActive()
{
	if (m_AreaTable.isAct)
		return true;
	else
		return false;

}

//�õ���������ļ�
CString getAreaAct()
{
	return m_AreaTable.item;
}

//����м����ע���ļ�
bool isNoteActive()
{
	if (m_NoteTable.isAct)
		return true;
	else
		return false;
}

//�õ������ע���ļ�
CString getNoteAct()
{
	return m_NoteTable.item;
}

//�������ݿ⺯��
void GetConnect(CoConnect& conn)
{
	CoConnect MyConn(m_DB.szDsn,m_DB.szName,m_DB.szPassword);
	MyConn.Connect();
	conn = MyConn;
}

//���ӵ�ǰ���̵ı�
void AddTables(CString temItem,bool isopen,bool isactive,CString filetype)
{
	AllTalble tempTalble;
	tempTalble.itemnode=temItem;
	tempTalble.isOpen=isopen;
	tempTalble.isActive=isactive;
	tempTalble.fileTyep=filetype;
	theTables.push_back(tempTalble);
}

//���ô򿪱��
void setOpenMark(CString temItem)
{
	for (int i=0;i<theTables.size();i++)
		{
			if (theTables[i].itemnode==temItem)
			{
				theTables[i].isOpen=true;
				break;
			}
		}
}

//���ùرձ��
void setCloseMark(CString temItem)
{
	for (int i=0;i<theTables.size();i++)
	{
		if (theTables[i].itemnode==temItem)
		{
			theTables[i].isOpen=false;
			if(theTables[i].isActive)
			{
				if (theTables[i].itemnode==m_PntTable.item)
				{
					m_PntTable.isAct=false;
				}
				if (theTables[i].itemnode==m_LineTable.item)
				{
					m_LineTable.isAct=false;
				}
				if (theTables[i].itemnode==m_AreaTable.item)
				{
					m_AreaTable.isAct=false;
				}
				if (theTables[i].itemnode==m_NoteTable.item)
				{
					m_NoteTable.isAct=false;
				}
				theTables[i].isActive=false;
			}
			break;
		}
	}
}

//���ü����־
bool setActiveMark(CString temItem,CString&reItem)
{
	for (int i=0;i<theTables.size();i++)
	{
		if (theTables[i].itemnode==temItem)
		{
			theTables[i].isOpen=true;
			theTables[i].isActive=true;
			if (theTables[i].fileTyep==_T("COP"))//���������ǵ��ļ�
			{
				if(isPntActive())//������ڼ���ĵ��ļ�
				{
					setOpenMark(m_PntTable.item);
					reItem=m_PntTable.item;//����֮ǰ����Ľڵ�
					m_PntTable.isAct=true;
					m_PntTable.item=temItem;//�����µļ���ڵ�
					return true;
				}
				else
				{
					m_PntTable.isAct=true;
					m_PntTable.item=temItem;
					return false;
				}
			}
			if (theTables[i].fileTyep==_T("COL"))//�������������ļ�
			{
				if(isLineActive())//������ڼ���ĵ��ļ�
				{
					setOpenMark(m_LineTable.item);
					reItem=m_LineTable.item;//����֮ǰ����Ľڵ�
					m_LineTable.isAct=true;
					m_LineTable.item=temItem;//�����µļ���ڵ�
					return true;
				}
				else
				{
					m_LineTable.isAct=true;
					m_LineTable.item=temItem;
					return false;
				}
			}
			if (theTables[i].fileTyep==_T("COA"))//�������������ļ�
			{
				if(isAreaActive())//������ڼ���ĵ��ļ�
				{
					setOpenMark(m_AreaTable.item);
					reItem=m_AreaTable.item;//����֮ǰ����Ľڵ�
					m_AreaTable.isAct=true;
					m_AreaTable.item=temItem;//�����µļ���ڵ�
					return true;
				}
				else
				{
					m_AreaTable.isAct=true;
					m_AreaTable.item=temItem;
					return false;
				}
			}
			if (theTables[i].fileTyep==_T("CON"))//����������ע���ļ�
			{
				if(isNoteActive())//������ڼ���ĵ��ļ�
				{
					setOpenMark(m_NoteTable.item);
					reItem=m_NoteTable.item;//����֮ǰ����Ľڵ�
					m_NoteTable.isAct=true;
					m_NoteTable.item=temItem;//�����µļ���ڵ�
					return true;
				}
				else
				{
					m_NoteTable.isAct=true;
					m_NoteTable.item=temItem;
					return false;
				}
			}
		}
	}
}

//ɾ��һ����¼
void remItemMark(CString temItem)
{
	if (temItem==m_PntTable.item)
	{
		m_PntTable.isAct=false;
	}
	if (temItem==m_LineTable.item)
	{
		m_LineTable.isAct=false;
	}
	if (temItem==m_AreaTable.item)
	{
		m_AreaTable.isAct=false;
	}
	if (temItem==m_NoteTable.item)
	{
		m_NoteTable.isAct=false;
	}
	//�������Ԫ���������е�λ��
	/*AllTalble t_Table;
	for (int i=theTables.size();i>=0;i--)
	{
		if (theTables[i].itemnode==temItem)
		{
			theTables[i].isActive=false;
			theTables[i].isOpen=false;
			break;
		}
	}   */
	//vector<AllTalble> myvector;
	for(vector<AllTalble>::iterator iter=theTables.begin();iter!=theTables.end();)
	{
		if(temItem == (*iter).itemnode)
			iter=theTables.erase(iter);
		else
			++iter;
	} 
}