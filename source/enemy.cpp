#include "enemy.h"

#include "inlinehelpers.h"
#include "renderer.h"
#include "animatedsprite.h"
#include "player.h"
#include "collision.h"

Enemy::Enemy(Player *pPlayer)
	: Entity()
	, m_iDamage(5)
	, m_fInitialScale(0.25f)
	, m_bAngry(false)
	, m_pPlayer(pPlayer)
{
	m_fSpeedScale /= 2; // enemy is half speed of player
}

Enemy::~Enemy()
{
}

void Enemy::Initialise(Renderer& renderer)
{
	Entity::Initialise(renderer, "sprites\\enemy.png", 307); //super()
	
	m_pSprite->SetScale(m_fInitialScale);

	if (GetRandomPercentage() < 0.5f)
	{
		m_bAngry = true;
	}
	else
	{
		m_bAngry = false;
		m_pSprite->SetFrameDuration(0.1f);
		m_pSprite->SetBlueTint(0.5f);
		m_pSprite->SetGreenTint(0.5f);
	}
}

void Enemy::Process(float deltaTime)
{
	Entity::Process(deltaTime); // super
	m_pSprite->Process(deltaTime);

	// make bot follow player
	float playerX = m_pPlayer->GetX();
	float playerY = m_pPlayer->GetY();
	float dx = playerX - m_position.x;
	float dy = playerY - m_position.y;
	bool canSeePlayer = !RaycastHits(dx, dy);
	if (m_bAngry && (canSeePlayer))
	{ // beeline to player
		const float velocitydeweight = 0.25f;
		const int botSpeed = 200;
		m_velocity.x = deltaTime * botSpeed * (dx + m_pPlayer->GetVelocity().x * velocitydeweight);
		m_velocity.y = deltaTime * botSpeed * (dy + m_pPlayer->GetVelocity().y * velocitydeweight);
		m_pSprite->SetFrameDuration(2.0f);
	}
	else
	{// otherwise wander aimlessly
		m_velocity.x += (float)GetRandom(-10, 10);
		m_velocity.y += (float)GetRandom(-10, 10);
		m_pSprite->SetFrameDuration(0.2f);
	}

	// denote size as health
	float scale = (float)m_iHealth / m_iMaxHealth * m_fInitialScale;
	m_pSprite->SetScale(scale);
	m_hitbox.setDimensions((float)m_pSprite->GetWidth(), (float)m_pSprite->GetHeight());
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
	m_bAngry = true;
}

void Enemy::SetToNotAngry()
{
	m_bAngry = false;
}

bool Enemy::IsTargetingPlayer()
{
	return m_bAngry;
}