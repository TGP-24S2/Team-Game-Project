#include "level.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

Level::Level(const std::string& filename)
{
    LoadLevelFile(filename);
}

Level::~Level()
{   // deconstruct
    for (auto vec : m_vveLevelData)
    {
        vec.clear();
    }
    m_vveLevelData.clear();
}

bool Level::LoadLevelFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string section;
    std::string line;
    while (std::getline(file, line))
    {
        // current line vector
        std::vector<enum LevelCell> lineVec;

        for (char ch : line)
        {
            enum LevelCell cell;
            switch (ch)
            {
                case 'W': cell = LC_WALL; break;
                case 'P': cell = LC_PLAYER; break;
                default: cell = LC_NONE; break;
            }
            lineVec.push_back(cell);
        }

        m_vveLevelData.push_back(lineVec);
    }

    file.close();
    return true;
}

std::vector<std::vector<enum LevelCell>> Level::GetLevelData()
{
    return m_vveLevelData;
}
