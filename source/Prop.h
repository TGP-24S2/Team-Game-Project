#pragma once

// Local includes:
#include "rectangle.h"
#include "vector2.h"
#include "player.h"
#include "enemy.h"

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
	void UpdateColor();

	void ComputeBounds();
	void Spawn();

	static void setPlayer(Player* player);
	static void setEnemies(std::vector<Enemy*> m_vpEnemies);
private:

protected:

	// Member data:
public:
	Renderer* m_pRenderer;
	bool m_bIsAlive = false;

	Sprite* m_pSprite;
	PropTemplate* m_pTemplate;
	Vector2 m_position;
	Rectangle m_hitbox;
	static std::vector<std::string> m_spritePaths;

	float r, g, b; // Color components: Red, Green, Blue
	float alpha;

	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
	static Player* m_pPlayer;
	static std::vector<Enemy*> m_vpEnemies;

private:

protected:

};

