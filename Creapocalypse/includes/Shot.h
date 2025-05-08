#pragma once
#include "Entity.h"

class Shot :
    public Entity
{
public:
    Shot();
    ~Shot();

    void Init(sf::Texture* texture, sf::Vector2f position, sf::Vector2f direction);
    void Move(float deltaTime) override;
    void Shoot() override{};

protected:
    sf::Vector2f m_direction;
    float m_speed = 50.0f;
};

