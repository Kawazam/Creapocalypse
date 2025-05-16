#include "Shot.h"
#include "Maths.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::Init(sf::Texture* texture, sf::Vector2f position, sf::Vector2f direction)
{
	Entity::Init(texture, position);
	m_direction = Maths::Normalize(direction);

}

void Shot::Move(float deltaTime)
{
	m_sprite.move(m_direction * m_speed * deltaTime);
}
