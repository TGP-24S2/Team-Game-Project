#pragma once

// Local includes:
#include "rectangle.h"
#include "vector2.h"
#include "player.h"

// Library includes:
#include <vector>
#include <string>

// Forward declarations:
class Renderer;
class Sprite;
class PropTemplate;

class Prop
{
	// Member methods:
public:
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void SetTemplate(PropTemplate* propTemplate);

	void ChangeSprite();
	void setColor(float newR, float newG, float newB);
	void setAlpha(float newA);

	static void setPlayer(Player* player);
	static void setEnemies(Enemy** m_lpEnemies);
private:

protected:

	// Member data:
public:
	Renderer* m_pRenderer;

	Sprite* m_pSprite;
	PropTemplate* m_pTemplate;
	Vector2 m_position;
	Rectangle m_hitbox;
	static std::vector<std::string> m_spritePaths;

	float r, g, b; // Color components: Red, Green, Blue
	float alpha;

	static Player* m_pPlayer;
	static Enemy** m_lpEnemies

private:

protected:

};

