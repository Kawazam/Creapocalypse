#pragma once
#include "Tower.h"

class ShortRangeTower :
    public Tower
{
public:
    ShortRangeTower();
    ~ShortRangeTower();

    void Init();
    void Release();
    Tower* CreateShortRangeTower(sf::Vector2f position);

private:
    sf::Texture* m_shortRangeTowerTexture;
};
