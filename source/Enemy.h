#pragma once

#include "entity.h"

class AnimatedSprite;

class Enemy : public Entity {

	// methods:
public:
	Enemy();
	Enemy(int health, int dmg);
	~Enemy();
	void SetSprite(AnimatedSprite* pSprite);
	int GetHealth();
	int GetDamage();
	void SetDamage(int damage);
	void SetToAngry();
	void SetToNotAngry();
protected:
private:

	// vars:
public:
protected:
	int m_iHealth;
	int m_iDamage;
	bool m_bTargetingPlayer;

private:

};
