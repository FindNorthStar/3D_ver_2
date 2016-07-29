#include "stdafx.h"
#include "Config.h"
#include <stdexcept>

double Config::GetConfig(Config::ConfigIndex index)
{
	if (index < 0 || index >= ConfigIndex::CONFIG_SIZE) throw std::runtime_error("IndexError.\n");
	return configData[index];
}

double*Config::GetAllConfig()
{
	return configData;
}

void Config::SetConfig(double val, Config::ConfigIndex index)
{
	if (index < 0 || index >= ConfigIndex::CONFIG_SIZE) throw std::runtime_error("IndexError.\n");
	configData[index] = val;
}

void Config::SetAllConfig(double*data)
{
	for (int i = 0; i < CONFIG_SIZE;i++)
	{
		configData[i] = data[i];
	}
}