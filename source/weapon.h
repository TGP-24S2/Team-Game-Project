// COMP710 GP Framework
#ifndef __WEAPON_H__
#define __WEAPON_H__

// Library includes:
#include <vector>
#include <string>

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

    void SetWeaponName(std::string name);

    void SetDamage(int value);
    void SetRange(float value);
    void SetWeaponSprite(const char* spritePath);

    void SetBulletSprite(const char* spritePath);
    void SetMinAngle(float minAngle);
    void SetMaxAngle(float maxAngle);
    void SetBulletCount(int bulletCount);

    void DebugDraw();

protected:

private:
    Weapon(const Weapon& weapon);
    Weapon& operator=(const Weapon& weapon);

    // Member data:
public:
    bool m_bActive; //holding weapon
    bool m_bOwned; //owned weapon
    std::string m_sName;

protected:
    Sprite* m_pSelfSprite;

    float m_fX;
    float m_fY;


private:

};
#endif //__PARTICLEEMITTER_H__