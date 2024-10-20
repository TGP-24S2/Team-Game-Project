#include "HUD.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "player.h"

#include <iostream>

HUD::HUD()
	: m_eCurrentWeaponType(MELEE)
	, m_pAmmoCross(nullptr)
	, m_pHealthBar(nullptr)
	, m_pLevelText(nullptr)
	, m_pMagazineCapacity{0,0,0}
	, m_pMagazineCount{0,0,0}
	, m_pPlayer(nullptr)
	, m_pRenderer(nullptr)
	, m_pWeapon(nullptr)
	, m_pWeaponIcon(nullptr)
{
}

HUD::~HUD()
{
}

bool HUD::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

	m_pHealthBar = renderer.CreateAnimatedSprite("sprites\\health.png");
	m_pHealthBar->SetupFrames(102, 4);
	m_pHealthBar->SetFrameDuration(0.1f);
	m_pHealthBar->SetLooping(false);

	m_pHealthBar->SetScale(4.0f);
	m_pHealthBar->SetX(renderer.GetWidth() / 2);
	m_pHealthBar->SetY((int)(renderer.GetHeight() - m_pHealthBar->GetHeight() * 1.5f));


	//initialise text sprites
	for (int i = 0; i < 10; i++)
	{
		renderer.CreateStaticText(std::to_string(i).c_str(), 30);
	}

	renderer.CreateStaticText(" x ", 30);
	m_pAmmoCross = renderer.CreateSprite(" x ");

	return true;
}

void HUD::Process(float deltaTime)
{
	if (m_pPlayer != nullptr)
	{
		UpdateHealth();
	}
	if (m_pWeapon != nullptr)
	{
		UpdateAmmo();
	}
	UpdateLevels();
}

void HUD::Draw(Renderer& renderer)
{
	m_pHealthBar->Draw(renderer);
	if (m_pWeapon != nullptr)
	{
		m_pWeaponIcon->Draw(renderer);

		for (int i = 0; i < 3; i++)
		{
			if (m_pMagazineCount[i] == nullptr) continue;

			m_pMagazineCount[i]->Draw(renderer);
		}
		m_pAmmoCross->Draw(renderer);
		for (int i = 0; i < 3; i++)
		{
			if (m_pMagazineCapacity[i] == nullptr) continue;

			m_pMagazineCapacity[i]->Draw(renderer);
		}
	}
	if (m_pLevelText != nullptr) {
		m_pLevelText->Draw(renderer);
	}
}

void HUD::DebugDraw()
{
}

void HUD::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

void HUD::SetLevelGoal(int level)
{
	m_iLevelGoal = level;
}

void HUD::ProgressOneLevel()
{
	m_iCurrentLevels++;
}

void HUD::ResetLevelProgress()
{
	m_iCurrentLevels = 0;
}

void HUD::UpdateWeapon(Weapon* weapon)
{
	m_pWeapon = weapon;
	m_pWeaponIcon = m_pWeapon->GetIconSprite();
	m_eCurrentWeaponType = m_pWeapon->GetWeaponType();
	UpdateAmmo();
}

void HUD::UpdateLevels()
{
	std::string text = std::to_string(m_iCurrentLevels) + " / " + std::to_string(m_iLevelGoal);
	m_pRenderer->CreateStaticText(text.c_str(), 30);
	m_pLevelText = m_pRenderer->CreateSprite(text.c_str());
	m_pLevelText->SetY(m_pHealthBar->GetY());
	m_pLevelText->SetX(m_pRenderer->GetWidth() - ((m_pLevelText->GetWidth() / 2) + 10 /*extra offset from edge*/));
}

void HUD::UpdateHealth()
{
	// Get an Integer % representation of health (0-100)
	int healthPercent = (int) (m_pPlayer->GetHealthRatio() * 100);
	m_pHealthBar->SetFrame(healthPercent);
}

void HUD::UpdateAmmo()
{
	int y = m_pHealthBar->GetY();
	if (m_eCurrentWeaponType == MELEE)
	{
		m_pWeaponIcon->SetAngle(270.0f);
		m_pWeaponIcon->SetX(0 + m_pWeaponIcon->GetHeight());
		m_pWeaponIcon->SetY(y);

		for (int i = 0; i < 3; i++)
		{
			m_pMagazineCapacity[i] = nullptr;
			m_pAmmoCross->SetAlpha(0.0f);
			m_pMagazineCount[i] = nullptr;
		}
	}
	else
	{
		m_pAmmoCross->SetAlpha(1.0f);
		m_pWeaponIcon->SetX(0 + m_pWeaponIcon->GetWidth());
		m_pWeaponIcon->SetAngle(0);
		m_pWeaponIcon->SetY(y);

		int magazineCount = m_pWeapon->GetAmmoCount();

		int hundreds = (magazineCount / 100) % 10;
		int tens = (magazineCount / 10) % 10;
		int ones = magazineCount % 10;

		m_pMagazineCount[0] = (hundreds == 0) ? nullptr : m_pRenderer->CreateSprite(std::to_string(hundreds).c_str());
		m_pMagazineCount[1] = m_pRenderer->CreateSprite(std::to_string(tens).c_str());
		m_pMagazineCount[2] = m_pRenderer->CreateSprite(std::to_string(ones).c_str());

		for (int i = 0; i < 3; i++)
		{
			if (m_pMagazineCount[i] == nullptr) continue;

			m_pMagazineCount[i]->SetX(m_pWeaponIcon->GetX() + m_pWeaponIcon->GetWidth() + (i * 15));
			m_pMagazineCount[i]->SetY(y);
		}

		m_pAmmoCross->SetX(m_pMagazineCount[2]->GetX() + (m_pMagazineCount[2]->GetWidth() * 2));
		m_pAmmoCross->SetY(y);

		int reserveMagazines = m_pWeapon->GetMagCount();

		hundreds = (reserveMagazines / 100) % 10;
		tens = (reserveMagazines / 10) % 10;
		ones = reserveMagazines % 10;

		m_pMagazineCapacity[0] = (hundreds == 0) ? nullptr : m_pRenderer->CreateSprite(std::to_string(hundreds).c_str());
		m_pMagazineCapacity[1] = m_pRenderer->CreateSprite(std::to_string(tens).c_str());
		m_pMagazineCapacity[2] = m_pRenderer->CreateSprite(std::to_string(ones).c_str());

		for (int i = 0; i < 3; i++)
		{
			if (m_pMagazineCapacity[i] == nullptr) continue;

			m_pMagazineCapacity[i]->SetX(m_pAmmoCross->GetX() + m_pAmmoCross->GetWidth() + (i * 15));
			m_pMagazineCapacity[i]->SetY(y);
		}
	}
}
