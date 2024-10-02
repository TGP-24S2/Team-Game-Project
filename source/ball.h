#pragma once
// COMP710 GP Framework 2022
#ifndef __BALL_H__
#define __BALL_H__ 

// Local includes:
#include "vector2.h"
#include "entity.h"

// Forward declarations:
class Renderer;

// Class declaration:
class Ball : public Entity
{
	// Member methods:
public:
	Ball();
	~Ball();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void RandomiseColour();
	void RandomiseSize();

	Vector2& Position();

	virtual void DebugDraw();

	void SetAsPlayer();
	void SetGood();
	void SetBad();
	void Shrink();
	void Enlarge();
	float GetRadius();
	void SetPosition(int, int);
	void Kill();
	bool IsAlive() const;

protected:
	void ComputeBounds(int width, int height);

private:
	Ball(const Ball& ball);
	Ball& operator=(const Ball& ball);

	// Member data:
public:

protected:
	Vector2 m_position;
	Vector2 m_velocity;

	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;

private:

};

#endif //__BALL_H__ 
