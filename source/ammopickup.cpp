#include "ammopickup.h"

#include "inlinehelpers.h"
#include "sprite.h"
#include "renderer.h"
#include "weapon.h"

AmmoPickup::AmmoPickup(Renderer& renderer, int weaponType)
	: m_pSprite(nullptr)
	, m_iWeaponType(weaponType)
	, m_iAmmoCount(GetRandom(0,5))
{
	m_pSprite = renderer.CreateSprite("sprites\\bullet.png");

	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();
	m_pSprite->SetScale(0.25f);
	m_pSprite->SetX(GetRandom(0, SCREEN_WIDTH));
	m_pSprite->SetY(GetRandom(0, SCREEN_HEIGHT));
}

AmmoPickup::~AmmoPickup()
{}

Sprite* AmmoPickup::GetSprite()
{
	return m_pSprite;
}
