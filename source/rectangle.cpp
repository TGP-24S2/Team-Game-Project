#include "rectangle.h"

#include "vector2.h"


Rectangle::Rectangle()
    : width(0), height(0), m_position(nullptr)
{

}

void Rectangle::setDimensions(float newWidth, float newHeight)
{
    width = newWidth;
    height = newHeight;
}

void Rectangle::setPosition(Vector2& position)
{
    m_position = &position;
}