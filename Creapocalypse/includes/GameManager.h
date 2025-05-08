#pragma once
#include <list>
#include <SFML/Window/Mouse.hpp>
#include "Alien.h"
#include "Tower.h"

namespace sf { 
	class RenderWindow;
}

//Forward Declaration
class Map;
class AlienFactory;
class ShotSystem;
//ADDING-------------------------------
class ShortRangeTower;
class LongRangeTower;
class MissileTower;
class WallTower;
//-------------------------------------

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
	void MoveCamera(sf::Vector2f, float);
	void SpawnAlienWave();
	//ADDING---------------------------
	void SpawnTower(int towerType, sf::Vector2i position);
	//---------------------------------

	sf::RenderWindow* m_window;
	Map* m_map;
	AlienFactory* m_alienFactory;
	ShotSystem* m_shotSystem;
	//ADDING---------------------------
	ShortRangeTower* m_shortRangeTower;
	LongRangeTower* m_longRangeTower;
	MissileTower* m_missileTower;
	WallTower* m_wallTower;
	//---------------------------------

	float m_cameraSpeed = 50.0f;
	sf::Vector2f m_cameraMoveInputAxes;
	sf::Vector2f m_cameraDirection;
	std::list<Alien*> m_alienList;
	//ADDING---------------------------
	int m_towerType = 0;
	std::vector<Tower*> m_towerList;
	//---------------------------------
	sf::Clock m_clock;

};