#include "sceneFFgame.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inputsystem.h"

SceneFFGame::SceneFFGame()
{
}

SceneFFGame::~SceneFFGame()
{
}

bool SceneFFGame::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	m_pPlayerSprite = renderer.CreateSprite("sprites\\ball.png");
	m_pCursorSprite = renderer.CreateSprite("sprites\\ball.png");

	m_pPlayerSprite->SetScale(0.3f);
	m_pCursorSprite->SetScale(0.3f);

	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_position.x = SCREEN_WIDTH / 2;
	m_position.y = SCREEN_HEIGHT / 2;

	ComputeBounds(SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void SceneFFGame::Process(float deltaTime, InputSystem& inputSystem)
{
	//update timer
	m_fTimeSinceInput += deltaTime;

	//Player aim:
	m_cursorPosition = inputSystem.GetMousePosition();
	m_pCursorSprite->SetX(static_cast<int>(m_cursorPosition.x));
	m_pCursorSprite->SetY(static_cast<int>(m_cursorPosition.y));

	//Player self:
	ButtonState leftArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_LEFT));
	ButtonState rightArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_RIGHT));
	ButtonState upArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_UP));
	ButtonState downArrowState = (inputSystem.GetKeyState(SDL_SCANCODE_DOWN));

	//deceleration
	if (m_velocity.x > 0)
	{
		m_velocity.x -= m_fDecelerationRate * m_fSpeedScale;
		if (m_velocity.x < 0) //do not decelerate past 0
			m_velocity.x = 0;
	}
	else if (m_velocity.x < 0)
	{
		m_velocity.x += m_fDecelerationRate * m_fSpeedScale;
		if (m_velocity.x > 0) //do not decelerate past 0
			m_velocity.x = 0;
	}

	if (m_velocity.y > 0)
	{
		m_velocity.y -= m_fDecelerationRate * m_fSpeedScale;
		if (m_velocity.y < 0) //do not decelerate past 0
			m_velocity.y = 0;
	}
	else if (m_velocity.y < 0)
	{
		m_velocity.y += m_fDecelerationRate * m_fSpeedScale;
		if (m_velocity.y > 0) //do not decelerate past 0
			m_velocity.y = 0;
	}

	if (leftArrowState == BS_HELD)
	{
		m_velocity.x -= m_fAccelerationRate * m_fSpeedScale;
		m_fTimeSinceInput = 0;
	}

	if (rightArrowState == BS_HELD)
	{
		m_velocity.x += m_fAccelerationRate * m_fSpeedScale;
		m_fTimeSinceInput = 0;
	}

	if (upArrowState == BS_HELD)
	{
		m_velocity.y -= m_fAccelerationRate * m_fSpeedScale;
		m_fTimeSinceInput = 0;
	}

	if (downArrowState == BS_HELD)
	{
		m_velocity.y += m_fAccelerationRate * m_fSpeedScale;
		m_fTimeSinceInput = 0;
	}

	CapSpeed();

	//Game Logic:
	float ratio = 1.0f - (m_fTimeSinceInput / m_fPostMovementTimeBuffer);
	if (ratio < 0.0f)
	{
		ratio = 0.0f; //prevent negative values
	}
	m_fLocalDeltaTime = deltaTime * ratio;
	//m_fLocalDeltaTime = deltaTime;

	m_position += m_velocity * m_fLocalDeltaTime;
	m_pPlayerSprite->SetX(static_cast<int>(m_position.x));
	m_pPlayerSprite->SetY(static_cast<int>(m_position.y));
	m_pPlayerSprite->Process(m_fLocalDeltaTime);

	m_pCursorSprite->Process(m_fLocalDeltaTime);
}

void SceneFFGame::Draw(Renderer& renderer)
{
	m_pPlayerSprite->Draw(renderer);
	m_pCursorSprite->Draw(renderer);
}

void SceneFFGame::ComputeBounds(int width, int height)
{
	m_boundaryLow.x = (m_pPlayerSprite->GetWidth() / 2.0f);
	m_boundaryLow.y = (m_pPlayerSprite->GetHeight() / 2.0f);

	m_boundaryHigh.x = width - (m_pPlayerSprite->GetWidth() / 2.0f);
	m_boundaryHigh.y = height - (m_pPlayerSprite->GetHeight() / 2.0f);
}

void SceneFFGame::CapSpeed()
{
	if (m_velocity.x > m_fMaxSpeed)
	{
		m_velocity.x = m_fMaxSpeed;
	}
	else if (m_velocity.x < (0-m_fMaxSpeed)) {
		m_velocity.x = (0 - m_fMaxSpeed);
	}

	if (m_velocity.y > m_fMaxSpeed)
	{
		m_velocity.y = m_fMaxSpeed;
	}
	else if (m_velocity.y < (0 - m_fMaxSpeed)) {
		m_velocity.y = (0 - m_fMaxSpeed);
	}
}


void SceneFFGame::DebugDraw()
{
}
