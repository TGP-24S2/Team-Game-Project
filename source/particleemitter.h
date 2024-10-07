// COMP710 GP Framework
#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

// Library includes:
#include <vector>
#include "weapon.h"

// Forward declarations:
class Renderer;
class Sprite;
class Particle;

// Class declaration:
class ParticleEmitter : public Weapon
{
    // Member methods:
public:
    ParticleEmitter();
    ~ParticleEmitter();

    bool Initialise(Renderer& renderer);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    void SetXY(float x, float y);

    void Spawn();

    void DebugDraw();

    void SetTint(float red, float green, float blue);
    
    void SetActive(bool active);

    void SetAccelerationScalar(float scalar);

    void SetEmitAngle(float minAngle, float maxAngle);
    
    void SetWeaponName(std::string name);

    void SetDamage(int value);
    void SetRange(float value);
    void SetWeaponSprite(const char* spritePath);
    void SetBulletSprite(const char* spritePath);
    void SetMinAngle(float minAngle);
    void SetMaxAngle(float maxAngle);
    void SetBulletCount(int bulletCount);

protected:

private:
    ParticleEmitter(const ParticleEmitter& particleemitter);
    ParticleEmitter& operator=(const ParticleEmitter& particleemitter);

    // Member data:
public:

protected:
    Sprite* m_pSharedSprite;

    Sprite* m_pSelfSprite;

    std::vector<Particle*> m_particles;

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

private:

};
#endif //__PARTICLEEMITTER_H__