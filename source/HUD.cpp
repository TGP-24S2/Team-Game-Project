#include "HUD.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "player.h"

HUD::HUD()
{
}

HUD::~HUD()
{
}

bool HUD::Initialise(Renderer& renderer)
{
	m_pHealthBar = renderer.CreateAnimatedSprite("sprites\\health.png");
	m_pHealthBar->SetupFrames(102, 4);
	m_pHealthBar->SetFrameDuration(0.1f);
	m_pHealthBar->SetLooping(false);

	m_pHealthBar->SetScale(4.0f);
	m_pHealthBar->SetX((float)renderer.GetWidth() / 2.0f);
	m_pHealthBar->SetY((float)renderer.GetHeight() - m_pHealthBar->GetHeight());

	return true;
}

void HUD::Process(float deltaTime)
{
	if (m_pPlayer != nullptr)
	{
		UpdateHealth();
	}
}

void HUD::Draw(Renderer& renderer)
{
	m_pHealthBar->Draw(renderer);
}

void HUD::DebugDraw()
{
}

void HUD::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

void HUD::UpdateHealth()
{
	// Get an Integer % representation of health (0-100)
	int healthPercent = (int) (m_pPlayer->GetHealthRatio() * 100);
	m_pHealthBar->SetFrame(healthPercent);
}
