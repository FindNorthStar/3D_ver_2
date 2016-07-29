// SetIntervalButton.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetIntervalButton.h"
#include "afxdialogex.h"


// CSetIntervalButton 对话框

IMPLEMENT_DYNAMIC(CSetIntervalButton, CDialogEx)

CSetIntervalButton::CSetIntervalButton(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetIntervalButton::IDD, pParent)
{

}

CSetIntervalButton::~CSetIntervalButton()
{
}

void CSetIntervalButton::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetIntervalButton, CDialogEx)
END_MESSAGE_MAP()


// CSetIntervalButton 消息处理程序
