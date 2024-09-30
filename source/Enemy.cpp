#include "Enemy.h"

#include "sprite.h"

Enemy::Enemy()
	: Entity()
	, m_iHealth(0)
	, m_iDamage(0)
	, m_bTargetingPlayer(false)
{
}

Enemy::Enemy(int health, int damage)
	: Enemy()
{
	m_iHealth = health;
	m_iDamage = damage;
}

Enemy::~Enemy()
{
}

void Enemy::SetSprite(AnimatedSprite* pSprite)
{
	m_pSprite = pSprite;
}

int Enemy::GetHealth()
{
	return m_iHealth;
}

void Enemy::SetDamage(int damage)
{
	m_iDamage = damage;
}

int Enemy::GetDamage()
{
	return m_iDamage;
}

void Enemy::SetToAngry()
{
	m_bTargetingPlayer = true;
}

void Enemy::SetToNotAngry()
{
	m_bTargetingPlayer = false;
}