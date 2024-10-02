#include "Enemy.h"

#include "inlinehelpers.h"
#include "renderer.h"
#include "animatedsprite.h"

Enemy::Enemy()
	: Entity()
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

void Enemy::Initialise(Renderer& renderer, const char* spritePath)
{
	Entity::Initialise(renderer, spritePath); //super()
	
	m_pSprite->SetScale(0.5f);
	// set bad
	m_pSprite->SetRedTint(1.0f);
	m_pSprite->SetBlueTint(0.0f);
	m_pSprite->SetGreenTint(0.0f);

	const int EDGE_LIMIT = m_pSprite->GetWidth();
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_position.x = static_cast<float>(GetRandom(EDGE_LIMIT, SCREEN_WIDTH - EDGE_LIMIT));
	m_position.y = static_cast<float>(GetRandom(EDGE_LIMIT, SCREEN_HEIGHT - EDGE_LIMIT));

}

void Enemy::Process(float deltaTime)
{
	Entity::Process(deltaTime);

	m_velocity.x = GetRandomPercentage();
	m_velocity.y = GetRandomPercentage();
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