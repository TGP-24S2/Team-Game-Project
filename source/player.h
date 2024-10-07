#ifndef __PLAYER_H__
#define __PLAYER_H__

// Local includes:
#include "vector2.h"

// Forward declarations:
class Sprite;
class Renderer;
class InputSystem;

class Player
{
	// Member methods:
public:
	Player();
	~Player();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void Draw(Renderer& renderer);

	void ComputeBounds(int width, int height);
	void CapSpeed();

	float GetX();
	float GetY();

protected:

private:


	// Member data:

public:

protected:

private:
	Sprite* m_pPlayerSprite;

	Vector2 m_position;
	Vector2 m_velocity;

	float m_fAccelerationRate = 3.0f;
	float m_fDecelerationRate = 0.3f;
	float m_fSpeedScale = 1.0f;
	float m_fMaxSpeed = 1000.0f;
	float m_fWallBounceDecay = 0.8f;

	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
};

#endif // __PLAYER_H__