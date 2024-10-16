#ifndef __COLLISION_H__
#define __COLLISION_H__
// forward declarations
class Sprite;
class Rectangle;
class Vector2;

class Collision
{
public:
	static bool CheckRectangleCollision(Rectangle, Rectangle);
	static bool CheckPointInRectangle(Vector2, Rectangle);
	static bool CheckSpriteCollision(Sprite*, Sprite*);
};
#endif // __COLLISION_H__
