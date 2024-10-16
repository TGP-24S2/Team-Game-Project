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
    , m_pSprite(nullptr)
{
}

Particle::~Particle()
{
    //delete m_pSprite;
    m_pSprite = nullptr;
}

bool
Particle::Initialise(Sprite& sprite)
{
    m_pSprite = &sprite;
    m_hitbox.setPosition(m_position);
    m_hitbox.setDimensions((float)m_pSprite->GetWidth(), (float)m_pSprite->GetHeight());
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
        m_pSprite->SetRedTint(m_fColour[0]);
        m_pSprite->SetGreenTint(m_fColour[1]);
        m_pSprite->SetBlueTint(m_fColour[2]);
        //float alpha = (float)(1.0f - (m_fCurrentAge / m_fMaxLifespan));
        //m_pSprite->SetAlpha(alpha);
        m_pSprite->SetAngle(-m_fCurrentAngle-90);
        m_pSprite->SetX((int)m_position.x);
        m_pSprite->SetY((int)m_position.y);
        m_pSprite->Draw(renderer);
    }
}

Sprite* Particle::GetSprite(void)
{
    return m_pSprite;
}

void Particle::SetPosition(float x, float y)
{
    m_position = Vector2(x, y);
}

void Particle::SetVelocity(float x, float y)
{
    m_velocity = Vector2(x, y);
}

void Particle::SetEnabled(void)
{
    m_bAlive = true;
}

void Particle::SetDisabled(void)
{
    m_bAlive = false;
}

void Particle::SetMaxLifespan(float n)
{
    m_fMaxLifespan = n;
}

void Particle::SetColour(float rgb[3])
{
    m_fColour[0] = rgb[0];
    m_fColour[1] = rgb[1];
    m_fColour[2] = rgb[2];
}

void Particle::SetColour(float r, float g, float b)
{
    m_fColour[0] = r;
    m_fColour[1] = g;
    m_fColour[2] = b;
}