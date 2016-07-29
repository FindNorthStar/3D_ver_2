
// 3D_ver_2Dlg.h : ͷ�ļ�
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


// CMy3D_ver_2Dlg �Ի���
class CMy3D_ver_2Dlg : public CDialogEx
{
	// ����
public:
	CMy3D_ver_2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTime();

	// �Ի�������
	enum { IDD = IDD_MY3D_VER_2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	string ShowSetTime = "���õ�ʱ����";

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
