#pragma once

#include "EnttHandler.h"
#include "ComponentHandler.h"
#include "Global.h"

class Game
{
public:
	Game(Global& globalPtr);
	void beginPlay();
	void process();
	void endGame();


	void addEntt();

	

private:
	Global *global;

	EnttHandler enttHandler;

};

