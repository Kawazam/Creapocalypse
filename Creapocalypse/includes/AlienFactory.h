#pragma once
#include <SFML/Graphics.hpp>

class Alien;

class AlienFactory
{
public:
	AlienFactory();
	~AlienFactory();

	void Init();
	void Release();
	Alien* CreateAlienTank(sf::Vector2f position);
	Alien* CreateAlienRunner(sf::Vector2f position);
	Alien* CreateRandomAlien(sf::Vector2f position);

private:
	sf::Texture* m_alienTankTexture;
	sf::Texture* m_alienRunnerTexture;
};

