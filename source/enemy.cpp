#include "enemy.h"

#include "inlinehelpers.h"
#include "renderer.h"
#include "animatedsprite.h"
#include "player.h"

Enemy::Enemy()
	: Entity()
	, m_iDamage(5)
	, m_fInitialScale(0.5f)
	, m_bTargetingPlayer(false)
	, m_pPlayer(nullptr)
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

void Enemy::Initialise(Renderer& renderer)
{
	Entity::Initialise(renderer, "sprites\\enemy.png", 307); //super()
	
	m_pSprite->SetScale(m_fInitialScale);

	RandomStartPlace();

}

void Enemy::Process(float deltaTime)
{
	Entity::Process(deltaTime); // super
	m_pSprite->Process(deltaTime);

	// make bot somewhat follow player
	Vector2 playerVel = m_pPlayer->GetVelocity();
	m_velocity.x += playerVel.x * deltaTime;
	m_velocity.y += playerVel.y * deltaTime;

	// denote size as health
	float scale = (float)m_iHealth / m_iMaxHealth * m_fInitialScale;
	m_pSprite->SetScale(scale);
	if (scale < 0.01f) 
		Kill(); // kill if too small
}

void Enemy::SetPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
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

bool Enemy::IsTargetingPlayer()
{
	return m_bTargetingPlayer;
}