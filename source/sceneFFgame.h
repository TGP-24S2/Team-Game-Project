#pragma once
#ifndef __SCENEFFGAME_H__
#define __SCENEFFGAME_H__

// Local includes: 
#include "scene.h"
#include "vector2.h"
#include "vector"

#include <fmod.hpp>
#include <map.>

// Forward declarations:
class Sprite;
class Ball;
class Enemy;
class Player;
class Rectangle;
class SoundSystem;
class Weapon;
class Level;

enum GameStatus
{
	GS_RUNNING,
	GS_WIN,
	GS_LOSS
};

class SceneFFGame : public Scene
{
	// Member methods:
public:
	SceneFFGame();
	 ~SceneFFGame();

	 bool Initialise(Renderer& renderer, SoundSystem* soundSystem);
	 void Process(float deltaTime, InputSystem& inputSystem);
	 void Draw(Renderer& renderer);
	 void WipeScene();
	 void DebugDraw();
protected:

private:

	// Member data:
public:
	// game
	enum GameStatus m_eStatus;
	float m_fLocalDeltaTime;
	float m_fTimeSinceInput;
	float m_fPostMovementTimeBuffer = 0.7f; //how long game processes after controls are released

	// level
	Level* m_pLevel;
	std::vector<Sprite*> m_vpPropSprites;

	// player
	Player* m_pPlayer;

	// enemies
	std::vector<Enemy*> m_vpEnemies;

	// text sprites
	Sprite* m_pGameOverSprite;
	Sprite* m_pYouWinSprite;

	// cursor
	Sprite* m_pCursorSprite;
	Vector2 m_cursorPosition;

	//TESTING remove later probs
	Ball* m_pTestBall;

	// weapons
	int m_iCurrentWeapon;
	std::vector<Weapon*> m_vpWeapons;
	std::vector<Sprite*> m_vpWeaponIconSprites;

	Rectangle* m_pRectangle;


protected:

private:
	Renderer* m_pRenderer;
	SoundSystem* m_pSoundSystem;
};

#endif // __SCENEFFGAME_H__