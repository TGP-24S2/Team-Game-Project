#include "rectanglemaker.h"
#include <glew.h>

// Default constructor
Rectangle::Rectangle() : length(1.0f), height(1.0f), x(0.0f), y(0.0f), r(1.0f), g(1.0f), b(1.0f) {}

// Parameterized constructor
Rectangle::Rectangle(float length, float height, float x, float y, float r, float g, float b)
    : length(length), height(height), x(x), y(y), r(r), g(g), b(b) {}

// Getters
float Rectangle::getLength() const {
    return length;
}

float Rectangle::getHeight() const {
    return height;
}

float Rectangle::getX() const {
    return x;
}

float Rectangle::getY() const {
    return y;
}

void Rectangle::getColor(float& outR, float& outG, float& outB) const {
    outR = r;
    outG = g;
    outB = b;
}

// Setters
void Rectangle::setLength(float newLength) {
    length = newLength;
}

void Rectangle::setHeight(float newHeight) {
    height = newHeight;
}

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
void Rectangle::draw() const {
    glColor3f(r, g, b); // Set the color
    glBegin(GL_QUADS); // Draw a rectangle using a quad
    glVertex2f(x, y);                // Bottom-left corner
    glVertex2f(x + length, y);        // Bottom-right corner
    glVertex2f(x + length, y + height); // Top-right corner
    glVertex2f(x, y + height);        // Top-left corner
    glEnd();
}
