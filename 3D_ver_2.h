
// 3D_ver_2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy3D_ver_2App: 
// �йش����ʵ�֣������ 3D_ver_2.cpp
//

class CMy3D_ver_2App : public CWinApp
{
public:
	CMy3D_ver_2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy3D_ver_2App theApp;