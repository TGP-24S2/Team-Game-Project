#pragma once

#include "entity.h"

class AnimatedSprite;
class Renderer;
class Player;

class Enemy : public Entity {

	// methods:
public:
	Enemy(Player*);
	~Enemy();

	void Initialise(Renderer& renderer);
	void Process(float deltaTime);

	void SetPlayer(Player* pPlayer);
	int GetHealth();
	int GetDamage();
	void SetDamage(int damage);
	void SetToAngry();
	void SetToNotAngry();
	bool IsTargetingPlayer();
protected:
private:

	// vars:
public:

protected:
	int m_iDamage;
	float m_fInitialScale;
	Player* m_pPlayer;
	bool m_bAngry;

private:

};
