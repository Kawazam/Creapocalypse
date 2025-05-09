#include <iostream>
#include "Tower.h"
#include "GameManager.h"
#include "ShotSystem.h"
#include "Maths.h"
#include "Alien.h"

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
	m_currentShootCooldown -= deltaTime;

	GameManager& gameManager = GameManager::GetInstance();
	std::list<Alien*> alienList = gameManager.GetAliensList();

	Alien* closestAlienInRange = nullptr;
	float closestSquaredDistance = m_range * m_range;

	//Find the closest alien in range
	for (Alien* alien : alienList)
	{
		const sf::Vector2f alienPosition = alien->GetPosition();
		const sf::Vector2f towerPosition = GetPosition();
		float squaredDistance = (alienPosition.x - towerPosition.x) * (alienPosition.x - towerPosition.x) + (alienPosition.y - towerPosition.y) * (alienPosition.y - towerPosition.y);

		if (squaredDistance < closestSquaredDistance)
		{
			closestSquaredDistance = squaredDistance;
			closestAlienInRange = alien;
		}
	}

	if (closestAlienInRange == nullptr)
	{
    	return; //No aliens in range
	}
	//Shoot the closest alien only if the cooldown allows it
	if (m_currentShootCooldown <= 0)
	{
		sf::Vector2f shootDirection = Maths::Normalize(closestAlienInRange->GetPosition() - GetPosition());
		ShotSystem* shotSystem = gameManager.GetShotSystem();
		shotSystem->CreateShot(GetPosition(), shootDirection);
		m_currentShootCooldown = m_shootCooldownDuration;
	}
}
