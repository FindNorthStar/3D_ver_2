#pragma once


// CSetTimeDlg 对话框

class CSetTimeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetTimeDlg)

public:
	CSetTimeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetTimeDlg();

// 对话框数据
	enum { IDD = IDD_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	int m_SetH;
	int m_SetM;
	afx_msg void OnEnChangeHourEdit();
	afx_msg void OnEnChangeMinuteEdit();
	afx_msg void OnBnClickedComfirm();
	CSpinButtonCtrl m_HCtrl;
	CSpinButtonCtrl m_MCtrl;
	CEdit m_HVCtrl;
	CEdit m_MVCtrl;
	afx_msg void OnBnClickedDefault();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
};
