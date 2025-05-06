#include "Entity.h"

Entity::Entity() :
	m_sprite(*(new sf::Texture()))
{
}

Entity::~Entity()
{
}

void Entity::Init(sf::Texture* texture, sf::Vector2f position)
{
	m_sprite.setTexture(*texture, true);
	SetPosition(position);
}

void Entity::Release()
{
}

//void Entity::Move()
//{
//}
//
//void Entity::Shoot()
//{
//}