// This include:
#include "player.h"

// Local includes:
#include "renderer.h"
#include "animatedsprite.h"
#include "inputsystem.h"

#include "imgui.h"

#include <iostream>

Player::Player()
	: m_iWeaponType(0)
{
}

Player::~Player()
{
}

bool Player::Initialise(Renderer& renderer)
{
	Entity::Initialise(renderer, "sprites\\player.png", 300); // super();

	m_pSprite->SetScale(m_fInitialScale);
	m_hitbox.setDimensions((float)m_pSprite->GetWidth(), (float)m_pSprite->GetHeight());

	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();

	ComputeBounds(SCREEN_WIDTH, SCREEN_HEIGHT);

	RandomStartPlace();

	return true;
}

void Player::Process(float deltaTime, InputSystem& inputSystem)
{
	Entity::Process(deltaTime); // super()
	m_pSprite->Process(deltaTime);

	// denote size as health
	float scale = (float)m_iHealth / m_iMaxHealth * m_fInitialScale;
	m_pSprite->SetScale(scale);
	if (scale < 0.01f)
		Kill(); // kill if too small

	//Player self:
	ButtonState leftMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_A));
	ButtonState rightMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_D));
	ButtonState upMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_W));
	ButtonState downMoveState = (inputSystem.GetKeyState(SDL_SCANCODE_S));
	ButtonState mouse1State = (inputSystem.GetMouseButtonState(1));

	Decelerate();

	// Player input:
	float mvRate = m_fAccelerationRate * m_fAccelScale;
	if (leftMoveState == BS_HELD)
		m_velocity.x -= mvRate;
	if (rightMoveState == BS_HELD)
		m_velocity.x += mvRate;
	if (upMoveState == BS_HELD)
		m_velocity.y -= mvRate;
	if (downMoveState == BS_HELD)
		m_velocity.y += mvRate;

	//gun recoil //need to change to detect melee to not have knockback for melee.
	if (mouse1State == BS_PRESSED) {
		if (m_iWeaponType == 0) {
			m_velocity.x -= mvRate * 200 * cosf(m_fAngle);//change this
			m_velocity.y -= mvRate * 200 * sinf(m_fAngle);
		}
	}

	CapSpeed();
}

void Player::Draw(Renderer& renderer)
{
	Entity::Draw(renderer); //super()
}

void Player::Decelerate()
{
	float decelRate = m_fDecelerationRate * m_fDecelScale;
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
}

void Player::CapSpeed()
{
	float scaledMaxSpeed = m_fMaxSpeed * m_fMaxSpeedScale;
	if (m_velocity.x > scaledMaxSpeed)	{
		m_velocity.x = scaledMaxSpeed;
	}
	else if (m_velocity.x < (0 - scaledMaxSpeed)) {
		m_velocity.x = (0 - scaledMaxSpeed);
	}

	if (m_velocity.y > scaledMaxSpeed)	{
		m_velocity.y = scaledMaxSpeed;
	}
	else if (m_velocity.y < (0 - scaledMaxSpeed)) {
		m_velocity.y = (0 - scaledMaxSpeed);
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

void Player::SetWeaponType(int weaponType) {
	m_iWeaponType = weaponType;
}

void Player::SetSpeedProfile(float accelScale, float decelScale, float speedScale)
{
	m_fAccelScale = accelScale;
	m_fDecelScale = decelScale;
	m_fMaxSpeedScale = speedScale;
}

void Player::DebugDraw()
{
	ImGui::Text("Player Settings");
	ImGui::Text("Position: %f, %f", m_position.x, m_position.y);
	ImGui::Text("Velocity: %f, %f", m_velocity.x, m_velocity.y);
}
