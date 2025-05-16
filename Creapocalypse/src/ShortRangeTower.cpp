#include "ShortRangeTower.h"

ShortRangeTower::ShortRangeTower() :
    m_shortRangeTowerTexture(nullptr)
{
}

ShortRangeTower::~ShortRangeTower()
{
}

void ShortRangeTower::Init()
{
    m_shortRangeTowerTexture = new sf::Texture("./img/Short_Range_Tower.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
}

void ShortRangeTower::Release()
{
    if (m_shortRangeTowerTexture != nullptr)
    {
        delete m_shortRangeTowerTexture;
        m_shortRangeTowerTexture = nullptr;
    }
}

Tower* ShortRangeTower::CreateShortRangeTower(sf::Vector2f position)
{
    Tower* tower = new Tower();
    tower->Init(m_shortRangeTowerTexture, position);
    tower->SetHealth(50);
    //TODO: add a line to set the shoot of this tower
    return tower;
}