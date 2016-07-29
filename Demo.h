#pragma once
#include"Graph.h"


// CDemo 对话框

class CDemo : public CDialogEx
{
	DECLARE_DYNAMIC(CDemo)

public:
	CDemo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDemo();

// 对话框数据
	enum { IDD = IDD_DEMO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CGraph *m_pdisplay;
public:
	double m_angle;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeOutput();
	CString m_output;
};
