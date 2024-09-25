// COMP710 GP Framework 2022 
#ifndef __SCENESPLASHAUT_H   
#define __SCENESPLASHAUT_H 
// Local includes: 
#include "scene.h"
// Forward declarations: 
class Renderer;
class Sprite;
class InputSystem;
class SoundSystem;
// Class declaration:
class SceneSplashAUT : public Scene
{
	// Member methods: 
public:
	SceneSplashAUT();
	virtual ~SceneSplashAUT();
	virtual bool Initialise(Renderer& renderer, SoundSystem* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
protected:
private:
	SceneSplashAUT(const SceneSplashAUT& sceneSplashAUT);
	SceneSplashAUT& operator=(const SceneSplashAUT& sceneSplashAUT);

	// Member data:
public:

protected:
	Sprite* m_pSplash;
	float m_fadeSpeed;
	float m_alpha;
	bool m_fadeIn;
	Sprite* m_pText;
private:

};

#endif //   SCENESPLASHAUT_H 
