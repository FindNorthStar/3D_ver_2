// Demo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "Demo.h"
#include "afxdialogex.h"
#include"3D_ver_2Dlg.h"


// CDemo �Ի���

IMPLEMENT_DYNAMIC(CDemo, CDialogEx)

CDemo::CDemo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemo::IDD, pParent)
{

}

CDemo::~CDemo()
{
}

void CDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OUTPUT, m_output);
}


BEGIN_MESSAGE_MAP(CDemo, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_OUTPUT, &CDemo::OnEnChangeOutput)
END_MESSAGE_MAP()


// CDemo ��Ϣ�������


int CDemo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rect(0, 0, 800, 500);
	this->GetClientRect(&rect);
	rect.bottom = rect.Height()-50;
	m_pdisplay = new CGraph;
	m_pdisplay->Create(NULL, NULL, WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE, rect, this, 0);
	this->SetTimer(0, 20, 0);
	return 0;

}


void CDemo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
	m_output = m_pdisplay->GetOutput();
	m_angle = m_pdisplay->GetAngle();
	UpdateData(false);
}


void CDemo::OnEnChangeOutput()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	m_output = m_pdisplay->GetOutput();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
