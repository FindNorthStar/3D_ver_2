// SetSoundButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetSoundButton.h"
#include "afxdialogex.h"


// CSetSoundButton �Ի���

IMPLEMENT_DYNAMIC(CSetSoundButton, CDialogEx)

CSetSoundButton::CSetSoundButton(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetSoundButton::IDD, pParent)
{

}

CSetSoundButton::~CSetSoundButton()
{
}

void CSetSoundButton::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetSoundButton, CDialogEx)
END_MESSAGE_MAP()


// CSetSoundButton ��Ϣ�������
