#include "collision.h"

// Local includes:
#include "sprite.h"

bool Collision::CheckRectanglesColliding(Rectangle r1, Rectangle r2)
{
	float r1Left = (float)(r1.x) - (r1.w / 2.0f);
	float r1Right = (float)(r1.x) + (r1.w / 2.0f);
	float r1Top = (float)(r1.y) - (r1.h / 2.0f);
	float r1Bottom = (float)(r1.y) + (r1.h / 2.0f);

	float r2Left = (float)(r2.x) - (r2.w / 2.0f);
	float r2Right = (float)(r2.x) + (r2.w / 2.0f);
	float r2Top = (float)(r2.y) - (r2.h / 2.0f);
	float r2Bottom = (float)(r2.y) + (r2.h / 2.0f);

	if (r1Right < r2Left) return false;
	if (r1Left > r2Right) return false;
	if (r1Bottom < r2Top) return false;
	if (r1Top > r2Bottom) return false;

	else
	return true;
}

/// Checks if the first sprite is within the second sprite.
bool Collision::CheckSizedSpritesColliding(Sprite* pSprite1, int size1, Sprite* pSprite2, int size2)
{
	float scale1 = pSprite1->GetScale() * size1;
	Rectangle r1 = Rectangle();
	r1.x = pSprite1->GetX() - (int)scale1 / 2;
	r1.y = pSprite1->GetY() - (int)scale1 / 2;
	r1.w = r1.h = scale1;

	float scale2 = pSprite2->GetScale() * size2;
	Rectangle r2 = Rectangle();
	r2.x = pSprite2->GetX() - (int)scale2 / 2;
	r2.y = pSprite2->GetY() - (int)scale2 / 2;
	r2.w = r2.h = scale2;

	return CheckRectanglesColliding(r1, r2);
}
