#include "MissileTower.h"

MissileTower::MissileTower() :
    m_missileTowerTexture(nullptr)
{
}

MissileTower::~MissileTower()
{
}

void MissileTower::Init()
{
    m_missileTowerTexture = new sf::Texture("./img/Missile_Tower.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
}

void MissileTower::Release()
{
    if (m_missileTowerTexture != nullptr)
    {
        delete m_missileTowerTexture;
        m_missileTowerTexture = nullptr;
    }
}

Tower* MissileTower::CreateMissileTower(sf::Vector2f position)
{
    Tower* tower = new Tower();
    tower->Init(m_missileTowerTexture, position);
    tower->SetHealth(50);
    //TODO: add a line to set th shoot of this tower
    return tower;
}
