// COMP710 GP Framework
#ifndef __WEAPON_H__
#define __WEAPON_H__

// Library includes:
#include <vector>

// Forward declarations:
class Renderer;
class Sprite;

// Class declaration:
class Weapon
{
    // Member methods:
public:
    Weapon();
    ~Weapon();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void SetXY(float x, float y);

    void DebugDraw();

protected:

private:
    Weapon(const Weapon& weapon);
    Weapon& operator=(const Weapon& weapon);

    // Member data:
public:
    bool active;
    bool owned;

protected:
    Sprite* m_pSelfSprite;

    float m_fX;
    float m_fY;


private:

};
#endif //__PARTICLEEMITTER_H__