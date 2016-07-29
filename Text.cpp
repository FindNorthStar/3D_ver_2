// Text.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "Text.h"
#include "afxdialogex.h"
#include "PicExampleDlg.h"
#include "MediaDlg.h"


// CText 对话框

IMPLEMENT_DYNAMIC(CText, CDialogEx)

CText::CText(CWnd* pParent /*=NULL*/)
	: CDialogEx(CText::IDD, pParent)
{

}

CText::~CText()
{
}

void CText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CText, CDialogEx)
	ON_BN_CLICKED(IDC_SHOW_PIC, &CText::OnBnClickedShowPic)
	ON_BN_CLICKED(IDC_SHOW_VIDEO, &CText::OnBnClickedShowVideo)
END_MESSAGE_MAP()


// CText 消息处理程序


void CText::OnBnClickedShowPic()
{
	// TODO:  在此添加控件通知处理程序代码
	CPicExampleDlg dlg;
	dlg.DoModal();
}


void CText::OnBnClickedShowVideo()
{
	// TODO:  在此添加控件通知处理程序代码
	CMediaDlg dlg;
	dlg.DoModal();
}
