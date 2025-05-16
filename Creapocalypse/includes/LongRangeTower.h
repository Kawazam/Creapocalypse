#pragma once
#include "Tower.h"

class LongRangeTower :
    public Tower
{
public:
    LongRangeTower();
    ~LongRangeTower();

    void Init();
    void Release();
    Tower* CreateLongRangeTower(sf::Vector2f position);

private:
    sf::Texture* m_longRangeTowerTexture;
};

