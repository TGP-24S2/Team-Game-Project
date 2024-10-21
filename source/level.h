#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <string>
#include <vector>

enum LevelCell
{
	LC_NONE, // blank or other
	LC_WALL, // W
	LC_PLAYER, // P
};

class Level
{
	// Methods:
public:
	Level(const std::string&);
	~Level();
	bool LoadLevelFile(const std::string&);
	std::vector<std::vector<enum LevelCell>> GetLevelData();
protected:
private:
	
	// Instance variables:
public:
protected:
	std::vector<std::vector<enum LevelCell>> m_vveLevelData;
private:
};

#endif // __LEVEL_H__
