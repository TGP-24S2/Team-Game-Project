#ifndef __PLAYER_H__
#define __PLAYER_H__

// Local includes:
#include "vector2.h"
#include "entity.h"

#include <vector>

// Forward declarations:
class Renderer;
class InputSystem;
class Rectangle;

class Player : public Entity
{
	// Member methods:
public:
	Player();
	~Player();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);

	void CapSpeed();

	float GetX();
	float GetY();

	void SetAimAngle(float angle);
	void SetWeaponType(int weaponType);
	void SetCurrentAmmo(int ammo);
	void SetSpeedProfile(float accelScale, float decelScale, float speedScale);
	
	void DebugDraw();

protected:

private:
	void Decelerate();

	// Member data:
public:

protected:

private:
	float m_fAccelerationRate = 0.8f;
	float m_fAccelScale = 1.0f;

	float m_fDecelerationRate = 0.3f;
	float m_fDecelScale = 1.0f;

	float m_fMaxSpeed = 1000.0f;
	float m_fMaxSpeedScale = 1.0f;

	float m_fWallBounceDecay = 0.8f;
	float m_fInitialScale = 0.3f;
	float m_fAngle = 0.0f;

	int m_iWeaponType;
	int m_iWeaponAmmo;
};

#endif // __PLAYER_H__