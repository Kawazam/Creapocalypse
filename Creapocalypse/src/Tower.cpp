#include <iostream>
#include "Tower.h"

Tower::Tower()
{
}

Tower::~Tower()
{
}

void Tower::Init(sf::Texture* texture, sf::Vector2f position)
{
	Entity::Init(texture, position);
}

void Tower::Release()
{
}

void Tower::Move(float deltaTime)
{
	//Do nothing, if Move() is called write an error in the console
	std::cerr << "Error: Move() called on Tower, which should be stationary!" << std::endl;
}

void Tower::Shoot(float deltaTime)
{
}
