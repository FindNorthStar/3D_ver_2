#pragma once


// CText �Ի���

class CText : public CDialogEx
{
	DECLARE_DYNAMIC(CText)

public:
	CText(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CText();

// �Ի�������
	enum { IDD = IDD_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShowPic();
	afx_msg void OnBnClickedShowVideo();
};
