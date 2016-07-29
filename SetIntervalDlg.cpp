// SetIntervalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetIntervalDlg.h"
#include "afxdialogex.h"


// CSetIntervalDlg 对话框

IMPLEMENT_DYNAMIC(CSetIntervalDlg, CDialogEx)

CSetIntervalDlg::CSetIntervalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetIntervalDlg::IDD, pParent)
{
	
}

CSetIntervalDlg::~CSetIntervalDlg()
{
}

void CSetIntervalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HF_EDIT, maxTime[CGraph::WrongGesture::HEAD_FOREWARD]);
	DDX_Text(pDX, IDC_HLEDIT, maxTime[CGraph::WrongGesture::HEAD_LEFT]);
	DDX_Text(pDX, IDC_HREDIT, maxTime[CGraph::WrongGesture::HEAD_RIGHT]);
	DDX_Text(pDX, IDC_BFEDIT, maxTime[CGraph::WrongGesture::ASIDE_BODY_FOREWARD]);
	DDX_Text(pDX, IDC_BBEDIT, maxTime[CGraph::WrongGesture::ASIDE_HEAD_FOREWARD]);
	DDX_Control(pDX, IDC_HF_EDIT, m_HFCtrl);
	DDX_Control(pDX, IDC_HLEDIT, m_HLCtrl);
	DDX_Control(pDX, IDC_HREDIT, m_HRCtrl);
	DDX_Control(pDX, IDC_BFEDIT, m_BFCtrl);
	DDX_Control(pDX, IDC_BBEDIT, m_BBCtrl);
}


BEGIN_MESSAGE_MAP(CSetIntervalDlg, CDialogEx)
	ON_BN_CLICKED(IDC_COMFIRM, &CSetIntervalDlg::OnBnClickedComfirm)
	ON_EN_SETFOCUS(IDC_HF_EDIT, &CSetIntervalDlg::OnEnSetfocusHfEdit)
	ON_EN_SETFOCUS(IDC_HLEDIT, &CSetIntervalDlg::OnEnSetfocusHledit)
	ON_EN_SETFOCUS(IDC_HREDIT, &CSetIntervalDlg::OnEnSetfocusHredit)
	ON_EN_SETFOCUS(IDC_BFEDIT, &CSetIntervalDlg::OnEnSetfocusBfedit)
	ON_EN_SETFOCUS(IDC_BBEDIT, &CSetIntervalDlg::OnEnSetfocusBbedit)
	ON_BN_CLICKED(IDC_CANCEL, &CSetIntervalDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetIntervalDlg 消息处理程序


void CSetIntervalDlg::OnBnClickedComfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CGraph::pThis->SetMaxTime(maxTime);
	CDialogEx::OnCancel();
}


BOOL CSetIntervalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*maxTime[CGraph::WrongGesture::HEAD_FOREWARD] = 5.0;
	m_HeadLeft = 3.0;
	m_HeadRight = 3.0;
	m_BodyForward = 5.0;
	m_BodyBackward = 5.0;*/
	double*temp = CGraph::GetMaxTime();
	for (unsigned int i = 0; i < CGraph::WrongGesture::WRONGGESTURE_SIZE; i++)
	{
		maxTime[i] = temp[i];
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CSetIntervalDlg::OnEnSetfocusHfEdit()
{
	// TODO:  在此添加控件通知处理程序代码
	m_HFCtrl.Clear();
}


void CSetIntervalDlg::OnEnSetfocusHledit()
{
	// TODO:  在此添加控件通知处理程序代码
	m_HLCtrl.Clear();
}


void CSetIntervalDlg::OnEnSetfocusHredit()
{
	// TODO:  在此添加控件通知处理程序代码
	m_HRCtrl.Clear();
}


void CSetIntervalDlg::OnEnSetfocusBfedit()
{
	// TODO:  在此添加控件通知处理程序代码
	m_BFCtrl.Clear();
}


void CSetIntervalDlg::OnEnSetfocusBbedit()
{
	// TODO:  在此添加控件通知处理程序代码
	m_BBCtrl.Clear();
}


void CSetIntervalDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
