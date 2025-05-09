#pragma once
#include <list>
#include "Shot.h"

class ShotSystem
{
public:
	ShotSystem();
	~ShotSystem();
	void Init();
	void Release();
	void Update(float deltaTime);
	void CreateShot(sf::Vector2f spawnPosition, sf::Vector2f moveDirection);
	void Draw(sf::RenderWindow* window);

protected:
	sf::Texture* m_shotTexture;
	std::list<Shot> m_shotList;
};

