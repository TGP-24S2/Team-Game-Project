#pragma once

#include "entity.h"

class AnimatedSprite;
class Renderer;

class Enemy : public Entity {

	// methods:
public:
	Enemy();
	Enemy(int health, int dmg);
	~Enemy();
	void Initialise(Renderer& renderer, const char* spritePath);
	void Process(float deltaTime);
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
