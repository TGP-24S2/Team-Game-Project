#include "collision.h"

#include <corecrt_math_defines.h>
// Local includes:
#include "sprite.h"
#include "rectangle.h"
#include "entity.h"
bool Collision::CheckRectangleCollision(Rectangle r1, Rectangle r2)
{
	float r1Left = (float)(r1.m_position->x) - (r1.width / 2.0f);
	float r1Right = (float)(r1.m_position->x) + (r1.width / 2.0f);
	float r1Top = (float)(r1.m_position->y) - (r1.height / 2.0f);
	float r1Bottom = (float)(r1.m_position->y) + (r1.height / 2.0f);

	float r2Left = (float)(r2.m_position->x) - (r2.width / 2.0f);
	float r2Right = (float)(r2.m_position->x) + (r2.width / 2.0f);
	float r2Top = (float)(r2.m_position->y) - (r2.height / 2.0f);
	float r2Bottom = (float)(r2.m_position->y) + (r2.height / 2.0f);

	if (r1Right < r2Left) return false;
	if (r1Left > r2Right) return false;
	if (r1Bottom < r2Top) return false;
	if (r1Top > r2Bottom) return false;
	return true;
}

bool Collision::CheckPointInRectangle(Vector2 point, Rectangle rect)
{
	float rectLeft = (float)(rect.m_position->x) - (rect.width / 2.0f);
	float rectRight = (float)(rect.m_position->x) + (rect.width / 2.0f);
	float rectTop = (float)(rect.m_position->y) - (rect.height / 2.0f);
	float rectBottom = (float)(rect.m_position->y) + (rect.height / 2.0f);

	// Check if point is within rectangle's bounds
	return (point.x >= rectLeft && point.x <= rectRight &&
		point.y >= rectTop && point.y <= rectBottom);
}

/// Checks if the first sprite is within the second sprite.
bool Collision::CheckSpriteCollision(Sprite* pSprite1, Sprite* pSprite2)
{
	Rectangle r1 = Rectangle();
	Vector2 v1 = Vector2();
	v1.x = (float)pSprite1->GetX();
	v1.y = (float)pSprite1->GetY();
	r1.setPosition(v1);
	r1.setDimensions((float)pSprite1->GetWidth(), (float)pSprite1->GetHeight());

	Rectangle r2 = Rectangle();
	Vector2 v2 = Vector2();
	v2.x = (float)pSprite2->GetX();
	v2.y = (float)pSprite2->GetY();
	r2.setPosition(v2);
	r2.setDimensions((float)pSprite2->GetWidth(), (float)pSprite2->GetHeight());

	return CheckRectangleCollision(r1, r2);
}
