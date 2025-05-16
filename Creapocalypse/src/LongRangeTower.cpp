#include "LongRangeTower.h"

LongRangeTower::LongRangeTower():
    m_longRangeTowerTexture(nullptr)
{
}

LongRangeTower::~LongRangeTower()
{
}

void LongRangeTower::Init()
{
    m_longRangeTowerTexture = new sf::Texture("./img/Long_Range_Tower.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
}

void LongRangeTower::Release()
{
    if (m_longRangeTowerTexture != nullptr)
    {
        delete m_longRangeTowerTexture;
        m_longRangeTowerTexture = nullptr;
    }
}

Tower* LongRangeTower::CreateLongRangeTower(sf::Vector2f position)
{
    Tower* tower = new Tower();
    tower->Init(m_longRangeTowerTexture, position);
    tower->SetHealth(50);
    //TODO: add a line to set the shoot of this tower
    return tower;
}
