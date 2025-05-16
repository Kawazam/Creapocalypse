#pragma once
#include "Tower.h"

class MissileTower :
    public Tower
{
public:
    MissileTower();
    ~MissileTower();

    void Init();
    void Release();
    Tower* CreateMissileTower(sf::Vector2f position);

private:
    sf::Texture* m_missileTowerTexture;
};

