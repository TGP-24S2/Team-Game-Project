#include "Prop.h"

#include "sprite.h"
#include "renderer.h"
#include "inlinehelpers.h"
#include "PropTemplate.h"

#include <iostream>

std::vector<std::string> Prop::m_spritePaths;

Prop::Prop()
    {}

bool Prop::Initialise(Renderer& renderer)
{
    m_pRenderer = &renderer;

    if (m_spritePaths.empty())
    {
        m_spritePaths.push_back("rect1");
        m_spritePaths.push_back("rect2");
        m_spritePaths.push_back("rect3");
        m_spritePaths.push_back("rect4");
        m_spritePaths.push_back("rect5");
        m_spritePaths.push_back("rect6");
        m_spritePaths.push_back("rect7");
    }
    m_hitbox.setPosition(m_position);

    return true;
}

void Prop::Process(float deltaTime)
{
    m_pSprite->Process(deltaTime);
}

void Prop::Draw(Renderer& renderer)
{
    if (m_bIsAlive)
    {
        m_pSprite->Draw(renderer);
    }
}

void Prop::SetTemplate(PropTemplate* propTemplate)
{
    m_pTemplate = propTemplate;
    if (m_pSprite != nullptr)
    {
        UpdateColor();
    }
}

void Prop::ChangeSprite()
{
    std::string spriteName = m_spritePaths[GetRandom(0, m_spritePaths.size() - 1)];

    m_pSprite = m_pRenderer->CreateSprite(("sprites\\props\\" + spriteName + ".png").c_str());
    UpdateColor();

    m_hitbox.setDimensions((float)m_pSprite->GetWidth(), (float)m_pSprite->GetHeight());
    ComputeBounds();
}

void Prop::UpdateColor()
{
    m_pSprite->SetRedTint(m_pTemplate->colour[0]);
    m_pSprite->SetGreenTint(m_pTemplate->colour[1]);
    m_pSprite->SetBlueTint(m_pTemplate->colour[2]);
}

void Prop::ComputeBounds()
{
    m_boundaryLow.x = static_cast<float>(m_hitbox.width / 2.0f);
    m_boundaryLow.y = static_cast<float>(m_hitbox.height / 2.0f);

    m_boundaryHigh.x = m_pRenderer->GetWidth() - static_cast<float>(m_hitbox.width / 2.0f);
    m_boundaryHigh.y = m_pRenderer->GetHeight() - static_cast<float>(m_hitbox.height / 2.0f);
}

void Prop::Spawn()
{
    if (m_pTemplate != nullptr)
    {
        ChangeSprite();
        m_position.x = static_cast<float>(GetRandom(static_cast<int>(m_boundaryLow.x), static_cast<int>(m_boundaryHigh.x)));
        m_position.y = static_cast<float>(GetRandom(static_cast<int>(m_boundaryLow.y), static_cast<int>(m_boundaryHigh.y)));
        m_pSprite->SetPosition((int)m_position.x, (int)m_position.y);
    }
}
