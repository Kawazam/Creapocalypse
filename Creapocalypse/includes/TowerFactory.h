#pragma once
#include "Tower.h"
#include "ExampleTower.h"

typedef enum TowerTypes
{
	EXAMPLE1,
	EXAMPLE2,
	// Add more tower types here
} TowerType;

class TowerFactory
{
public:
	TowerFactory();
	~TowerFactory();

	void Init();
	void Release();

	Tower* CreateTower(TowerType type, sf::Vector2f position);
	ExampleTower* CreateExample1Tower(sf::Texture* texture, sf::Vector2f position);
	//ExampleTower* CreateExample2Tower(sf::Texture* texture, sf::Vector2f position);

protected:
	sf::Texture* m_example1TowerTexture;
	//sf::Texture* m_example2TowerTexture;
};