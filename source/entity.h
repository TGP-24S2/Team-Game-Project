// COMP710 GP Framework 2022 
#ifndef __ENTITY_H 
#define __ENTITY_H 

// Local includes:
#include "entity.h" 
#include "vector2.h"

// Forward declarations:
class Renderer; 
class AnimatedSprite;

// Class declaration:
class Entity
{
	// Member methods: 
public:
	Entity();
	~Entity();

	bool Initialise(Renderer& renderer, const char* spritePath); 
	void Process(float deltaTime);
	void Draw(Renderer& renderer);
	AnimatedSprite* GetSprite();
	float GetRadius();
	void SetPosition(int x, int y);
	Vector2& GetPosition(); 
	Vector2& GetVelocity();
	void SetVelocity(int x, int y);
	bool IsCollidingWith(Entity* toCheck); 
	bool IsAlive();
	void Kill();
	void ComputeBounds(int width, int height);
	void CheckBounds();
protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	// Member data: 
public:

protected:
	AnimatedSprite* m_pSprite; 
	Vector2 m_position; 
	Vector2 m_velocity; 
	bool m_bAlive;
	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;

private:

};

#endif //   ENTITY_H 
