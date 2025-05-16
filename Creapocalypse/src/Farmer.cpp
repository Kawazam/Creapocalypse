#include <iostream>
#include "Farmer.h"
#include "Maths.h"

Farmer::Farmer()
{
}

Farmer::~Farmer()
{
}

void Farmer::Init(sf::Texture* texture, sf::Vector2f position)
{
	m_farmerUpTexture = new sf::Texture("./img/Farmer_Up.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
	m_farmerRightTexture = new sf::Texture("./img/Farmer_Right.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
	m_farmerDownTexture = new sf::Texture("./img/Farmer_Down.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
	m_farmerLeftTexture = new sf::Texture("./img/Farmer_Left.png", false, sf::IntRect({ 0,0 }, { 32,32 }));
}

void Farmer::Release()
{
}

void Farmer::Move(float deltaTime)
{
	//cause an issue because m_destination is a Vector2i (set from mouse's position) and GetPosition() is a Vector2f.
	//sf::Vector2f direction = Maths::Normalize(m_destination - GetPosition());
}

void Farmer::Shoot(float deltaTime)
{
	//Do nothing, if Shot() is called write an error in the console
	std::cerr << "Error: Shot() called on Farmer, which should be stationary!" << std::endl;
}
