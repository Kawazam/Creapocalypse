#include "Map.h"
#include <SFML/Graphics.hpp>

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init()
{
    m_texture = new sf::Texture("./img/Grass.png", false, sf::IntRect({0,0}, {32, 32}));

    m_tiles.reserve(m_width * m_height);

    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            sf::Sprite* sprite = new sf::Sprite(*m_texture);
            sprite->setPosition({ i * 32.0f, j * 32.0f });
            m_tiles.push_back(sprite);
        }
    }
}

void Map::Release()
{
    for (int i = 0; i < m_tiles.size(); i++)
    {
        if (m_tiles[i] != nullptr)
        {
            delete m_tiles[i];
            m_tiles[i] = nullptr;
        }
    }
}

void Map::Draw(sf::RenderWindow* window)
{
    for (int i = 0; i < m_tiles.size(); i++)
    {
        window->draw(*m_tiles[i]); //TODO: optimise to draw only visible tiles
    }
}

