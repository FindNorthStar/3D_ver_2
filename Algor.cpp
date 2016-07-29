#include "stdafx.h"
#include "Algor.h"
#include <algorithm>
#include <OpenNI.h>

#define WATCHER(tar,w,h) \
unsigned char watch[h][w];\
for (int i = 0; i < h; i++)\
{\
	for (int j = 0; j < w; j++)\
				{\
		watch[i][j] = tar[width*i + j];\
				}\
}

#define ADD_ELEMENT(tar) \
	pointTemp.push_back(tar);\
	exist[width*h + tar] = PIX_BODY;

#define ADD_ELE(index) \
	middle.push_back(index);\
	prior.push_back(index);\
	jointPoint.push_back(PointData(index,h,oridata[width*h+index][2]));

bool Algor::ForceIn(Location local, int w, int h)
{
	if (exist[width*h + w] == false) return true;

	switch (local)
	{
	case LOC_DOWN:
		if (h + 1 >= height || w >= width) return true;
		return !exist[width*(h + 1) + w];
	case LOC_LEFT_DOWN:
		if (h + 1 >= height || w - 1 < 0) return true;
		return !exist[width*(h + 1) + w - 1];
	case LOC_LEFT:
		if (w - 1 < 0) return true;
		return !exist[width*h + w - 1];
	case LOC_LEFT_UP:
		if (h - 1 < 0 || w - 1 < 0) return true;
		return !exist[width*(h - 1) + w - 1];
	case LOC_UP:
		if (h - 1 < 0) return true;
		return !exist[width*(h - 1) + w];
	case LOC_RIGHT_UP:
		if (h - 1 < 0 || w + 1 >= width) return true;
		return !exist[width*(h - 1) + w + 1];
	case LOC_RIGHT:
		if (w + 1 >= width) return true;
		return !exist[width*h + w + 1];
	case LOC_RIGHT_DOWN:
		if (w + 1 >= width || h + 1 >= height) return true;
		return !exist[width*(h + 1) + w + 1];
	default:
		return true;
	}

	//switch (local)
	//{
	//case LOC_DOWN:
	//	if (h - 1 < 0) return true;
	//	return !exist[width*(h - 1) + w];
	//case LOC_LEFT_DOWN:
	//	if (h - 1 < 0 || w - 1 < 0) return true;
	//	return !exist[width*(h - 1) + w - 1];
	//case LOC_LEFT:
	//	if (w - 1 < 0) return true;
	//	return !exist[width*h + w - 1];
	//case LOC_LEFT_UP:
	//	if (h + 1 >= height || w - 1 < 0) return true;
	//	return !exist[width*(h + 1) + w - 1];
	//case LOC_UP:
	//	if (h + 1 >= height) return true;
	//	return !exist[width*(h + 1) + w];
	//case LOC_RIGHT_UP:
	//	if (h + 1 >= height || w + 1 >= width) return true;
	//	return !exist[width*(h + 1) + w + 1];
	//case LOC_RIGHT:
	//	if (w + 1 >= width) return true;
	//	return !exist[width*h + w + 1];
	//case LOC_RIGHT_DOWN:
	//	if (h - 1 < 0 || w + 1 >= width) return true;
	//	return !exist[width*(h - 1) + w + 1];
	//default:
	//	true;
	//}

}

bool Algor::InspectNeighbor(int w, int h, bool isLong, bool converToJoint)
{
	bool changed = false;
	if (exist[width*h + w] == false) return false;
	if (isLong)
	{
		for (int x = w; x >= 0; x--)
		{
			if (exist[width*h + x] == PIX_NONE) break;
			if (ForceIn(LOC_UP, x, h))
			{
				if (converToJoint)exist[width*h + x] = PIX_JOINT;
				changed = true;
				break;
			}
		}
		for (int x = w; x < width; x++)
		{
			if (exist[width*h + x] == PIX_NONE) break;
			if (ForceIn(LOC_UP, x, h))
			{
				if (converToJoint)exist[width*h + x] = PIX_JOINT;
				changed = true;
				break;
			}
		}
		for (int y = h; y >= 0; y--)
		{
			if (exist[width*y + w] == PIX_NONE) break;
			if (ForceIn(LOC_UP, w, y))
			{
				if (converToJoint)exist[width*y + w] = PIX_JOINT;
				changed = true;
				break;
			}
		}
		for (int y = h; y < height; y++)
		{
			if (exist[width*y + w] == PIX_NONE) break;
			if (ForceIn(LOC_UP, w, y))
			{
				if (converToJoint)exist[width*y + w] = PIX_JOINT;
				changed = true;
				break;
			}
		}
	}
	else
	{
		if (h - 1 >= 0)
		{
			if (ForceIn(LOC_UP, w, h - 1) && exist[width*(h - 1) + w])
			{
				if (converToJoint)exist[width*(h - 1) + w] = PIX_JOINT;
				changed = true;
			}
		}
		if (h + 1 < height)
		{
			if (ForceIn(LOC_UP, w, h + 1) && exist[width*(h + 1) + w])
			{
				if (converToJoint)exist[width*(h + 1) + w] = PIX_JOINT;
				changed = true;
			}
		}
		if (w - 1 >= 0)
		{
			if (ForceIn(LOC_UP, w - 1, h) && exist[width*h + w - 1])
			{
				if (converToJoint)exist[width*h + w - 1] = PIX_JOINT;
				changed = true;
			}
		}
		if (w + 1 < width)
		{
			if (ForceIn(LOC_UP, w + 1, h) && exist[width*h + w + 1])
			{
				if (converToJoint)exist[width*h + w + 1] = PIX_JOINT;
				changed = true;
			}
		}
	}
	if (changed) exist[width*h + w] = PIX_NONE;
	return changed;
}

bool Algor::Cmp(void*data)
{
	unsigned char d = *((unsigned char*)data);
	if (d > 125) return true;
	else return false;
}

int Algor::NeighborNum(int w, int h)
{
	unsigned int count = 0;
	for (int x = w - 1; x >= 0 && x < width&&x < w + 2; x++)
	{
		for (int y = h - 1; y >= 0 && y < height&&y < h + 2; y++)
		{
			if (exist[width*y + x]) count++;
		}
	}
	return count - 1;
}

int Algor::Eight_ConnectionKnot(int w, int h)
{
	PixelType x[10] = {
		exist[width*h + w] ? PIX_BODY : PIX_NONE, ForceIn(LOC_RIGHT, w, h) ? PIX_BODY : PIX_NONE, ForceIn(LOC_RIGHT_UP, w, h) ? PIX_BODY : PIX_NONE, ForceIn(LOC_UP, w, h) ? PIX_BODY : PIX_NONE, ForceIn(LOC_LEFT_UP, w, h) ? PIX_BODY : PIX_NONE
		, ForceIn(LOC_LEFT, w, h) ? PIX_BODY : PIX_NONE, ForceIn(LOC_LEFT_DOWN, w, h) ? PIX_BODY : PIX_NONE, ForceIn(LOC_DOWN, w, h) ? PIX_BODY : PIX_NONE, ForceIn(LOC_RIGHT_DOWN, w, h) ? PIX_BODY : PIX_NONE, ForceIn(LOC_RIGHT, w, h) ? PIX_BODY : PIX_NONE
	};
	int res = 0;
	for (int i = 1; i <= 4; i++)
	{
		res += x[2 * i - 1] - x[2 * i - 1] * x[2 * i] * x[2 * i + 1];
	}
	return res;
}

int Algor::Four_ConnectionKnot(int w, int h)
{
	PixelType x[10] = {
		exist[width*h + w] ? PIX_NONE : PIX_BODY, ForceIn(LOC_RIGHT, w, h) ? PIX_NONE : PIX_BODY, ForceIn(LOC_RIGHT_UP, w, h) ? PIX_NONE : PIX_BODY, ForceIn(LOC_UP, w, h) ? PIX_NONE : PIX_BODY, ForceIn(LOC_LEFT_UP, w, h) ? PIX_NONE : PIX_BODY
		, ForceIn(LOC_LEFT, w, h) ? PIX_NONE : PIX_BODY, ForceIn(LOC_LEFT_DOWN, w, h) ? PIX_NONE : PIX_BODY, ForceIn(LOC_DOWN, w, h) ? PIX_NONE : PIX_BODY, ForceIn(LOC_RIGHT_DOWN, w, h) ? PIX_NONE : PIX_BODY, ForceIn(LOC_RIGHT, w, h) ? PIX_NONE : PIX_BODY
	};
	int res = 0;
	for (int i = 1; i <= 4; i++)
	{
		res += x[2 * i - 1] - x[2 * i - 1] * x[2 * i] * x[2 * i + 1];
	}
	return res;
}

int Algor::Argor_EPM()
{
	int reserve = 0;
	for (unsigned int h = 0; h < height; h++)
	{
		for (unsigned int w = 0; w < width; w++)
		{
			switch (exist[width*h + w])
			{
			case PIX_NONE:
				break;
			case PIX_BODY:
				if (ForceIn(LOC_UP, w, h))
				{
					reserve++;
					exist[width*h + w] = PIX_JOINT;
					break;
				}
				else if ((ForceIn(LOC_LEFT_DOWN, w, h) == true && ForceIn(LOC_LEFT, w, h) == false)
					|| (ForceIn(LOC_LEFT, w, h) == true && ForceIn(LOC_LEFT_UP, w, h) == false)
					|| (ForceIn(LOC_RIGHT_UP, w, h) == false && ForceIn(LOC_RIGHT, w, h) == true)
					|| (ForceIn(LOC_RIGHT, w, h) == false && ForceIn(LOC_RIGHT_DOWN, w, h) == true))
				{
					reserve++;
					exist[width*h + w] = PIX_JOINT;
					break;
				}
				else if (InspectNeighbor(w, h))
					reserve++;
				else exist[width*h + w] = PIX_NONE;
				break;
			case PIX_JOINT:
				break;
			default:
				break;
			}
		}
	}
	return reserve;
}

int Algor::Argor_Hilditch()
{
	int reserve = 0;
	for (unsigned int h = 0; h < height; h++)
	{
		for (unsigned int w = 0; w < width; w++)
		{
			if (exist[width*h + w])
			{
				if (!(!ForceIn(LOC_RIGHT, w, h) && !ForceIn(LOC_UP, w, h) && !ForceIn(LOC_LEFT, w, h) && !ForceIn(LOC_DOWN, w, h)))
				{
					if (NeighborNum(w, h) >= 2)
					{
						if (Eight_ConnectionKnot(w, h) == 1)
						{
							if (h - 1 >= 0)
							{
								PixelType store_3 = exist[width*(h - 1) + w];
								exist[width*(h - 1) + w] = PIX_NONE;
								if (Eight_ConnectionKnot(w, h) == 1)
								{
									exist[width*(h - 1) + w] = store_3;
									if (w - 1 >= 0)
									{
										PixelType store_5 = exist[width*h + w - 1];
										exist[width*h + w - 1] = PIX_NONE;
										if (Eight_ConnectionKnot(w, h) == 1)
										{
											exist[width*h + w - 1] = store_5;
											exist[width*h + w] = PIX_NONE;
											reserve++;
										}
										exist[width*h + w - 1] = store_5;
									}
									else
									{
										if (Eight_ConnectionKnot(w, h) == 1)
										{
											exist[width*h + w] = PIX_NONE;
											reserve++;
										}
									}
								}
								exist[width*(h - 1) + w] = store_3;
							}
							else
							{
								if (Eight_ConnectionKnot(w, h) == 1)
								{
									if (w - 1 >= 0)
									{
										PixelType store_5 = exist[width*h + w - 1];
										exist[width*h + w - 1] = PIX_NONE;
										if (Eight_ConnectionKnot(w, h) == 1)
										{
											exist[width*h + w - 1] = store_5;
											exist[width*h + w] = PIX_NONE;
											reserve++;
										}
										exist[width*h + w - 1] = store_5;
									}
									else
									{
										if (Eight_ConnectionKnot(w, h) == 1)
										{
											exist[width*h + w] = PIX_NONE;
											reserve++;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return reserve;
}

int Algor::Argor_Pavlidis()
{
	unsigned long ly = height, lx = width;
	unsigned long i, j;
	for (i = 0; i < ly; i++)
	{
		for (j = 0; j < lx; j++)
		{
			if (exist[i*width + j]>PIX_BODY)
				exist[i*width + j] = PIX_BODY;
		}
	}
	char erase, n[8];
	char *f;
	unsigned char bdr1, bdr2, bdr4, bdr5;
	short c, k, b;
	long kk, kk1, kk2, kk3;
	f = (char*)exist;

	for (i = 1; i < lx - 1; i++)
	{
		for (j = 1; j < ly - 1; j++)
		{
			kk = i*ly + j;
			if (f[kk])
				f[kk] = 1;
		}
	}

	for (i = 0, kk1 = 0, kk2 = ly - 1; i < lx; i++, kk1 += ly, kk2 += ly)
	{
		f[kk1] = 0;
		f[kk2] = 0;
	}

	for (j = 0, kk = (lx - 1)*ly; j < ly; j++, kk++)
	{
		f[j] = 0;
		f[kk] = 0;
	}

	c = 5;
	erase = 1;
	while (erase)
	{
		c++;
		for (i = 1; i < lx - 1; i++)
		{
			for (j = 1; j < ly - 1; j++)
			{
				kk = i*ly + j;
				if (f[kk] != 1)
					continue;

				kk1 = kk - ly - 1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[3] = f[kk1];
				n[2] = f[kk2];
				n[1] = f[kk3];
				kk1 = kk - 1;
				kk3 = kk + 1;
				n[4] = f[kk1];
				n[0] = f[kk3];
				kk1 = kk + ly - 1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[5] = f[kk1];
				n[6] = f[kk2];
				n[7] = f[kk3];

				bdr1 = 0;
				for (k = 0; k < 8; k++)
				{
					if (n[k] >= 1)
						bdr1 |= 0x80 >> k;
				}

				if ((bdr1 & 0252) == 0252)
					continue;
				f[kk] = 2;
				b = 0;

				for (k = 0; k <= 7; k++)
				{
					b += bdr1&(0x80 >> k);
				}

				if (b <= 1)
					f[kk] = 3;

				if ((bdr1 & 0160) != 0 && (bdr1 & 07) != 0 && (bdr1 & 0210) == 0)
					f[kk] = 3;
				else if ((bdr1 && 0301) != 0 && (bdr1 & 034) != 0 && (bdr1 & 042) == 0)
					f[kk] = 3;
				else if ((bdr1 & 0202) == 0 && (bdr1 & 01) != 0)
					f[kk] = 3;
				else if ((bdr1 & 0240) == 0 && (bdr1 & 0100) != 0)
					f[kk] = 3;
				else if ((bdr1 & 050) == 0 && (bdr1 & 020) != 0)
					f[kk] = 3;
				else if ((bdr1 & 012) == 0 && (bdr1 & 04) != 0)
					f[kk] = 3;
			}
		}

		for (i = 1; i < lx - 1; i++)
		{
			for (j = 1; j < ly - 1; j++)
			{
				kk = i*ly + j;
				if (!f[kk])
					continue;

				kk1 = kk - ly - 1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[3] = f[kk1];
				n[2] = f[kk2];
				n[1] = f[kk3];
				kk1 = kk - 1;
				kk2 = kk + 1;
				n[4] = f[kk1];
				n[0] = f[kk3];
				kk1 = kk + ly - 1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[5] = f[kk1];
				n[6] = f[kk2];
				n[7] = f[kk3];
				bdr1 = bdr2 = 0;

				for (k = 0; k <= 7; k++)
				{
					if (n[k] >= 1)
						bdr1 |= 0x80 >> k;
					if (n[k] >= 2)
						bdr2 |= 0x80 >> k;
				}

				if (bdr1 == bdr2)
				{
					f[kk] = 4;
					continue;
				}

				if (f[kk] != 2)
					continue;

				if ((bdr2 & 0200) != 0 && (bdr1 & 010) == 0 &&
					((bdr1 & 0100) != 0 && (bdr1 & 001) != 0 ||
					((bdr1 & 0100) != 0 || (bdr1 & 001) != 0) &&
					(bdr1 & 060) != 0 && (bdr1 & 06) != 0))
				{
					f[kk] = 4;
				}

				else if ((bdr2 & 040) != 0 && (bdr1 & 02) == 0 &&
					((bdr1 & 020) != 0 && (bdr1 & 0100) != 0 ||
					((bdr1 & 020) != 0 || (bdr1 & 0100) != 0) &&
					(bdr1 & 014) != 0 && (bdr1 & 0201) != 0))
				{
					f[kk] = 4;
				}

				else if ((bdr2 & 010) != 0 && (bdr1 & 0200) == 0 &&
					((bdr1 & 04) != 0 && (bdr1 & 020) != 0 ||
					((bdr1 & 04) != 0 || (bdr1 & 020) != 0) &&
					(bdr1 & 03) != 0 && (bdr1 & 0140) != 0))
				{
					f[kk] = 4;
				}

				else if ((bdr2 & 02) != 0 && (bdr1 & 040) == 0 &&
					((bdr1 & 01) != 0 && (bdr1 & 04) != 0 ||
					((bdr1 & 01) != 0 || (bdr1 & 04) != 0) &&
					(bdr1 & 0300) != 0 && (bdr1 & 030) != 0))
				{
					f[kk] = 4;
				}
			}
		}

		for (i = 1; i < lx - 1; i++)
		{
			for (j = 1; j < ly - 1; j++)
			{
				kk = i*ly + j;
				if (f[kk] != 2)
					continue;
				kk1 = kk - ly - 1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[3] = f[kk1];
				n[2] = f[kk2];
				n[1] = f[kk3];
				kk1 = kk - 1;
				kk2 = kk + 1;
				n[4] = f[kk1];
				n[0] = f[kk3];
				kk1 = kk + ly - 1;
				kk2 = kk1 + 1;
				kk3 = kk2 + 1;
				n[5] = f[kk1];
				n[6] = f[kk2];
				n[7] = f[kk3];
				bdr4 = bdr5 = 0;
				for (k = 0; k <= 7; k++)
				{
					if (n[k] >= 4)
						bdr4 |= 0x80 >> k;
					if (n[k] >= 5)
						bdr5 |= 0x80 >> k;
				}
				if ((bdr4 & 010) == 0)
				{
					f[kk] = 5;
					continue;
				}
				if ((bdr4 & 040) == 0 && bdr5 == 0)
				{
					f[kk] = 5;
					continue;
				}
				if (f[kk] == 3 || f[kk] == 4)
					f[kk] = c;
			}
		}

		erase = 0;
		for (i = 1; i < lx - 1; i++)
		{
			for (j = 1; j < ly - 1; j++)
			{
				kk = i*ly + j;
				if (f[kk] == 2 || f[kk] == 5)
				{
					erase = 1;
					f[kk] = 0;
				}
			}
		}
	}
	return 0;
}

int Algor::Argor_Zhaoyue()
{
	enum FlagStatus { FLA_IN, FLA_OUT };
	vector<PointData> jointPoint;
	vector<int> boundary;
	vector<int> middle;
	vector<int> prior;
	for (int h = 0; h < height; h++)
	{
		FlagStatus flag = FLA_OUT;
		boundary.clear();
		for (int w = 0; w < width; w++)
		{
			if (w == width - 1 && exist[h*width + w]) exist[h*width + w] = PIX_NONE;
			if (exist[width*h + w] && flag == FLA_OUT)
			{
				boundary.push_back(w); 
				flag = FLA_IN;
			}
			if (!exist[width*h + w] && flag == FLA_IN)
			{
				boundary.push_back(w);
				flag = FLA_OUT;
			}
		}
		auto dealFunc=
			[&](int leftBoun,int rightBoun)
		{
			const int index = (leftBoun+rightBoun) / 2;
			if (prior.size() == 0)
			{
				ADD_ELE(index);
			}
			else if (prior.size() == 1)
			{
				int pt = prior[0];
				prior.clear();
				if (index < pt)
				{
					ADD_ELE(pt);
					if (pt - 1 >= 0)
					{
						ADD_ELE(pt - 1);
					}
				}
				else if (index == pt)
				{
					ADD_ELE(pt);
				}
				else if (index > pt)
				{
					ADD_ELE(pt);
					if (pt + 1 <width)
					{
						ADD_ELE(pt+1);
					}
				}
			}
			else if (prior.size() == 2)
			{
				int pt, pn;
				prior[0] > prior[1] ? pt = prior[1], pn = prior[0] : pt = prior[0], pn = prior[1];
				prior.clear();
				if (index < pt)
				{
					ADD_ELE(pt);
					if (pt - 1 >= 0)
					{
						ADD_ELE(pt-1);
					}
				}
				else if (index == pt)
				{
					ADD_ELE(pt);
				}
				else if (index == pn)
				{
					ADD_ELE(pn);
				}
				else if (index > pn)
				{
					ADD_ELE(pn);
					if (pn + 1 < width)
					{
						ADD_ELE(pn+1);
					}
				}
			}
		};
		int _size=boundary.size();
		if (boundary.size() == 2)
		{
			dealFunc(boundary[0],boundary[1]);
		}
		else if (boundary.size() > 2 )
		{
			if (boundary.size() % 2 == 1) boundary.pop_back();
			vector<int> all,dis;
			for (int i = 0; i < boundary.size(); i += 2)
			{
				all.push_back((boundary[i] + boundary[i + 1]) / 2);
			}
			if (prior.size() == 0)
			{
				if (middle.size() == 0) continue;
				for (int i = 0; i < all.size(); i++)
				{
					dis.push_back(abs(all[i] - middle[middle.size()-1]));
				}
				int min_index = 0, min_val = 0;
				for (int i = 0; i < dis.size(); i++)
				{
					if (min_val < dis[i])
					{
						min_val = dis[i];
						min_index = i;
					}
				}
				dealFunc(boundary[2 * min_index], boundary[2 * min_index + 1]);
			}
			else
			{
				for (int i = 0; i < all.size(); i++)
				{
					dis.push_back(abs(all[i] - prior[0]));
				}
				int min_index = 0, min_val = 0;
				for (int i = 0; i < dis.size(); i++)
				{
					if (min_val < dis[i])
					{
						min_val = dis[i];
						min_index = i;
					}
				}
				dealFunc(boundary[2 * min_index], boundary[2 * min_index + 1]);
			}
		}
	}
	memset(exist, 0, sizeof(PixelType)*width*height);
	for (int i = 0; i < jointPoint.size(); i++)
	{
		exist[width*jointPoint[i].y + jointPoint[i].x] = PIX_BODY;
	}
	//for (int i = 20; jointPoint.size() >= 23 && i != jointPoint.size() - 2; i++)
	//{
	//	if (abs(jointPoint[i + 1].z - jointPoint[i].z) >= 50 && abs(jointPoint[i + 2].z - jointPoint[i+1].z) >= 50)
	//	{
	//		exist[width*jointPoint[i + 1].y + jointPoint[i].x] = PIX_JOINT;
	//		joint.push_back(PointData(jointPoint[i + 1]));
	//		jointSize++;
	//	}
	//}
	int ave = 0;
	const int start = 21;
	const int dlt = -60;
	int neckIndex = 0,headIndex=0;
	for (int i = start; i < jointPoint.size(); i++)
	{
		if (i == start) ave = jointPoint[i].z;
		else
		{
			if (jointPoint[i].z - ave > dlt)
			{
				ave = (ave*(i - start) + jointPoint[i].z) / (i - start + 1);
			}
			else
			{
				neckIndex = i;
				headIndex = neckIndex / 2;
				exist[width*jointPoint[i].y + jointPoint[i].x] = PIX_JOINT;
				joint.push_back(PointData(jointPoint[i]));
				exist[width*jointPoint[headIndex].y + jointPoint[headIndex].x] = PIX_JOINT;
				joint.push_back(PointData(jointPoint[headIndex]));
				dataValid = true;
				break;
			}
		}
	}

	int max_z = 0;
	for (int i = 0; i < jointPoint.size(); i++)
	{
		if (max_z < jointPoint[i].z) max_z = jointPoint[i].z;
	}
	sprintf(outputBuffer, "%d", max_z);
	output = CString(outputBuffer);
	return 0;
}

Algor::Algor()
	:width(0), height(0), hbmp(0), bmp({ 0 }), gray(0), exist(0), oridata(0), output(""), memValid(false), dataValid(false)
{}

Algor::~Algor()
{
	if (memValid)
	{
		delete []exist;
		delete []gray;
	}
	if (oridata)
	delete []oridata;
}

bool Algor::CreateFromBMP(const char*filename)
{
	hbmp = (HBITMAP)LoadImageA(GetModuleHandleA(0), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hbmp, sizeof(BITMAP), &bmp);
	unsigned char*rawdata = (unsigned char*)bmp.bmBits;
	width = bmp.bmWidth;
	height = bmp.bmHeight;
	unsigned char*data = new unsigned char[height*width * 3];
	gray = new unsigned char[height*width];
	exist = new PixelType[width*height];
	if (data == NULL || rawdata == NULL || gray == NULL || exist == NULL) return false;
	for (unsigned int h = 0; h < height; h++)
	{
		for (unsigned int w = 0; w < width; w++)
		{
			const unsigned char r = data[width * 3 * h + 3 * w + 0] = rawdata[bmp.bmWidthBytes*h + 3 * w + 0];
			const unsigned char g = data[width * 3 * h + 3 * w + 1] = rawdata[bmp.bmWidthBytes*h + 3 * w + 1];
			const unsigned char b = data[width * 3 * h + 3 * w + 2] = rawdata[bmp.bmWidthBytes*h + 3 * w + 2];
			gray[width*h + w] = (r + g + b) / 3;
			exist[width*h + w] = Cmp(gray + width*h + w) ? PIX_BODY : PIX_NONE;
		}
	}
	delete []data;
	Reverce_UD(&exist, width, height);
	return true;
}

bool Algor::CreateFromData(unsigned int(*_d)[3], int _width, int _height)
{
	memValid = false;
	width = _width;
	height = _height;
	exist = new PixelType[width*height];
	gray = new unsigned char[height*width];
	oridata = new unsigned int[height*width][3];
	memcpy(oridata, _d, sizeof(unsigned int)*width*height * 3);
	if (gray == NULL || exist == NULL) return false;
	for (unsigned int h = 0; h < height; h++)
	{
		for (unsigned int w = 0; w < width; w++)
		{
			const unsigned char r = _d[width * h + w][0];
			const unsigned char g = _d[width * h + w][1];
			const unsigned char b = _d[width * h + w][2];
			gray[width*h + w] = r;
			exist[width*h + w] = Cmp(gray + width*h + w) ? PIX_BODY : PIX_NONE;
		}
	}
	memValid = true;
	return true;
}
bool Algor::AnalyzeData()
{
	if (!memValid) return false;
	int reserve = 0;
	do
	{
		reserve = Argor_Zhaoyue();
	} while (reserve > 0);
	return true;
}
void Algor::Refine()
{
	bool flag = false;
	PixelType watch[17][11];
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			watch[i][j] = exist[i*width + j];
		}
	}
	do
	{
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				flag = false;
				if (exist[width*h + w])
				{
					if (h - 1 >= 0 && w - 1 >= 0)
					{
						if (exist[width*(h - 1) + w] && exist[width*h + w - 1])
							flag = true;
					}
					if (h - 1 >= 0 && w + 1 < width)
					{
						if (exist[width*(h - 1) + w] && exist[width*h + w + 1])
							flag = true;
					}
					if (h + 1 < height&&w - 1 >= 0)
					{
						if (exist[width*(h + 1) + w] && exist[width*h + w - 1])
							flag = true;
					}
					if (h + 1 < height&&w + 1 < width)
					{
						if (exist[width*(h + 1) + w] && exist[width*h + w + 1])
							flag = true;
					}
					if (flag) exist[width*h + w] = PIX_NONE;
				}
			}
		}
	} while (flag);
}
template<class T>
static void Algor::Reverce_LR(T**data, int width, int height)
{
	T*d = *data;
	T*mem = new T[width*height];
	memset(mem, 0, sizeof(T)*width*height);
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			mem[width*h + w] = d[width*h + width - w - 1];
		}
	}
	delete []d;
	*data = mem;
}
template <class T>
static void Algor::Reverce_UD(T**data, int width, int height)
{
	T*d = *data;
	T*mem = new T[width*height];
	memset(mem, 0, sizeof(T)*width*height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			mem[width*y + x] = d[width*(height - 1 - y) + x];
		}
	}
	delete []d;
	*data = mem;
}