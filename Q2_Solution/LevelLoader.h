#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct TankData
{
	float m_x;
	float m_y;
	float m_scale;
	int m_rotation;
};

struct LevelData
{
   std::vector<TankData> m_tanks;
};

class LevelLoader
{
public:
   static void load(int t_levelNr, LevelData& t_level);
};
