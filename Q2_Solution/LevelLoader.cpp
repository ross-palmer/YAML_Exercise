#include "LevelLoader.h"

void operator >> (const YAML::Node& t_tankNode, TankData& t_tank)
{
	t_tank.m_x = t_tankNode["position"]["x"].as<float>();
	t_tank.m_y = t_tankNode["position"]["y"].as<float>();
	t_tank.m_scale = t_tankNode["scale"].as<float>();
	t_tank.m_rotation = t_tankNode["rotation"].as<int>();
}

void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{
   // Process the sequence of tanks
   const YAML::Node& tanksNode = t_levelNode["tanks"].as<YAML::Node>();
   for (unsigned i = 0; i < tanksNode.size(); ++i)
   {
	  TankData tank;
	  tanksNode[i] >> tank;
	  t_level.m_tanks.push_back(tank);
   }
}

void LevelLoader::load(int t_levelNr, LevelData& t_level)
{
   std::string filename = "./levelData/level" + std::to_string(t_levelNr) + ".yaml";

   try
   {
	   YAML::Node baseNode = YAML::LoadFile(filename);
	   if (baseNode.IsNull())
	   {
		   std::string message("File: " + filename + " not found");
		   throw std::exception(message.c_str());
	   }
	   // Call overloaded operator >>, passing baseNode as arg1, t_level as arg2
	   baseNode >> t_level;
   }
   catch (YAML::ParserException& e)
   {
	   std::string message(e.what());
	   message = "YAML Parser Error: " + message;
	   throw std::exception(message.c_str());
   }
   catch (std::exception& e)
   {
	   std::string message(e.what());
	   message = "Unexpected Error: " + message;
	   throw std::exception(message.c_str());
   }
}
