#pragma once
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

// Class declaration:
class ParticleEmitter
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
    void SetAngle(float playerAngle);

    void SetWeaponName(std::string name);
    std::string GetWeaponName();
    void SetDamage(int value);
    int GetDamage(void);
    void SetRange(float value);
    void SetWeaponSprite(const char* spritePath);
    void SetBulletSprite(const char* spritePath);
    void SetMinAngle(float minAngle);
    void SetMaxAngle(float maxAngle);
    void SetBulletCount(int bulletCount);
    std::vector<Particle*> GetParticles(void);

    void SetMelee();
    void SetGun();

    void SpawnMeleeSwing();
    void UpdateMeleeSwing(Particle* particle, float deltaTime);

    int GetWeaponType();
protected:

private:
    ParticleEmitter(const ParticleEmitter& particleemitter);
    ParticleEmitter& operator=(const ParticleEmitter& particleemitter);

    // Member data:
public:

protected:
    Sprite* m_pSharedSprite;

    Sprite* m_pSelfSprite;

    Renderer* m_pRenderer;

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

    int m_iDamage;

    bool m_bOwned; //owned weapon

    int m_iWeaponType;

    std::string m_sName;
private:

};
#endif //__PARTICLEEMITTER_H__