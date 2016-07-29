
// 3D_ver_2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3D_ver_2.h"
#include "3D_ver_2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int CMy3D_ver_2Dlg::beep1 = 0;
int CMy3D_ver_2Dlg::SetH = 0;
int CMy3D_ver_2Dlg::SetM = 0;
int CMy3D_ver_2Dlg::CountH = 0;
int CMy3D_ver_2Dlg::CountM = 0;
int CMy3D_ver_2Dlg::CountS = 0;
bool CMy3D_ver_2Dlg::issettune = false;
bool CMy3D_ver_2Dlg::isset = false;
bool CMy3D_ver_2Dlg::isdue = false;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy3D_ver_2Dlg 对话框



CMy3D_ver_2Dlg::CMy3D_ver_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy3D_ver_2Dlg::IDD, pParent)
	, m_CurrentTime(_T(""))
	, m_SetTime(_T(""))
	, m_RemainingTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3D_ver_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CURRENT_TIME_TEXT, m_CurrentTime);
	DDX_Text(pDX, IDC_SETTIME_TEXT, m_SetTime);
	DDX_Text(pDX, IDC_REMAINING_TEXT, m_RemainingTime);
	DDX_Control(pDX, IDC_ABOUT, m_About);
}

BEGIN_MESSAGE_MAP(CMy3D_ver_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ABOUT, &CMy3D_ver_2Dlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_SETSOUND, &CMy3D_ver_2Dlg::OnBnClickedSetsound)
	//ON_BN_CLICKED(IDC_SETTIME, &CMy3D_ver_2Dlg::OnBnClickedSettime)
	ON_BN_CLICKED(IDC_SETINTERVAL, &CMy3D_ver_2Dlg::OnBnClickedSetinterval)
	ON_BN_CLICKED(IDC_SETTIME, &CMy3D_ver_2Dlg::OnBnClickedSettime)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CMy3D_ver_2Dlg 消息处理程序

BOOL CMy3D_ver_2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	//控制窗口大小
	MoveWindow(0, 0, 1136, 660, 1);

	//显示右上角时间
	
	//CString strTime;
	//CTime tm;
	//tm = CTime::GetCurrentTime();
	//strTime = tm.Format("%y年%m月%d日 %X");
	//SetDlgItemText(IDC_CURRENT_TIME_TEXT, strTime);
	//SetTimer(1, 1000, NULL);

	//加载声音按钮位图
	GetDlgItem(IDC_SETSOUND)->MoveWindow(50,420 , 200, 50, 1);
	CBMBS.LoadBitmaps(IDB_SOUND_UP, IDB_SOUND_DOWN, IDB_SOUND_FOCUS);
	CBMBS.SubclassDlgItem(IDC_SETSOUND, this);
	CBMBS.SizeToContent();

	//加载定时器按钮位图
	GetDlgItem(IDC_SETTIME)->MoveWindow(50,480 , 200, 50, 1);
	CBMBT.LoadBitmaps(IDB_TIME_UP, IDB_TIME_DOWN, IDB_TIME_FOCUS);
	CBMBT.SubclassDlgItem(IDC_SETTIME, this);
	CBMBT.SizeToContent();

	//加载摆头区间按钮位图
	GetDlgItem(IDC_SETINTERVAL)->MoveWindow(50,540 , 200, 50, 1);
	CBMBI.LoadBitmaps(IDB_INTERVAL_UP, IDB_INTERVAL_DOWN, IDB_INTERVAL_FOCUS);
	CBMBI.SubclassDlgItem(IDC_SETINTERVAL, this);
	CBMBI.SizeToContent();

	//显示使用说明窗口
	GetDlgItem(IDC_TEXT_WINDOW)->MoveWindow(50, 60, 200, 350, 1);
	m_TextDlg.Create(IDD_TEXT, this);
	GetDlgItem(IDC_TEXT_WINDOW)->GetWindowRect(&m_TextWindow);
	ScreenToClient(m_TextWindow);
	m_TextDlg.MoveWindow(m_TextWindow);
	m_TextDlg.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_TEXT_WINDOW)->ShowWindow(false);

	//显示3D摄像头画面窗口
	GetDlgItem(IDC_CHILD_WINDOW)->MoveWindow(270, 80, 800, 500, 1);
	m_DemoDlg.Create(IDD_DEMO, this);
	GetDlgItem(IDC_CHILD_WINDOW)->GetWindowRect(&m_DialogChild);
	ScreenToClient(m_DialogChild);
	m_DemoDlg.MoveWindow(m_DialogChild);
	m_DemoDlg.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CHILD_WINDOW)->ShowWindow(false);

	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy3D_ver_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy3D_ver_2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy3D_ver_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy3D_ver_2Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

string CMy3D_ver_2Dlg::GetNextSecond(int& Hour, int& Minute, int& Second){
	string outcome = "剩余时长：";
	if (isdue == true)
		return "时间到！";
	else if (Hour == 0 && Minute == 0 && Second == 0 && isdue == false && isset == true){
		Beep(beep1, 500);
		isdue = true;
		isset = false;
		return "时间到！";
	}
	else if (Hour > 0 && Minute == 0 && Second == 0 && isset == true){
		Hour--;
		Minute = 59;
		Second = 59;
	}
	else if (Minute > 0 && Second == 0 && isset == true){
		Minute--;
		Second = 59;
	}
	else if (Second > 0 && isset == true)
		Second--;
	else return "";
	stringstream oh, om, os;
	string tempm = "", temph = "", temps;
	oh << Hour;
	oh >> temph;
	om << Minute;
	om >> tempm;
	os << Second;
	os >> temps;
	outcome += "\t" + temph + "h" + tempm + "m" + temps + "s";
	return outcome;
}

/*void CMy3D_ver_2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString strTime;
	CTime tm;
	tm = CTime::GetCurrentTime();
	strTime = tm.Format("%Y-%m-%d %H:%M:%S");
	//SetDlgItemText(IDC_CURRENT_TIME, strTime);        //显示系统时间
	m_CurrentTime = strTime;
	m_RemainingTime = GetNextSecond(CountH, CountM, CountS).c_str();
	UpdateData(false);
	if (isset == true){
		if (isset == true){
			GetDlgItem(IDC_SETTIME_TEXT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_REMAINING_TEXT)->ShowWindow(SW_SHOW);
		}
		if (issettune == false)
			beep1 = 500;
		stringstream sh, sm;
		string tempm = "", temph = "";
		sh << SetH;
		sh >> temph;
		sm << SetM;
		sm >> tempm;
		ShowSetTime += +"\t" + temph + "h\t" + tempm + "m";
		m_SetTime = ShowSetTime.c_str();
		UpdateData(false);
	}
	CDialogEx::OnTimer(nIDEvent);

	CDialogEx::OnTimer(nIDEvent);
}*/


void CMy3D_ver_2Dlg::OnBnClickedAbout()
{
	// TODO:  在此添加控件通知处理程序代码
	CAboutbox dlg;
	dlg.DoModal();
}


void CMy3D_ver_2Dlg::OnBnClickedSetsound()
{
	// TODO:  在此添加控件通知处理程序代码
	CSetSoundDlg dlg;
	dlg.DoModal();
}


void CMy3D_ver_2Dlg::OnBnClickedSettime()
{
	// TODO:  在此添加控件通知处理程序代码
	CSetTimeDlg dlg;
	dlg.DoModal();
}



void CMy3D_ver_2Dlg::OnBnClickedSetinterval()
{
	// TODO:  在此添加控件通知处理程序代码
	CSetIntervalDlg dlg;
	dlg.DoModal();
}


HBRUSH CMy3D_ver_2Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CMy3D_ver_2Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CGraph::OnKeyDown(nChar, nRepCnt, nFlags);

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CMy3D_ver_2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	return CWnd::PreTranslateMessage(pMsg);
}