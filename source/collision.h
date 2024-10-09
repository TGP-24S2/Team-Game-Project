#ifndef __COLLISION_H__
#define __COLLISION_H__
// forward declarations
class Sprite;

class Rectangle
{
public:
	int x;
	int y;
	float w;
	float h;
};

class Collision
{
public:
	static bool CheckRectanglesColliding(Rectangle, Rectangle);
	static bool CheckSizedSpritesColliding(Sprite*, int baseSize1, Sprite*, int baseSize2);
};
#endif // __COLLISION_H__
