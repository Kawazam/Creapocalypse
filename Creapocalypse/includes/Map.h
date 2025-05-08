#pragma once
#include <vector>

namespace sf
{
	class RenderWindow;
	class Texture;
	class Sprite;
}

class Map
{
public:
	Map();
	~Map();

	void Init();
	void Release();
	void Draw(sf::RenderWindow* window);

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	float m_width = 200;
	float m_height = 200;

	sf::Texture* m_texture;
	std::vector<sf::Sprite*> m_tiles;
};

