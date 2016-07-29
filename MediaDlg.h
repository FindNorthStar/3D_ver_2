#pragma once
#include "wmpplayer4.h"
#include "wmpcontrols.h"
#include "wmpmedia.h"
#include "wmpsettings.h"
#include "afxcmn.h"
#include "afxwin.h"

#if !defined(AFX_MYNEWPLAYERDLG_H__96CDC286_BD02_4D09_BB44_868D66A8C1B8__INCLUDED_)
#define AFX_MYNEWPLAYERDLG_H__96CDC286_BD02_4D09_BB44_868D66A8C1B8__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif
// CMediaDlg 对话框

class CMediaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMediaDlg)

public:
	CMediaDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMediaDlg();

// 对话框数据
	enum { IDD = IDD_MEDIA };
	CWMPPlayer4	m_Movie;
	CWMPMedia m_Media;
	CWMPControls m_Control;
	CWMPSettings m_Set;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString FilePathName;
	CString m_EditFileName;
	UINT m_TimerID;
	long state;
	afx_msg void OnAbout();
	afx_msg void OnExit();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedReplay();
};
#endif