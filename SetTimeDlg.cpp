// SetTimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "SetTimeDlg.h"
#include "afxdialogex.h"
#include "3D_ver_2Dlg.h"


// CSetTimeDlg �Ի���

IMPLEMENT_DYNAMIC(CSetTimeDlg, CDialogEx)

CSetTimeDlg::CSetTimeDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSetTimeDlg::IDD, pParent)
, m_SetH(0)
, m_SetM(0)
{

}

CSetTimeDlg::~CSetTimeDlg()
{
}

void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOUR_EDIT, m_SetH);
	DDX_Text(pDX, IDC_MINUTE_EDIT, m_SetM);
	DDX_Control(pDX, IDC_HOUR_SPIN, m_HCtrl);
	DDX_Control(pDX, IDC_MINUTE_SPIN, m_MCtrl);
	DDX_Control(pDX, IDC_HOUR_EDIT, m_HVCtrl);
	DDX_Control(pDX, IDC_MINUTE_EDIT, m_MVCtrl);
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_HOUR_SPIN, &CSetTimeDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MINUTE_SPIN, &CSetTimeDlg::OnDeltaposSpin2)
	ON_EN_CHANGE(IDC_HOUR_EDIT, &CSetTimeDlg::OnEnChangeHourEdit)
	ON_EN_CHANGE(IDC_MINUTE_EDIT, &CSetTimeDlg::OnEnChangeMinuteEdit)
	ON_BN_CLICKED(IDC_COMFIRM, &CSetTimeDlg::OnBnClickedComfirm)
	ON_BN_CLICKED(IDC_DEFAULT, &CSetTimeDlg::OnBnClickedDefault)
	ON_BN_CLICKED(IDC_CANCEL, &CSetTimeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetTimeDlg ��Ϣ�������


void CSetTimeDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (pNMUpDown->iDelta == -1 && m_SetH > 0)
		m_SetH--;
	else if (pNMUpDown->iDelta == -1 && m_SetH == 0){
		m_SetH = 23;
		UpdateData(false);
	}
	else if (pNMUpDown->iDelta == 1 && m_SetH < 23)
		m_SetH++;
	else if (pNMUpDown->iDelta == 1 && m_SetH == 23){
		m_SetH = 0;
		UpdateData(false);
	}
	UpdateData(false);

	*pResult = 0;
}


void CSetTimeDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (pNMUpDown->iDelta == -1 && m_SetM > 0)
		m_SetM--;
	else if (pNMUpDown->iDelta == -1 && m_SetM == 0)
		m_SetM = 59;
	else if (pNMUpDown->iDelta == 1 && m_SetM < 59)
		m_SetM++;
	else if (pNMUpDown->iDelta == 1 && m_SetM == 59)
		m_SetM = 0;
	UpdateData(false);
	*pResult = 0;
}


void CSetTimeDlg::OnEnChangeHourEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
}


void CSetTimeDlg::OnEnChangeMinuteEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(FALSE);
}


void CSetTimeDlg::OnBnClickedComfirm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_SetH == 0 && m_SetM == 0)
		EndDialog(0);
	else{
		CMy3D_ver_2Dlg::SetH = m_SetH;
		CMy3D_ver_2Dlg::SetM = m_SetM;
		CMy3D_ver_2Dlg::CountH = m_SetH;
		CMy3D_ver_2Dlg::CountM = m_SetM;
		CMy3D_ver_2Dlg::CountS = 0;
		CMy3D_ver_2Dlg::isdue = false;
		CMy3D_ver_2Dlg::isset = true;
		EndDialog(0);
	}
}




void CSetTimeDlg::OnBnClickedDefault()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_SetH = 0;
	m_SetM = 0;
	UpdateData(FALSE);
}

BOOL CSetTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_HCtrl.SetBuddy(GetDlgItem(m_SetH));
	m_HCtrl.SetRange(0, 23);
	m_MCtrl.SetBuddy(GetDlgItem(m_SetM));
	m_MCtrl.SetRange(0, 59);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CSetTimeDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

