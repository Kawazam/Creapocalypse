#include <cstdlib>
#include "AlienFactory.h"
#include "Alien.h"

AlienFactory::AlienFactory() :
	m_alienTankTexture(nullptr),
	m_alienRunnerTexture(nullptr)
{
}

AlienFactory::~AlienFactory()
{
}

void AlienFactory::Init()
{
	m_alienTankTexture = new sf::Texture("./img/Alien_Tank.png", false, sf::IntRect({ 0,0 }, { 32, 32 }));
	m_alienRunnerTexture = new sf::Texture("./img/Alien_Runner.png", false, sf::IntRect({ 0,0 }, { 32, 32 }));
}

void AlienFactory::Release()
{
	if (m_alienTankTexture != nullptr)
	{
		delete m_alienTankTexture;
		m_alienTankTexture = nullptr;
	}	
	
	if (m_alienRunnerTexture != nullptr)
	{
		delete m_alienRunnerTexture;
		m_alienRunnerTexture = nullptr;
	}
}

Alien* AlienFactory::CreateAlienTank(sf::Vector2f position)
{
	Alien* alien = new Alien();
	alien->Init(m_alienTankTexture, position);
	alien->SetHealth(30);
	alien->SetSpeed(40.0f);
	alien->SetCoolDownDuration(2.0f);
	return alien;
}

Alien*  AlienFactory::CreateAlienRunner(sf::Vector2f position)
{
	Alien* alien = new Alien();
	alien->Init(m_alienRunnerTexture, position);
	alien->SetHealth(5);
	alien->SetSpeed(80.0f);
	alien->SetCoolDownDuration(2.0f);
	return alien;
}

Alien* AlienFactory::CreateRandomAlien(sf::Vector2f position)
{
	int maxValue = 2; //number of different alien type
	int randomAlienType = std::rand() % maxValue;
	Alien* alien = nullptr;
	switch (randomAlienType)
	{
	case 0:
		alien = CreateAlienTank(position);
		break;
	case 1:
	default: //secure the potential issue with the randomAlienType
		alien = CreateAlienRunner(position);
		break;
	}
	return alien;
}
