#pragma once
#include "Entity.h"

class Tower : public Entity
{
public:
	Tower();
	~Tower();

	void Init(sf::Texture* texture, sf::Vector2f position);
	void Release();

	void Move() override {};
	void Shoot() override;
};