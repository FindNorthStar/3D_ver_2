#pragma once


// CAboutbox �Ի���

class CAboutbox : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutbox)

public:
	CAboutbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAboutbox();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
