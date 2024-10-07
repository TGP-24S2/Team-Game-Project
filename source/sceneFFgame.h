#pragma once
#ifndef __SCENEFFGAME_H__
#define __SCENEFFGAME_H__

// Local includes: 
#include "scene.h"
#include "vector2.h"

// Forward declarations:
class Sprite;
class Ball;
class Enemy;
class Player;

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

protected:

private:

	// Member data:
public:
	//TESTING
	Ball* m_pTestBall;
	Enemy* m_pTestEnemy;

	// game
	float m_fLocalDeltaTime;
	float m_fTimeSinceInput;
	float m_fPostMovementTimeBuffer = 0.7f; //how long game processes after controls are released

	// player
	Player* m_pPlayer;

	// cursor
	Sprite* m_pCursorSprite;

	Vector2 m_cursorPosition;

protected:

private:

};

#endif // __SCENEFFGAME_H__