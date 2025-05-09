#include "TowerFactory.h"

TowerFactory::TowerFactory() : 
	m_example1TowerTexture(nullptr)
	//, m_example2TowerTexture(nullptr)
{
}

TowerFactory::~TowerFactory()
{
}

void TowerFactory::Init()
{
	m_example1TowerTexture = new sf::Texture("./img/Example1TowerTexture.png", false, sf::IntRect({ 0,0 }, { 32, 32 }));
	//m_example2TowerTexture = new sf::Texture("./img/Example2TowerTexture.png", false, sf::IntRect({ 0,0 }, { 32, 32 }));
}

void TowerFactory::Release()
{
	if (m_example1TowerTexture != nullptr)
	{
		delete m_example1TowerTexture;
		m_example1TowerTexture = nullptr;
	}

	//if (m_example2TowerTexture != nullptr)
	//{
	//	delete m_example2TowerTexture;
	//	m_example2TowerTexture = nullptr;
	//}
}

Tower* TowerFactory::CreateTower(TowerType type, sf::Vector2f position)
{
	switch (type)
	{
	case EXAMPLE1:
		return CreateExample1Tower(m_example1TowerTexture, position);
	//case EXAMPLE2:
		//return CreateExample2Tower(m_example2TowerTexture, position);
	}
}

ExampleTower* TowerFactory::CreateExample1Tower(sf::Texture* texture, sf::Vector2f position)
{
	ExampleTower* tower = new ExampleTower();
	tower->Init(m_example1TowerTexture, position);
	tower->SetHealth(30);
	/* Add other settings if necessary or pass them in a custom Init(). */
	return tower;
}

//Example2Tower* TowerFactory::CreateExample2Tower(sf::Texture* texture, sf::Vector2f position)
//{
//	Example2Tower* tower = new Example2Tower();
//	tower->Init(m_example2TowerTexture, position);
//	tower->SetHealth(30);
//	return tower;
//}

