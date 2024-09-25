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
	bool IsAlive() const;
	void SetDead();
	float GetRadius();
	void SetPosition(int x, int y);

	Vector2& GetPosition(); 
	Vector2& GetVelocity();
	void SetVelocity(int x, int y);
	bool IsCollidingWith(Entity* toCheck); 
	AnimatedSprite* GetSprite();
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

private:

};

#endif //   ENTITY_H 
