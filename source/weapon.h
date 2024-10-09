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
    virtual ~Weapon();

    virtual bool Initialise(Renderer& renderer);
    virtual void Process(float deltaTime);
    virtual void Draw(Renderer& renderer);

    virtual void SetXY(float x, float y);

    virtual void SetWeaponName(std::string name);
    virtual std::string GetWeaponName();

    virtual void SetDamage(int value);
    virtual void SetRange(float value);
    virtual void SetWeaponSprite(const char* spritePath);

    virtual void SetBulletSprite(const char* spritePath);
    virtual void SetMinAngle(float minAngle);
    virtual void SetMaxAngle(float maxAngle);
    virtual void SetBulletCount(int bulletCount);

    virtual void SetAngle(float angle);

    virtual void DebugDraw();

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
#endif //__WEAPON_H__
