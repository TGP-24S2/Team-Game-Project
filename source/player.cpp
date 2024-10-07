// This include:
#include "player.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inputsystem.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Initialise(Renderer& renderer)
{
	m_pPlayerSprite = renderer.CreateSprite("sprites\\ball.png");
	m_pPlayerSprite->SetScale(0.3f);

	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_position.x = SCREEN_WIDTH / 2.0f;
	m_position.y = SCREEN_HEIGHT / 2.0f;

	ComputeBounds(SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void Player::Process(float deltaTime, InputSystem& inputSystem)
{
	//Player self:
	ButtonState leftMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_A));
	ButtonState rightMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_D));
	ButtonState upMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_W));
	ButtonState downMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_S));
	ButtonState mouse1State = (inputSystem.GetMouseButtonState(1));

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

	// Player input:
	if (leftMoveState == BS_HELD)
	{
		m_velocity.x -= m_fAccelerationRate * m_fSpeedScale;
	}

	if (rightMoveState == BS_HELD)
	{
		m_velocity.x += m_fAccelerationRate * m_fSpeedScale;
	}

	if (upMoveState == BS_HELD)
	{
		m_velocity.y -= m_fAccelerationRate * m_fSpeedScale;
	}

	if (downMoveState == BS_HELD)
	{
		m_velocity.y += m_fAccelerationRate * m_fSpeedScale;
	}

	CapSpeed();


	// Bounds checks:
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
	m_position += m_velocity * deltaTime;
	m_pPlayerSprite->SetX(static_cast<int>(m_position.x));
	m_pPlayerSprite->SetY(static_cast<int>(m_position.y));
	m_pPlayerSprite->Process(deltaTime);
}

void Player::Draw(Renderer& renderer)
{
	m_pPlayerSprite->Draw(renderer);
}

void Player::ComputeBounds(int width, int height)
{
	m_boundaryLow.x = (m_pPlayerSprite->GetWidth() / 2.0f);
	m_boundaryLow.y = (m_pPlayerSprite->GetHeight() / 2.0f);

	m_boundaryHigh.x = width - (m_pPlayerSprite->GetWidth() / 2.0f);
	m_boundaryHigh.y = height - (m_pPlayerSprite->GetHeight() / 2.0f);
}

void Player::CapSpeed()
{
	if (m_velocity.x > m_fMaxSpeed)	{
		m_velocity.x = m_fMaxSpeed;
	}
	else if (m_velocity.x < (0 - m_fMaxSpeed)) {
		m_velocity.x = (0 - m_fMaxSpeed);
	}

	if (m_velocity.y > m_fMaxSpeed)	{
		m_velocity.y = m_fMaxSpeed;
	}
	else if (m_velocity.y < (0 - m_fMaxSpeed)) {
		m_velocity.y = (0 - m_fMaxSpeed);
	}
}

float Player::GetX() {
	return m_position.x;
}
float Player::GetY() {
	return m_position.y;
}