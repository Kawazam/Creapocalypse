#pragma once
#include "Tower.h"
class WallTower :
    public Tower
{
public:
    WallTower();
    ~WallTower();

    void Init();
    void Release();
    Tower* CreateWallTower(sf::Vector2f position);

private:
    sf::Texture* m_wallTowerTexture;
};

