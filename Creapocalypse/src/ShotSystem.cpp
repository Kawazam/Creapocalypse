#include "ShotSystem.h"

ShotSystem::ShotSystem()
{
}

ShotSystem::~ShotSystem()
{
}

void ShotSystem::Init()
{
	m_shotTexture = new sf::Texture("./img/Shot.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
}

void ShotSystem::Release()
{
}

void ShotSystem::Update(float deltaTime)
{
	for (Shot shot : m_shotList)
	{
		shot.Move(deltaTime);
	}
}

void ShotSystem::CreateShot(sf::Vector2f spawnPosition, sf::Vector2f moveDirection)
{
	Shot& spawnedShot = m_shotList.emplace_back();
	spawnedShot.Init(m_shotTexture, spawnPosition, moveDirection);
}
