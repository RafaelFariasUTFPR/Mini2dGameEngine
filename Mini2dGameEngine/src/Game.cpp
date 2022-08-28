#include "Game.h"


Game::Game(Global &globalPtr) : enttHandler(globalPtr)
{
	global = &globalPtr;
}

void Game::beginPlay()
{
	enttHandler.beginPlay();
}