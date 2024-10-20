#pragma once

// COMP710 GP Framework 2022 
#ifndef __SCENECONTORLSPLASH_H   
#define __SCENECONTORLSPLASH_H 
// Local includes: 
#include "scene.h"
// Forward declarations: 
class Renderer;
class Sprite;
class InputSystem;
class SoundSystem;
// Class declaration:
class SceneControlInstructionSplash : public Scene
{
	// Member methods: 
public:
	SceneControlInstructionSplash();
	virtual ~SceneControlInstructionSplash();
	virtual bool Initialise(Renderer& renderer, SoundSystem* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
protected:
private:
	SceneControlInstructionSplash(const SceneControlInstructionSplash& sceneControlInstructionSplash);
	SceneControlInstructionSplash& operator=(const SceneControlInstructionSplash& sceneControlInstructionSplash);

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
