// SetSoundDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetSoundDlg.h"
#include "afxdialogex.h"
#include "3D_ver_2Dlg.h"


// CSetSoundDlg 对话框

IMPLEMENT_DYNAMIC(CSetSoundDlg, CDialogEx)

CSetSoundDlg::CSetSoundDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetSoundDlg::IDD, pParent)
{

}

CSetSoundDlg::~CSetSoundDlg()
{
}

void CSetSoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetSoundDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BEEP1, &CSetSoundDlg::OnBnClickedBeep1)
	ON_BN_CLICKED(IDC_BEEP2, &CSetSoundDlg::OnBnClickedBeep2)
	ON_BN_CLICKED(IDC_BEEP3, &CSetSoundDlg::OnBnClickedBeep3)
	ON_BN_CLICKED(IDC_BEEP4, &CSetSoundDlg::OnBnClickedBeep4)
	ON_BN_CLICKED(IDC_BEEP5, &CSetSoundDlg::OnBnClickedBeep5)
	ON_BN_CLICKED(IDC_BEEP6, &CSetSoundDlg::OnBnClickedBeep6)
	ON_BN_CLICKED(IDC_BEEP7, &CSetSoundDlg::OnBnClickedBeep7)
	ON_BN_CLICKED(IDC_BEEP8, &CSetSoundDlg::OnBnClickedBeep8)
	ON_BN_CLICKED(IDC_BEEP_DEFAULT, &CSetSoundDlg::OnBnClickedBeepDefault)
	ON_BN_CLICKED(IDC_COMFIRM, &CSetSoundDlg::OnBnClickedComfirm)
	ON_BN_CLICKED(IDCANCEL, &CSetSoundDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetSoundDlg 消息处理程序


void CSetSoundDlg::OnBnClickedBeep1()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 300;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep2()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 400;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep3()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 600;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep4()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 700;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep5()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 800;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep6()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 900;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep7()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 1000;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep8()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 1100;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeepDefault()
{
	// TODO:  在此添加控件通知处理程序代码
	tempbeep1 = 500;
	Beep(tempbeep1, 500);
}


BOOL CSetSoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CheckDlgButton(IDC_BEEP_DEFAULT, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CSetSoundDlg::OnBnClickedComfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	CMy3D_ver_2Dlg::beep1 = tempbeep1;
	CMy3D_ver_2Dlg::issettune = true;
	EndDialog(0);
}


void CSetSoundDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CSetSoundDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnCancel();
	CDialogEx::OnClose();
}


HBRUSH CSetSoundDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
