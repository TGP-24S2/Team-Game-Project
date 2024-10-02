#include "Entity.h"
#include "Sprite.h"
#include "animatedsprite.h"
#include "Renderer.h"
#include <cmath>  // for std::abs
#include "iniparser.h"

Entity::Entity()
    : m_pSprite(nullptr)
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

bool Entity::Initialise(Renderer& renderer, const char* spritePath)
{
    m_pSprite = renderer.CreateAnimatedSprite(spritePath);  // Allow dynamic loading of sprites for different entities
    m_pSprite->SetFrameDuration(0.2f);
    m_pSprite->SetLooping(true);
    m_pSprite->SetupFrames(307,307);
    int winHeight = IniParser::GetInstance().GetValueAsInt("Window", "Height");
    float tileHeight = (float)winHeight / 24;
    float tileScale = tileHeight / 307; //307 is the sprite height
    m_pSprite->SetScale(tileScale);
    return (m_pSprite != nullptr);
}

void Entity::Process(float deltaTime)
{
    if (m_bAlive) {
        // Move the entity according to its velocity, but this is grid-based (no floating-point delta time)
        m_pSprite->Process(deltaTime);
        m_position += m_velocity;  // Move in grid steps
    }
}

void Entity::Draw(Renderer& renderer)
{
    if (m_bAlive)
    {
        m_pSprite->SetPosition(static_cast<int>(m_position.x), static_cast<int>(m_position.y));  // Set grid-based position
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

float Entity::GetRadius()
{
    // Radius is irrelevant for a grid-based snake game, return a placeholder or remove it
    return 0.0f;
}

AnimatedSprite* Entity::GetSprite() {
    return m_pSprite;
}

void Entity::Kill()
{
    m_bAlive = false;
}

bool Entity::IsAlive()
{
    return m_bAlive;
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
