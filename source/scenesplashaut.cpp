// COMP710 GP Framework 2022
// This include:
#include "scenesplashaut.h"

// Local includes:
#include "renderer.h" 
#include "sprite.h"
#include "imgui.h"
#include "soundsystem.h"

// Library includes:
#include <cassert>
#include "game.h"

SceneSplashAUT::SceneSplashAUT()
	: m_pSplash(nullptr)
	, m_pText(nullptr)
	, m_alpha(0.0f)
	, m_fadeSpeed(0.25f)
	, m_fadeIn(true)
{
}

SceneSplashAUT::~SceneSplashAUT()
{
	delete m_pSplash;
	m_pSplash = nullptr;
	delete m_pText;
	m_pText = nullptr;
}
bool
SceneSplashAUT::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	m_pSplash = renderer.CreateSprite("sprites\\autlogo.png");

	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_pSplash->SetX(SCREEN_WIDTH / 2);
	m_pSplash->SetY(SCREEN_HEIGHT / 2);


	// Load static text textures into the Texture Manager... 
	const char* checkerBoardText = "FreezeFrame";
	renderer.CreateStaticText(checkerBoardText, 60);

	// Generate sprites that use the static text textures... 
	m_pText = renderer.CreateSprite(checkerBoardText);

	m_pText->SetX(SCREEN_WIDTH / 2);
	m_pText->SetY((SCREEN_HEIGHT / 2) + (m_pSplash->GetHeight() / 2) + (m_pText->GetHeight()));

	return true;
}
void
SceneSplashAUT::Process(float deltaTime, InputSystem& inputSystem)
{
	if (m_fadeIn) {
		m_alpha += m_fadeSpeed * deltaTime;
		if (m_alpha >= 1.0f) {
			m_fadeIn = false;
		}
		m_pSplash->SetAlpha(m_alpha);
	}
	if (!m_fadeIn) {
		m_alpha -= m_fadeSpeed * deltaTime;
		m_pSplash->SetAlpha(m_alpha);
	}
	if (m_alpha <= 0.0f) {
		Game::GetInstance().ChangeScene(1);
	}
	
	m_pSplash->Process(deltaTime);

	m_pText->Process(deltaTime);
}

void
SceneSplashAUT::Draw(Renderer& renderer)
{
	m_pSplash->Draw(renderer);
	m_pText->Draw(renderer);
}

void SceneSplashAUT::DebugDraw()
{
	ImGui::Text("Scene: AUT Splash Screen");
	ImGui::SliderFloat("Fade speed", &m_fadeSpeed, 0.0f, 1.0f, "%.3f");
	float scale = m_pSplash->GetScale();
	ImGui::SliderFloat("Demo scale", &scale, 0.0f, 1.0f, "%.3f");
	m_pSplash->SetScale(scale);

	int position[2];
	position[0] = m_pSplash->GetX();
	position[1] = m_pSplash->GetY();
	ImGui::InputInt2("Demo position", position);
	m_pSplash->SetX(position[0]);
	m_pSplash->SetY(position[1]);
	float tint[4];
	tint[0] = m_pSplash->GetRedTint();
	tint[1] = m_pSplash->GetGreenTint();
	tint[2] = m_pSplash->GetBlueTint();
	tint[3] = m_pSplash->GetAlpha();
	ImGui::ColorEdit4("Demo tint", tint);
	m_pSplash->SetRedTint(tint[0]);
	m_pSplash->SetGreenTint(tint[1]);
	m_pSplash->SetBlueTint(tint[2]);
	m_pSplash->SetAlpha(tint[3]);
	ImGui::Checkbox("Fade In", &m_fadeIn);
}
