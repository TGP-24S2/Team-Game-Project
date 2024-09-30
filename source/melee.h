// COMP710 GP Framework
#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

// Library includes:
#include <vector>
#include "weapon.h"

// Forward declarations:
class Renderer;
class Sprite;

// Class declaration:
class Melee : public Weapon
{
    // Member methods:
public:
    Melee();
    ~Melee();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void SetXY(float x, float y);

    void DebugDraw();
protected:

private:
    Melee(const Melee& melee);
    Melee& operator=(const Melee& melee);

    // Member data:
public:

protected:
    Sprite* m_pSelfSprite;

    float m_fX;
    float m_fY;

private:

};
#endif //__PARTICLEEMITTER_H__