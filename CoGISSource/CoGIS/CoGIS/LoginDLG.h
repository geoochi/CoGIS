#pragma once


// LoginDLG �Ի���

class LoginDLG : public CDialog
{
	DECLARE_DYNAMIC(LoginDLG)

public:
	LoginDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginDLG();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_pwd;
	CBrush m_brBk;//����һ��������ˢ
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_serverName;
	CString m_sa;
	CString m_gis;
};
