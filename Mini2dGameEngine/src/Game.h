#pragma once

#include "EnttHandler.h"
#include "ComponentHandler.h"
#include "Global.h"

class Game
{
public:
	Game(Global& globalPtr);
	void beforePlay();
	void beginPlay();
	void process();
	void draw();
	void endGame();


	bool running = true;

	EnttHandler enttHandler;

private:
	Global *global;

};

