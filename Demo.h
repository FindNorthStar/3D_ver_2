#pragma once
#include"Graph.h"


// CDemo �Ի���

class CDemo : public CDialogEx
{
	DECLARE_DYNAMIC(CDemo)

public:
	CDemo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDemo();

// �Ի�������
	enum { IDD = IDD_DEMO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CGraph *m_pdisplay;
public:
	double m_angle;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeOutput();
	CString m_output;
};
