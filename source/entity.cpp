#include "entity.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "renderer.h"
#include <cmath>  // for std::abs
#include "iniparser.h"
#include "inlinehelpers.h"


// Static members:
float Entity::sm_fBoundaryWidth = 0.0f;
float Entity::sm_fBoundaryHeight = 0.0f;

Entity::Entity()
    : m_pSprite(nullptr)
    , m_iHealth(1000)
    , m_iMaxHealth(1000)
    , m_bAlive(true)
    , m_position(0, 0)
    , m_velocity(0, 0)
{
}

Entity::~Entity()
{
    delete m_pSprite;
    m_pSprite = nullptr;
}

bool Entity::Initialise(Renderer& renderer, const char* spritePath, int spriteSize)
{
    m_pSprite = renderer.CreateAnimatedSprite(spritePath);  // Allow dynamic loading of sprites for different entities
    m_pSprite->Animate();
    m_pSprite->SetFrameDuration(1.0f);
    m_pSprite->SetLooping(true);
    m_pSprite->SetupFrames(spriteSize, spriteSize);

    int winHeight = IniParser::GetInstance().GetValueAsInt("Window", "Height");
    float tileHeight = (float)winHeight / 24;
    float tileScale = tileHeight / spriteSize;
    m_pSprite->SetScale(tileScale);

    const int SCREEN_WIDTH = renderer.GetWidth();
    const int SCREEN_HEIGHT = renderer.GetHeight();
    sm_fBoundaryWidth = static_cast<float>(SCREEN_WIDTH);
    sm_fBoundaryHeight = static_cast<float>(SCREEN_HEIGHT);

    ComputeBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
    RandomStartPlace();

    return (m_pSprite != nullptr);
}

void Entity::Process(float deltaTime)
{
    if (!m_bAlive)
        return;

    // process movement
    CheckBounds();

    m_position += m_velocity * deltaTime;
    m_pSprite->SetPosition(static_cast<int>(m_position.x), static_cast<int>(m_position.y));  // Set grid-based position
    m_pSprite->Process(deltaTime);

    // process health
    if (m_iHealth <= 0)
        m_bAlive = false;
}

void Entity::Draw(Renderer& renderer)
{
    if (m_bAlive)
    {
        m_pSprite->Draw(renderer);
    }
}

Vector2& Entity::GetPosition()
{
    return m_position;
}

void Entity::SetPosition(int x, int y)
{
    m_position.x = (float)x;
    m_position.y = (float)y;
}

Vector2& Entity::GetVelocity()
{
    return m_velocity;
}

void Entity::SetVelocity(int x, int y)
{
    m_velocity.x = (float)x;
    m_velocity.y = (float)y;
}

bool Entity::IsCollidingWith(Entity* toCheck)
{
    // For grid-based movement, collision occurs when both entities are on the same tile
    return (m_position.x == toCheck->m_position.x && m_position.y == toCheck->m_position.y);
}

AnimatedSprite* Entity::GetSprite() {
    return m_pSprite;
}

int Entity::GetHealth()
{
    return m_iHealth;
}

int Entity::GetMaxHealth()
{
    return m_iMaxHealth;
}

void Entity::Kill()
{
    m_bAlive = false;
}

bool Entity::IsAlive()
{
    return m_bAlive;
}

void Entity::TakeDamage(int damage)
{
    m_iHealth -= damage;
}

void Entity::ComputeBounds(int width, int height)
{
    int w = m_pSprite->GetWidth();
    int h = m_pSprite->GetHeight();

    m_boundaryLow.x = w / 2.0f;
    m_boundaryLow.y = h / 2.0f;

    m_boundaryHigh.x = width - w / 2.0f;
    m_boundaryHigh.y = height - h / 2.0f;
}

void Entity::CheckBounds()
{
    if (m_position.x >= (m_boundaryHigh.x))
    {
        m_position.x = m_boundaryHigh.x;
        m_velocity.x *= -1.0f;
    }
    else if (m_position.x <= (m_boundaryLow.x))
    {
        m_position.x = m_boundaryLow.x;
        m_velocity.x *= -1.0f;
    }

    if (m_position.y >= (m_boundaryHigh.y))
    {
        m_position.y = m_boundaryHigh.y;
        m_velocity.y *= -1.0f;
    }
    else if (m_position.y <= (m_boundaryLow.y))
    {
        m_position.y = m_boundaryLow.y;
        m_velocity.y *= -1.0f;
    }
}

void Entity::RandomStartPlace()
{
    const int MAX_SPEED = 250; //this is bum someone get rid of this
    const int EDGE_LIMIT = m_pSprite->GetWidth();

    m_position.x = static_cast<float>(GetRandom(EDGE_LIMIT, (int) m_boundaryHigh.x - EDGE_LIMIT));
    m_position.y = static_cast<float>(GetRandom(EDGE_LIMIT, (int) m_boundaryHigh.y - EDGE_LIMIT));

    m_velocity.x = GetRandomPercentage() * MAX_SPEED * GetPositiveOrNegative();
    m_velocity.y = GetRandomPercentage() * MAX_SPEED * GetPositiveOrNegative();
}