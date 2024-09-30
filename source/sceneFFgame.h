#pragma once
#ifndef __SCENEFFGAME_H__
#define __SCENEFFGAME_H__

// Local includes: 
#include "scene.h"
#include "vector2.h"

// Forward declarations:
class Sprite;

class SceneFFGame : public Scene
{
	// Member methods:
public:
	SceneFFGame();
	 ~SceneFFGame();

	 bool Initialise(Renderer& renderer, SoundSystem* soundSystem);
	 void Process(float deltaTime, InputSystem& inputSystem);
	 void Draw(Renderer& renderer);

	 void DebugDraw();

	 void ComputeBounds(int width, int height);

	 void CapSpeed();

protected:

private:

	// Member data:
public:
	// game
	float m_fLocalDeltaTime;
	float m_fTimeSinceInput;
	float m_fPostMovementTimeBuffer = 0.7f; //how long game processes after controls are released

	// player
	Sprite* m_pPlayerSprite;

	Vector2 m_position;
	Vector2 m_velocity;

	float m_fAccelerationRate = 3.0f;
	float m_fDecelerationRate = 1.5f;
	float m_fSpeedScale = 1.0f;
	float m_fMaxSpeed = 400.0f;

	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;

	// cursor
	Sprite* m_pCursorSprite;

	Vector2 m_cursorPosition;

protected:

private:

};

#endif // __SCENEFFGAME_H__