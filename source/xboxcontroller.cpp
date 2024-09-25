// COMP710 GP Framework 2022

// This include:
#include "xboxcontroller.h"

// Local includes: 
#include "renderer.h" 
#include "logmanager.h"

// Library includes: 
#include <cassert>

XboxController::XboxController()
	: m_pController(nullptr)
	, m_bConnected(false)
	, m_fLeftTrigger(0)
	, m_fRightTrigger(0)
	, m_currentButtons("")
	, m_previousButtons("")
{

}

XboxController::~XboxController()
{
}
bool
XboxController::Initialise(int controllerIndex)
{
	for (int k = 0; k < SDL_CONTROLLER_BUTTON_MAX; ++k)
	{
		m_previousButtons[k] = 0;
		m_currentButtons[k] = 0;
	}
	m_pController = SDL_GameControllerOpen(controllerIndex); 
	m_bConnected = m_pController != 0;

	return true;
}

void XboxController::ProcessInput()
{
	// Store previous input state:
	for (int k = 0; k < SDL_CONTROLLER_BUTTON_MAX; ++k)
	{
		m_previousButtons[k] = m_currentButtons[k];
	}

	// Get new input state:
	for (int k = 0; k < SDL_CONTROLLER_BUTTON_MAX; ++k)
	{
		m_currentButtons[k] = SDL_GameControllerGetButton(m_pController, SDL_GameControllerButton(k));
	}

	m_leftStick.x = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_LEFTX); 
	m_leftStick.y = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_LEFTY);

	m_rightStick.x = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_RIGHTX); 
	m_rightStick.y = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_RIGHTY);

	m_fLeftTrigger = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_TRIGGERLEFT); 
	m_fRightTrigger = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
}
ButtonState XboxController::GetButtonState(SDL_GameControllerButton button)
{
	if (m_previousButtons[button] == 0)
	{
		if (m_currentButtons[button] == 0)
		{
			return BS_NEUTRAL;
		}
		else
		{
			return BS_PRESSED;
		}
	}
	else
	{
		if (m_currentButtons[button] == 0)
		{
			return BS_RELEASED;
		}
		else
		{
			return BS_HELD;
		}
	}
}
float
XboxController::GetLeftTrigger() const
{
	return m_fLeftTrigger;
}

float
XboxController::GetRightTrigger() const
{
	return m_fRightTrigger;
}

const Vector2& XboxController::GetLeftStick() const
{
	return m_leftStick;
}

const Vector2& XboxController::GetRightStick() const
{
	return m_rightStick;
}
