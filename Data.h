#include <NiTE.h>
#include "Conclusion.h"
#pragma once 
class CData
{
public:
	friend class CConculate;
	int x;
	int y;
	double cosl;
	double dist;
	static unsigned int size;
	static CData*pstart;
	static CData*pnow;
	CData*pnext;
	CData*pback;
	CData*pthis;
	CData();
	~CData();
	CData* Add(const int&x, const int&y, const openni::DepthPixel&depth);
	CData* operator [](unsigned int index);
	static void Deldata(void);
	void Judge(openni::RGB888Pixel*CData, const unsigned int&y);
};