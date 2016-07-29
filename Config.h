#pragma once
#include "stdafx.h"

class Config
{
public:
	enum ConfigIndex{
		CONFIG_SHOULDER_MIN, CONFIG_SHOULDER_MAX, CONFIG_HEAD_ANGLE_A, CONFIG_HEAD_ANGLE_B_MIN, CONFIG_HEAD_ANGLE_B_MAX
		, CONFIG_ABDOMEN_ANGLE, CONFIG_ASIDE_HEAD_ANGLE_MIN, CONFIG_ASIDE_HEAD_ANGLE_MAX, CONFIG_DELAY, CONFIG_SIZE
	};
private:
	char outputBuffer[256];
	double configData[CONFIG_SIZE];
public:
	Config()
	{
		for (int i = 0; i < CONFIG_SIZE;i++)
		{
			configData[i] = 0;
		}
	}
	double GetConfig(ConfigIndex index);
	double*GetAllConfig();
	void SetConfig(double val, ConfigIndex index);
	void SetAllConfig(double*data);
};