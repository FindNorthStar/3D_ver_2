
// 3D_ver_2Dlg.h : 头文件
//

#include "stdafx.h"
#include<string>
#include<sstream>
#include<iostream>
#include "afxwin.h"
#include"Demo.h"
#include"SetSoundDlg.h"
#include"SetTimeDlg.h"
#include"SetIntervalDlg.h"
#include"PicExampleDlg.h"
#include"MediaDlg.h"
#include"Demo.h"
#include"Aboutbox.h"
#include"Text.h"
#include"Graph.h"
using namespace std;
#pragma once


// CMy3D_ver_2Dlg 对话框
class CMy3D_ver_2Dlg : public CDialogEx
{
	// 构造
public:
	CMy3D_ver_2Dlg(CWnd* pParent = NULL);	// 标准构造函数
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTime();

	// 对话框数据
	enum { IDD = IDD_MY3D_VER_2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	string ShowSetTime = "设置的时长：";

	static int SetH;
	static int SetM;

	static int CountH;
	static int CountM;
	static int CountS;

	static int beep1;
	static bool issettune;

	string GetNextSecond(int&, int&, int&);
	static bool isdue, isset;

	CDemo m_DemoDlg;
	CRect m_DialogChild;
	CText m_TextDlg;
	CRect m_TextWindow;
	CString m_CurrentTime;
	CString m_SetTime;
	CString m_RemainingTime;
	//CButton m_SetSoundButton;
	//CButton m_SetTimeButton;
	//CButton m_SetIntervalButton;
	CBitmapButton CBMBS, CBMBT, CBMBI;
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_About;
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedSetsound();
//	afx_msg void OnBnClickedSettime();
	afx_msg void OnBnClickedSetinterval();
//	afx_msg void OnBnClickedSetsound1();
	afx_msg void OnBnClickedSettime1();
	afx_msg void OnBnClickedSetinterval1();
	afx_msg void OnBnClickedSettime();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
