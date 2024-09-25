#ifndef INIPARSER_H
#define INIPARSER_H

#include <string>
#include <map>

class IniParser {
public:
    static IniParser& GetInstance();
    static void DestroyInstance();
    bool LoadIniFile(const std::string& filename);
    std::string GetValueAsString(const std::string& iniSection, const std::string& key);
    int GetValueAsInt(const std::string& iniSection, const std::string& key);
    float GetValueAsFloat(const std::string& iniSection, const std::string& key);
    bool GetValueAsBoolean(const std::string& iniSection, const std::string& key);
protected:
private:
public:
    static IniParser* sm_pInstance;
protected:
private:
    std::map<std::string, std::string> data;
    std::string CreateMapKey(const std::string& section, const std::string& key);
};

#endif // INIPARSER_H
