// Demo.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "Demo.h"
#include "afxdialogex.h"
#include"3D_ver_2Dlg.h"


// CDemo 对话框

IMPLEMENT_DYNAMIC(CDemo, CDialogEx)

CDemo::CDemo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemo::IDD, pParent)
{

}

CDemo::~CDemo()
{
}

void CDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OUTPUT, m_output);
}


BEGIN_MESSAGE_MAP(CDemo, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_OUTPUT, &CDemo::OnEnChangeOutput)
END_MESSAGE_MAP()


// CDemo 消息处理程序


int CDemo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect(0, 0, 800, 500);
	this->GetClientRect(&rect);
	rect.bottom = rect.Height()-50;
	m_pdisplay = new CGraph;
	m_pdisplay->Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE, rect, this, 0);
	this->SetTimer(0, 20, 0);
	return 0;

}


void CDemo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	m_output = m_pdisplay->GetOutput();
	m_angle = m_pdisplay->GetAngle();
	UpdateData(false);
}


void CDemo::OnEnChangeOutput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_output = m_pdisplay->GetOutput();
	// TODO:  在此添加控件通知处理程序代码
}
