// COMP710 GP Framework
#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

// Library includes:
#include <vector>
#include "string"

// Forward declarations:
class Renderer;
class Sprite;
class Particle;

static std::vector<Particle*> m_particles;

enum weaponType
{
    GUN,
    MELEE
};

// Class declaration:
class Weapon
{
    // Member methods:
public:
    Weapon();
    ~Weapon();

    bool Initialise(Renderer &renderer);
    void Process(float deltaTime);
    void Draw(Renderer &renderer);

    void SetXY(float x, float y);

    void Spawn();

    void DebugDraw();

    void SetTint(float red, float green, float blue);
    void SetActive(bool active);
    void SetAccelerationScalar(float scalar);
    void SetAngle(float playerAngle);

    void SetWeaponName(std::string name);
    std::string GetWeaponName();
    void SetDamage(int value);
    int GetDamage(void);
    void SetRange(float value);
    void SetWeaponSprite(const char* spritePath);
    void SetIconSprite(const char* spritePath);
    Sprite *GetIconSprite();
    void SetBulletSprite(const char *spritePath);
    void SetMinAngle(float minAngle);
    void SetMaxAngle(float maxAngle);
    void SetBulletCount(int bulletCount);
    std::vector<Particle *> GetParticles(void);

    void SetMelee();
    void SetGun();

    void SpawnMeleeSwing();
    void UpdateMeleeSwing(Particle *particle, float deltaTime);
    void AddAmmo(int);
    weaponType GetWeaponType();
    void SetMagSize(int magSize);
    int GetMagSize();
    int GetAmmoCount();
    void ReloadWeapon();
    int GetMagCount();
    void SetMagCount(int magCount);
    void InitialiseAmmoCount();
protected:
private:
    Weapon(const Weapon &weapon);
    Weapon &operator=(const Weapon &weapon);

    // Member data:
public:
protected:
    Sprite *m_pSharedSprite;
    Sprite *m_pSelfSprite;
    Sprite* m_pIconSprite;

    Renderer *m_pRenderer;

    float m_fTimeElapsed;

    int m_iSpawnBatchSize;
    float m_fEmitRate;
    float m_fMaxLifespan;
    float m_fAccelerationScalar;
    float m_fColour[3];
    float m_fMinAngle;
    float m_fMaxAngle;
    float m_fX;
    float m_fY;

    bool m_bActive;

    int m_iDamage;

    bool m_bOwned; // owned weapon

    //see enum
    weaponType m_iWeaponType;

    int m_iMagSize; //constant size of mag/clip of weapon. irrelevant for melee
    int m_iAmmoCount; //variable ammo count. min 0, max magsize * bulletcount(spawnbatchsize).
    int m_iMagCount; //practically the number of reloads

    std::string m_sName;

private:
};
#endif //__PARTICLEEMITTER_H__
