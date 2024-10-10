// COMP710 GP Framework
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// Local includes:
#include "Vector2.h"
#include "entity.h"

// Forward declarations:
class Renderer;
class Sprite;

// Class declaration:
class Particle : public Entity
{
    // Member methods:
public:
    Particle();
    ~Particle();
    bool Initialise(Sprite& sprite);
    void Process(float deltaTime);
    void Draw(Renderer& renderer);

    Sprite* GetSprite(void);
    void SetPosition(float, float);
    void SetVelocity(float, float);
    void SetAlive(void);
    void SetUnalive(void);

protected:

private:
    Particle(const Particle& particle);
    Particle& operator=(const Particle& particle);

    // Member data:
public:
    Sprite* m_pSharedSprite;
    float m_fMaxLifespan;
    float m_fCurrentAge;
    float m_fColour[3];
    float m_fCurrentAngle;

protected:
    Vector2 m_acceleration;
private:
};

#endif //__PARTICLE_H__