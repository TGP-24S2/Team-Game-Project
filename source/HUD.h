#pragma once

#ifndef __HUD_H__
#define __HUD_H__

// Local includes:
#include "weapon.h"

// Library includes:
#include <vector>
#include <string>

//Forward declarations:
class Renderer;
class Sprite;
class AnimatedSprite;
class Player;

class HUD
{
	// Member methods:
public:
	HUD();
	~HUD();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void DebugDraw();

	void SetPlayer(Player* player);
	void SetLevelGoal(int level);
	void UpdateWeapon(Weapon* weapon);

protected:

private:
	void UpdateHealth();	
	void UpdateAmmo();

	// Member data:
public:
	Renderer* m_pRenderer;

	Sprite* m_pLevelText;
	int m_iCurrentLevels;
	int m_iLevelGoal;
	
	Player* m_pPlayer;
	AnimatedSprite* m_pHealthBar;

	Weapon* m_pWeapon;
	Sprite* m_pWeaponIcon;

	weaponType m_eCurrentWeaponType;

	Sprite* m_pMagazineCapacity[3];
	Sprite* m_pAmmoCross;
	Sprite* m_pMagazineCount[3];

protected:

private:


};

#endif // __HUD_H__