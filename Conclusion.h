#include <OpenNI.h>
#include <NiTE.h>

#pragma once
class CConculate
{
public:
	friend class CData;
	CConculate(const int&mapx, const int&y);
	~CConculate();
	void Add(int&x, int&y);
	static int mapx, mapy;
	static int*xchater;
	static int*ychater;
	static void GetData(const nite::JointType&joint, int*px, int*py, CData&CData);
};

