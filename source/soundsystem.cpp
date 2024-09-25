#include "SoundSystem.h"
#include "logmanager.h"
#include <cassert>


SoundSystem* SoundSystem::sm_pInstance = 0;
SoundSystem&
SoundSystem::GetInstance()
{
    if (sm_pInstance ==
        0)
    {
        sm_pInstance =
            new SoundSystem();
    }return (*sm_pInstance);
}
void
SoundSystem::DestroyInstance()
{
    delete sm_pInstance;
    sm_pInstance = 0;
}

SoundSystem::SoundSystem()
    : m_pSystem(nullptr)
{
}

SoundSystem::~SoundSystem()
{
    Release();
}

bool SoundSystem::Initialise()
{
    FMOD_RESULT result;

    // Create the FMOD system
    result = FMOD::System_Create(&m_pSystem);
    if (result != FMOD_OK)
    {
        LogManager::GetInstance().Log("FMOD system creation failed!");
        return false;
    }

    // Initialize the FMOD system
    result = m_pSystem->init(512, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK)
    {
        LogManager::GetInstance().Log("FMOD system initialization failed!");
        return false;
    }

    LogManager::GetInstance().Log("FMOD system initialized.");
    return true;
}

void SoundSystem::Update()
{
    // Update FMOD
    if (m_pSystem)
    {
        m_pSystem->update();
    }
}

void SoundSystem::Release()
{
    // Release all loaded sounds
    for (auto& soundEntry : m_pLoadedSounds)
    {
        if (soundEntry.second)
        {
            soundEntry.second->release();
        }
    }
    m_pLoadedSounds.clear();

    // Release the FMOD system
    if (m_pSystem)
    {
        m_pSystem->close();
        m_pSystem->release();
        m_pSystem = nullptr;
    }

    LogManager::GetInstance().Log("FMOD system released.");
}

FMOD::Sound* SoundSystem::LoadSound(const std::string& filename, bool is3D, bool isLooping, bool isStreaming)
{
    if (m_pLoadedSounds.find(filename) != m_pLoadedSounds.end())
    {
        return m_pLoadedSounds[filename];
    }

    FMOD::Sound* pSound = nullptr;
    FMOD_MODE mode = FMOD_DEFAULT;

    if (is3D) mode |= FMOD_3D;
    if (isLooping) mode |= FMOD_LOOP_NORMAL;
    if (isStreaming) mode |= FMOD_CREATESTREAM;

    FMOD_RESULT result = m_pSystem->createSound(filename.c_str(), mode, nullptr, &pSound);
    if (result != FMOD_OK)
    {
        std::string soundcreation = "FMOD sound creation failed: " + filename;
        LogManager::GetInstance().Log(soundcreation.c_str());
        return nullptr;
    }

    m_pLoadedSounds[filename] = pSound;
    std::string loadedsound = "Loaded sound: " + filename;
    LogManager::GetInstance().Log(loadedsound.c_str());
    return pSound;
}

void SoundSystem::PlaySound(std::string filename, bool paused, FMOD::Channel** channel)
{
    FMOD::Sound* sound = m_pLoadedSounds[filename];
    if (!sound)
    {
        LogManager::GetInstance().Log("Invalid sound to play.");
        return;
    }

    FMOD_RESULT result = m_pSystem->playSound(sound, nullptr, paused, channel);
    if (result != FMOD_OK)
    {
        LogManager::GetInstance().Log("FMOD failed to play sound.");
    }
}

void SoundSystem::StopAllSounds()
{
    FMOD::ChannelGroup* masterChannelGroup = nullptr;
    m_pSystem->getMasterChannelGroup(&masterChannelGroup);
    if (masterChannelGroup)
    {
        masterChannelGroup->stop();
    }
}
