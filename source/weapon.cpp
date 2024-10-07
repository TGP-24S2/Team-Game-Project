// ParticleEmitter.cpp
#include "weapon.h"
#include "renderer.h"
#include "sprite.h"
#include "imgui.h"

Weapon::Weapon()
    : m_pSelfSprite(nullptr)
    , m_fX(0.0f)
    , m_fY(0.0f)
{
}

Weapon::~Weapon()
{
}

bool Weapon::Initialise(Renderer& renderer)
{
    // Generated method stub

    return false;
}

void Weapon::Process(float deltaTime)
{
}

void Weapon::Draw(Renderer& renderer)
{
    
}

void Weapon::DebugDraw()
{
    ImGui::Text("Weapon Settings");

}

void Weapon::SetXY(float x, float y) {
    m_fX = x;
    m_fY = y;
}

void Weapon::SetWeaponName(std::string name) {
    m_sName = name;
}