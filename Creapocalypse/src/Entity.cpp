#include "Entity.h"
#include "Globals.h"

Entity::Entity() :
	m_sprite(*GetNullTexture())
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