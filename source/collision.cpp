#include "collision.h"

#include <corecrt_math_defines.h>
// Local includes:
#include "sprite.h"
#include "rectangle.h"
#include "entity.h"

bool Collision::CheckRectangleCollision(Rectangle r1, Rectangle r2)
{
	float r1Left = (float)(r1.x) - (r1.width / 2.0f);
	float r1Right = (float)(r1.x) + (r1.width / 2.0f);
	float r1Top = (float)(r1.y) - (r1.height / 2.0f);
	float r1Bottom = (float)(r1.y) + (r1.height / 2.0f);

	float r2Left = (float)(r2.x) - (r2.width / 2.0f);
	float r2Right = (float)(r2.x) + (r2.width / 2.0f);
	float r2Top = (float)(r2.y) - (r2.height / 2.0f);
	float r2Bottom = (float)(r2.y) + (r2.height / 2.0f);

	if (r1Right < r2Left) return false;
	if (r1Left > r2Right) return false;
	if (r1Bottom < r2Top) return false;
	if (r1Top > r2Bottom) return false;
	return true;
}

/// Checks if the first sprite is within the second sprite.
bool Collision::CheckSpriteCollision(Sprite* pSprite1, int size1, Sprite* pSprite2, int size2)
{
	float scale1 = pSprite1->GetScale() * size1;
	Rectangle r1 = Rectangle();
	r1.x = pSprite1->GetX() - scale1 / 2;
	r1.y = pSprite1->GetY() - scale1 / 2;
	r1.width = r1.height = scale1;

	float scale2 = pSprite2->GetScale() * size2;
	Rectangle r2 = Rectangle();
	r2.x = pSprite2->GetX() - scale2 / 2;
	r2.y = pSprite2->GetY() - scale2 / 2;
	r2.width = r2.height = scale2;

	return CheckRectangleCollision(r1, r2);
}

bool Collision::CheckBallCollision(Sprite* sprite1, Sprite* sprite2)
{
	int sprite1size = (int)sprite1->GetWidth() + 1;
	int sprite2size = (int)sprite2->GetWidth() + 1;
	return CheckSpriteCollision(sprite1, sprite1size, sprite2, sprite2size);
}
