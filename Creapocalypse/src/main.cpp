#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main()
{
	GameManager gameManager = GameManager();
	gameManager.Init();
	gameManager.Run();
	gameManager.Release();

}