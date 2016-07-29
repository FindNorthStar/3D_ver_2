// Text.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "Text.h"
#include "afxdialogex.h"
#include "PicExampleDlg.h"
#include "MediaDlg.h"


// CText �Ի���

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


// CText ��Ϣ�������


void CText::OnBnClickedShowPic()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CPicExampleDlg dlg;
	dlg.DoModal();
}


void CText::OnBnClickedShowVideo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMediaDlg dlg;
	dlg.DoModal();
}
