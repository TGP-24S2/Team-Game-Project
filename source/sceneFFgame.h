#pragma once
#ifndef __SCENEFFGAME_H__
#define __SCENEFFGAME_H__

// Local includes: 
#include "scene.h"
#include "vector2.h"
#include "vector"
#include "prop.h"
#include "HUD.h"

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
class AmmoPickup;

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
	Prop* GetPropPoolObject();
	void SpawnProps();

	float UpdateDifficultyModifier();

	// Member data:
public:
	// game
	enum GameStatus m_eStatus;
	float m_fLocalDeltaTime;
	float m_fTimeSinceInput;
	float m_fPostMovementTimeBuffer = 0.7f; //how long game processes after controls are released
	float m_fDifficultyModifier = 1.0f;
	int m_iCompletedLevels = 0;
	int m_iTotalLevels; //required amount of level completions before victory
	// the lower the number, the more ammo count will increase difficulty 
	// eg. ammo-derived difficulty is at its highest when the player has 5 magazines
	int MAGAZINE_DIFFICULTY_CAP = 5; 

	// hud
	HUD m_pHud;

	// level
	Level* m_pLevel;
	std::vector<Sprite*> m_vpPropSprites;

	// player
	Player* m_pPlayer;

	// prop templates
	std::vector<PropTemplate*> m_PropTemplates;

	// props
	static constexpr int MAX_PROPS = 5;
	Prop* m_Props[MAX_PROPS]; //prop object pool

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

	std::vector<AmmoPickup*> m_vpAmmoPickups;

	Rectangle* m_pRectangle;

protected:

private:
	Renderer* m_pRenderer;
	SoundSystem* m_pSoundSystem;
};

#endif // __SCENEFFGAME_H__