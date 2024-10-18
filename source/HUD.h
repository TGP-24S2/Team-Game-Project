#pragma once

#ifndef __HUD_H__
#define __HUD_H__

// Local includes:
#include "weapon.h"

// Library includes:
#include <vector>

//Forward declarations:
class Renderer;
class Sprite;
class AnimatedSprite;

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

	void SetMaxHealth(int hp);
	void UpdateCurrentHealth(int hp);
	void UpdateWeapon(Weapon weapon);

protected:

private:

	// Member data:
public:
	Sprite* m_pLevelText;
	
	Sprite* m_pHealthIcon;
	Sprite* m_pHealthText;

	Sprite* m_pWeaponIcon;

	Sprite* m_pMagazineCapacity;
	weaponType m_eCurrentWeaponType;
	Sprite* m_pMagazineCount;
	Sprite* m_pTotalAmmo;

protected:

private:


};

#endif // __HUD_H__