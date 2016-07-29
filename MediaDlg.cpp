// MediaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "MediaDlg.h"
#include "afxdialogex.h"
#include <direct.h>
#include <tchar.h>
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMediaDlg 对话框

IMPLEMENT_DYNAMIC(CMediaDlg, CDialogEx)

CMediaDlg::CMediaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMediaDlg::IDD, pParent)
{

}

CMediaDlg::~CMediaDlg()
{
}

void CMediaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX1, m_Movie);
}


BEGIN_MESSAGE_MAP(CMediaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CMediaDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_REPLAY, &CMediaDlg::OnBnClickedReplay)
END_MESSAGE_MAP()

void c2w(wchar_t *pwstr, size_t len, const char *str)

{
	if (str)
	{
		size_t nu = strlen(str);
		size_t n = (size_t)::MultiByteToWideChar(CP_ACP, 0, (const char *)str, (int)nu, NULL, 0);
		if (n >= len)n = len - 1;
		MultiByteToWideChar(CP_ACP, 0, (const char *)str, (int)nu, pwstr, (int)n);
		pwstr[n] = 0;
	}
}

// CMediaDlg 消息处理程序


BOOL CMediaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText(_T("视频演示"));
	char path[255];
	wchar_t wpath[255];
	_getcwd(path, 255);
	sprintf(path, "%s\\ini\\", path);
	c2w(wpath, 255, path);
	CreateDirectory(wpath, NULL);
	// TODO: 在此添加额外的初始化代码
	sprintf(path, "%s\\appname.ini", path);
	std::ofstream out(path, std::ios::trunc | std::ios::out);
	out << "[Section1]\nhelp.wmv=help.wmv" << std::flush;
	out.close();
	m_Set = m_Movie.GetSettings();
	FilePathName = "help.wmv";
	CString setingfile = wpath;
	setingfile = setingfile + L"appname.ini";
	CString str = PathFindFileName(FilePathName.GetBuffer());
	CString strFileNamePath;
	GetPrivateProfileString(_T("Section1"), str, NULL, strFileNamePath.GetBuffer(MAX_PATH), MAX_PATH, setingfile);
	strFileNamePath.ReleaseBuffer();

	m_Media = m_Movie.newMedia(strFileNamePath);
	m_Movie.SetCurrentMedia(m_Media);
	m_Control = m_Movie.GetControls();



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMediaDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMediaDlg::OnBnClickedReplay()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Movie.SetCurrentMedia(m_Media);
}

