#include "Tower.h"
#include "GameManager.h"
#include "ShotSystem.h"
#include "Maths.h"
#incldue "Alien.h"

Tower::Tower()
{
}

Tower::~Tower()
{
}

void Tower::Init(sf::Texture* texture, sf::Vector2f position)
{
}

void Tower::Release()
{
}

void Tower::Shoot()
{
	/* Add cooldown logic here */

	GameManager gameManager = GameManager::GetInstance();
	std::list<Alien*> alienList = gameManager.GetAliensList();

	Alien* closestAlienInRange = nullptr;
	float closestSquaredDistance = m_range * m_range; // closest Alien in range can only be set if aliens are within range

	// Find the closest alien within range
	for (Alien* alien : alienList) {
		const sf::Vector2f alienPosition = alien->GetPosition();
		const sf::Vector2f towerPosition = GetPosition();
		float squaredDistance = (alienPosition.x - towerPosition.x) * (alienPosition.x - towerPosition.x) +
			(alienPosition.y - towerPosition.y) * (alienPosition.y - towerPosition.y);

		if (squaredDistance < closestSquaredDistance) {
			closestSquaredDistance = squaredDistance;
			closestAlienInRange = alien;
		}
	}

	if (closestAlienInRange == nullptr) {
		return; // No aliens in range
	}

	sf::Vector2f direction = Maths::Normalize(alien->GetPosition() - GetPosition());
	ShotSystem* shotSystem = gameManager.GetShotSystem();
	shotSystem->CreateShot(GetPosition(), direction);
}