#include <SFML/Graphics.hpp>
#include <cmath>
#include "GameManager.h"
#include "Map.h"
#include "AlienFactory.h"

GameManager::GameManager() : 
    m_window(nullptr),
	m_map(nullptr),
	m_alienFactory(nullptr),
	m_towerFactory(nullptr),
	m_cameraSpeed(10.0f),
	m_cameraMoveInputAxes(0.0f, 0.0f),
	m_cameraDirection(0.0f, 0.0f)
{
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
    m_window = new sf::RenderWindow(sf::VideoMode({ 800, 800 }), "SFML works!");
    m_map = new Map();
    m_map->Init();
    m_alienFactory = new AlienFactory();
    m_alienFactory->Init();
    
    m_towerFactory = new TowerFactory();
    m_towerFactory->Init();

    m_window->setKeyRepeatEnabled(false);
}

void GameManager::Run()
{
    if (m_window == nullptr) return;

    while (m_window->isOpen())
    {
        Update();
    }
}

void GameManager::Update()
{
    HandleInputs();

    if (m_cameraDirection.x != 0.0f || m_cameraDirection.y != 0.0f)
    {
        MoveCamera(m_cameraDirection * m_cameraSpeed);
    }

    m_window->clear();
    m_map->Draw(m_window);
    for (Alien* alien : m_alienList)
    {
        m_window->draw(*alien->GetDrawable());
    }
    m_window->display();
}

void GameManager::HandleInputs()
{
    sf::Vector2f cameraMoveDirection = {0.0f, 0.0f};
    bool hasCameraDirectionChanged = false;

    while (const std::optional event = m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window->close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            const sf::Keyboard::Key pressedKeyCode = keyPressed->code;

            switch (pressedKeyCode)
            {
            case sf::Keyboard::Key::Escape :
                m_window->close();
                break;
            case sf::Keyboard::Key::Z:
                m_cameraMoveInputAxes.y -= 1.0f;
                break;
            case sf::Keyboard::Key::Q:
                m_cameraMoveInputAxes.x -= 1.0f;
                break;
            case sf::Keyboard::Key::S:
                m_cameraMoveInputAxes.y += 1.0f;
                break;
            case sf::Keyboard::Key::D:
                m_cameraMoveInputAxes.x += 1.0f;
                break;
            case sf::Keyboard::Key::Space:
                SpawnAlienWave();
            case sf::Keyboard::Key::Num1:
                m_selectedTowerType = TowerTypes::EXAMPLE1;
				break;
            case sf::Keyboard::Key::Num2:
				m_selectedTowerType = TowerTypes::EXAMPLE2;
				break;
            }

            if (pressedKeyCode == sf::Keyboard::Key::Z ||
                pressedKeyCode == sf::Keyboard::Key::Q ||
                pressedKeyCode == sf::Keyboard::Key::S ||
                pressedKeyCode == sf::Keyboard::Key::D)
            {
                hasCameraDirectionChanged = true;
            }
        }
        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            const sf::Keyboard::Key releasedKeyCode = keyReleased->code;

            switch (releasedKeyCode)
            {
            case sf::Keyboard::Key::Z:
                m_cameraMoveInputAxes.y += 1.0f;
                break;
            case sf::Keyboard::Key::Q:
                m_cameraMoveInputAxes.x += 1.0f;
                break;
            case sf::Keyboard::Key::S:
                m_cameraMoveInputAxes.y -= 1.0f;
                break;
            case sf::Keyboard::Key::D:
                m_cameraMoveInputAxes.x -= 1.0f;
                break;
            }
            if (releasedKeyCode == sf::Keyboard::Key::Z ||
                releasedKeyCode == sf::Keyboard::Key::Q ||
                releasedKeyCode == sf::Keyboard::Key::S ||
                releasedKeyCode == sf::Keyboard::Key::D)
            {
                hasCameraDirectionChanged = true;
            }
        }
        // detect mouse click now
        else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouseButtonPressed->button == sf::Mouse::Button::Left)
			{
                sf::Vector2f spawnPosition = m_window->mapPixelToCoords(mouseButtonPressed->position);
				m_towerList.push_back(m_towerFactory->CreateTower(m_selectedTowerType, spawnPosition));
			}
		}
    }
    if (hasCameraDirectionChanged)
    {
        const float magnitude = std::sqrt(m_cameraMoveInputAxes.x * m_cameraMoveInputAxes.x + m_cameraMoveInputAxes.y * m_cameraMoveInputAxes.y);
        if (magnitude != 0)
        {
            m_cameraDirection = m_cameraMoveInputAxes / magnitude;
        }
        else
        {
            m_cameraDirection = { 0.0f,0.0f };
        }
    }
}

void GameManager::MoveCamera(sf::Vector2f offset)
{
    sf::View view = m_window->getView();
    view.move(offset);
    m_window->setView(view);
}

void GameManager::SpawnAlienWave()
{
    sf::Vector2f spawnPosition = m_window->getView().getCenter();
    Alien* alien = m_alienFactory->CreateRandomAlien(spawnPosition);
    m_alienList.push_back(alien);
}

void GameManager::Release()
{
    if (m_window != nullptr)
    {
        delete m_window;
        m_window = nullptr;
    }
    
    if (m_map != nullptr)
    {
        m_map->Release();
        delete m_map;
        m_map = nullptr;
    }

    if (m_alienFactory != nullptr)
	{
		m_alienFactory->Release();
		delete m_alienFactory;
		m_alienFactory = nullptr;
	}

    if (m_towerFactory != nullptr)
	{
		m_towerFactory->Release();
		delete m_towerFactory;
		m_towerFactory = nullptr;
	}

	for (Tower* tower : m_towerList)
	{
        if (tower != nullptr)
		{
			tower->Release();
            delete tower;
		}
	}
	m_towerList.clear();

	for (Alien* alien : m_alienList)
	{
        if (alien != nullptr)
		{
			alien->Release();
			delete alien;
		}
	}
	m_alienList.clear();

}