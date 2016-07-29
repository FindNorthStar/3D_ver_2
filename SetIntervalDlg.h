#pragma once
#include "afxwin.h"
#include "Graph.h"

// CSetIntervalDlg �Ի���

class CSetIntervalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetIntervalDlg)

public:
	CSetIntervalDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetIntervalDlg();

// �Ի�������
	enum { IDD = IDD_INTERVAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//double m_HeadForward; 
	//double m_HeadLeft;
	//double m_HeadRight;
	//double m_BodyForward;
	//double m_BodyBackward;
	double maxTime[CGraph::WrongGesture::WRONGGESTURE_SIZE];
	afx_msg void OnBnClickedComfirm();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnSetfocusHfEdit();
	CEdit m_HFCtrl;
	CEdit m_HLCtrl;
	CEdit m_HRCtrl;
	CEdit m_BFCtrl;
	CEdit m_BBCtrl;
	afx_msg void OnEnSetfocusHledit();
	afx_msg void OnEnSetfocusHredit();
	afx_msg void OnEnSetfocusBfedit();
	afx_msg void OnEnSetfocusBbedit();
	afx_msg void OnBnClickedCancel();
};
