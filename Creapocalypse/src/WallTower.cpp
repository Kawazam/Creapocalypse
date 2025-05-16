#include "WallTower.h"

WallTower::WallTower():
    m_wallTowerTexture(nullptr)
{
}

WallTower::~WallTower()
{
}

void WallTower::Init()
{
    m_wallTowerTexture = new sf::Texture("./img/Wall_Tower.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
}

void WallTower::Release()
{
    if (m_wallTowerTexture != nullptr)
    {
        delete m_wallTowerTexture;
        m_wallTowerTexture = nullptr;
    }
}

Tower* WallTower::CreateWallTower(sf::Vector2f position)
{
    Tower* tower = new Tower();
    tower->Init(m_wallTowerTexture, position);
    tower->SetHealth(150);
    //TODO: add a line to set the shoot of this tower
    return tower;
}
