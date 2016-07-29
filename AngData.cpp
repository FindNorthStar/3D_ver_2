#include "stdafx.h"
#include "AngData.h"

unsigned int CAngData::sm_maxdiagram = 0;


CAngData::CAngData()
{
	m_pdata = 0;
	m_index = 0;
	CAngData::sm_maxdiagram = MAX_DIAGRAM_ANGLE;
}


CAngData::~CAngData()
{
	delete[]m_pdata;
}

void CAngData::Create(unsigned int size, bool circle)
{
	this->circle = circle;
	if (m_pdata != 0)
	{
		delete[]m_pdata;
	}
	this->m_size = size;
	m_pdata = new float[size];
	memset(m_pdata, 0, sizeof(float)*m_size);
	memset(m_diagram, 0, sizeof(unsigned int)*MAX_DIAGRAM_ANGLE);
	m_average = 0;
	m_index = 0;
	m_multi = 0;
}

float CAngData::operator[](unsigned int index)
{
	if (index >= m_size) return 0;
	return m_pdata[index];
}

float CAngData::Average(void)
{
	float temp = 0;
	int num = 0;
	for (unsigned int i = 0; i < m_size; i++)
	{
		if (abs(m_pdata[i]) > 0.01)
		{
			temp += m_pdata[i];
			num++;
		}
	}
	return m_average = temp / num;
}

void CAngData::AddData(const float&data)
{
	m_pdata[m_index++] = data;
	if (0 <= (int)data && (int)data < MAX_DIAGRAM_ANGLE)
	{
		m_diagram[(int)data]++;
	}
	else
	{
		m_diagram[MAX_DIAGRAM_ANGLE - 1]++;
	}
	if (circle = true)
	{
		m_average = Average();
	}
}

void CAngData::Clear(void)
{
	if (circle == false)
	{
		memset(m_pdata, 0, sizeof(float)*m_size);
		memset(m_diagram, 0, sizeof(unsigned int)*MAX_DIAGRAM_ANGLE);
		m_average = 0;
	}
	if (m_index >= m_size)
	{
		m_multi++;
	}
	m_index = 0;
}

void CAngData::Restart(void)
{
	memset(m_pdata, 0, sizeof(float)*m_size);
	memset(m_diagram, 0, sizeof(unsigned int)*MAX_DIAGRAM_ANGLE);
	m_average = 0;
	m_index = 0;
	m_multi = 0;
}

bool CAngData::IsFull(void)
{
	return (m_index < m_size) ? false : true;
}

void CAngData::GetData(CAngData & in)
{
	in.Calculate();
	if (m_multi > 1)
	{
		m_diagram[(int)m_pdata[m_index]]--;
	}
	m_pdata[m_index++] = in.m_average;
	m_diagram[(int)abs(in.m_average)]++;
}

void CAngData::Calculate(void)
{
	Average();
}