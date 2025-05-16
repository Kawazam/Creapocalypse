#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "GameManager.h"

int main()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	GameManager gameManager = GameManager::GetInstance();
	gameManager.Run();
	gameManager.Release();

}
