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
}

void Tower::Shoot()
{
}
