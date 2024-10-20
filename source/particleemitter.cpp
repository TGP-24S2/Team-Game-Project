// ParticleEmitter.cpp
#include "particleemitter.h"
#include "particle.h"
#include "renderer.h"
#include "sprite.h"
#include "imgui.h"
#include <iostream>

ParticleEmitter::ParticleEmitter()
    : m_pSharedSprite(nullptr)
    , m_fTimeElapsed(0.0f)
    , m_iSpawnBatchSize(10)
    , m_fEmitRate(1.0f)
    , m_fMaxLifespan(5.0f)
    , m_fAccelerationScalar(100.0f)
    , m_fX(0.0f)
    , m_fY(0.0f)
    , m_fMinAngle(0.0f)
    , m_fMaxAngle(360.0f)
    , m_bActive(false)
{
    m_fColour[0] = 1.0f; // Red
    m_fColour[1] = 1.0f; // Green
    m_fColour[2] = 1.0f; // Blue
}

ParticleEmitter::~ParticleEmitter()
{
    for (auto it = begin(m_particlesvector); it != end(m_particlesvector); ++it) {
        delete* it;
        *it = nullptr;
    }
    m_particlesvector.clear();
    delete m_pSharedSprite;
    m_pSharedSprite = nullptr;
}

bool ParticleEmitter::Initialise(Renderer& renderer)
{
    m_pSharedSprite = renderer.CreateSprite("sprites\\ball.png"); //subject to change
    m_pSharedSprite->SetScale(0.05f);
    return true;
}

void ParticleEmitter::Process(float deltaTime)
{
    m_fTimeElapsed += deltaTime;

    // Emit particles based on the elapsed time and emit rate
    if (m_fTimeElapsed > (1.0f / m_fEmitRate))
    {
        for (int i = 0; i < m_iSpawnBatchSize; ++i)
        {
            Spawn();
        }
        m_fTimeElapsed = 0.0f;
    }

    // Process and remove dead particles
    for (auto it = m_particlesvector.begin(); it != m_particlesvector.end(); )
    {
        Particle* particle = *it;
        if (particle->m_bAlive)
        {
            particle->Process(deltaTime);
            ++it;
        }
        else
        {
            delete particle;
            particle = nullptr;
            it = m_particlesvector.erase(it);
        }
    }
}

void ParticleEmitter::Draw(Renderer& renderer)
{
    if (m_bActive) {
        for (Particle* particle : m_particlesvector)
        {
            if (particle->m_bAlive)
            {
                particle->Draw(renderer);
            }
        }
    }
}

void ParticleEmitter::Spawn()
{
    Particle* particle = new Particle();
    
    if (particle->Initialise(*m_pSharedSprite))
    {
        
        particle->m_bAlive = true;
        particle->m_fMaxLifespan = m_fMaxLifespan;
        particle->m_position = Vector2(m_fX, m_fY);

        float angle = m_fMinAngle + (rand() / (float)RAND_MAX) * (m_fMaxAngle - m_fMinAngle);
        float radians = angle * (3.14159f / 180.0f);
        particle->m_velocity = Vector2(cosf(radians), sinf(radians)) * m_fAccelerationScalar;

        particle->m_fColour[0] = m_fColour[0];
        particle->m_fColour[1] = m_fColour[1];
        particle->m_fColour[2] = m_fColour[2];

        m_particlesvector.push_back(particle);
    }
    else
    {
        delete particle; // Cleanup if initialization fails
        particle = nullptr;
    }
}

void ParticleEmitter::DebugDraw()
{
    ImGui::Text("Particle Emitter Settings");

    ImGui::SliderFloat("Emit Rate", &m_fEmitRate, 0.0f, 100.0f);
    ImGui::SliderFloat("Max Lifespan", &m_fMaxLifespan, 0.0f, 10.0f);
    ImGui::SliderFloat("Acceleration Scalar", &m_fAccelerationScalar, 0.0f, 5.0f);
    ImGui::SliderFloat2("Position", &m_fX, -100.0f, 100.0f);
    ImGui::SliderFloat2("Min/Max Angle", &m_fMinAngle, -360.0f, 360.0f);
    ImGui::ColorEdit3("Particle Color", m_fColour);
}

void ParticleEmitter::SetXY(float x, float y) {
    m_fX = x;
    m_fY = y;
}

void ParticleEmitter::SetTint(float red, float green, float blue) {
    m_fColour[0] = red;
    m_fColour[1] = green;
    m_fColour[2] = blue;
}

void ParticleEmitter::SetActive(bool active) {
    m_bActive = active;
}

void ParticleEmitter::SetAccelerationScalar(float scalar) {
    m_fAccelerationScalar = scalar;
}