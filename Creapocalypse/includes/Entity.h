#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Init(sf::Texture* texture, sf::Vector2f position);
	virtual void Release();
	virtual void Move() = 0;
	virtual void Shoot() = 0;

	inline void SetPosition(sf::Vector2f position) { m_sprite.setPosition(position); };
	inline sf::Vector2f GetPosition() { return m_sprite.getPosition(); };
	inline sf::Drawable* GetDrawable() { return &m_sprite; };
	inline void SetHealth(int health) { m_health = health; };
	inline void SetSpeed(float speed) { m_speed = speed; };

protected:
	int m_health;
	sf::Sprite m_sprite;
	float m_speed;
};

