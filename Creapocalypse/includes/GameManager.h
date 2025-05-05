#pragma once

namespace sf { 
	class RenderWindow;
}

class Map;

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

	sf::RenderWindow* m_window;
	Map* m_map;

	float m_cameraSpeed = 10.0f;


};