#include "sceneFFgame.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inputsystem.h"
#include "ball.h"

SceneFFGame::SceneFFGame()
	: m_fLocalDeltaTime(0.0f)
	, m_fTimeSinceInput(0.0f)
	, m_pCursorSprite(nullptr)
	, m_pPlayerSprite(nullptr)
	, m_pTestBall(nullptr)
{
}

SceneFFGame::~SceneFFGame()
{
	delete m_pTestBall;
	delete m_pPlayerSprite;
	delete m_pCursorSprite;
}

bool SceneFFGame::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	m_pTestBall = new Ball();
	m_pTestBall->Initialise(renderer);
	m_pTestBall->SetGood();

	m_pPlayerSprite = renderer.CreateSprite("sprites\\ball.png");
	m_pCursorSprite = renderer.CreateSprite("sprites\\crosshair.png");

	m_pPlayerSprite->SetScale(0.3f);
	m_pCursorSprite->SetScale(0.05f);

	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_position.x = SCREEN_WIDTH / 2.0f;
	m_position.y = SCREEN_HEIGHT / 2.0f;

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
	ButtonState leftMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_A));
	ButtonState rightMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_D));
	ButtonState upMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_W));
	ButtonState downMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_S));

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

	if (leftMoveState == BS_HELD)
	{
		m_velocity.x -= m_fAccelerationRate * m_fSpeedScale;
		m_fTimeSinceInput = 0;
	}

	if (rightMoveState == BS_HELD)
	{
		m_velocity.x += m_fAccelerationRate * m_fSpeedScale;
		m_fTimeSinceInput = 0;
	}

	if (upMoveState == BS_HELD)
	{
		m_velocity.y -= m_fAccelerationRate * m_fSpeedScale;
		m_fTimeSinceInput = 0;
	}

	if (downMoveState == BS_HELD)
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

	if (m_position.x < m_boundaryLow.x) {
		m_position.x = m_boundaryLow.x;
		m_velocity.x *= -1;
		m_velocity.x *= m_fWallBounceDecay;
	}
	if (m_position.x > m_boundaryHigh.x) {
		m_position.x = m_boundaryHigh.x;
		m_velocity.x *= -1;
		m_velocity.x *= m_fWallBounceDecay;
	}
	if (m_position.y < m_boundaryLow.y) {
		m_position.y = m_boundaryLow.y;
		m_velocity.y *= -1;
		m_velocity.x *= m_fWallBounceDecay;
	}
	if (m_position.y > m_boundaryHigh.y) {
		m_position.y = m_boundaryHigh.y;
		m_velocity.y *= -1;
		m_velocity.x *= m_fWallBounceDecay;
	}
	m_position += m_velocity * m_fLocalDeltaTime;
	m_pPlayerSprite->SetX(static_cast<int>(m_position.x));
	m_pPlayerSprite->SetY(static_cast<int>(m_position.y));
	m_pPlayerSprite->Process(m_fLocalDeltaTime);

	m_pCursorSprite->Process(m_fLocalDeltaTime);

	m_pTestBall->Process(m_fLocalDeltaTime);
}

void SceneFFGame::Draw(Renderer& renderer)
{
	m_pPlayerSprite->Draw(renderer);
	m_pCursorSprite->Draw(renderer);
	m_pTestBall->Draw(renderer);
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
