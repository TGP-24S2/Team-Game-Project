#ifndef AMMO_PICKUP_H
#define AMMO_PICKUP_H

#include "entity.h"

class Sprite;
class Renderer;

class AmmoPickup : public Entity
{
	// Methods:
public:
	AmmoPickup(Renderer& renderer);
	~AmmoPickup();
	Sprite* GetSprite();
protected:
private:

	// Instance variables:
public:
	int m_iWeaponType;
	int m_iAmmoCount;
protected:
	Sprite* m_pSprite;
private:
};

#endif// AMMO_PICKUP_H
