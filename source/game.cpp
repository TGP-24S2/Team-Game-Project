// COMP710 GP Framework 2022
// This include:
#include "game.h"
// Library includes:
#include "renderer.h"
#include "logmanager.h"
#include "sprite.h"
#include "scenesplashaut.h"
#include "scenefmodsplash.h"
#include "scenecontrolinstructionsplash.h"
#include "imgui_impl_sdl2.h"
#include "inputsystem.h"
#include "xboxcontroller.h"
#include "soundsystem.h"
#include "iniparser.h"

// the GOAT INCLUDE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//?
#include "sceneFFgame.h"

#include <fmod.hpp>

// Static Members:
Game*
Game::sm_pInstance = 0;
Game&
Game::GetInstance()
{
	if(sm_pInstance	== 0)
	{
		sm_pInstance = new Game();
	}
	return (*sm_pInstance);
}
void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}
Game::Game()
	: m_pRenderer(nullptr),                 // Initialize pointer to Renderer
	  m_pInputSystem(nullptr),              // Initialize pointer to InputSystem
	  m_pSoundSystem(nullptr),              // Initialize pointer to SoundSystem
	  m_iLastTime(0),                       // Initialize 64-bit integer for time
	  m_fExecutionTime(0.0f),               // Initialize execution time as 0
	  m_fElapsedSeconds(0.0f),              // Initialize elapsed seconds as 0
	  m_iFrameCount(0),                     // Initialize frame count as 0
	  m_iFPS(0),                            // Initialize FPS as 0
	  m_scenes(),                           // Initialize vector of scenes (empty)
	  m_iCurrentScene(0),                   // Initialize current scene index as 0
	  m_bShowDebugWindow(false),            // Initialize debug window flag as false
	  m_bPauseSimulation(false),
	  m_bLooping(true)
{
	// Constructor body (if any logic is needed here)
}
Game::~Game()
{
	for (auto it = begin(m_scenes); it != end(m_scenes); ++it) {
		delete* it;
		*it = 0;
	}
	m_scenes.clear();
	delete m_pRenderer;
	m_pRenderer = 0;
	delete m_pInputSystem;
	m_pInputSystem = 0;
	SoundSystem::DestroyInstance();
	m_pSoundSystem = 0;
}
void
Game::Quit()
{
	m_bLooping = false;
}
bool
Game::Initialise()
{
	IniParser::GetInstance().LoadIniFile("config.ini");
	int bbWidth = IniParser::GetInstance().GetValueAsInt("Window","Width");
	int bbHeight = IniParser::GetInstance().GetValueAsInt("Window", "Height");
	m_pRenderer = &Renderer::GetInstance();
	if (!m_pRenderer -> Initialise(true, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}
	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();
	m_iLastTime = SDL_GetPerformanceCounter();
	m_pRenderer->SetClearColour(0, 0, 0);

	m_pInputSystem = &InputSystem::GetInstance();
	m_pInputSystem->Initialise();

	m_pSoundSystem = &SoundSystem::GetInstance();
	m_pSoundSystem->Initialise();

	Scene* pScene0 = 0;
	pScene0 = new SceneSplashAUT(); //CHECKERBOARDS!!!!!!!
	pScene0->Initialise(*m_pRenderer, m_pSoundSystem);
	m_scenes.push_back(pScene0);

	Scene* pScene1 = 0;
	pScene1 = new SceneFMODSplash();
	pScene1->Initialise(*m_pRenderer, m_pSoundSystem);
	m_scenes.push_back(pScene1);

	Scene* pScene2 = 0;
	pScene2 = new SceneControlInstructionSplash();
	pScene2->Initialise(*m_pRenderer, m_pSoundSystem);
	m_scenes.push_back(pScene2);

	Scene* pScene3 = 0;
	pScene3 = new SceneFFGame();
	pScene3->Initialise(*m_pRenderer, m_pSoundSystem);
	m_scenes.push_back(pScene3);

#if _DEBUG
	m_iCurrentScene = 3;
#else
	m_iCurrentScene = 0;
#endif

	return true;
}
bool
Game::DoGameLoop()
{
	const float	stepSize = 1.0f / 60.0f;// TODO: Process input here!
	m_pInputSystem->ProcessInput();

	if (m_bLooping)
	{
		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		m_iLastTime = current;
		m_fExecutionTime += deltaTime;
		Process(deltaTime);
#ifdef USE_LAG
		m_fLag += deltaTime;
		int innerLag = 0;
		while (m_fLag >= stepSize)
		{
			Process(stepSize);
			m_fLag -= stepSize;
			++m_iUpdateCount;
			++innerLag;
		}
#endif //USE_LAG
		Draw(*m_pRenderer);
	}
	return m_bLooping;
}
void
Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);

	if (m_bPauseSimulation)
	{
		deltaTime = 0.0f;
	}

	// TODO: Add game objects to process here!
	m_scenes[m_iCurrentScene]->Process(deltaTime, *m_pInputSystem);
	m_pSoundSystem->Update();
}
void
Game::Draw(Renderer& renderer)
{
	++m_iFrameCount;
	renderer.Clear();
	// TODO: Add game objects to draw here!
	m_scenes[m_iCurrentScene]->Draw(renderer);

	DebugDraw();

	renderer.Present();
}
void
Game::ProcessFrameCounting(float deltaTime)
{
	// Count total simulation time elapsed:
	m_fElapsedSeconds += deltaTime;
	// Frame Counter:
	if (m_fElapsedSeconds > 1.0f)
	{
		m_fElapsedSeconds -= 1.0f;
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}
}

void Game::DebugDraw()
{
	if (m_bShowDebugWindow)
	{
		bool open = true;
		ImGui::Begin("Debug Window", &open, ImGuiWindowFlags_MenuBar); 
		ImGui::Text("COMP710 GP Framework (%s)", "2022, S2");

		if (ImGui::Button("Pause simulation"))
		{
			m_bPauseSimulation = !m_bPauseSimulation;
		}

		if (ImGui::Button("Quit"))
		{
			Quit();
		}

		ImGui::Separator();
		LogManager::GetInstance().DebugDraw();
		ImGui::Separator();

		//m_pRenderer->DebugDraw();
		ImGui::Separator();

		ImGui::SliderInt("Active scene", &m_iCurrentScene, 0, m_scenes.size() - 1, "%d"); 
		m_scenes[m_iCurrentScene]->DebugDraw();

		ImGui::End();
	}
}


void Game::ToggleDebugWindow()
{
	m_bShowDebugWindow = !m_bShowDebugWindow;
	m_pInputSystem->ShowMouseCursor(m_bShowDebugWindow);
}

void Game::ChangeScene(int scene) {
	m_iCurrentScene = scene;
}