#include "Enemy.h"

#include "animatedsprite.h"

Enemy::Enemy()
	: Entity()
	, m_iHealth(0)
	, m_iDamage(0)
	, m_bTargetingPlayer(false)
{
}

Enemy::Enemy(int health, int damage)
	: Enemy() // call default constructor
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

	// set bad
	m_pSprite->SetRedTint(1.0f);
	m_pSprite->SetBlueTint(0.0f);
	m_pSprite->SetGreenTint(0.0f);
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