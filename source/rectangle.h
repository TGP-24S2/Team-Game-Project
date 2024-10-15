#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "vector2.h"

class Renderer;

class Rectangle {
public:
    // Constructors
    Rectangle();

    void setDimensions(float width, float height);
    void setPosition(Vector2& position);

public:
    Vector2* m_position; //will just reference position of owner
    float width;
    float height;
};

#endif