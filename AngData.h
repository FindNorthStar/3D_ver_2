#pragma once
#define MAX_DIAGRAM_ANGLE 50 
class CAngData
{
public:
	CAngData();
	~CAngData();
	float*m_pdata;
	float m_average;
	unsigned int m_size;
	unsigned int m_index;
	unsigned int m_diagram[MAX_DIAGRAM_ANGLE];
	bool circle;
	int m_multi;
	static unsigned int sm_maxdiagram;
	void Create(unsigned int size, bool circle = false);
	float operator[](unsigned int index);
	float Average(void);
	void AddData(const float&data);
	void GetData(CAngData&in);
	void Clear(void);
	void Restart(void);
	bool IsFull(void);
	void Calculate(void);
};

