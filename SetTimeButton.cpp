// SetTimeButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetTimeButton.h"
#include "afxdialogex.h"


// CSetTimeButton �Ի���

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


// CSetTimeButton ��Ϣ�������
