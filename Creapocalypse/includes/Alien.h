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
	void Move()override;
	void Shoot()override;
};
