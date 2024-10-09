#include "collision.h"

bool Collision::CheckRectanglesColliding(Rectangle r1, Rectangle r2)
{
	float r1Left = static_cast<float>(r1.x) - (r1.w / 2.0f);
	float r1Right = static_cast<float>(r1.x) + (r1.w / 2.0f);
	float r1Top = static_cast<float>(r1.y) - (r1.h / 2.0f);
	float r1Bottom = static_cast<float>(r1.y) + (r1.h / 2.0f);

	float r2Left = static_cast<float>(r2.x) - (r2.w / 2.0f);
	float r2Right = static_cast<float>(r2.x) + (r2.w / 2.0f);
	float r2Top = static_cast<float>(r2.y) - (r2.h / 2.0f);
	float r2Bottom = static_cast<float>(r2.y) + (r2.h / 2.0f);


	if (r1Right < r2Left) return false;
	if (r1Left > r2Right) return false;
	if (r1Bottom < r2Top) return false;
	if (r1Top > r2Bottom) return false;

	return true;
}
