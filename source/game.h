// COMP710 GP Framework 2022 
#ifndef __GAME_H 
#define __GAME_H 

//Library Includes
#include <vector>
#include <fmod.hpp>

// Forward declarations: 
class Renderer;
class InputSystem;
class Sprite;
class Scene;
class SoundSystem;
class Game
{
	// Member methods: 
public:
	static Game& GetInstance();
	static void DestroyInstance();
	bool Initialise();
	bool DoGameLoop();
	void Quit();
	void ToggleDebugWindow();
	void ChangeScene(int scene);

protected:
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	void ProcessFrameCounting(float deltaTime);
	void DebugDraw();
private:
	Game();
	~Game();
	Game(const Game& game);
	Game& operator=(const Game& game);
	// Member data: 
public:
protected:
	static Game* sm_pInstance;
	Renderer* m_pRenderer;
	InputSystem* m_pInputSystem;
	SoundSystem* m_pSoundSystem;
	__int64 m_iLastTime;
	float m_fExecutionTime;
	float m_fElapsedSeconds;
	int m_iFrameCount;
	int m_iFPS;
	std::vector<Scene*> m_scenes; 
	int m_iCurrentScene;
	bool m_bShowDebugWindow;
	bool m_bPauseSimulation;

#ifdef __USE_LAG 
	float m_fLag;
	int m_iUpdateCount;
#endif // USE_LAG
	bool m_bLooping;

	FMOD::System* m_soundSystem;
private:

};

#endif // __GAME_H 
