#include "IniParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

IniParser* IniParser::sm_pInstance = 0;
IniParser&
IniParser::GetInstance()
{
    if (sm_pInstance ==
        0)
    {
        sm_pInstance =
            new IniParser();
    }return (*sm_pInstance);
}
void
IniParser::DestroyInstance()
{
    delete sm_pInstance;
    sm_pInstance = 0;
}

bool IniParser::LoadIniFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string section;
    std::string line;
    while (std::getline(file, line)) {
        // Trim leading/trailing spaces
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue; // Skip comments and empty lines
        }

        if (line.front() == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2); // Extract section name
            section.erase(0, section.find_first_not_of(" \t"));
            section.erase(section.find_last_not_of(" \t") + 1);
        }
        else {
            std::size_t delimiterPos = line.find('=');
            if (delimiterPos == std::string::npos) {
                continue; // Skip lines without an '=' sign
            }

            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            // Trim key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // Store key-value in the map
            data[CreateMapKey(section, key)] = value;
        }
    }

    file.close();
    return true;
}

std::string IniParser::GetValueAsString(const std::string& iniSection, const std::string& key) {
    std::string mapKey = CreateMapKey(iniSection, key);
    if (data.find(mapKey) != data.end()) {
        return data[mapKey];
    }
    throw std::runtime_error("Key not found");
}

int IniParser::GetValueAsInt(const std::string& iniSection, const std::string& key) {
    return std::stoi(GetValueAsString(iniSection, key));
}

float IniParser::GetValueAsFloat(const std::string& iniSection, const std::string& key) {
    return std::stof(GetValueAsString(iniSection, key));
}

bool IniParser::GetValueAsBoolean(const std::string& iniSection, const std::string& key) {
    std::string value = GetValueAsString(iniSection, key);
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);

    if (value == "true" || value == "1") {
        return true;
    }
    else if (value == "false" || value == "0") {
        return false;
    }
    throw std::runtime_error("Invalid boolean value");
}

std::string IniParser::CreateMapKey(const std::string& section, const std::string& key) {
    return section + "|" + key;
}
