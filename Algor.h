#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;

enum Location { LOC_DOWN, LOC_LEFT_DOWN, LOC_LEFT, LOC_LEFT_UP, LOC_UP, LOC_RIGHT_UP, LOC_RIGHT, LOC_RIGHT_DOWN };
enum PixelType { PIX_NONE, PIX_BODY, PIX_JOINT };

using namespace std;
class PointData
{
public:
	int x, y, z;
	PointData()
		:x(0), y(0), z(0)
	{}
	PointData(int x, int y, int z)
		:x(x), y(y), z(z)
	{}
	PointData(const PointData&p)
		:x(p.x), y(p.y), z(p.z)
	{}
};

class Algor
{
public:
	unsigned int width;
	unsigned int height;
	HBITMAP hbmp;
	BITMAP bmp;
	bool memValid;
	bool dataValid;
	unsigned char*gray;
	unsigned int(*oridata)[3];
	PixelType*exist;
	vector<PointData> joint;
	CString output;
	char outputBuffer[256];

private:
	bool ForceIn(Location local, int w, int h);

	bool InspectNeighbor(int w, int h, bool isLong = true, bool converToJoint = false);
	bool Cmp(void*data);
	int NeighborNum(int w, int h);
	int Eight_ConnectionKnot(int w, int h);
	int Four_ConnectionKnot(int w, int h);
	int Argor_EPM();
	int Argor_Hilditch();
	int Argor_Pavlidis();
	int Argor_Zhaoyue();

public:
	Algor();
	~Algor();
	bool CreateFromBMP(const char*filename);
	bool CreateFromData(unsigned int(*data)[3], int width, int height);
	bool AnalyzeData();
	void Refine();
	template<class T>
	static void Reverce_LR(T**data, int width, int height);
	template <class T>
	static void Reverce_UD(T**data, int width, int height);


};
