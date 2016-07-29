// Aboutbox.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "Aboutbox.h"
#include "afxdialogex.h"


// CAboutbox 对话框

IMPLEMENT_DYNAMIC(CAboutbox, CDialogEx)

CAboutbox::CAboutbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAboutbox::IDD, pParent)
{

}

CAboutbox::~CAboutbox()
{
}

void CAboutbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutbox, CDialogEx)
END_MESSAGE_MAP()


// CAboutbox 消息处理程序
