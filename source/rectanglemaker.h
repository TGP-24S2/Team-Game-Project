#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
    float length;
    float height;
    float x;
    float y;
    float r, g, b; // Color components: Red, Green, Blue

public:
    // Constructors
    Rectangle();
    Rectangle(float length, float height, float x, float y, float r, float g, float b);

    // Getters
    float getLength() const;
    float getHeight() const;
    float getX() const;
    float getY() const;
    void getColor(float& outR, float& outG, float& outB) const;

    // Setters
    void setLength(float newLength);
    void setHeight(float newHeight);
    void setPosition(float newX, float newY);
    void setColor(float newR, float newG, float newB);

    // Method to draw the rectangle
    void draw() const;
};

#endif
