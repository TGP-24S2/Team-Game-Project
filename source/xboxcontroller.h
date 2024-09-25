// COMP710 GP Framework 2022 
#ifndef __XBOXCONTROLLER_H  
#define __XBOXCONTROLLER_H 

// Local includes:
#include "inputsystem.h" 
#include "vector2.h"

// Library includes:
#include <SDL.h>

// Class declaration:
class XboxController
{
	// Member methods: 
public:
	XboxController();
	~XboxController();

	bool Initialise(int controllerIndex); 
	void ProcessInput();

	ButtonState GetButtonState(SDL_GameControllerButton button); 
	float GetLeftTrigger() const;
	float GetRightTrigger() const; 
	const Vector2& GetLeftStick() const;
	const Vector2& GetRightStick() const;
protected:

private:
	XboxController(const XboxController& xboxcontroller); 
	XboxController& operator=(const XboxController& xboxcontroller);

	// Member data: 
public:

protected:
	unsigned char m_previousButtons[SDL_CONTROLLER_BUTTON_MAX]; 
	unsigned char m_currentButtons[SDL_CONTROLLER_BUTTON_MAX]; 
	SDL_GameController* m_pController;
	bool m_bConnected;

	Vector2 m_leftStick; 
	Vector2 m_rightStick; 
	float m_fLeftTrigger; 
	float m_fRightTrigger;

private:

};

#endif //   XBOXCONTROLLER_H 
