#pragma once


// CPicExampleDlg �Ի���

class CPicExampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPicExampleDlg)

public:
	CPicExampleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPicExampleDlg();

// �Ի�������
	enum { IDD = IDD_EXAMPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
