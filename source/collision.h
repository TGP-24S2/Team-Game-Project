#ifndef __COLLISION_H__
#define __COLLISION_H__
// forward declarations
class Sprite;
class Rectangle;

class Collision
{
public:
	static bool CheckRectangleCollision(Rectangle, Rectangle);
	static bool CheckSpriteCollision(Sprite*, int baseSize1, Sprite*, int baseSize2);
	static bool CheckBallCollision(Sprite*, Sprite*);
};
#endif // __COLLISION_H__
