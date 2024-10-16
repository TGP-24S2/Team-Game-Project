#include "entity.h"

#include "sprite.h"
#include "animatedsprite.h"
#include "renderer.h"
#include "rectangle.h"
#include "collision.h"
#include "iniparser.h"
#include "inlinehelpers.h"

#include <cmath>
#include <vector>

// Static members:
float Entity::sm_fBoundaryWidth = 0.0f;
float Entity::sm_fBoundaryHeight = 0.0f;

std::vector<Rectangle*> Entity::s_vpEnvHitboxes;

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

//static
void Entity::SetEnvHitboxes(std::vector<Rectangle*> hitboxes)
{
    s_vpEnvHitboxes = hitboxes;
}

bool Entity::Initialise(Renderer& renderer, const char* spritePath, int spriteSize)
{
    m_pSprite = renderer.CreateAnimatedSprite(spritePath);  // Allow dynamic loading of sprites for different entities
    m_pSprite->Animate();
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

    do
    {
        RandomStartPlace();
    } while (IsInsideWall(m_position));

    m_hitbox.setPosition(m_position);
    m_hitbox.setDimensions((float)m_pSprite->GetWidth(), (float)m_pSprite->GetHeight());

    return (m_pSprite != nullptr);
}

void Entity::Process(float deltaTime)
{
    if (!m_bAlive)
        return;

    CheckBounds();

    m_position += m_velocity * m_fSpeedScale * deltaTime;

    // shove backward if inside wall
    Vector2 curVel = m_velocity;
    for (int i = 0; i < 100 && IsInsideWall(m_position); i++)
    {
        m_velocity = Vector2(0, 0);
        m_position += Vector2(-curVel.x * deltaTime, -curVel.y * deltaTime);
    }

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

void Entity::SetSpeedScale(float scale)
{
    m_fSpeedScale = scale;
}

bool Entity::IsCollidingWith(Entity* toCheck)
{
    return Collision::CheckSpriteCollision(m_pSprite, toCheck->GetSprite());
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

bool Entity::IsInsideWall(Vector2 pos)
{
    for (Rectangle* hitbox : s_vpEnvHitboxes)
    {
        Vector2 entitySize = Vector2((float)m_pSprite->GetWidth(), (float)m_pSprite->GetHeight());
        Rectangle thisRect = Rectangle();
        thisRect.setPosition(m_position);
        thisRect.setDimensions(entitySize.x, entitySize.y);
        bool colliding = Collision::CheckRectangleCollision(thisRect, *hitbox);
        if (colliding)
            return true;
    }
    return false;
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

Rectangle Entity::GetHitbox()
{
    return m_hitbox;
}
