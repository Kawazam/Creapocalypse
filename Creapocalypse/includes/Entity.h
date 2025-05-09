#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Init(sf::Texture* texture, sf::Vector2f position);
	virtual void Release();
	virtual void Move(float deltaTime) = 0;
	virtual void Shoot(float deltaTime) = 0;

	inline sf::Vector2f GetPosition() { return m_sprite.getPosition(); };
	inline sf::Drawable* GetDrawable() { return &m_sprite; };
	inline void SetPosition(sf::Vector2f position) { m_sprite.setPosition(position); };
	inline void SetHealth(int health) { m_health = health; };
	inline void SetSpeed(float speed) { m_speed = speed; };
	inline void SetCoolDownDuration(float coolDownDuration) { m_shootCooldownDuration = coolDownDuration; };

protected:
	int m_health = 10;
	sf::Sprite m_sprite;
	float m_speed = 40.0f;
	float m_currentShootCooldown = 0.0f;
	float m_shootCooldownDuration = 1.0f;
	float m_range = 1000.0f;
};

