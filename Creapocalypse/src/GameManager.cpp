#include <SFML/Graphics.hpp>
#include <cmath>
#include "GameManager.h"
#include "Map.h"

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

    m_window->clear();
    m_map->Draw(m_window);
    m_window->display();
}

void GameManager::HandleInputs()
{
    sf::Vector2f cameraMoveDirection = {0.0f, 0.0f};

    while (const std::optional event = m_window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window->close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
                m_window->close();
            else if (keyPressed->code == sf::Keyboard::Key::Z)
                cameraMoveDirection.y -= 1.0f;            
            else if (keyPressed->code == sf::Keyboard::Key::Q)
                cameraMoveDirection.x -= 1.0f;            
            else if (keyPressed->code == sf::Keyboard::Key::S)
                cameraMoveDirection.y += 1.0f;
            else if (keyPressed->code == sf::Keyboard::Key::D)
                cameraMoveDirection.x += 1.0f;
        }
    }
    const float magnitude = std::sqrt(cameraMoveDirection.x * cameraMoveDirection.x + cameraMoveDirection.y * cameraMoveDirection.y);
    if (magnitude != 0)
    {
        MoveCamera((cameraMoveDirection / magnitude) * m_cameraSpeed);
    }
}

void GameManager::MoveCamera(sf::Vector2f offset)
{
    sf::View view = m_window->getView();
    view.move(offset);
    m_window->setView(view);
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