#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "GameManager.h"
#include "Maths.h"
#include "Map.h"
#include "AlienFactory.h"
#include "ShotSystem.h"
#include "Farmer.h"
//ADDING-------------------------------
#include "ShortRangeTower.h"
#include "LongRangeTower.h"
#include "MissileTower.h"
#include "WallTower.h"
//-------------------------------------

namespace
{
    GameManager* s_instance = nullptr;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

GameManager& GameManager::GetInstance()
{
    if (!s_instance) [[unlikely]]
    {
        s_instance = new GameManager();
        s_instance->Init();
        return *s_instance;
    }
    return *s_instance;

}

void GameManager::Init()
{
    m_window = new sf::RenderWindow(sf::VideoMode({ 800, 800 }), "SFML works!");
    m_map = new Map();
    m_map->Init();
    //An ancien version of the creation of the map
    //sf::View view = sf::View({ 0, 0 },{ 200.0f * 32, 200.0f * 32 });
    ////view.setSize({ 200.0f * 32,200.0f * 32 });
    //m_window->setView(view);
    m_alienFactory = new AlienFactory();
    m_alienFactory->Init();
    m_shotSystem = new ShotSystem();
    m_shotSystem->Init();
    m_farmer = new Farmer();
    //m_farmer->Init();
    //ADDING-------------------------------------------------------------------
    m_shortRangeTower = new ShortRangeTower();
    m_longRangeTower = new LongRangeTower();
    m_missileTower = new MissileTower();
    m_wallTower = new WallTower();
    m_shortRangeTower->Init();
    m_longRangeTower->Init();
    m_missileTower->Init();
    m_wallTower->Init();
    //-------------------------------------------------------------------------
    m_window->setKeyRepeatEnabled(false); //a function to disable a feature from Windows
}

void GameManager::Run()
{
    if (m_window == nullptr) return;

    m_clock.reset();
    while (m_window->isOpen())
    {
        Update();
    }
}

void GameManager::Update()
{
    sf::Time elapsedTime = m_clock.restart();
    float elapsedSeconds = elapsedTime.asSeconds();

    HandleInputs();

    if (m_cameraDirection.x != 0.0f || m_cameraDirection.y != 0.0f)
    {
        MoveCamera(m_cameraDirection * m_cameraSpeed, elapsedSeconds);
    }

    for (Alien* alien : m_alienList)
    {
        alien->Move(elapsedSeconds);
        alien->Shoot(elapsedSeconds);
    }
    for (Tower* tower : m_towerList)
    {
        tower->Shoot(elapsedSeconds);
    }

    m_shotSystem->Update(elapsedSeconds);

    m_window->clear();
    m_map->Draw(m_window);
    //Draw every alien from m_alienList
    for (Alien* alien : m_alienList)
    {
        m_window->draw(*alien->GetDrawable());
    }
    //Draw every tower from m_towerList
    for (Tower* tower : m_towerList)
    {
        m_window->draw(*tower->GetDrawable());
    }
    m_shotSystem->Draw(m_window);
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
            case sf::Keyboard::Key::Escape :       //Close the game
                m_window->close();
                break;
            case sf::Keyboard::Key::Z:             //Move Up
                m_cameraMoveInputAxes.y -= 1.0f;
                break;
            case sf::Keyboard::Key::Q:             //Move Left
                m_cameraMoveInputAxes.x -= 1.0f;
                break;
            case sf::Keyboard::Key::S:             //Move Down
                m_cameraMoveInputAxes.y += 1.0f;
                break;
            case sf::Keyboard::Key::D:             //Move Right
                m_cameraMoveInputAxes.x += 1.0f;
                break;
            case sf::Keyboard::Key::Space:         //Run an alien wave
                SpawnAlienWave();
                break;
            case sf::Keyboard::Key::Num1:          //Select Short Range Tower
                m_towerType = 1;
                std::cout << "Short range tower selected" << std::endl;
                break;
            case sf::Keyboard::Key::Num2:          //Select Long Range Tower
                m_towerType = 2;
                std::cout << "Long range tower selected" << std::endl;
                break;
            case sf::Keyboard::Key::Num3:          //Select Missile Tower
                m_towerType = 3;
                std::cout << "Missile tower selected" << std::endl;
                break;
            case sf::Keyboard::Key::Num4:          //Select Wall Tower
                m_towerType = 4;
                std::cout << "Wall range tower selected" << std::endl;
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
        else if (const auto* buttonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            const sf::Mouse::Button pressedButton = buttonPressed->button;
            const sf::Vector2i position = buttonPressed->position;

            switch (pressedButton)
            {
            case sf::Mouse::Button::Right:         //Spawn a tower
                SpawnTower(m_towerType, position);
                break;
            case sf::Mouse::Button::Left:
                m_farmer->SetDestination(position);
                //m_farmer->Move(deltaTime);
                //call Farmer::Move() and give it mouse position
                break;
            }
        }
    }
    if (hasCameraDirectionChanged)
    {
        m_cameraDirection = Maths::Normalize(m_cameraMoveInputAxes);
        //const float magnitude = std::sqrt(m_cameraMoveInputAxes.x * m_cameraMoveInputAxes.x + m_cameraMoveInputAxes.y * m_cameraMoveInputAxes.y);
        //if (magnitude != 0)
        //{
        //    m_cameraDirection = m_cameraMoveInputAxes / magnitude;
        //}
        //else
        //{
        //    m_cameraDirection = { 0.0f,0.0f };
        //}
    }
}

void GameManager::MoveCamera(sf::Vector2f offset, float deltaTime)
{
    //an ancien version fo the camera's mouvements
    //sf::View view = m_window->getView();
    //view.move(offset);
    //m_window->setView(view);
    sf::View view = m_window->getView();
    sf::Vector2f newCenter = view.getCenter() + (offset * deltaTime);
    sf::Vector2f viewSize = view.getSize()/* + sf::Vector2f({ 64.0f, 64.0f })*/;

    float mapWidth = static_cast<float>(m_map->GetWidth() * 32);
    float mapHeight = static_cast<float>(m_map->GetHeight() * 32);

    //prevent the camera to go out the map's limits
    newCenter.x = std::clamp(newCenter.x, viewSize.x / 2.0f, mapWidth - viewSize.x / 2.0f);
    newCenter.y = std::clamp(newCenter.y, viewSize.y / 2.0f, mapHeight - viewSize.y / 2.0f);

    view.setCenter(newCenter);
    m_window->setView(view);
}

void GameManager::SpawnAlienWave()
{
    float tileSize = 32.0f;
    float mapWidth = static_cast<float>(m_map->GetWidth()) * tileSize;
    float mapHeight = static_cast<float>(m_map->GetHeight()) * tileSize;
    sf::Vector2f spawnPosition;
    int side = rand() % 4; //0: up, 1: right, 2: down, 3: left

    switch (side)
    {
    case 0: //Up
        spawnPosition = { static_cast<float>(rand() % static_cast<int>(mapWidth)), -tileSize };
        break;
    case 1: //Right
        spawnPosition = { mapWidth + tileSize, static_cast<float>(rand() % static_cast<int>(mapHeight))};
        break;
    case 2: //Down
        spawnPosition = { static_cast<float>(rand() % static_cast<int>(mapWidth)), mapHeight + tileSize };
        break;
    case 3: //Left
        spawnPosition = { -tileSize, static_cast<float>(rand() % static_cast<int>(mapHeight))};
        break;
    }
    //spawnPosition = m_window->getView().getCenter();
    Alien* alien = m_alienFactory->CreateRandomAlien(spawnPosition);
    alien->SetDestination(/*m_window->getView().getCenter()*/{ mapWidth / 2, mapHeight / 2});
    m_alienList.push_back(alien);
}

void GameManager::SpawnTower(int towerType, sf::Vector2i position)
{
    sf::Vector2f worldPosition = m_window->mapPixelToCoords(position);
    //towerType = m_towerType;

    if (!m_shortRangeTower) return;

    switch (towerType)
    {
    case 1:
    default:
    {
        Tower* newTower = m_shortRangeTower->CreateShortRangeTower(worldPosition);
        m_towerList.push_back(newTower);
    }
        break;
    case 2:
    {
        Tower* newTower = m_longRangeTower->CreateLongRangeTower(worldPosition);
        m_towerList.push_back(newTower);
    }
        break;
    case 3:
    {
        Tower* newTower = m_missileTower->CreateMissileTower(worldPosition);
        m_towerList.push_back(newTower);
    }
        break;
    case 4:
    {
        Tower* newTower = m_wallTower->CreateWallTower(worldPosition);
        m_towerList.push_back(newTower);
    }
        break;
    }
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

    for (Tower* tower : m_towerList)
    {
        delete tower;
    }
    m_towerList.clear();
}

