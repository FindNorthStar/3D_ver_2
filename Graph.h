#include "stdafx.h"
#include "AngData.h"
#include <fstream>
#include <OpenNI.h>
#include <NiTE.h>
#include <Windows.h>
#include "glut.h"
#include "Algor.h"
#include "Config.h"


#pragma once

// CGraph


class CGraph : public CWnd
{
	DECLARE_DYNAMIC(CGraph)

public:
	static CGraph*pThis;
	CGraph();
	virtual ~CGraph();
	enum PlayMode { PLAYMODE_DEPTH = 1, PLAYMODE_COLOR, PLAYMODE_DEPTH_AND_COLOR };
	enum AnlyzeMode { ANLYZEMODE_FRONT, ANLYZEMODE_SIZE };
	enum JointData{ TEMP, LEFT_SHOULDER, RIGHT_SHOULDER, NECK, LEFT_HIP, RIGHT_HIP, LEFT_ELBOW, RIGHT_ELBOW, TORSO, HEAD, SHOULDER_ASIDE,HEAD_ASIDE, JOINTDATA_SIZE };
	enum TimeStatus { INCOUNTING, OVERTIME, CLOSED, NOTOVER };
	enum WrongGesture { HEAD_FOREWARD, HEAD_RIGHT, HEAD_LEFT, ASIDE_BODY_FOREWARD,ASIDE_HEAD_FOREWARD, WRONGGESTURE_SIZE };
	nite::JointType jType[JOINTDATA_SIZE];
protected:
	DECLARE_MESSAGE_MAP()
	double GetAngle(const double&x1, const double&y1, const double&z1, const double&x2, const double&y2, const double&z2);
public:
	bool SetPixel(HDC hdc);
	bool IsExist(void);

	char outputBuffer[256];
	CString output;
	void Calculate(float* pHistogram, int histogramSize, const openni::VideoFrameRef& depthFrame);
	void DataFun(void);
	void DataAnlyze(void);
	void DrawTexture(void);
	void DrawJointSphere(void);
	void DrawModel(void);
	void DrawChart(void);
	void DrawWarning(void);
	void GlPrintString(void *font, const char *str);
	void InitGraph(void);
	void InitDisplayMode(void);
	void JointFun(const nite::UserTracker&usertracker, const nite::UserData& userdata, const int&mapx, const int&mapy);
	void ReInitOpenLib(void);
	void SetMaxTime(double*maxtime);

	double GetAngle(void);

	CString GetOutput(void);
	static double*GetMaxTime(void);

	TimeStatus TimeCount(WrongGesture type, bool close = false);

private:
	bool m_exist;
	AnlyzeMode m_anlyzemode;
	PlayMode m_playmode;
	CAngData m_stddata1, m_stddata2;
	CAngData m_angdata1, m_angdata2, m_angdata3, m_angdata4;
	CAngData m_chart1, m_chart2;
	Config config;
	std::ofstream logfile;
	//0 - temp,1 - left_shoulder
	//2 - right_shoulder,3 - neck
	//4 - LEFT_HIP,5 - RIGHT_HIP
	//6 - LEFT_ELBOW,7 - Right_ELBOW
	//8 - TORSO,9 - head
	float x[JOINTDATA_SIZE - 1];
	float y[JOINTDATA_SIZE - 1];
	float z[JOINTDATA_SIZE - 1];
	int m_pixelindex;
	int m_mapx, m_mapy;
	double maxTime[WrongGesture::WRONGGESTURE_SIZE];
	static double smaxTime[WrongGesture::WRONGGESTURE_SIZE];
	double m_angle;
	nite::UserId m_firstuser;
	HGLRC m_hglrc;
	//static CGraph*pthis;
	openni::Device m_device;
	openni::VideoStream m_depthstream;
	openni::VideoFrameRef m_depthref;
	openni::VideoStream m_colorstream;
	openni::VideoFrameRef m_colorref;
	nite::UserTracker m_usertracker;
	nite::UserTrackerFrameRef m_userref;
	int m_width, m_height;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	/*virtual BOOL PreTranslateMessage(MSG* pMsg);*/
	static void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};
