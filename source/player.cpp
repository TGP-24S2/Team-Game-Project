// This include:
#include "player.h"

// Local includes:
#include "renderer.h"
#include "animatedsprite.h"
#include "inputsystem.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Initialise(Renderer& renderer)
{
	Entity::Initialise(renderer, "sprites\\ball.png"); // super();

	m_pSprite->SetScale(m_fInitialScale);

	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	m_position.x = 10;
	m_position.y = 10;

	ComputeBounds(SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void Player::Process(float deltaTime, InputSystem& inputSystem)
{
	Entity::Process(deltaTime); // super()

	m_pSprite->SetScale((float) m_iHealth / m_iMaxHealth * m_fInitialScale);

	//Player self:
	ButtonState leftMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_A));
	ButtonState rightMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_D));
	ButtonState upMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_W));
	ButtonState downMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_S));
	ButtonState mouse1State = (inputSystem.GetMouseButtonState(1));

	//deceleration
	float decelRate = m_fDecelerationRate * m_fSpeedScale;
	if (m_velocity.x > 0)
	{
		m_velocity.x -= decelRate;
		if (m_velocity.x < 0) //do not decelerate past 0
			m_velocity.x = 0;
	}
	else if (m_velocity.x < 0)
	{
		m_velocity.x += decelRate;
		if (m_velocity.x > 0) //do not decelerate past 0
			m_velocity.x = 0;
	}
	if (m_velocity.y > 0)
	{
		m_velocity.y -= decelRate;
		if (m_velocity.y < 0) //do not decelerate past 0
			m_velocity.y = 0;
	}
	else if (m_velocity.y < 0)
	{
		m_velocity.y += decelRate;
		if (m_velocity.y > 0) //do not decelerate past 0
			m_velocity.y = 0;
	}

	// Player input:
	float mvRate = m_fAccelerationRate * m_fSpeedScale;
	if (leftMoveState == BS_HELD)
		m_velocity.x -= mvRate;
	if (rightMoveState == BS_HELD)
		m_velocity.x += mvRate;
	if (upMoveState == BS_HELD)
		m_velocity.y -= mvRate;
	if (downMoveState == BS_HELD)
		m_velocity.y += mvRate;

	//gun recoil
	if (mouse1State == BS_PRESSED) {
		m_velocity.x -= mvRate * 200 * cos(m_fAngle);//change this
		m_velocity.y -= mvRate * 200 * sin(m_fAngle);
	}

	CapSpeed();
}

void Player::Draw(Renderer& renderer)
{
	Entity::Draw(renderer); //super()
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

void Player::SetAimAngle(float angle) {
	m_fAngle = angle;
}