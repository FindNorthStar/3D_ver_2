#pragma once


// CPicExampleDlg 对话框

class CPicExampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPicExampleDlg)

public:
	CPicExampleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPicExampleDlg();

// 对话框数据
	enum { IDD = IDD_EXAMPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
