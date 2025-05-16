#include "Alien.h"
#include "Maths.h"
#include "GameManager.h"
#include "ShotSystem.h"

Alien::Alien()
{
}

Alien::~Alien()
{
}

void Alien::Init(sf::Texture* texture, sf::Vector2f position)
{
	Entity::Init(texture, position);
}

void Alien::Release()
{
}

void Alien::Move(float deltaTime)
{
	sf::Vector2f direction = Maths::Normalize(m_destination - GetPosition());
	m_sprite.move(direction * m_speed * deltaTime);
}

void Alien::Shoot(float deltaTime)
{
	m_currentShootCooldown -= deltaTime;
	if (m_currentShootCooldown <= 0)
	{
		sf::Vector2f position = GetPosition();
		float squaredDistance = (m_destination.x - position.x) * (m_destination.x - position.x) + (m_destination.y - position.y) * (m_destination.y - position.y);
		if (squaredDistance <= m_range * m_range)
		{
			sf::Vector2f shootDirection = Maths::Normalize(m_destination - GetPosition());
			ShotSystem* shotSystem = GameManager::GetInstance().GetShotSystem();
			shotSystem->CreateShot(GetPosition(), shootDirection);
			m_currentShootCooldown = m_shootCooldownDuration;
		}
	}
}
