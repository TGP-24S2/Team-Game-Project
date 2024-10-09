#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    float width;
    float height;
    float x;
    float y;
    float r, g, b; // Color components: Red, Green, Blue

public:
    // Constructors
    Rectangle();
    Rectangle(float width, float height, float x, float y, float r, float g, float b);

    void setPosition(float newX, float newY);
    void setColor(float newR, float newG, float newB);

    // Method to draw the rectangle
    void draw() const;
};

#endif
