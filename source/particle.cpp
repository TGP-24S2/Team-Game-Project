// COMP710 GP Framework
// This include:
#include "particle.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"

Particle::Particle()
    : Entity()
    , m_fCurrentAge(0.0f)
    , m_fCurrentAngle(0.0f)
    , m_fColour{ 0.0f, 0.0f, 0.0f }
    , m_fMaxLifespan(0.0f)
    , m_pSharedSprite(nullptr)
{
}

Particle::~Particle()
{
    //delete m_pSharedSprite;
    m_pSharedSprite = nullptr;
}

bool
Particle::Initialise(Sprite& sprite)
{
    m_pSharedSprite = &sprite;
    return true;
}

void
Particle::Process(float deltaTime)
{
    if (m_bAlive)
    {
        m_fCurrentAge += deltaTime;
        m_velocity += m_acceleration * deltaTime;
        m_position += m_velocity * deltaTime;

        if (m_fCurrentAge > m_fMaxLifespan)
        {
            m_bAlive = false;
        }
    }
}

void
Particle::Draw(Renderer& renderer)
{
    if (m_bAlive)
    {
        m_pSharedSprite->SetRedTint(m_fColour[0]);
        m_pSharedSprite->SetGreenTint(m_fColour[1]);
        m_pSharedSprite->SetBlueTint(m_fColour[2]);
        //float alpha = (float)(1.0f - (m_fCurrentAge / m_fMaxLifespan));
        //m_pSharedSprite->SetAlpha(alpha);
        m_pSharedSprite->SetX((int)m_position.x);
        m_pSharedSprite->SetY((int)m_position.y);
        m_pSharedSprite->Draw(renderer);
    }
}

Sprite* Particle::GetSprite(void)
{
    return m_pSharedSprite;
}

void Particle::SetPosition(float x, float y)
{
    m_position = Vector2(x, y);
}

void Particle::SetVelocity(float x, float y)
{
    m_velocity = Vector2(x, y);
}

void Particle::SetAlive(void)
{
    m_bAlive = true;
}

void Particle::SetUnalive(void)
{
    m_bAlive = false;
}