#ifndef INIPARSER_H
#define INIPARSER_H

#include <string>
#include <map>
#include "vector"

class Weapon;
class Melee;
class ParticleEmitter;

class IniParser {
public:
    static IniParser& GetInstance();
    static void DestroyInstance();
    bool LoadIniFile(const std::string& filename);
    std::string GetValueAsString(const std::string& iniSection, const std::string& key);
    int GetValueAsInt(const std::string& iniSection, const std::string& key);
    float GetValueAsFloat(const std::string& iniSection, const std::string& key);
    bool GetValueAsBoolean(const std::string& iniSection, const std::string& key);

    std::vector<Weapon*> GetWeapons(const std::string& filename);
protected:
private:
    std::map<std::string, std::map<std::string, std::string>> GetWeaponData();
    bool IsWeaponSection(const std::string& section);
public:
    static IniParser* sm_pInstance;
protected:
private:
    std::map<std::string, std::string> data;
    std::string CreateMapKey(const std::string& section, const std::string& key);
};

#endif // INIPARSER_H
