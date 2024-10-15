#include "Prop.h"

#include "sprite.h"
#include "renderer.h"
#include "inlinehelpers.h"
#include "PropTemplate.h"

Player* Game::m_pPlayer = nullptr;
Enemy** Game::m_lpEnemies = nullptr;

bool Prop::Initialise(Renderer& renderer)
{
    m_hitbox.setPosition(m_position);
    
    ChangeSprite();

    return false;
}

void Prop::Draw(Renderer& renderer)
{
    m_pSprite->Draw(renderer);
}

void Prop::SetTemplate(PropTemplate* propTemplate)
{
    m_pTemplate = propTemplate;
}

void Prop::ChangeSprite()
{
    std::string spriteName = m_spritePaths[GetRandom(0, m_spritePaths.size() - 1)];

    m_pSprite = m_pRenderer->CreateSprite(("sprites\\" + spriteName + ".png").c_str());

    m_hitbox.setDimensions(m_pSprite->GetWidth(), m_pSprite->GetHeight());
}

void Prop::setColor(float newR, float newG, float newB)
{
    r = newR;
    g = newG;
    b = newB;
}

void Prop::setAlpha(float newA)
{
    alpha = newA;
}
