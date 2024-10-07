#pragma once

// Library includes:
#include <vector>

#ifndef __HUD_H__
#define __HUD_H__

//Forward declarations:
class Renderer;
class Sprite;
class AnimatedSprite;

class HUD
{
	// Member methods:
public:
	HUD();
	~HUD();

	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void DebugDraw();

protected:

private:

	// Member data:
public:

protected:

private:


};

#endif // __HUD_H__