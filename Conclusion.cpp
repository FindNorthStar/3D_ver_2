#include "stdafx.h"
#include "Conclusion.h"
#include "Data.h"
int*CConculate::xchater = 0;
int*CConculate::ychater = 0;
int CConculate::mapx = 0;
int CConculate::mapy = 0;

CConculate::CConculate(const int&mapx, const int&mapy)
{
	xchater = new int[mapx];
	ychater = new int[mapy];
	memset(xchater, 0, sizeof(int)*mapx);
	memset(ychater, 0, sizeof(int)*mapy);
	this->mapx = mapx;
	this->mapy = mapy;
}


CConculate::~CConculate()
{
	delete[]xchater;
	delete[]ychater;
}

void CConculate::Add(int&x, int&y)
{
	xchater[x]++;
	ychater[y]++;
}

void CConculate::GetData(const nite::JointType&joint, int*x, int*y, CData&data)
{
	int a[240];
	memcpy(a, ychater, 4 * 240);
	switch (joint)
	{
	case nite::JOINT_HEAD:
		break;
	case nite::JOINT_NECK:
		for (int i = 1; i < mapy - 1; i++)
		{
			if (ychater[i]>80)
			{
				if (ychater[i] - ychater[i - 1] > 3 &&
					ychater[i + 1] - ychater[i] > 3 &&
					ychater[i + 2] - ychater[i + 1] > 3)
				{
					*y = i;
					CData*pdata = data.pstart;
					for (int t = 0; t < data.size; t++)
					{
						if (pdata->y == i)
						{
							const int des = abs(pdata->pnext->x - pdata->x);
							*x = (pdata->x + pdata->pnext->x) / 2;
							break;
						}
						pdata = pdata->pnext;
					}
				}
			}
		}
		break;
	}
}