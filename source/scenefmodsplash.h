// COMP710 GP Framework 2022 
#ifndef __SCENEFMODSPLASH_H   
#define __SCENEFMODSPLASH_H 
// Local includes: 
#include "scene.h"
// Forward declarations: 
class Renderer;
class Sprite;
class InputSystem;
class SoundSystem;
// Class declaration:
class SceneFMODSplash : public Scene
{
	// Member methods: 
public:
	SceneFMODSplash();
	virtual ~SceneFMODSplash();
	virtual bool Initialise(Renderer& renderer, SoundSystem* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
protected:
private:
	SceneFMODSplash(const SceneFMODSplash& sceneFMODSplash);
	SceneFMODSplash& operator=(const SceneFMODSplash& sceneFMODSplash);

	// Member data:
public:

protected:
	Sprite* m_pSplash;
	float m_fadeSpeed;
	float m_alpha;
	bool m_fadeIn;
private:

};

#endif //   SCENESPLASHAUT_H 
