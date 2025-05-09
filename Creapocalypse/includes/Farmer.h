#pragma once
#include "Entity.h"
class Farmer :
    public Entity
{
public:
    Farmer();
    ~Farmer();

    void Init(sf::Texture* texture, sf::Vector2f position)override;
    void Release()override;
    void Move(float deltaTime)override;
    void Shoot(float deltaTime)override;
private:
    sf::Texture* m_farmerUpTexture;
    sf::Texture* m_farmerRightTexture;
    sf::Texture* m_farmerDownTexture;
    sf::Texture* m_farmerLeftTexture;
};
