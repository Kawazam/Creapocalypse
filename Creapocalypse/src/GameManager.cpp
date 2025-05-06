#include <SFML/Graphics.hpp>
#include <cmath>
#include "GameManager.h"
#include "Map.h"
#include "AlienFactory.h"

GameManager::GameManager()
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

}