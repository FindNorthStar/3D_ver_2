// CGraph.cpp : 实现文件
//
#pragma warning (disable : 4996 )
#pragma comment (lib,"openNI2.lib")
#pragma comment (lib,"NITE2.lib")
#pragma comment (lib,"glut32.lib")


#include "stdafx.h"
#include "Graph.h"
#include "3D_ver_2.h"
#include "Data.h"
#include "Conclusion.h"
#include "3D_ver_2Dlg.h"
#include "Algor.h"

using std::ofstream;
CGraph*CGraph::pThis = NULL;
double CGraph::smaxTime[CGraph::WrongGesture::WRONGGESTURE_SIZE] = { 3, 3, 3, 3,3 };
#pragma region GolbelValue
#define UNINIT 1
#define COUNTING 2
#define WRONGGESTURE(ges,output)\
{\
	if (TimeCount(ges) == TimeStatus::OVERTIME&&noWrong)\
			{\
		sprintf(message, "%s\n", output);\
		noWrong = false;\
			}\
}\
else\
{\
	TimeCount(ges, true);\
}

static int clocks = 0, sign = 0;
static float statistic[151] = { 0.0 };

static HBITMAP hWarningBmp;
static BITMAP oWarningBmp;

static int isinit = 0;
static int isinitgraph = 0;
static int istracked = 0;
static int isstart = 0;
static int restart = 0;
static int isclear = 0;

static float rat = 0.025;

static GLint list[1] = { 0 };

static GLfloat ambient0[] = { 0.6, 0.6, 0.6, 1 };
static GLfloat position0[] = { 3, 0, 1, 1 };
static GLfloat diffuse0[] = { 0.8, 0.4, 0, 1 };
static GLfloat specular0[] = { 0.4, 0.4, 0.4, 1 };

static GLfloat ambient1[] = { 0.4, 0.4, 0.4, 1 };
static GLfloat position1[] = { 0, 0, 5, 1 };
static GLfloat diffuse1[] = { 0.4, 0.6, 0.4, 1 };
static GLfloat specular1[] = { 0.2, 0.2, 0.2, 1 };

static GLfloat ambient2[] = { 0.5, 0.5, 0.5, 1 };
static GLfloat position2[] = { 0, 0, 5, 1 };
static GLfloat diffuse2[] = { 0.3, 0.5, 0.3, 1 };
static GLfloat specular2[] = { 0.0, 0.0, 0.0, 1 };

#pragma endregion

IMPLEMENT_DYNAMIC(CGraph, CWnd)
BEGIN_MESSAGE_MAP(CGraph, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	/*ON_WM_KEYDOWN()*/
END_MESSAGE_MAP()

CGraph::CGraph()
{
	pThis = this;
	logfile.open("Application.log", std::fstream::out | std::fstream::app);
	SYSTEMTIME systime;
	::GetLocalTime(&systime);
	logfile << "\n" << endl;
	logfile << "The Running Date is : " << systime.wYear << " " << systime.wMonth << " " << systime.wDay << endl;
	logfile << "The Time is: " << systime.wHour << " " << systime.wMinute << " " << systime.wSecond << endl;
	logfile.flush();
	memset(x, 0, sizeof(float)*JointData::JOINTDATA_SIZE);
	memset(y, 0, sizeof(float)*JointData::JOINTDATA_SIZE);
	memset(z, 0, sizeof(float)*JointData::JOINTDATA_SIZE);
	m_pixelindex = 0;
	m_hglrc = 0;
	m_angle = 0;
	m_firstuser = 0;
	m_playmode = PLAYMODE_DEPTH;
	m_stddata1.Create(30);
	m_stddata2.Create(5);
	m_angdata1.Create(30);
	m_angdata2.Create(60, true);
	m_angdata3.Create(60, true);
	m_angdata4.Create(24, true);
	m_chart1.Create(1);
	m_chart2.Create(60, true);
	m_anlyzemode = ANLYZEMODE_FRONT;
	memcpy(maxTime, smaxTime, sizeof(double)*WrongGesture::WRONGGESTURE_SIZE);
	nite::JointType data[JOINTDATA_SIZE] = { nite::JOINT_HEAD, nite::JOINT_LEFT_SHOULDER, nite::JOINT_RIGHT_SHOULDER
		, nite::JOINT_NECK, nite::JOINT_LEFT_HIP, nite::JOINT_RIGHT_HIP
		, nite::JOINT_LEFT_ELBOW, nite::JOINT_RIGHT_ELBOW, nite::JOINT_TORSO, nite::JOINT_HEAD, nite::JOINT_LEFT_SHOULDER, nite::JOINT_HEAD };
	memcpy(jType, data, sizeof(nite::JointType)*JOINTDATA_SIZE);
	double init[Config::CONFIG_SIZE];
	init[Config::CONFIG_SHOULDER_MIN] = 60;
	init[Config::CONFIG_SHOULDER_MAX] = 200;
	init[Config::CONFIG_HEAD_ANGLE_A] = 0;
	init[Config::CONFIG_HEAD_ANGLE_B_MIN] = 0;
	init[Config::CONFIG_HEAD_ANGLE_B_MAX] = 7;
	init[Config::CONFIG_ABDOMEN_ANGLE] = 7.5;
	init[Config::CONFIG_ASIDE_HEAD_ANGLE_MIN] = 1.5;
	init[Config::CONFIG_ASIDE_HEAD_ANGLE_MAX] = 7.5;
	init[Config::CONFIG_DELAY] = 10;
	config.SetAllConfig(init);
}

CGraph::~CGraph()
{
	//OnDestory();
	logfile << "destory method start..." << endl;
	logfile.flush();
	m_exist = false;
	m_depthref.release();
	m_userref.release();
	m_colorref.release();
	m_colorstream.destroy();
	m_depthstream.destroy();
	m_usertracker.destroy();
	m_device.close();
	nite::NiTE::shutdown();
	openni::OpenNI::shutdown();
	wglMakeCurrent(0, 0);
	wglDeleteContext(m_hglrc);
	//CMy3D_ver_2Dlg::m_startCtrl.EnableWindow(true);
	logfile << "destory method accomplished..." << endl;
	logfile.close();

}

// CGraph 消息处理程序
void CGraph::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (pThis == NULL)
	{
		return;
	}
	switch (nChar)
	{
		pThis->logfile << "Press Button " << nChar << endl;
		pThis->logfile.flush();
	case '1':
		pThis->m_playmode = PLAYMODE_DEPTH;
		pThis->m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_OFF);
		break;
	case '2':
		pThis->m_playmode = PLAYMODE_COLOR;
		pThis->m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_OFF);
		break;
	case '3':
		pThis->m_playmode = PLAYMODE_DEPTH_AND_COLOR;
		pThis->m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
		break;
	case '4':
		pThis->m_anlyzemode = ANLYZEMODE_FRONT;
		break;
	case '5':
		pThis->m_anlyzemode = ANLYZEMODE_SIZE;
		break;
	case 'S':
		isstart = 1;
		break;
	case 'P':
		isstart = 0;
		break;
	case 'R':
		restart = 1;
		break;
	case 'T':
		isclear = 1;
		break;
	default:
		break;
	}

};

// void CGraph::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	switch (nChar)
//	{
//		logfile << "Press Button " << nChar << endl;
//		logfile.flush();
//	case '1':
//		m_playmode = PLAYMODE_DEPTH;
//		m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_OFF);
//		break;
//	case '2':
//		m_playmode = PLAYMODE_COLOR;
//		m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_OFF);
//		break;
//	case '3':
//		m_playmode = PLAYMODE_DEPTH_AND_COLOR;
//		m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
//		break;
//	case '4':
//		m_anlyzemode = ANLYZEMODE_FRONT;
//		break;
//	case '5':
//		m_anlyzemode = ANLYZEMODE_SIZE;
//		break;
//	case 'S':
//		isstart = 1;
//		break;
//	case 'P':
//		isstart = 0;
//		break;
//	case 'R':
//		restart = 1;
//		break;
//	case 'T':
//		isclear = 1;
//	}
//
//	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
//};

void CGraph::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	m_width = cx, m_height = cy;
	//if (isinit == 1)
	//{
	//	InitGraph();
	//	isinit = 0;
	//}
}

void CGraph::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	this->GetClientRect(&rect);
	InvalidateRect(rect, false);
	CWnd::OnTimer(nIDEvent);
}

void CGraph::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	logfile << "Ondestroy method start..." << endl;
	logfile.flush();
	restart = 0;
	istracked = 0;
	isstart = 0;
	isinit = 0;
	isinitgraph = 0;
	m_stddata1.Restart();
	m_stddata2.Restart();
	m_angdata1.Restart();
	m_angdata2.Restart();
	m_angdata3.Restart();
	m_angdata4.Restart();
	m_chart1.Restart();
	m_chart2.Restart();
	m_depthref.release();
	m_userref.release();
	m_colorref.release();
	m_colorstream.destroy();
	m_depthstream.destroy();
	m_usertracker.destroy();
	m_device.close();
	//nite::NiTE::shutdown();
	//openni::OpenNI::shutdown();
	//wglMakeCurrent(0, 0);
	//wglDeleteContext(m_hglrc);
	//CMy3D_ver_2Dlg::m_startCtrl.EnableWindow(true);
	//this->CloseWindow();
	logfile << "Ondestroy method accomplished..." << endl;
	logfile.flush();
};

void CGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	if (m_exist != true && isinit != 1)
	{
		DrawWarning();
		return;
	}
	if (isinitgraph == 0)
	{
		InitGraph();
	}
	//SetFocus();
	InitDisplayMode();
	DrawTexture();
	DrawJointSphere();
	DataFun();
	DrawModel();
	DrawChart();
	m_userref.release();
	if (restart == 1)
	{
		m_usertracker.destroy();
		m_usertracker.create(&m_device);
		restart = 0;
		istracked = 0;
		isstart = 0;
		m_stddata1.Restart();
		m_stddata2.Restart();
		m_angdata1.Restart();
		m_angdata2.Restart();
		m_angdata3.Restart();
		m_angdata4.Restart();
		m_chart1.Restart();
		m_chart2.Restart();
	}

	glFlush();
	SwapBuffers(dc.m_hDC);
}

int CGraph::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!logfile.fail())
	{
		logfile << "Init starting..." << endl;
		logfile.flush();
	}
	HWND hwnd = GetSafeHwnd();
	HDC hdc = ::GetDC(hwnd);
	SetPixel(hdc);
	m_hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, m_hglrc);
	this->SetTimer(1, 20, 0);
	openni::OpenNI::initialize();
	nite::NiTE::initialize();
	isinitgraph = 0;
	m_width = 0, m_height = 0;
	if (m_device.open(openni::ANY_DEVICE) != openni::STATUS_OK)
	{
		m_device.close();
		MessageBox(L"OPEN ERROR--NOT FIND DEVICES");
		logfile << "OPEN ERROR--NOT FIND DEVICES" << endl;
		logfile.flush();
		//OnDestroy();
		//exit(0);
		m_exist = false;
		//CMy3D_ver_2Dlg::m_startCtrl.EnableWindow(true);
		isinit = 0;
		return -1;
	}
	m_usertracker.create(&m_device);
	m_colorstream.create(m_device, openni::SENSOR_COLOR);
	m_colorstream.start();
	m_depthstream.create(m_device, openni::SENSOR_DEPTH);
	m_depthstream.start();
	m_exist = true;
	isinit = 1;
	logfile << "Init OK!" << endl;
	logfile.flush();
	return 0;
}

void CGraph::Calculate(float* pHistogram, int histogramSize, const openni::VideoFrameRef& depthFrame)
{
	const openni::DepthPixel* pDepth = (const openni::DepthPixel*)depthFrame.getData();
	int width = depthFrame.getWidth();
	int height = depthFrame.getHeight();
	memset(pHistogram, 0, histogramSize*sizeof(float));
	int restOfRow = depthFrame.getStrideInBytes() / sizeof(openni::DepthPixel) - width;

	unsigned int nNumberOfPoints = 0;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x, ++pDepth)
		{
			if (*pDepth != 0)
			{
				pHistogram[*pDepth]++;
				nNumberOfPoints++;
			}
		}
		pDepth += restOfRow;
	}
	for (int nIndex = 1; nIndex < histogramSize; nIndex++)
	{
		pHistogram[nIndex] += pHistogram[nIndex - 1];
	}
	if (nNumberOfPoints)
	{
		for (int nIndex = 1; nIndex < histogramSize; nIndex++)
		{
			pHistogram[nIndex] = (256 * (1.0f - (pHistogram[nIndex] / nNumberOfPoints)));
		}
	}
}

void CGraph::DataAnlyze(void)
{
	bool noWrong = true;

	float headangle = ((y[HEAD] - y[NECK]) / (z[HEAD] - z[NECK]));
	float headangle2 = ((y[HEAD] - y[NECK]) / (x[HEAD] - x[NECK]));
	float torsoangle2 = (y[HEAD] - y[TORSO]) / (x[HEAD] - x[TORSO]);
	float torsoangle3 = (y[NECK] - y[TORSO]) / (x[NECK] - x[TORSO]);
	float hipangle4;
	if (z[RIGHT_HIP]<z[LEFT_HIP])
	{
		hipangle4 = (y[HEAD] - y[RIGHT_HIP]) / (x[HEAD] - x[RIGHT_HIP]);
	}
	else
	{
		hipangle4 = (y[HEAD] - y[LEFT_HIP]) / (x[HEAD] - x[LEFT_HIP]);
	}
	float hipangle5 = (y[NECK] - y[RIGHT_HIP]) / (x[NECK] - x[RIGHT_HIP]);
	float shoulderangle1 = (y[SHOULDER_ASIDE] - y[HEAD]) / (x[SHOULDER_ASIDE] - x[HEAD]);
	m_angle = GetAngle(0, 1, 0, x[HEAD] - x[NECK], y[HEAD] - y[NECK], z[HEAD] - z[NECK]);
	char message[100];
	memset(message, 0, sizeof(char) * 100);
	float shoulder_distance = abs(z[LEFT_SHOULDER] - z[RIGHT_SHOULDER]);
	if (shoulder_distance >= config.GetConfig(Config::CONFIG_SHOULDER_MAX))
	{
		m_anlyzemode = ANLYZEMODE_SIZE;
	}
	else if (shoulder_distance <= config.GetConfig(Config::CONFIG_SHOULDER_MIN))
	{
		m_anlyzemode = ANLYZEMODE_FRONT;
	}
	if (m_anlyzemode == ANLYZEMODE_FRONT)
	{
		if (/*headangle >= 30.0 || */headangle <= config.GetConfig(Config::CONFIG_HEAD_ANGLE_A))
			WRONGGESTURE(WrongGesture::HEAD_FOREWARD, "Your head is upwards too much!");

		if (headangle2 >= config.GetConfig(Config::CONFIG_HEAD_ANGLE_B_MIN) && headangle2 <= config.GetConfig(Config::CONFIG_HEAD_ANGLE_B_MAX))
			WRONGGESTURE(WrongGesture::HEAD_RIGHT, "Your head is right too much!");

		if (headangle2 >= -1 * config.GetConfig(Config::CONFIG_HEAD_ANGLE_B_MAX) && headangle2 <= config.GetConfig(Config::CONFIG_HEAD_ANGLE_B_MIN))
			WRONGGESTURE(WrongGesture::HEAD_LEFT, "Your head is left too much!");
	}
	else
	{
		if (abs(hipangle5) <= config.GetConfig(Config::CONFIG_ABDOMEN_ANGLE))
			WRONGGESTURE(WrongGesture::ASIDE_BODY_FOREWARD, "Your body is forwards too much!");

		if (abs(shoulderangle1) <= config.GetConfig(Config::CONFIG_ASIDE_HEAD_ANGLE_MIN) && abs(hipangle5) >= config.GetConfig(Config::CONFIG_ASIDE_HEAD_ANGLE_MAX))
			WRONGGESTURE(WrongGesture::ASIDE_HEAD_FOREWARD, "Your head is foreward too much!");

	}

	if (noWrong)
	{
		sprintf(message, "%s\n", "Correct! ");
	}
	if (message[0] != '\0')
	{
		char *msg = message;
		glColor3f(1.0f, 0.0f, 0.0f);
		glRasterPos2i(50, 20);//glRasterPos2i(200, 200); 改变光栅位置光栅(Raster):由像素构成的一个矩形网格。要在光栅上显示的数据保存于帧缓存内。
		GlPrintString(GLUT_BITMAP_TIMES_ROMAN_24, msg);
	}
}

void CGraph::DrawWarning(void)
{
	return;
	hWarningBmp = ::LoadBitmap(::GetModuleHandle(0), L"warning.bmp");
	::GetObject(hWarningBmp, sizeof(BITMAP), &oWarningBmp);
	unsigned char texrureData[256 * 256][3];
	memset(texrureData, 0, sizeof(texrureData));
	gluScaleImage(GL_RGB, oWarningBmp.bmWidth, oWarningBmp.bmHeight, GL_UNSIGNED_BYTE, oWarningBmp.bmBits, 256, 256, GL_UNSIGNED_BYTE, texrureData);

};

void CGraph::DrawTexture(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(0,0,)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_width, m_height, 0, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, m_width*0.75, m_height);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, -1, 0, 1, 0);
	glColor3f(1, 1, 1);

	Algor algor;
	float colorconst[10000];
	openni::RGB888Pixel*texdata = new openni::RGB888Pixel[m_mapx*m_mapy];
	memset(texdata, 0, sizeof(openni::RGB888Pixel)*m_mapx*m_mapy);
	int d_width = m_depthref.getWidth();
	int d_height = m_depthref.getHeight();
	//CData pointdata;
	//CConculate Conclusion(m_mapx, m_mapy);
	if (m_colorref.isValid() && (m_playmode == PLAYMODE_COLOR || m_playmode == PLAYMODE_DEPTH_AND_COLOR))
	{
		memcpy(texdata, m_colorref.getData(), m_mapx*m_mapy*sizeof(openni::RGB888Pixel));
	}

	if (m_depthref.isValid() && (m_playmode == PLAYMODE_DEPTH || m_playmode == PLAYMODE_DEPTH_AND_COLOR))
	{
		Calculate(colorconst, 10000, m_depthref);
		int colorset[][3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
		const nite::UserMap usermap = m_userref.getUserMap();
		const nite::UserId *userdata = usermap.getPixels();
		const openni::DepthPixel*depthdata = (const openni::DepthPixel*)m_depthref.getData();
		openni::RGB888Pixel*ptexdata = texdata;
		unsigned int(*dtemp)[3] = new unsigned int[d_width*d_height][3];
		const nite::UserId *flag = usermap.getPixels();
		memset(dtemp, 0, sizeof(unsigned int)*d_width*d_height * 3);
		for (int h = 0; h < d_height; h++)
		{
			for (int w = 0; w < d_width; w++, flag++)
			{
				if (*flag != 0)
				{
					dtemp[h*d_width + w][0] = 255;
					dtemp[h*d_width + w][1] = 255;
					dtemp[h*d_width + w][2] = depthdata[h*d_width + w];
				}
			}
		}
		algor.CreateFromData(dtemp, d_width, d_height);
		algor.AnalyzeData();
		if (algor.dataValid)
		{
			float testAngle;
			int shoulder[3], head[3], iflag = 0;
			float shoulderW[3], headW[3];
			shoulder[0] = algor.joint[0].x;
			shoulder[1] = algor.joint[0].y;
			shoulder[2] = algor.joint[0].z;
			head[0] = algor.joint[1].x;
			head[1] = algor.joint[1].y;
			head[2] = algor.joint[1].z;
			openni::CoordinateConverter::convertDepthToWorld(m_depthstream, shoulder[0], shoulder[1], shoulder[2], shoulderW, shoulderW + 1, shoulderW + 2);
			openni::CoordinateConverter::convertDepthToWorld(m_depthstream, head[0], head[1], head[2], headW, headW + 1, headW + 2);
			x[SHOULDER_ASIDE] = shoulderW[0];
			y[SHOULDER_ASIDE] = shoulderW[1];
			z[SHOULDER_ASIDE] = shoulderW[2];
			x[HEAD_ASIDE] = head[0];
			y[HEAD_ASIDE] = head[1];
			z[HEAD_ASIDE] = head[2];
			testAngle = (shoulderW[1] - headW[1]) / (shoulderW[0] - headW[0]);
			if (testAngle < 1.5) iflag = 1;
			sprintf(outputBuffer, "%4s,%4.2f,%d", algor.outputBuffer, testAngle, iflag);
			output = CString(outputBuffer);
		}
		delete[]dtemp;
		for (int y = 0; y < m_depthref.getHeight(); y++)
		{
			for (int x = 0; x < m_depthref.getWidth(); x++, userdata++, depthdata++, ptexdata++)
			{
				if (*userdata != 0)
				{
					ptexdata->r = colorset[(int)(*userdata) % 3][0] * (int)(*depthdata);
					ptexdata->g = colorset[(int)(*userdata) % 3][1] * (int)(*depthdata);
					ptexdata->b = colorset[(int)(*userdata) % 3][2] * (int)(*depthdata);
					if (isstart == 1)
					{
						if (*(userdata - m_depthref.getWidth()) == 0 || *(userdata + m_depthref.getWidth()) == 0
							|| *(userdata + 1) == 0 || *(userdata - 1) == 0)
						{
							//pointdata.Add(x, y, *depthdata);
							ptexdata->r = 255;
							ptexdata->g = 125;
							ptexdata->b = 0;
						}

						//Conclusion.Add(x, y);
					}
				}
				else
				{
					if (m_playmode == PLAYMODE_DEPTH)
					{
						ptexdata->r = colorconst[*depthdata];
						ptexdata->g = colorconst[*depthdata];
						ptexdata->b = colorconst[*depthdata];
					}
				}
				if (algor.exist[y*d_width + x] == PIX_BODY)
				{
					ptexdata->r = 255;
					ptexdata->g = 255;
					ptexdata->b = 0;
				}
				else if (algor.exist[y*d_width + x] == PIX_JOINT)
				{
					ptexdata->r = 255;
					ptexdata->g = 0;
					ptexdata->b = 255;
				}
			}
		}
	}
#ifdef GL_GENERATE_MIPMAP_SGIS
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
#else
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#endif
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_mapx, m_mapy, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(m_width, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(m_width, m_height, 0);
	glTexCoord2f(0, 1); glVertex3f(0, m_height, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 0, 1);
	for (unsigned int i = 0; i < algor.joint.size(); i++)
	{
		glPushMatrix();
		glTranslated(algor.joint[i].x*1.0 / d_width*m_width, algor.joint[i].y*1.0 / d_height*m_height, 0);
		glutSolidSphere(5, 100, 100);
		glPopMatrix();
	}
	//pointdata.Deldata();
	delete[]texdata;
}

void CGraph::DrawJointSphere()
{
	const nite::Array<nite::UserData>&userjointdata = m_userref.getUsers();
	for (int i = 0; i < userjointdata.getSize(); i++)
	{
		if (i == 1) break;
		if (userjointdata[i].isNew())
		{
			m_usertracker.startSkeletonTracking(userjointdata[i].getId());
			m_usertracker.startPoseDetection(userjointdata[i].getId(), nite::POSE_PSI);
		}
		if (!userjointdata[i].isLost())
		{
			static int flag = 0;
			const nite::PoseData&pose = userjointdata[i].getPose(nite::POSE_PSI);
			JointFun(m_usertracker, userjointdata[i], m_mapx, m_mapy);
			if (pose.isEntered())
			{
				flag = (flag + 1) % 2;
				if (flag == 1) isstart = 1;
				else isstart = 0;
			}
		}
	}
}

void CGraph::DrawModel(void)
{
	static int init = 0;
	static float sx, sy, sz;
	static float angle = 0;
	int ratio = 100;
	float mx1 = x[CGraph::JointData::HEAD] / ratio, mx2 = x[CGraph::JointData::LEFT_SHOULDER] / ratio, mx3 = x[CGraph::JointData::RIGHT_SHOULDER] / ratio, mx4 = x[CGraph::JointData::NECK] / ratio;
	float my1 = y[CGraph::JointData::HEAD] / ratio, my2 = y[CGraph::JointData::LEFT_SHOULDER] / ratio, my3 = y[CGraph::JointData::RIGHT_SHOULDER] / ratio, my4 = y[CGraph::JointData::NECK] / ratio;
	float mz1 = z[CGraph::JointData::HEAD] / ratio, mz2 = z[CGraph::JointData::LEFT_SHOULDER] / ratio, mz3 = z[CGraph::JointData::RIGHT_SHOULDER] / ratio, mz4 = z[CGraph::JointData::NECK] / ratio;
	glEnable(GL_SCISSOR_TEST);
	glScissor(m_width*0.75, m_height*0.75, m_width, m_height);
	glColor4f(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, m_width*1.0 / m_height, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(m_width*0.75, m_height*0.75, m_width*0.25, m_height*0.25);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_FILL);
	glShadeModel(GL_SMOOTH);
	position2[0] = sx + 5 * cos(angle / 180 * 3.14);
	position2[1] = sy + 0;
	position2[2] = sz + 5 * sin(angle / 180 * 3.14);
	angle += 5;
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	if (istracked == 0 || isstart == 0)
	{
		sx = sy = sz = 0;
		init = 0;
		gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
		glPushMatrix();
		glutSolidSphere(1, 100, 100);
		glPopMatrix();
	}
	else
	{
		if (init == 0)
		{
			sx = mx4, sy = my4, sz = mz4;
			position0[0] = sx + 5;
			position0[1] = sy;
			position0[2] = sz;
			position1[0] = sx;
			position1[1] = sy;
			position1[2] = sz + 5;
			glLightfv(GL_LIGHT0, GL_POSITION, position0);
			glLightfv(GL_LIGHT1, GL_POSITION, position1);
			init = 1;
		}

		double distance = sqrt((sx - mx4)*(sx - mx4) + (sy - my4)*(sy - my4) + (sz - mz4)*(sz - mz4));
		if (distance >= 8)
		{
			sx = sx - (mx4 - sx) / distance*0.1;
			sy = sy - (my4 - sy) / distance*0.1;
			sz = sz - (mz4 - sz) / distance*0.1;
		}
		double distance2 = sqrt((sz - mz4)*(sz - mz4));
		if (distance2 <= 2 && distance2 > 0.1)
			sz = sz + (mz4 - sz) / distance2*0.1;
		double distance3 = sqrt((sx - mx4)*(sx - mx4) + (sy - my4)*(sy - my4));
		if (distance3 >= 2)
		{
			sx = sx + (mx4 - sx) / distance3*0.1;
			sy = sy + (my4 - sy) / distance3*0.1;
		}

		gluLookAt(sx + 7 * cos(45.0 / 180 * 3.14), sy, sz + 7 * sin(45.0 / 180 * 3.14), sx, sy, sz, 0, 1, 0);
		////////////head//////////////
		glPushMatrix();
		glTranslatef(mx1, my1, mz1);
		glutSolidSphere(0.5, 100, 100);
		glPopMatrix();
		///////////left-shoulder/////
		glPushMatrix();
		glTranslatef(mx2, my2, mz2);
		glutSolidSphere(0.5, 100, 100);
		glPopMatrix();
		//////////righr-shoulder////
		glPushMatrix();
		glTranslatef(mx3, my3, mz3);
		glutSolidSphere(0.5, 100, 100);
		glPopMatrix();
		//////////neck/////////////
		glPushMatrix();
		glTranslatef(mx4, my4, mz4);
		glutSolidSphere(0.5, 100, 100);
		glPopMatrix();
		//////////line-to-joint////

		glLineWidth(2.5);
		float mambient0[] = { 0.3, 0.3, 0.3, 0.5 };
		glPushAttrib(GL_LIGHTING_BIT);
		glBegin(GL_LINES);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mambient0);
		glVertex3f(mx4, my4, mz4);
		glVertex3f(mx1, my1, mz1);
		glVertex3f(mx4, my4, mz4);
		glVertex3f(mx2, my2, mz2);
		glVertex3f(mx4, my4, mz4);
		glVertex3f(mx3, my3, mz3);
		glEnd();
		glPopAttrib();
	}
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glDisable(GL_SCISSOR_TEST);
}

void CGraph::DrawChart(void)
{
	int scx = m_width*0.75, scy = 0;
	int scwid = m_width*0.25, schei = m_height*0.75;

	glEnable(GL_SCISSOR_TEST);
	glScissor(scx, scy, scwid, schei);
	glColor3f(0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, scwid, 0, schei, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(scx, scy, scwid, schei);
	gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1);
	//glDepthMask(GL_FALSE);
	glCallList(list[0]);
	//glDepthMask(GL_TRUE);
	glLineWidth(1.5);

	/////////////////////////std-data//////////////////////
	glColor4f(1.0, 0.6, 0, 1);
	float drawx, drawy;
	drawx = m_width*0.075, drawy = m_height*0.375;
	glBegin(GL_LINE_STRIP);
	for (int i = m_stddata2.m_index - 1; i >= 0 && drawx >= -0.001; i--)
	{
		float drtoy = m_stddata2[i] / 10 * m_height*rat + drawy;
		glVertex3f(drawx, drtoy, 1);
		drawx -= m_width*rat;
	}
	glEnd();

	/////////////////////per-second/////////////
	glColor4f(0.5, 1.0, 0, 1);
	drawx = m_width*0.25, drawy = m_height*0.375;
	glBegin(GL_LINE_STRIP);
	for (int i = m_angdata2.m_index; i >= 0 && drawx >= -0.001; i--)
	{
		if (i == 0 && m_angdata2.m_multi > 0)
		{
			i = m_angdata2.m_size - 1;
		}
		if (i == 0 && m_angdata2.m_multi == 0)break;
		float drtoy = m_angdata2[i - 1] / 10 * m_height*rat + drawy;
		glVertex3f(drawx, drtoy, 1);
		drawx -= m_width*rat;
	}
	glEnd();

	/////////////////////per-minter/////////////
	glColor4f(0, 0.9, 1.0, 1);
	drawx = m_width*0.25, drawy = m_height*0.375;
	glBegin(GL_LINE_STRIP);
	for (int i = m_angdata3.m_index; i >= 0 && drawx >= -0.001; i--)
	{
		if (i == 0 && m_angdata3.m_multi > 0)
		{
			i = m_angdata3.m_size - 1;
		}
		if (i == 0 && m_angdata3.m_multi == 0)break;
		float drtoy = m_angdata3[i - 1] / 10 * m_height*rat + drawy;
		glVertex3f(drawx, drtoy, 1);
		drawx -= m_width*rat;
	}
	glEnd();

	//////////////////////per-hour///////////
	glColor4f(0.9, 0.45, 0.9, 1);
	drawx = m_width*0.25, drawy = m_height*0.375;
	glBegin(GL_LINE_STRIP);
	for (int i = m_angdata4.m_index; i >= 0 && drawx >= -0.001; i--)
	{
		if (i == 0 && m_angdata4.m_multi > 0)
		{
			i = m_angdata4.m_size - 1;
		}
		if (i == 0 && m_angdata4.m_multi == 0)break;
		float drtoy = m_angdata4[i - 1] / 10 * m_height*rat + drawy;
		glVertex3f(drawx, drtoy, 1);
		drawx -= m_width*rat;
	}
	glEnd();

	////////////////////////diagram///////////////////
	glColor4f(1.0, 0.9, 0.5, 1);
	drawx = m_width*0.25 / m_angdata2.sm_maxdiagram, drawy = 0;
	glBegin(GL_QUADS);
	for (unsigned int i = 0; i < m_angdata2.sm_maxdiagram; i++)
	{
		drawy = 1.0 * m_angdata2.m_diagram[i] / m_angdata2.m_size*0.3*m_height;
		if (drawy >= 0.3*m_height)
		{
			drawy = 0.3*m_height;
		}
		glVertex3f(i*drawx, 0, 0.5);
		glVertex3f((i + 1)*drawx, 0, 0.5);
		glVertex3f((i + 1)*drawx, drawy, 0.5);
		glVertex3f(i*drawx, drawy, 0.5);
	}
	glEnd();
	/////////////////////////dia for 1 fream///////////
	glColor4f(0.964, 0.443, 0.725, 0.5);
	drawx = m_width*0.25 / m_chart2.sm_maxdiagram, drawy = 0;
	glBegin(GL_QUADS);
	for (unsigned int i = 0; i < m_chart2.sm_maxdiagram; i++)
	{
		drawy = 1.0 * m_chart2.m_diagram[i] / m_chart2.m_size*0.3*m_height;
		if (drawy >= 0.3*m_height)
		{
			drawy = 0.3*m_height;
		}
		glVertex3f(i*drawx, 0, 0.5);
		glVertex3f((i + 1)*drawx, 0, 0.5);
		glVertex3f((i + 1)*drawx, drawy, 0.5);
		glVertex3f(i*drawx, drawy, 0.5);
	}
	glEnd();
	glBlendFunc(GL_ONE, GL_ZERO);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);
}

void CGraph::DataFun(void)
{
	if (isclear == 1)
	{
		m_stddata1.Restart();
		m_stddata2.Restart();
		m_angdata1.Restart();
		m_angdata2.Restart();
		m_angdata3.Restart();
		m_angdata4.Restart();
		m_chart1.Restart();
		m_chart2.Restart();
		isclear = 0;
		isstart = 0;
	}
	if (isstart == 1 && istracked == 1)
	{
		////////////////std-data////////////////
		if (!m_stddata2.IsFull())
		{
			m_stddata1.AddData(m_angle);
			if (m_stddata1.IsFull())
			{
				m_stddata2.GetData(m_stddata1);
				if (m_stddata2.m_pdata[m_stddata2.m_index - 1] < 2)
				{
					m_stddata2.m_pdata[m_stddata2.m_index - 1] = 2;
				}
				m_stddata1.Clear();
			}
		}
		//////////current-data//////////////////
		m_angdata1.AddData(m_angle);
		if (m_angdata1.IsFull())
		{
			m_angdata2.GetData(m_angdata1);
			m_angdata1.Clear();
			if (m_angdata2.IsFull())
			{
				m_angdata3.GetData(m_angdata2);
				m_angdata2.Clear();
				if (m_angdata3.IsFull())
				{
					m_angdata4.GetData(m_angdata3);
					m_angdata3.Clear();
					if (m_angdata4.IsFull())
					{
						m_angdata4.Clear();
					}
				}
			}
		}
		m_chart1.AddData(m_angle);
		if (m_chart1.IsFull())
		{
			m_chart2.GetData(m_chart1);
			m_chart1.Clear();
			if (m_chart2.IsFull())
			{
				m_chart2.Clear();
			}
		}
		DataAnlyze();
	}
}

void CGraph::GlPrintString(void *font, const char *str)
{
	int i, l = (int)strlen(str);
	for (i = 0; i < l; i++)
	{
		glutBitmapCharacter(font, *str++);
	}
}

double CGraph::GetAngle(const double&x1, const double&y1, const double&z1, const double&x2, const double&y2, const double&z2)
{
	const double&mul = x1 * x2 + y1 * y2 + z1 * z2;
	const double&mod1 = sqrt(x1 * x1 + y1 * y1 + z1 * z1);
	const double&mod2 = sqrt(x2 * x2 + y2 * y2 + z2 * z2);
	m_angle = acos(mul / (mod1*mod2)) / 3.1415 * 180;
	return m_angle;
};

double CGraph::GetAngle(void)
{
	return m_angle;
}

double*CGraph::GetMaxTime(void)
{
	return pThis->maxTime;
}

void CGraph::InitDisplayMode()
{
	m_usertracker.readFrame(&m_userref);
	openni::VideoStream *stream[2] = { 0 };
	stream[0] = &m_depthstream;
	stream[1] = &m_colorstream;
	int streamindex;
	openni::OpenNI::waitForAnyStream(stream, 2, &streamindex);
	if (m_playmode == PLAYMODE_DEPTH) streamindex = 0;
	if (m_playmode == PLAYMODE_COLOR) streamindex = 1;
	switch (streamindex)
	{
	case 0:
		m_depthstream.readFrame(&m_depthref);
		m_depthref = m_userref.getDepthFrame();
		m_mapx = m_depthref.getVideoMode().getResolutionX();
		m_mapy = m_depthref.getVideoMode().getResolutionY();
		break;
	case 1:
		m_colorstream.readFrame(&m_colorref);
		m_mapx = m_colorref.getVideoMode().getResolutionX();
		m_mapy = m_colorref.getVideoMode().getResolutionY();
		break;

	}
}

void CGraph::InitGraph(void)
{
	if (m_width == 0 || m_height == 0)
	{
		isinitgraph = 0;
		return;
	}
	isinitgraph = 1;
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);

	list[0] = glGenLists(1);
	glNewList(list[0], GL_COMPILE);
	float tempx = m_width*0.25;
	float tempy = m_height*0.75;
	//glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor4f(0.7, 0.7, 0.7, 0.4);
	for (float x = 0; x <= tempx + 0.001; x += m_width*rat)
	{
		glVertex3f(x, 0, 0);
		glVertex3f(x, tempy, 0);
	}
	for (float y = 0; y <= tempy + 0.001; y += m_height*rat)
	{
		glVertex3f(0, y, 0);
		glVertex3f(tempx, y, 0);
	}
	glEnd();
	glLineWidth(3);
	glColor4f(0.5, 0.4, 1, 0.4);
	glBegin(GL_LINES);
	glVertex3f(0, m_height*0.375, 0);
	glVertex3f(m_width*0.25, m_height*0.375, 0);
	glEnd();
	glEndList();
}

bool CGraph::IsExist(void)
{
	return m_exist;
};

void CGraph::JointFun(const nite::UserTracker&usertracker, const nite::UserData&data, const int&mapx, const int&mapy)
{
	static const unsigned int total = JOINTDATA_SIZE - 2;
	float cood[3 * total];
	memset(cood, 0, sizeof(float) * 3 * total);
	for (int i = 0; i < total; i++)
	{
		//if ((i == SHOULDER_ASIDE || i == HEAD_ASIDE)) continue;
		x[i] = data.getSkeleton().getJoint(jType[i]).getPosition().x;
		y[i] = data.getSkeleton().getJoint(jType[i]).getPosition().y;
		z[i] = data.getSkeleton().getJoint(jType[i]).getPosition().z;
	}

	if (x[0] == 0 || y[0] == 0 || x[1] == 0 || y[1] == 0 || x[2] == 0 || y[2] == 0)
	{
		istracked = 0;
		m_angle = 0;
		return;
	}
	istracked = 1;
	/*if (abs(x[LEFT_SHOULDER] - x[RIGHT_SHOULDER]) <= 10)
	{
	m_playmode = PLAYMODE_DEPTH_SIDE;
	}
	else
	{
	m_playmode = PLAYMODE_DEPTH;
	}*/
	for (int i = 0; i < total; i++)
	{
		usertracker.convertJointCoordinatesToDepth(x[i], y[i], z[i], cood + 3 * i, cood + 3 * i + 1);
		cood[3 * i + 0] *= m_width*1.0 / mapx;
		cood[3 * i + 1] *= m_height*1.0 / mapy;
		cood[3 * i + 2] *= 0;
	}
	glColor3f(1, 0.5, 0);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCullFace(GL_BACK);
	for (int i = 1; i < total; i++)
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(cood[i * 3], cood[i * 3 + 1], cood[i * 3 + 2]);
		glutSolidSphere(10, 100, 100);
		glPopMatrix();
	}
	glDisable(GL_CULL_FACE);

};

//BOOL CGraph::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO:  在此添加专用代码和/或调用基类
//	SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
//	return CWnd::PreTranslateMessage(pMsg);
//}

void CGraph::ReInitOpenLib(void)
{
	if (m_device.open(openni::ANY_DEVICE) != openni::STATUS_OK)
	{
		m_device.close();
		MessageBox(L"OPEN ERROR--NOT FIND DEVICES");
		m_exist = false;
		//CMy3D_ver_2Dlg::m_startCtrl.EnableWindow(true);
		isinit = 0;
		return;
	}
	m_usertracker.create(&m_device);
	m_colorstream.create(m_device, openni::SENSOR_COLOR);
	m_colorstream.start();
	m_depthstream.create(m_device, openni::SENSOR_DEPTH);
	m_depthstream.start();
	m_exist = true;
	isinit = 1;
	InitGraph();
};

bool CGraph::SetPixel(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pixel =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL |
		PFD_DRAW_TO_WINDOW | PFD_TYPE_RGBA,
		PFD_TYPE_RGBA,
		32,
		8, 16, 8, 8, 8, 0,                    //忽略颜色位
		8,                              //没用非透明度缓存
		24,                              //忽略移位位
		0,                              //无累加缓存
		0, 0, 0, 0,                        //忽略累加位
		32,                             //32位深度缓存
		8,                              //无模版缓存
		4,                              //无辅助缓存
		PFD_MAIN_PLANE,                 //主层
		0,                              //保留
		0, 0, 0                          //忽略层，可见性和损毁掩模
	};
	m_pixelindex = ChoosePixelFormat(hdc, &pixel);
	if (m_pixelindex == 0)
	{
		DescribePixelFormat(hdc, m_pixelindex, sizeof(PIXELFORMATDESCRIPTOR), &pixel);
	}
	if (SetPixelFormat(hdc, m_pixelindex, &pixel)) return 1;
	return 0;
}

void CGraph::SetMaxTime(double*maxtime)
{
	for (unsigned int i = 0; i < WrongGesture::WRONGGESTURE_SIZE; i++)
	{
		maxTime[i] = maxtime[i];
	}
}

CString CGraph::GetOutput()
{
	return output;
}

CGraph::TimeStatus CGraph::TimeCount(WrongGesture type, bool close/* = false*/)
{
	static unsigned int statusTable[WrongGesture::WRONGGESTURE_SIZE];
	static double timeTable[WrongGesture::WRONGGESTURE_SIZE];///ERROR-NUMBER
	static int init = 0;
	if (init == 0)
	{
		for (int i = 0; i < WrongGesture::WRONGGESTURE_SIZE; i++)
		{
			statusTable[i] = UNINIT;
		}
		init = 1;
	}
	double time = GetCurrentTime()*1.0 / 1000;
	double des = 0;
	if (close == true)
	{
		statusTable[type] = UNINIT;
		return TimeStatus::CLOSED;
	}
	switch (statusTable[type])
	{
	case UNINIT:
		timeTable[type] = time;
		statusTable[type] = COUNTING;
		return TimeStatus::INCOUNTING;
		break;

	case COUNTING:
		des = time - timeTable[type];
		if (des >= maxTime[type]) return TimeStatus::OVERTIME;
		else return TimeStatus::NOTOVER;
		break;

	}
	return TimeStatus::OVERTIME;
}
