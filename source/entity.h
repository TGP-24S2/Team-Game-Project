// COMP710 GP Framework 2022 
#ifndef __ENTITY_H 
#define __ENTITY_H 

// Local includes:
#include "entity.h" 
#include "vector2.h"
#include "rectangle.h"

#include <vector>

// Forward declarations:
class Renderer; 
class AnimatedSprite;
class Rectangle;

// Class declaration:
class Entity
{
	// Member methods: 
public:
	Entity();
	~Entity();

	static void SetEnvHitboxes(std::vector<Rectangle*>);

	bool Initialise(Renderer& renderer, const char* spritePath, int spriteSize); 
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	AnimatedSprite* GetSprite();
	void SetPosition(int x, int y);
	Vector2& GetPosition(); 
	Vector2& GetVelocity();
	void SetVelocity(int x, int y);
	void SetSpeedScale(float scale);
	int GetHealth();
	int GetMaxHealth();
	float GetHealthRatio();
	bool RaycastHits(float dx, float dy);
	bool IsCollidingWith(Entity* toCheck);
	bool IsAlive();
	void Kill();
	void TakeDamage(int);
	void ComputeBounds(int width, int height);
	void CheckBounds();
	bool IsInsideWall(Vector2);
	void RandomStartPlace();

	Rectangle GetHitbox();

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	// Member data: 
public:
	static std::vector<Rectangle*> s_vpEnvHitboxes;

protected:
	AnimatedSprite* m_pSprite; 

	int m_iHealth;
	int m_iMaxHealth;
	bool m_bAlive;

	Rectangle m_hitbox;
	Vector2 m_position; 
	Vector2 m_velocity; 
	float m_fSpeedScale = 1.0f;

	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;

private:

};

#endif //   ENTITY_H 
