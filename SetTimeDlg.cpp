// SetTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetTimeDlg.h"
#include "afxdialogex.h"
#include "3D_ver_2Dlg.h"


// CSetTimeDlg 对话框

IMPLEMENT_DYNAMIC(CSetTimeDlg, CDialogEx)

CSetTimeDlg::CSetTimeDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSetTimeDlg::IDD, pParent)
, m_SetH(0)
, m_SetM(0)
{

}

CSetTimeDlg::~CSetTimeDlg()
{
}

void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOUR_EDIT, m_SetH);
	DDX_Text(pDX, IDC_MINUTE_EDIT, m_SetM);
	DDX_Control(pDX, IDC_HOUR_SPIN, m_HCtrl);
	DDX_Control(pDX, IDC_MINUTE_SPIN, m_MCtrl);
	DDX_Control(pDX, IDC_HOUR_EDIT, m_HVCtrl);
	DDX_Control(pDX, IDC_MINUTE_EDIT, m_MVCtrl);
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_HOUR_SPIN, &CSetTimeDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MINUTE_SPIN, &CSetTimeDlg::OnDeltaposSpin2)
	ON_EN_CHANGE(IDC_HOUR_EDIT, &CSetTimeDlg::OnEnChangeHourEdit)
	ON_EN_CHANGE(IDC_MINUTE_EDIT, &CSetTimeDlg::OnEnChangeMinuteEdit)
	ON_BN_CLICKED(IDC_COMFIRM, &CSetTimeDlg::OnBnClickedComfirm)
	ON_BN_CLICKED(IDC_DEFAULT, &CSetTimeDlg::OnBnClickedDefault)
	ON_BN_CLICKED(IDC_CANCEL, &CSetTimeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetTimeDlg 消息处理程序


void CSetTimeDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (pNMUpDown->iDelta == -1 && m_SetH > 0)
		m_SetH--;
	else if (pNMUpDown->iDelta == -1 && m_SetH == 0){
		m_SetH = 23;
		UpdateData(false);
	}
	else if (pNMUpDown->iDelta == 1 && m_SetH < 23)
		m_SetH++;
	else if (pNMUpDown->iDelta == 1 && m_SetH == 23){
		m_SetH = 0;
		UpdateData(false);
	}
	UpdateData(false);

	*pResult = 0;
}


void CSetTimeDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (pNMUpDown->iDelta == -1 && m_SetM > 0)
		m_SetM--;
	else if (pNMUpDown->iDelta == -1 && m_SetM == 0)
		m_SetM = 59;
	else if (pNMUpDown->iDelta == 1 && m_SetM < 59)
		m_SetM++;
	else if (pNMUpDown->iDelta == 1 && m_SetM == 59)
		m_SetM = 0;
	UpdateData(false);
	*pResult = 0;
}


void CSetTimeDlg::OnEnChangeHourEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(FALSE);
}


void CSetTimeDlg::OnEnChangeMinuteEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(FALSE);
}


void CSetTimeDlg::OnBnClickedComfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_SetH == 0 && m_SetM == 0)
		EndDialog(0);
	else{
		CMy3D_ver_2Dlg::SetH = m_SetH;
		CMy3D_ver_2Dlg::SetM = m_SetM;
		CMy3D_ver_2Dlg::CountH = m_SetH;
		CMy3D_ver_2Dlg::CountM = m_SetM;
		CMy3D_ver_2Dlg::CountS = 0;
		CMy3D_ver_2Dlg::isdue = false;
		CMy3D_ver_2Dlg::isset = true;
		EndDialog(0);
	}
}




void CSetTimeDlg::OnBnClickedDefault()
{
	// TODO:  在此添加控件通知处理程序代码
	m_SetH = 0;
	m_SetM = 0;
	UpdateData(FALSE);
}

BOOL CSetTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_HCtrl.SetBuddy(GetDlgItem(m_SetH));
	m_HCtrl.SetRange(0, 23);
	m_MCtrl.SetBuddy(GetDlgItem(m_SetM));
	m_MCtrl.SetRange(0, 59);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSetTimeDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

