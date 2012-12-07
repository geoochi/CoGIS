#ifndef __COSTRUCTCLASS_H_
#define __COSTRUCTCLASS_H_

#include <vector>
using namespace std;

//������
typedef struct
{
	double x;
	double y;
}CoPnt;

//������
typedef struct  
{
	long PntID;
	int PntRadio;
	int  PntStyle;
	COLORREF  PntColor;
	int PntLayer;
}CoPntPro;

//�߽ṹ��
typedef struct
{
	vector<CoPnt>Line;
}CoLine;

//������
typedef struct
{
	long LineID;
	int  LineWidth;
	int  LineStyle;
	COLORREF LineColor;
	int LineLayer;
}CoLinePro;

//���ṹ��
typedef struct
{
	vector<CoPnt>Poly;
}CoPoly;
//������
typedef struct
{
	long PolyID;
    int PolyStyle;
	COLORREF PolyColor;
	int PolyLayer;
    double PolyArea;
	int PolyFillStyle;
}CoPolyPro;
//ע������
typedef struct
{
	int ID;
	int TagHeight;    //����߶�
	int TagWidth;     //������
	float TagAngle;  //����Ƕ�
	float TextAngle; //�ı��Ƕ�
	COLORREF TagColor;//������ɫ
	int  TagOffsite;  //������
	CString TagFont;  //��������
	CString TagStr;   //�ַ���
	int	TagLayer; //ע��ͼ��
}CoTagPro;

//��Ӿ���
typedef struct
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
}CoRect;

typedef struct
{
	int ID;
	CString UserName;//�û���
    CString UserSex;
	CString UserPassword;//�û�����
	CString UserDuties;//ְ��
	CString UserAddress;//סַ
	CString Email;
	CString UserQQ;
}CoUser;

typedef struct
{
	CString szIP;
	CString szDsn;
	CString szName;
	CString szPassword;
}CoDB;

typedef struct
{
	int index;//��¼ѡ�����������
	vector<CoPnt>Object;//��¼ѡ�е�����
}MyTopo;

typedef struct	//������¼��ʷ��Ļ�����Ľṹ
{
	double blc;	//������
	double sx;	//��Ļ���½ǵĺ�����
	double sy;	//��Ļ���½ǵ�������
    int wScreen;    //��Ļ��
    int hScreen;    //��Ļ��
}CoScreen;

typedef struct
{
	HTREEITEM Item;
	CString Text;
	UINT State;
}CoTreeNode;

typedef struct
{
	int ID;
	CString ItemName;
	CString CreateTime;
	CString ModifyTime;
	CString Creater;
	int State;
	int TableType;

}CoDirectory;
//�����������ݿ�ı�
typedef struct
{
	CString itemnode;
	bool      isOpen;
	bool      isActive;
	CString   fileTyep;
}AllTalble;
//��ǰ����ı�
typedef struct
{
	CString   item;
	bool      isAct;
}AcTable;
	
#endif
