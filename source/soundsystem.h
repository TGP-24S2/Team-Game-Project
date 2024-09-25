#ifndef __SOUNDSYSTEM_H  
#define __SOUNDSYSTEM_H 

#include <fmod.hpp>
#include <map>
#include <string>

class SoundSystem
{
public:
    SoundSystem();
    ~SoundSystem();

    static SoundSystem& GetInstance();
    static void DestroyInstance();

    bool Initialise();
    void Update();
    void Release();

    FMOD::Sound* LoadSound(const std::string& filename, bool is3D = false, bool isLooping = false, bool isStreaming = false);
    void PlaySound(std::string filename, bool paused = false, FMOD::Channel** channel = 0);
    void StopAllSounds();

protected:
private:
public:
protected:
    static SoundSystem* sm_pInstance;
private:
    FMOD::System* m_pSystem;
    std::map<std::string, FMOD::Sound*> m_pLoadedSounds;
};

#endif 