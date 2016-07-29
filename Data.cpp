#include "stdafx.h"
#include "Data.h"
unsigned int CData::size = 0;
CData *CData::pstart = 0;
CData *CData::pnow = 0;

CData::CData()
{
	cosl = 0;
	dist = 0;
	x = 0;
	y = 0;
	pnext = 0;
	pback = 0;
	pthis = this;
	if (size == 0) pstart = this;
	pnow = this;
	size++;
};

CData::~CData()
{

};

void CData::Deldata()
{
	CData*p1, *p2;
	p1 = pstart->pnext;
	for (unsigned int i = 1; i < size; i++)
	{
		p2 = p1->pnext;
		delete p1;
		p1 = p2;
	}
	size = 0;
};

CData*CData::Add(const int&x, const int&y, const openni::DepthPixel&depth)
{
	CData*p = pnow;
	pnow->x = x;
	pnow->y = y;
	pnow->dist = sqrt(x*x*1.0 + y*y*1.0);
	pnow->cosl = (x)*1.0 / (pnow->dist);
	p->pnext = new CData;
	pnow->pback = p;
	p = pnow;
	return p;
};

CData* CData::operator[](unsigned int index)
{
	if (index >= size || index < 0) return 0;
	CData*p = pstart;
	for (unsigned int i = 1; i < size; i++)
	{
		p = p->pnext;
	}
	return p;
};

void CData::Judge(openni::RGB888Pixel*CData, const unsigned int&y)
{

}