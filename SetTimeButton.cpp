// SetTimeButton.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetTimeButton.h"
#include "afxdialogex.h"


// CSetTimeButton 对话框

IMPLEMENT_DYNAMIC(CSetTimeButton, CDialogEx)

CSetTimeButton::CSetTimeButton(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetTimeButton::IDD, pParent)
{

}

CSetTimeButton::~CSetTimeButton()
{
}

void CSetTimeButton::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetTimeButton, CDialogEx)
END_MESSAGE_MAP()


// CSetTimeButton 消息处理程序
