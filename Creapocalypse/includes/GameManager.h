#pragma once
#include <list>
#include "Alien.h"
#include "TowerFactory.h"

namespace sf { 
	class RenderWindow;
}

class Map;
class AlienFactory;

class GameManager {
public:

	GameManager();
	~GameManager();
	
	void Init();
	void Run();
	void Release();

protected:
	void Update();
	void HandleInputs();
	void MoveCamera(sf::Vector2f);
	void SpawnAlienWave();

	sf::RenderWindow* m_window;
	Map* m_map;
	AlienFactory* m_alienFactory;

	float m_cameraSpeed = 10.0f;
	sf::Vector2f m_cameraMoveInputAxes;
	sf::Vector2f m_cameraDirection;
	std::list<Alien*> m_alienList;

	TowerTypes m_selectedTowerType = TowerTypes::EXAMPLE1;
	TowerFactory* m_towerFactory;
	std::vector<Tower*> m_towerList;
};