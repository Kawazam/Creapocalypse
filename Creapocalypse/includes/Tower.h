#pragma once
#include "Entity.h"

class Tower :
    public Entity
{
public:
    Tower();
    ~Tower();

    void Init(sf::Texture* texture, sf::Vector2f position)override;
    void Release()override;
    void Move(float deltaTime)override;
    void Shoot()override;
};

