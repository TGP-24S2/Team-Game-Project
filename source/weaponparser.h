#ifndef INIPARSER_H
#define INIPARSER_H

#include <string>
#include <map>

class IniParser;

class WeaponParser {
public:
    static WeaponParser& GetInstance();
    static void DestroyInstance();
    bool LoadIniFile(const std::string& filename);

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
