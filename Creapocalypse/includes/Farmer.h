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
    inline void SetDestination(sf::Vector2i destination) { m_destination = destination; };
private:
    sf::Vector2i m_destination; //m_destination needs to be a Vector2i cause it's set by mouse's position (which is a Vector2i)  
    sf::Texture* m_farmerUpTexture;
    sf::Texture* m_farmerRightTexture;
    sf::Texture* m_farmerDownTexture;
    sf::Texture* m_farmerLeftTexture;
};
