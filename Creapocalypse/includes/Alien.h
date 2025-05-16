#pragma once
#include "Entity.h"

class Alien :
    public Entity
{
public:
	Alien();
	~Alien();

	void Init(sf::Texture* texture, sf::Vector2f position)override;
	void Release()override;
	void Move(float deltaTime)override;
	void Shoot(float deltaTime)override;
	inline void SetDestination(sf::Vector2f destination) { m_destination = destination; };
private:
	sf::Vector2f m_destination;

};
