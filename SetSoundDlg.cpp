// SetSoundDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetSoundDlg.h"
#include "afxdialogex.h"
#include "3D_ver_2Dlg.h"


// CSetSoundDlg �Ի���

IMPLEMENT_DYNAMIC(CSetSoundDlg, CDialogEx)

CSetSoundDlg::CSetSoundDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetSoundDlg::IDD, pParent)
{

}

CSetSoundDlg::~CSetSoundDlg()
{
}

void CSetSoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetSoundDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BEEP1, &CSetSoundDlg::OnBnClickedBeep1)
	ON_BN_CLICKED(IDC_BEEP2, &CSetSoundDlg::OnBnClickedBeep2)
	ON_BN_CLICKED(IDC_BEEP3, &CSetSoundDlg::OnBnClickedBeep3)
	ON_BN_CLICKED(IDC_BEEP4, &CSetSoundDlg::OnBnClickedBeep4)
	ON_BN_CLICKED(IDC_BEEP5, &CSetSoundDlg::OnBnClickedBeep5)
	ON_BN_CLICKED(IDC_BEEP6, &CSetSoundDlg::OnBnClickedBeep6)
	ON_BN_CLICKED(IDC_BEEP7, &CSetSoundDlg::OnBnClickedBeep7)
	ON_BN_CLICKED(IDC_BEEP8, &CSetSoundDlg::OnBnClickedBeep8)
	ON_BN_CLICKED(IDC_BEEP_DEFAULT, &CSetSoundDlg::OnBnClickedBeepDefault)
	ON_BN_CLICKED(IDC_COMFIRM, &CSetSoundDlg::OnBnClickedComfirm)
	ON_BN_CLICKED(IDCANCEL, &CSetSoundDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetSoundDlg ��Ϣ�������


void CSetSoundDlg::OnBnClickedBeep1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 300;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 400;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 600;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 700;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 800;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 900;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 1000;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeep8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 1100;
	Beep(tempbeep1, 500);
}


void CSetSoundDlg::OnBnClickedBeepDefault()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	tempbeep1 = 500;
	Beep(tempbeep1, 500);
}


BOOL CSetSoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CheckDlgButton(IDC_BEEP_DEFAULT, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CSetSoundDlg::OnBnClickedComfirm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMy3D_ver_2Dlg::beep1 = tempbeep1;
	CMy3D_ver_2Dlg::issettune = true;
	EndDialog(0);
}


void CSetSoundDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CSetSoundDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnCancel();
	CDialogEx::OnClose();
}


HBRUSH CSetSoundDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
