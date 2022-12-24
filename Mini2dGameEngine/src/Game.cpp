#include "Game.h"


Game::Game(Global &globalPtr) : enttHandler(globalPtr)
{
	global = &globalPtr;
}

void Game::beforePlay()
{
	enttHandler.beforePlay();
}

void Game::beginPlay()
{
	enttHandler.beginPlay();
	running = true;
}

void Game::process()
{
	enttHandler.process();
}

void Game::draw()
{
	enttHandler.draw();
}

void Game::endGame()
{
	running = false;
	enttHandler.endGame();
}

