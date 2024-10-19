// weapon.cpp
#include "weapon.h"
#include "particle.h"
#include "renderer.h"
#include "sprite.h"
#include "imgui.h"
#include "inputsystem.h"

Weapon::Weapon()
    : m_pSharedSprite(nullptr), m_pSelfSprite(nullptr), m_fTimeElapsed(0.0f), m_iSpawnBatchSize(10), m_fEmitRate(1.0f), m_fMaxLifespan(5.0f), m_fAccelerationScalar(1000.0f), m_fX(0.0f), m_fY(0.0f), m_fMinAngle(0.0f), m_fMaxAngle(360.0f), m_bActive(true)
{
    m_fColour[0] = 1.0f; // Red
    m_fColour[1] = 1.0f; // Green
    m_fColour[2] = 1.0f; // Blue
}

Weapon::~Weapon()
{
    for (auto it = begin(m_particles); it != end(m_particles); ++it)
    {
        delete *it;
        *it = nullptr;
    }
    m_particles.clear();
    delete m_pSharedSprite;
    m_pSharedSprite = nullptr;
}

bool Weapon::Initialise(Renderer &renderer)
{
    m_pRenderer = &renderer;
    m_pSharedSprite = renderer.CreateSprite("sprites\\ball.png"); // default sprite //bullet sprite
    m_pSharedSprite->SetScale(0.05f);
    return true;
}

void Weapon::Process(float deltaTime)
{
    ButtonState mouse1State = (InputSystem::GetInstance().GetMouseButtonState(1));
    ButtonState reloadButtonState = (InputSystem::GetInstance().GetKeyState(SDL_SCANCODE_R));

    if (mouse1State == BS_PRESSED)
    {
        if (m_iWeaponType == GUN)
        {
            // Fire bullets
            if (m_iAmmoCount >= m_iSpawnBatchSize) {
                for (int i = 0; i < m_iSpawnBatchSize; ++i)
                {
                    Spawn(); // spawn bullets
                }
                m_iAmmoCount = m_iAmmoCount - m_iSpawnBatchSize;
            }            
        }
        else if (m_iWeaponType == MELEE) {
            // Start the melee swing
            if (!m_particles.empty())
            {
                //SpawnMeleeSwing(); // Spawn the melee weapon particle
                m_particles[0]->SetEnabled();
                m_particles[0]->SetMaxLifespan(m_fMaxLifespan); // Set lifespan as needed
                m_particles[0]->SetPosition(m_fX, m_fY);        // Initial position is at the player
                m_particles[0]->SetColour(m_fColour);

                // Initialize swing angle
                m_particles[0]->m_fCurrentAngle = (m_fMinAngle);
            }
        }
    }

    if (reloadButtonState == BS_PRESSED) {
        if (m_iAmmoCount<m_iSpawnBatchSize) { //reload only if bullet is shot. otherwise dont.
            ReloadWeapon();
        }
    }
    
    if (m_particles[0]->IsAlive()) {
        UpdateMeleeSwing(m_particles[0], deltaTime);
    }

    // Process particles
    for (size_t i = 1; i < m_particles.size();)
    {
        Particle* particle = m_particles[i];
        if (particle->IsAlive())
        {
            particle->Process(deltaTime);
            i++; // Increment only if particle is still alive
        }
        else
        {
            delete particle;
            particle = nullptr;
            m_particles.erase(m_particles.begin() + i); // Erase the particle and don't increment i
        }
    }


    if (m_iWeaponType == GUN && m_pSelfSprite)
    {
        // Draw the player's weapon (self sprite) if it's not melee
        m_pSelfSprite->SetPosition((int)m_fX, (int)m_fY);
        m_pSelfSprite->Process(deltaTime);
    }
}

void Weapon::Draw(Renderer &renderer)
{
    if (m_bActive)
    {
        for (Particle *particle : m_particles)
        {
            if (particle->IsAlive())
            {
                particle->Draw(renderer);
            }
        }

        // Only draw the self sprite (e.g., gun) if it's not a melee weapon
        if (m_iWeaponType != MELEE && m_pSelfSprite)
        {
            m_pSelfSprite->Draw(renderer);
        }
    }
}

void Weapon::Spawn()
{
    Particle *particle = new Particle();

    if (particle->Initialise(*m_pSharedSprite))
    {
        particle->SetEnabled();
        particle->SetMaxLifespan(m_fMaxLifespan);
        particle->SetPosition(m_fX, m_fY);

        float angle = m_fMinAngle + (rand() / (float)RAND_MAX) * (m_fMaxAngle - m_fMinAngle);
        float radians = angle * (3.14159f / 180.0f);
        Vector2 vel = Vector2(cosf(radians), sinf(radians)) * m_fAccelerationScalar;
        particle->SetVelocity(vel.x, vel.y);

        particle->SetColour(m_fColour);

        m_particles.push_back(particle);
    }
    else
    {
        delete particle; // Cleanup if initialization fails
        particle = nullptr;
    }
}

void Weapon::DebugDraw()
{
    ImGui::Text("Weapon Settings");

    ImGui::SliderFloat("Emit Rate", &m_fEmitRate, 0.0f, 100.0f);
    ImGui::SliderFloat("Max Lifespan", &m_fMaxLifespan, 0.0f, 10.0f);
    ImGui::SliderFloat("Acceleration Scalar", &m_fAccelerationScalar, 0.0f, 500.0f);
    ImGui::SliderFloat2("Position", &m_fX, -100.0f, 100.0f);

    // Control angle ranges
    ImGui::SliderFloat("Min Angle", &m_fMinAngle, -360.0f, 360.0f);
    ImGui::SliderFloat("Max Angle", &m_fMaxAngle, -360.0f, 360.0f);

    ImGui::ColorEdit3("Particle Color", m_fColour);

    ImGui::SliderInt("AmmoCount: ", &m_iAmmoCount, 0, 100);
    ImGui::SliderInt("MagCount: ", &m_iMagCount, 0, 100);
    ImGui::SliderInt("MagSize: ", &m_iMagSize, 0, 100);
}

void Weapon::SetXY(float x, float y)
{
    m_fX = x;
    m_fY = y;
}

void Weapon::SetTint(float red, float green, float blue)
{
    m_fColour[0] = red;
    m_fColour[1] = green;
    m_fColour[2] = blue;
}

void Weapon::SetActive(bool active)
{
    m_bActive = active;
}

void Weapon::SetAccelerationScalar(float scalar)
{
    m_fAccelerationScalar = scalar;
}

void Weapon::SetAngle(float playerAngle)
{
    float spread = m_fMaxAngle - m_fMinAngle;
    float halfSpread = spread / 2;
    m_fMinAngle = playerAngle - halfSpread;
    m_fMaxAngle = playerAngle + halfSpread;
    m_pSelfSprite->SetAngle(-playerAngle);
}

// for initialization

void Weapon::SetWeaponName(std::string name)
{
    m_sName = name;
}

void Weapon::SetDamage(int value)
{
    m_iDamage = value;
}

int Weapon::GetDamage(void)
{
    return m_iDamage;
}

void Weapon::SetRange(float value)
{
    m_fMaxLifespan = value;
}

void Weapon::SetWeaponSprite(const char *spritePath)
{
    m_pSelfSprite = m_pRenderer->CreateSprite(spritePath);
    if (m_iWeaponType == GUN)
    {
        m_pSelfSprite->SetScale(0.1f);
        m_pSharedSprite->SetScale(0.08f);
    }
    else if (m_iWeaponType == MELEE)
    {
        m_pSharedSprite->SetScale(0.5f);
    }
}

void Weapon::SetIconSprite(const char* spritePath)
{
    m_pIconSprite = m_pRenderer->CreateSprite(spritePath);
    m_pIconSprite->SetScale(0.4f);
    m_pIconSprite->SetX(50);
    m_pIconSprite->SetY(50);
}

Sprite *Weapon::GetIconSprite()
{
    return m_pIconSprite;
}

void Weapon::SetBulletSprite(const char *spritePath)
{
    m_pSharedSprite = m_pRenderer->CreateSprite(spritePath);
    if (m_iWeaponType == GUN)
    {
        m_pSharedSprite->SetScale(0.05f);
    }
    else if (m_iWeaponType == MELEE)
    {
        m_pSharedSprite->SetScale(0.5f);
    }
}

void Weapon::SetMinAngle(float minAngle)
{
    m_fMinAngle = minAngle;
}

void Weapon::SetMaxAngle(float maxAngle)
{
    m_fMaxAngle = maxAngle;
}

void Weapon::SetBulletCount(int bulletCount)
{
    m_iSpawnBatchSize = bulletCount;
}

// for using
std::string Weapon::GetWeaponName()
{
    return m_sName;
}

std::vector<Particle *> Weapon::GetParticles()
{
    return m_particles;
}

void Weapon::SetMelee()
{
    m_iWeaponType = MELEE;
}

void Weapon::SetGun()
{
    m_iWeaponType = GUN;
}

void Weapon::AddAmmo(int amount) {
    m_iAmmoCount += amount;
    if (m_iAmmoCount > m_iMagSize)
        m_iAmmoCount = m_iMagSize;
}

void Weapon::SpawnMeleeSwing()
{
    Particle *particle = new Particle();

    if (particle->Initialise(*m_pSelfSprite))
    {
        m_particles.push_back(particle); // Add this particle to the emitter
    }
    else
    {
        delete particle;
        particle = nullptr;
    }
}

void Weapon::UpdateMeleeSwing(Particle *particle, float deltaTime)
{
    // Increment the angle over time to simulate the swinging motion
    float swingSpeed = 360.0f; // Degrees per second, tweak as needed
    particle->m_fCurrentAngle += swingSpeed * deltaTime;

    // Clamp angle between minAngle and maxAngle
    if (particle->m_fCurrentAngle > m_fMaxAngle)
    {
        particle->SetDisabled(); // End the swing when maxAngle is reached
        return;
    }

    // Convert angle to radians
    float radians = particle->m_fCurrentAngle * (3.14159f / 180.0f);

    // Calculate new position based on radius and angle
    float radius = 100.0f; // Distance of the weapon from the player, tweak as needed
    float x = m_fX + cosf(radians) * radius;
    float y = m_fY + sinf(radians) * radius;

    // Update the particle's position
    particle->SetPosition(x, y);
}

weaponType Weapon::GetWeaponType()
{
    return m_iWeaponType;
}

void Weapon::SetMagSize(int magSize) {
    m_iMagSize = magSize;
}

int Weapon::GetMagSize() {
    return m_iMagSize;
}

int Weapon::GetAmmoCount() {
    return m_iAmmoCount;
}

void Weapon::ReloadWeapon() {
    if (m_iMagCount > 0) {
        m_iAmmoCount = m_iMagSize * m_iSpawnBatchSize;
        m_iMagCount--;
    }    
}

void Weapon::InitialiseAmmoCount() {
    m_iAmmoCount = m_iMagSize * m_iSpawnBatchSize;
}

int Weapon::GetMagCount() {
    return m_iMagCount;
}

void Weapon::SetMagCount(int magCount) {
    m_iMagCount = magCount;
}

