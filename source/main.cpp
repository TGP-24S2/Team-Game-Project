// COMP710 GP Framework 2022
// Library includes:
#include <SDL.h>
#include <crtdbg.h>
// Local includes:
#include "game.h"
#include "logmanager.h"
#include "iniparser.h"
int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game& gameInstance = Game::GetInstance();
	if (!gameInstance.Initialise())
	{
		LogManager::GetInstance().Log("Game initialise failed!");
		return 1;
	}
	while (gameInstance.DoGameLoop())
	{
		// No body.
	}
	Game::DestroyInstance();
	LogManager::DestroyInstance();
	IniParser::DestroyInstance();
	return 0;
}