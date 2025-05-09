#pragma once
#include "Tower.h"

class ExampleTower : public Tower
{
	public:
	ExampleTower();
	~ExampleTower();

	void Init(sf::Texture* texture, sf::Vector2f position) override;
	void Release() override;

	void Move() override {};
	void Shoot() override;
};