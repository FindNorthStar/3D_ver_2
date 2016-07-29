#pragma once


// CSetSoundDlg 对话框

class CSetSoundDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSoundDlg)

public:
	CSetSoundDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetSoundDlg();

// 对话框数据
	enum { IDD = IDD_SOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int tempbeep1;
	afx_msg void OnBnClickedBeep1();
	afx_msg void OnBnClickedBeep2();
	afx_msg void OnBnClickedBeep3();
	afx_msg void OnBnClickedBeep4();
	afx_msg void OnBnClickedBeep5();
	afx_msg void OnBnClickedBeep6();
	afx_msg void OnBnClickedBeep7();
	afx_msg void OnBnClickedBeep8();
	afx_msg void OnBnClickedBeepDefault();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedComfirm();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
