#pragma once


// CText 对话框

class CText : public CDialogEx
{
	DECLARE_DYNAMIC(CText)

public:
	CText(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CText();

// 对话框数据
	enum { IDD = IDD_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShowPic();
	afx_msg void OnBnClickedShowVideo();
};
