// PicExampleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "PicExampleDlg.h"
#include "afxdialogex.h"


// CPicExampleDlg 对话框

IMPLEMENT_DYNAMIC(CPicExampleDlg, CDialogEx)

CPicExampleDlg::CPicExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPicExampleDlg::IDD, pParent)
{

}

CPicExampleDlg::~CPicExampleDlg()
{
}

void CPicExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPicExampleDlg, CDialogEx)
END_MESSAGE_MAP()


// CPicExampleDlg 消息处理程序
