#include "rectangle.h"
#include <glew.h>
#include "renderer.h"
#include <iostream>

// Default constructor
Rectangle::Rectangle() : width(1.0f), height(1.0f), x(0.0f), y(0.0f), r(0.0f), g(0.0f), b(0.0f), alpha(1.0f){}

// Parameterized constructor
Rectangle::Rectangle(float length, float height, float x, float y, float r, float g, float b)
    : width(length), height(height), x(x), y(y), r(r), g(g), b(b) {}

void Rectangle::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Rectangle::setColor(float newR, float newG, float newB) {
    r = newR;
    g = newG;
    b = newB;
}

// Method to draw the rectangle
void Rectangle::Draw(Renderer& renderer){
    //renderer.DrawRectangle(x, y, width, height, r, g, b, alpha);
}
